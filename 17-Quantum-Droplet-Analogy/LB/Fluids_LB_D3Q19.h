#ifndef __LB_CPP_FLUIDS_LB_D3Q19_H
#define __LB_CPP_FLUIDS_LB_D3Q19_H

#include "LB_D3Q19.h"

// Oscillation
#define omega (2*M_PI*8.0417e-3)
#define gravity 5.0700e-4
#define vel (4.5*gravity)

#undef f_eq

// eq function for fluids
#define f_eq(rho0, U_Vi, U_2, i) (rho0*w[i]*(1.0 + 3.0*U_Vi + 4.5*U_Vi*U_Vi - 1.5*U_2))

class Fluids : public LatticeBoltzmann{
    private:
        int opposite_of[19] = {0, 2, 1, 4, 3, 6, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15, 18, 17};
    public:
        void collide(void);
        void propagate(void);
        void initialize(void);
        void impose_fields(double t);
        void save(std::string filename);
        void save_2D(std::string filename, int x_pos);
};

#endif
