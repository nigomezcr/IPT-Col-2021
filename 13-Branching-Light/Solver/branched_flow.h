#include<iostream>
#include<complex>
#include<memory>
#include<vector>
#include<string>

#include"file_handler.h"
#include"constants.h"

/**
 * Transform from 2D notation to 1D notation 
 * @return 1D macro-coordinate on array
 */
#define get_1D(ix, iy) ((ix*Ly) + iy)

class BranchedFlow{
    private:
        int Lx = 0, Ly = 0;
        std::vector< std::vector<double> > potential;
        double *film = NULL;
    public:
        ~BranchedFlow();
        void initialize(std::string potential_file);
        // void rk4_step(int ix);
        // void rk4_solve(void);
        // void save(std::string filename);
};
