#include<iostream>
#include<complex>
#include<vector>
#include<string>
#include<exception>

#include"file_handler.h"

#define c_double std::complex<double>

/**
 * Transform from 2D notation to 1D notation 
 * @return 1D macro-coordinate on array
 */
#define get_1D(ix, iy) ((ix*Ly) + iy)

// Constants (lengths in nanometers)
#define N0 1.003
#define K0 0.01181049869770599 // 2 pi/lambda
#define C 4.220859e+01

#define dy 7.519531e+03
#define dy2 5.654335e+07 // dy^2
#define o_dy2 1.768555e-08 // dy^(-2)
#define h 8.907584e+01

class BranchedFlow{
    private:
        int Lx = 0, Ly = 0;
        const c_double j = {0.0, 1.0};

        c_double *film = NULL;
        double *potential = NULL;
    public:
        ~BranchedFlow();
        void initialize(std::string potential_file, int init_cond=0);
        c_double paraxial_equation(c_double u_xy, c_double uxy1, c_double uxy_1, double potential);
        void rk4_solve(void);
        void save(std::string filename, bool show_v=false, int x_step=100);
};

struct ValueError: public std::exception{
    const char * what() const throw () {
        return "invalid argument";
    }
};
