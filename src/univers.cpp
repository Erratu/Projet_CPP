#include "univers.hpp"
#include <iostream>
#include <fstream>

template <int D>
void Univers<D>::majCells() {
    for (auto& cell : cellules) {
        cell.particules.clear();
    }

    for (auto& p : particules) {
        std::array<int, D> p_coords;
        // getPosition
        for (int i = 0; i < D; ++i) {
            int coord_cell = static_cast<int>(p.pos[i] / rayon_coupe);
            if (coord_cell >= n_cells[i]) coord_cell = n_cells[i] - 1;
            if (coord_cell < 0) coord_cell = 0;
            p_coords[i] = coord_cell;
        }
        
        int cell_index = getIndexCell(p_coords);
        cellules[cell_index].particules.push_back(&p);
    }
}

template <int D>
void Univers<D>::calculerForces(double epsilon, double sigma) {
    for (auto &p : particules) {
        for (int i = 0; i < D; ++i) {
            p.f[i] = 0.0;
        }
    }

    double r_cut_carre = rayon_coupe * rayon_coupe;

    for (size_t i = 0; i < cellules.size(); ++i) {
        Cellule& cell = cellules[i];

        for (Particule<D>* p : cell.particules) {
            for (int voisin : cell.voisines) {
                Cellule& voisin_cell = cellules[voisin];
                for (Particule<D>* q : voisin_cell.particules) {
                    if (p < q) {
                        Vecteur<D> dist = q->pos - p->pos; // Vecteur rij

                        double r2 = 0.0; 
                        for (int k = 0; k < D; ++k) {
                            r2 += dist[k] * dist[k];
                        }

                        //double r = std::sqrt(r2);
                        //double f_mag = p->masse * q->masse / (r2 * r);
                        
                        if (r2 <= r_cut_carre && r2 > 0) {
                            double sr2 = (sigma * sigma) / r2;
                            double sr6 = sr2 * sr2 * sr2;
                            double f_mag = 24.0 * epsilon * (1.0 / r2) * sr6 * (1.0 - 2.0 * sr6);

                            Vecteur<D> fpos = dist * f_mag;
                            
                            for (int k = 0; k < D; ++k) {
                                p->f[k] += fpos[k];
                                q->f[k] -= fpos[k]; 
                            }
                        }
                    }
                }
            }
        }
    }
}   

template <int D>
void Univers<D>::algoStormerVerlet(double t_end, double dt, double epsilon, double sigma) {

    //std::ofstream file("positions_astres.txt");
    double t = 0.0;

    calculerForces(epsilon, sigma);

    std::vector<std::vector<double>> f_old(D);
    for(int i=0; i<D; ++i) f_old[i].reserve(particules.size());

    while (t < t_end) {
        t += dt;
        for(int i=0; i<D; ++i) f_old[i].clear();

        for (auto &p : particules) {
            for (int i = 0; i < D; ++i) {
                f_old[i].push_back(p.f[i]);
                p.pos[i] += dt * (p.v[i] + 0.5 / p.masse * p.f[i] * dt); // dans particule, pareil pour vitesse et force
            }
        }

        majCells();
        calculerForces(epsilon, sigma);

        int i = 0;
        for (auto &p : particules) {
            for (int j = 0; j < D; ++j) {
                p.v[j] += dt * 0.5 / p.masse * (p.f[j] + f_old[j][i]);
            }
            i++;
        }

        //for (auto &p : particules) {
        //    file << p.pos << " ";
        //}
        //file << "\n";
    }
    //file.close();
};

// template max 3, 3 boucles avec la troisième une seule fois, 2 ...
template<>
void Univers<2>::setupVoisins(int cell_index) {
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
void Univers<3>::setupVoisins(int cell_index) {
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

template class Univers<3>;
template class Univers<2>;