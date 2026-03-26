#include "univers.hpp"
#include <iostream>
#include <fstream>

template <int D>
void Univers<D>::calculerForces() {
    for (auto &p : particules) {
        for (int i = 0; i < D; ++i) {
            p.f[i] = 0.0;
        }
    }

    for (auto it_i = particules.begin(); it_i != particules.end(); ++it_i) {

        auto it_j = it_i;
        ++it_j;

        for (; it_j != particules.end(); ++it_j) {

            Vecteur<D> dpos = it_j->pos - it_i->pos;

            double r2 = 0.0;
            for (int i = 0; i < D; ++i) {
                r2 += dpos[i] * dpos[i];
            }
            double r = std::sqrt(r2);

            double inv_r3 = 1.0 / (r2 * r);

            double f = it_i->masse * it_j->masse * inv_r3;

            Vecteur<D> fpos = dpos * f;

            for (int i = 0; i < D; ++i) {
                it_i->f[i] += fpos[i];
                it_j->f[i] -= fpos[i];
            }

        }
    }
};     

template <int D>
void Univers<D>::algoStormerVerlet(double t_end, double dt) {

    std::ofstream file("positions_astres.txt");
    double t = 0.0;

    calculerForces();

    while (t < t_end) {
        t += dt;

        std::vector<std::vector<double>> f_old(D);

        for (auto &p : particules) {
            for (int i = 0; i < D; ++i) {
                f_old[i].push_back(p.f[i]);
                p.pos[i] += dt * (p.v[i] + 0.5 / p.masse * p.f[i] * dt);
            }
        }

        calculerForces();

        int i = 0;
        for (auto &p : particules) {
            for (int j = 0; j < D; ++j) {
                p.v[j] += dt * 0.5 / p.masse * (p.f[j] + f_old[j][i]);
            }
            i++;
        }

        for (auto &p : particules) {
            file << p.pos << " ";
        }
        file << "\n";
    }
    file.close();
};

template class Univers<3>;
template class Univers<2>;