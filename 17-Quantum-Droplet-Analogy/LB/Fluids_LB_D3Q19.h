#ifndef __LB_CPP_FLUIDS_LB_D3Q19_H
#define __LB_CPP_FLUIDS_LB_D3Q19_H

#include "LB_D3Q19.h"
#include "molecular_dynamics.h"

class Body;

// Oscillation
#define omega (2*M_PI*1.3403e-03)
#define gravity 7.0417e-6
#define gamma (2*gravity)

#define UmU2tau (1.0 - 0.5*Utau)

#undef f_eq

// eq function for fluids
#define f_eq(rho0, U_Vi, U_2, i) (rho0*w[i]*(1.0 + 3.0*U_Vi + 4.5*U_Vi*U_Vi - 1.5*U_2))

class Fluids : public LatticeBoltzmann{
    private:
        int opposite_of[19] = {0, 2, 1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17};
    public:
        void collide(double t, Body *drops, int N);
        void propagate(Body *drops, int N);
        void initialize(Body *drops, int N);

        void save(std::string filename);
        void save_2D(std::string filename, int x_pos);

        bool is_fluid(Body *drops, int x, int y, int z, int N);

        friend class Collider;
};

#endif
