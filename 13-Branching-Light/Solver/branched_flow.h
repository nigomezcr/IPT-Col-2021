#include<iostream>
#include<complex>
#include<vector>
#include<string>

#include"file_handler.h"
#include"constants.h"

#define c_double std::complex<double>

/**
 * Transform from 2D notation to 1D notation 
 * @return 1D macro-coordinate on array
 */
#define get_1D(ix, iy) ((ix*Ly) + iy)

class BranchedFlow{
    private:
        int Lx = 0, Ly = 0;
        double C, h;
        const c_double j = {0.0, 1.0};

        c_double *film = NULL;
        double *potential = NULL;
    public:
        ~BranchedFlow();
        void initialize(std::string potential_file);
        c_double paraxial_equation(c_double u_xy, c_double uxy1, c_double uxy_1, double potential);
        void rk4_solve(void);
        void save(std::string filename);
};
