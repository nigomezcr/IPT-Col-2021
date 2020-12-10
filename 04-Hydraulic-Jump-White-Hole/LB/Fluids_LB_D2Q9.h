#ifndef __LB_CPP_FLUIDS_LB_D2Q9_H
#define __LB_CPP_FLUIDS_LB_D2Q9_H

#include "LB_D2Q9.h"

#undef f_eq

// eq function for fluids
#define f_eq(rho0, U_Vi, U_2, i) (rho0*w[i]*(1.0 + 3.0*U_Vi + 4.5*U_Vi*U_Vi - 1.5*U_2))

class Fluids : public LatticeBoltzmann{
    private:
        int opposite_of[9] = {0, 3, 4, 1, 2, 7, 8, 5, 6};
    public:
        void collide(void);
        void propagate(void);
        void initialize(double rho0, double Ux0, double Uy0, double Uz0);
        void impose_fields(double v);
        double detector(int x_pos);
        void save(std::string filename, double v);
        void save_2D(std::string filename, int z_pos, double v);
        void print(double v);
};

#endif
