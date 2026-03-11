#include "univers.hpp"
#include <iostream>

void Univers::calculerForces() {
    for (auto &p : particules) {
        p.fx = 0.0;
        p.fy = 0.0;
        p.fz = 0.0;
    }

    for (auto it_i = particules.begin(); it_i != particules.end(); ++it_i) {

        auto it_j = it_i;
        ++it_j;

        for (; it_j != particules.end(); ++it_j) {

            double dx = it_j->x - it_i->x;
            double dy = it_j->y - it_i->y;
            double dz = it_j->z - it_i->z;

            double r2 = dx*dx + dy*dy + dz*dz;
            double r = std::sqrt(r2);

            double inv_r3 = 1.0 / (r2 * r);

            double f = it_i->m * it_j->m * inv_r3;

            double fx = f * dx;
            double fy = f * dy;
            double fz = f * dz;

            it_i->fx += fx;
            it_i->fy += fy;
            it_i->fz += fz;

            it_j->fx -= fx;
            it_j->fy -= fy;
            it_j->fz -= fz;
        }
    }
};    

void Univers::algoStormerVerlet(double t_end=468.5, double dt = 0.015) {
    std::ofstream file("positions_astres.txt");
    double t = 0.0;

    calculerForces();

    while (t < t_end) {
        t += dt;

        std::vector<double> fx_old, fy_old, fz_old;

        for (auto &p : particules) {

            fx_old.push_back(p.fx);
            fy_old.push_back(p.fy);
            fz_old.push_back(p.fz);

            p.x += dt * (p.vx + 0.5 / p.m * p.fx * dt);
            p.y += dt * (p.vy + 0.5 / p.m * p.fy * dt);
            p.z += dt * (p.vz + 0.5 / p.m * p.fz * dt);
        }

        calculerForces();

        int i = 0;
        for (auto &p : particules) {
            p.vx += dt * 0.5 / p.m * (p.fx + fx_old[i]);
            p.vy += dt * 0.5 / p.m * (p.fy + fy_old[i]);
            p.vz += dt * 0.5 / p.m * (p.fz + fz_old[i]);
            i++;
        }

        for (auto &p : particules) {
            std::cout << t << " "
                      << p.x << " "
                      << p.y << std::endl;

            file << p.x << " " << p.y << " ";
        }
        file << "\n";
    }
    file.close();
};