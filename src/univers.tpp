#include <random>
#include <cmath>

template<int D>
std::list<Particule<D>> Univers<D>::genererParticules(int nb_particules, Vecteur<D> l) {
    std::list<Particule<D>> ps;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (int i=0; i<nb_particules; ++i) {
        Vecteur<D> pos, vel;
        for (int j = 0; j < D; ++j) {
            pos[j] = dist(mt) * l[j];
            vel[j] = 0.0;
        }
        ps.emplace_back(Particule<D>{pos, vel, dist(mt), i, "Ab"});
    }
    return ps;
}

// Constructors

template<int D>
Univers<D>::Univers(int nb_particules, Vecteur<D> l, double r_coupe) 
    : Univers(genererParticules(nb_particules, l), l, r_coupe) {}

template<int D>
Univers<D>::Univers(std::list<Particule<D>> ps, Vecteur<D> l, double r_coupe) {
    particules = ps;

    for (int i = 0; i < D; ++i) {
        longueurs[i] = l[i];
    }

    rayon_coupe = r_coupe;

    int tot_n_cells = 1;
    for (int i = 0; i < D; ++i) {
        n_cells[i] = static_cast<int>(longueurs[i] / rayon_coupe);
        if (n_cells[i] < 1) n_cells[i] = 1;
        tot_n_cells *= n_cells[i];
    }
    cellules.resize(tot_n_cells);

    mult_dim[0] = 1;
    for (int i = 0; i < D - 1; ++i) {
        mult_dim[i+1] = mult_dim[i] * n_cells[i];
    }

    for (int i = 0; i < tot_n_cells; ++i) {
        cellules[i].coords = getCoordsCell(i); 
        setupVoisins(i); 
    }

    majCells();
}

template<int D>
Univers<D>::Univers(const Univers& autre) {
    for(const auto& p : autre.particules) {
        particules.emplace_back(p);
    }

    rayon_coupe = autre.rayon_coupe;
    for (int i = 0; i < D; ++i) {
        longueurs[i] = autre.longueurs[i];
        n_cells[i] = autre.n_cells[i];
    }
}

// Grid utility methods

template<int D>
int Univers<D>::getIndexCell(std::array<int, D> coords) const {
    int index = 0;
    for (int i = 0; i < D; ++i) {
        index += coords[i] * mult_dim[i];
    }
    return index;
}

template<int D>
std::array<int, D> Univers<D>::getCoordsCell(int index) const {
    std::array<int, D> coords;
    for (int i = D - 1; i >= 0; --i) {
        coords[i] = index / mult_dim[i];
        index %= mult_dim[i];
    }
    return coords;
}

template <int D>
void Univers<D>::majCells() {
    for (auto& cell : cellules) {
        cell.particules.clear();
    }

    for (auto& p : particules) {
        const auto& p_pos = p.getPos();
        std::array<int, D> p_coords;
        
        for (int i = 0; i < D; ++i) {
            int coord_cell = static_cast<int>(p_pos[i] / rayon_coupe);
            if (coord_cell >= n_cells[i]) coord_cell = n_cells[i] - 1;
            if (coord_cell < 0) coord_cell = 0;
            p_coords[i] = coord_cell;
        }
        
        int cell_index = getIndexCell(p_coords);
        cellules[cell_index].particules.push_back(&p);
    }
}

template<>
inline void Univers<2>::setupVoisins(int cell_index) {
    std::array<int, 2> coords = cellules[cell_index].coords;
    for (int dj = -1; dj <= 1; ++dj) {
        for (int di = -1; di <= 1; ++di) {
            int ni = coords[0] + di;
            int nj = coords[1] + dj;
            if (ni >= 0 && ni < n_cells[0] && nj >= 0 && nj < n_cells[1]) {
                cellules[cell_index].voisines.push_back(getIndexCell({ni, nj}));
            }
        }
    }
}

template<>
inline void Univers<3>::setupVoisins(int cell_index) {
    std::array<int, 3> coords = cellules[cell_index].coords;
    for (int dk = -1; dk <= 1; ++dk) {
        for (int dj = -1; dj <= 1; ++dj) {
            for (int di = -1; di <= 1; ++di) {
                int ni = coords[0] + di;
                int nj = coords[1] + dj;
                int nk = coords[2] + dk;
                if (ni >= 0 && ni < n_cells[0] && 
                    nj >= 0 && nj < n_cells[1] && 
                    nk >= 0 && nk < n_cells[2]) {
                    cellules[cell_index].voisines.push_back(getIndexCell({ni, nj, nk}));
                }
            }
        }
    }
}

template <int D>
void Univers<D>::calculerForces(double epsilon, double sigma) {
    for (auto &p : particules) {
        p.resetForce();
    }

    double r_cut_carre = rayon_coupe * rayon_coupe;

    for (size_t i = 0; i < cellules.size(); ++i) {
        Cellule& cell = cellules[i];

        for (Particule<D>* p : cell.particules) {
            for (int voisin : cell.voisines) {
                Cellule& voisin_cell = cellules[voisin];
                for (Particule<D>* q : voisin_cell.particules) {
                    if (p < q) {
                        Vecteur<D> dist = p->dist(*q); 

                        double r2 = 0.0; 
                        for (int k = 0; k < D; ++k) {
                            r2 += dist[k] * dist[k];
                        }
                        
                        if (r2 <= r_cut_carre && r2 > 0) {
                            double sr2 = (sigma * sigma) / r2;
                            double sr6 = sr2 * sr2 * sr2;
                            double f_mag = 24.0 * epsilon * (1.0 / r2) * sr6 * (1.0 - 2.0 * sr6);

                            Vecteur<D> fpos = dist * f_mag;
                            
                            p->addForce(fpos);
                            q->addForce(-fpos); 
                        }
                    }
                }
            }
        }
    }
}   

template <int D>
void Univers<D>::algoStormerVerlet(double t_end, double dt, double epsilon, double sigma) {
    double t = 0.0;
    //std::ofstream file("positions_astres.txt");

    calculerForces(epsilon, sigma);

    while (t < t_end) {
        t += dt;

        for (auto &p : particules) {
            p.updatePosition(dt);
        }

        majCells();
        calculerForces(epsilon, sigma);

        for (auto &p : particules) {
            p.updateV(dt);
        }
        //for (auto &p : particules) {
        //    file << p << " ";
        //}
        //file << "\n";
    }
    //file.close();
};