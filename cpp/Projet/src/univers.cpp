#include "univers.hpp"
#include <iostream>
#include <fstream>

template <int D>
void Univers<D>::calculerForces() {
    for (auto &p : particules) {
        p.f.x = 0.0;
        p.f.x = 0.0;
        p.f.x = 0.0;
    }

    for (auto it_i = particules.begin(); it_i != particules.end(); ++it_i) {

        auto it_j = it_i;
        ++it_j;

        for (; it_j != particules.end(); ++it_j) {

            double dx = it_j->pos.x - it_i->pos.x;
            double dy = it_j->pos.y - it_i->pos.y;
            double dz = it_j->pos.z - it_i->pos.z;

            double r2 = dx*dx + dy*dy + dz*dz;
            double r = std::sqrt(r2);

            double inv_r3 = 1.0 / (r2 * r);

            double f = it_i->masse * it_j->masse * inv_r3;

            double fx = f * dx;
            double fy = f * dy;
            double fz = f * dz;

            it_i->f.x += fx;
            it_i->f.y += fy;
            it_i->f.z += fz;

            it_j->f.x -= fx;
            it_j->f.y -= fy;
            it_j->f.z -= fz;
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

        std::vector<double> fx_old, fy_old, fz_old;

        for (auto &p : particules) {

            fx_old.push_back(p.f.x);
            fy_old.push_back(p.f.y);
            fz_old.push_back(p.f.z);

            p.pos.x += dt * (p.v.x + 0.5 / p.masse * p.f.x * dt);
            p.pos.y += dt * (p.v.y + 0.5 / p.masse * p.f.y * dt);
            p.pos.z += dt * (p.v.z + 0.5 / p.masse * p.f.z * dt);
        }

        calculerForces();

        int i = 0;
        for (auto &p : particules) {
            p.v.x += dt * 0.5 / p.masse * (p.f.x + fx_old[i]);
            p.v.y += dt * 0.5 / p.masse * (p.f.y + fy_old[i]);
            p.v.z += dt * 0.5 / p.masse * (p.f.z + fz_old[i]);
            i++;
        }

        for (auto &p : particules) {
            //std::cout << t << " "
            //          << p.x << " "
            //          << p.y << std::endl;

            file << p.pos.x << " " << p.pos.y << " " << p.pos.z << " ";
        }
        file << "\n";
    }
    file.close();
};