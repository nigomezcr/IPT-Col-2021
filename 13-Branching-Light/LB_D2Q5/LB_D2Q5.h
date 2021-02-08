/**
 * 2D Lattice Boltzmann module.
 * 
 * This module requires a constants.h file, where geometry, relaxation time (tau), LB type and 
 * evolution algorithm are specified. Everything you would need to modify should be there.
 * 
 * constants.h requirements:
 * - Lx, Ly: Integers defining number of nodes in x and y, respectively
 * - tau, o_tau, o_m_o_tou: Doubles defining relaxation time tau, (1/tau) and (1 - 1/tau), respectiveley
 * - LB_TYPE: Either 1 (diffusion) or 2 (waves). Defines if LB evaluates fluids or diffusion.
 * - EVOLUTION_ALGORITHM: Either 2 (two steps) or 1 (one step). Defines if LB evolution is done in a single
 *      step, with collision and streaming done in a single pass over the f array, or with collision
 *      and streaming having separate passes, respectiveley. Note: Two step evolution requires more 
 *      allocated memory than single step.
 */
#ifndef __LB_CPP_LB_D2Q5_H
#define __LB_CPP_LB_D2Q5_H

#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#include<sstream>

#include "constants.h"

// Geometry
#define D 2
#define Q 5

#define C_S 0.5 // speed of sound c_s = 1/2
#define C_S2 0.25 // (c_s)^2
#define O_C_S 2.0 // (1/c_s)
#define O_C_S2 4.0 // (1/c_s)^2


// Equilibrium function
#undef f_eq

#if LB_TYPE == 1
/**
 * Equilibrium function for diffusion
 * @param rho: density at position.
 * @param U_Vi: velocity field U dot velocity vector V_i. (U . V_i).
 */
#define f_eq(rho, U_Vi, i) (rho*w[i]*(1.0 + U_Vi*O_C_S2))

#elif LB_TYPE == 2
/**
 * Equilibrium function for waves, index 0
 * @param rho: density at position.
 */
#define f_eq0(rho) (rho*0.5) // f_eq, i=0 = rho*(1 - 3*C_S2*(1 - w[0]) )
/**
 * Equilibrium function for waves, other indexes
 * @param rho: density at position.
 * @param J_Vi: momentum field J dot velocity vector V_i. (J . V_i).
 */
#define f_eq(rho, J_Vi, i) (w[i]*(3*C_S2*rho0 + 3*J_Vi))

#endif // LB_TYPE


class LatticeBoltzmann2D{
    private:
        double w[Q]; int V[D][Q];
        double *f = NULL;

        #if EVOLUTION_ALGORITHM == 2
        double *f_new = NULL;
        #endif // EVOLUTION_ALGORITHM

        int opposite_of[Q] = {0, 3, 4, 1, 2};

    public:
        LatticeBoltzmann2D(void);
        ~LatticeBoltzmann2D();

        void initialize(void);

        void collide(void);
        void stream(void);
        void evolve(void);

        double rho(int position);
        double Jx(int position);
        double Jy(int position);

        void save(std::string filename, double mult=1);

        double Jx_new(int ix, int iy);
        double Jy_new(int ix, int iy);
};


// 2D to 1D
#define SIZE (Lx*Ly*Q)
#define X_MULT (Ly*Q)
#define Y_MULT Q

/**
 * Transform from 2D notation to 1D notation 
 * @return 1D macro-coordinate on array
 */
#define get_1D(ix, iy) ((ix*X_MULT) + (iy*Y_MULT))


// 1D to 2D
/**
 * Transform from 1D notation to 2D notation
 * @return x coordinate
 */
#define get_ix(index) (index/(X_MULT))
/**
 * Transform from 1D notation to 2D notation
 * @return y coordinate
 */
#define get_iy(index) ((index/Y_MULT)%Ly)


#endif // __LB_CPP_LB_D2Q5_H