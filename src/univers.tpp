#include <random>
#include <cmath>

#include <fstream>
#include <iomanip>
#include <sstream>

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
    particules.reserve(ps.size());
    for (const auto& p : ps) {
        particules.push_back(p);
    }

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
    particules.reserve(autre.particules.size());
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
void Univers<D>::calculerForces(double epsilon, double sigma, double G) {
    for (auto &p : particules) {
        p.resetForce();
        
        // La gravité s'applique sur la composante verticale (index 1)
        if (G != 0.0 && D >= 2) {
            Vecteur<D> f_grav; 
            f_grav[1] = p.masse * G; 
            p.addForce(f_grav);
        }
    }

    if (condition_limite == ConditionLimite::REFLEXION_POTENTIEL) {
        double r_cut_mur = std::pow(2.0, 1.0 / 6.0) * sigma; //

        for (auto &p : particules) {
            Vecteur<D> f_murs;
            
            for (int d = 0; d < D; ++d) {
                // Mur à la coordonnée 0
                double r_bas = p.pos[d]; // Distance au mur
                if (r_bas > 0.0 && r_bas < r_cut_mur) {
                    double term6 = std::pow(sigma / (2.0 * r_bas), 6.0); // (sigma / 2r)^6
                    double force_mag = -24.0 * epsilon * (1.0 / (2.0 * r_bas)) * term6 * (1.0 - 2.0 * term6);
                    f_murs[d] += force_mag; // Pousse vers l'intérieur (valeurs positives de d)
                }

                // Mur à la coordonnée longueurs[d]
                double r_haut = longueurs[d] - p.pos[d]; // Distance au mur opposé
                if (r_haut > 0.0 && r_haut < r_cut_mur) {
                    double term6 = std::pow(sigma / (2.0 * r_haut), 6.0);
                    double force_mag = -24.0 * epsilon * (1.0 / (2.0 * r_haut)) * term6 * (1.0 - 2.0 * term6);
                    f_murs[d] -= force_mag;
                }
            }
            p.addForce(f_murs);
        }
    }

    double r_cut_carre = rayon_coupe * rayon_coupe;

    for (size_t i = 0; i < cellules.size(); ++i) {
        Cellule& cell = cellules[i];

        for (Particule<D>* p : cell.particules) {

            if (std::isnan(p->pos[0])) {
                throw SimulationException("Erreur critique : La position de la particule " + std::to_string(p->id) + " est devenue NaN (explosion numérique).");
            }

            for (int voisin : cell.voisines) {
                Cellule& voisin_cell = cellules[voisin];
                for (Particule<D>* q : voisin_cell.particules) {
                    if (p < q) {
                        Vecteur<D> dist = p->dist(*q); 

                        double r2 = 0.0; 
                        for (int k = 0; k < D; ++k) {
                            r2 += dist[k] * dist[k];
                        }

                        if (r2 == 0.0) {
                            throw SimulationException("Collision parfaite détectée entre les particules " + std::to_string(p->id) + " et " + std::to_string(q->id) + " (Division par zéro empêchée).");
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

template<int D>
bool Univers<D>::appliquerConditionsLimites(Particule<D>& p) {
    bool a_detruire = false;

    for (int d = 0; d < D; ++d) {
        if (condition_limite == ConditionLimite::ABSORPTION) {
            if (p.pos[d] < 0.0 || p.pos[d] > longueurs[d]) {
                a_detruire = true;
                break; // On arrête dès qu'une dimension sort
            }
        } 
        else if (condition_limite == ConditionLimite::REFLEXION) {
            if (p.pos[d] < 0.0) {
                p.pos[d] = -p.pos[d];
                p.v[d] = -p.v[d];
            } else if (p.pos[d] > longueurs[d]) {
                p.pos[d] = 2.0 * longueurs[d] - p.pos[d];
                p.v[d] = -p.v[d];
            }
        } 
        else if (condition_limite == ConditionLimite::PERIODIQUE) {
            p.pos[d] = std::fmod(p.pos[d], longueurs[d]);
            if (p.pos[d] < 0.0) p.pos[d] += longueurs[d];
        }
        else if (condition_limite == ConditionLimite::REFLEXION_POTENTIEL) {
            // Sécurité : si la particule a traversé malgré tout (dt trop grand), on l'absorbe.
            if (p.pos[d] < 0.0 || p.pos[d] > longueurs[d]) {
                a_detruire = true;
                break;
            }
        }
    }
    return a_detruire;
}

template<int D>
void Univers<D>::appliquerThermostat(double Ec_cible) {
    double Ec_actuelle = 0.0;
    
    // Calcul de Ec_actuelle
    for (const auto& p : particules) {
        double v2 = 0.0;
        for (int d = 0; d < D; ++d) {
            v2 += p.v[d] * p.v[d];
        }
        Ec_actuelle += 0.5 * p.masse * v2; // Ec = 1/2 m v^2
    }

    // Mise à l'échelle des vitesses
    if (Ec_actuelle > 0.0) {
        double beta = std::sqrt(Ec_cible / Ec_actuelle);
        for (auto& p : particules) {
            for (int d = 0; d < D; ++d) {
                p.v[d] *= beta; 
            }
        }
    }
}

template <int D>
void Univers<D>::algoStormerVerlet(double t_end, double dt, double epsilon, double sigma, double G, 
    double Ec_cible, int freq_vtk, const std::string& dossier) {
    double t = 0.0;
    int iteration = 0;

    calculerForces(epsilon, sigma, G);

    while (t < t_end) {
        t += dt;
        iteration++;

        auto it = particules.begin();
        while (it != particules.end()) {
            it->updatePosition(dt);
            
            if (appliquerConditionsLimites(*it)) {
                *it = particules.back();
                particules.pop_back();
            } else {
                ++it;
            }
        }

        majCells();
        calculerForces(epsilon, sigma, G);

        for (auto &p : particules) {
            p.updateV(dt);
        }

        if (Ec_cible > 0.0 && iteration % 1000 == 0) {
            appliquerThermostat(Ec_cible);
        }

        if (freq_vtk > 0 && iteration % freq_vtk == 0) {
            saveVTK(iteration / freq_vtk, dossier);
            std::cout << "Export VTK... t=" << t << "/" << t_end << "\n";
        }
    }
};

template<int D>
void Univers<D>::saveVTK(int iteration, const std::string& dossier) const {
    // Création du nom de fichier avec des zéros devant si nécessaire
    if (!dossier.empty()) {
        std::filesystem::create_directories(dossier);
    }

    std::ostringstream filename;
    if (!dossier.empty()) {
        filename << dossier << "/";
    }
    filename << "output_" << std::setw(4) << std::setfill('0') << iteration << ".vtu";
    
    std::ofstream file(filename.str());

    if (!file.is_open()) {
        throw SimulationException("Erreur critique : impossible d'ouvrir le fichier d'exportation " + filename.str());
    }

    int num_points = particules.size();

    // En-tête VTK
    file << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
    file << "  <UnstructuredGrid>\n";
    file << "    <Piece NumberOfPoints=\"" << num_points << "\" NumberOfCells=\"0\">\n";
    
    // Positions
    file << "      <Points>\n";
    file << "        <DataArray type=\"Float32\" Name=\"Position\" NumberOfComponents=\"3\" format=\"ascii\">\n";
    for (const auto& p : particules) {
        // En 2D, Z à 0.0
        file << "          " << p.getPos()[0] << " " << p.getPos()[1] << " " << (D == 3 ? p.getPos()[2] : 0.0) << "\n";
    }
    file << "        </DataArray>\n";
    file << "      </Points>\n";

    // Vitesse et Masse
    file << "      <PointData Vectors=\"vector\">\n";
    file << "        <DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">\n";
    for (const auto& p : particules) {
        file << "          " << p.getVitesse()[0] << " " << p.getVitesse()[1] << " " << (D == 3 ? p.getVitesse()[2] : 0.0) << "\n";
    }
    file << "        </DataArray>\n";

    file << "        <DataArray type=\"Float32\" Name=\"Masse\" format=\"ascii\">\n";
    for (const auto& p : particules) {
        file << "          " << p.getMasse() << "\n";
    }
    file << "        </DataArray>\n";
    file << "      </PointData>\n";

    // Cells
    file << "      <Cells>\n";
    file << "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n        </DataArray>\n";
    file << "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n        </DataArray>\n";
    file << "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n        </DataArray>\n";
    file << "      </Cells>\n";

    file << "    </Piece>\n";
    file << "  </UnstructuredGrid>\n";
    file << "</VTKFile>\n";

    file.close();
}