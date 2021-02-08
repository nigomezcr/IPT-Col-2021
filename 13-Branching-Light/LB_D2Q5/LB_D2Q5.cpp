#include "LB_D2Q5.h"


void LatticeBoltzmann2D::collide(void){
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++){
                unsigned int pos = get_1D(ix, iy);

                double rho0 = rho(pos);

                double Ux = Jx(pos)/rho0;
                double Uy = Jy(pos)/rho0;

                double U2 = Ux*Ux + Uy*Uy;

                for(int i=0; i<Q; i++){
                    double UdotVi = Ux*V[0][i] + Uy*V[1][i];

                    f_new[pos + i] = o_m_o_tau*f[pos + i] + o_tau*f_eq(rho0, UdotVi, i);
                }
            }
}

void LatticeBoltzmann2D::stream(void){
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++){
                unsigned int pos = get_1D(ix, iy);

                for(int i=0; i<Q; i++){
                    unsigned int x = ix + V[0][i];
                    unsigned int y = iy + V[1][i];

                    if( // Walls by halfway bounce back
                        (x > Lx-1) || (y > Ly-1)
                    ){
                        f_new[pos + opposite_of[i]] = f[pos+i];
                    }
                    else{ // Fluid site
                        unsigned int streamed_pos = get_1D(x, y);
                        f[streamed_pos + i] = f_new[pos + i];
                    }
                }
            }
}

// Initialize population using the mei et al. scheme
void LatticeBoltzmann2D::initialize(void){
    #define V0 0.0
    #define rho0 1.0

    // Load initial density
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++){
                unsigned int pos = get_1D(ix, iy);

                for(int i=0; i<Q; i++) f[pos + i] = f_eq(rho0, V0, i);
        }
    #undef rho0

    // Collide & propagate just the density
    #define STEPS 100
    for(int t=0; t<STEPS; t++){
        for(unsigned int pos=0; pos<SIZE; pos+=Q){
            double rho0 = rho(pos);

            for(int i=0; i<Q; i++) f_new[pos + i] = o_m_o_tau*f[pos + i] + o_tau*f_eq(rho0, V0, i);
        }
        stream();
    }
    #undef V0
    #undef STEPS
}



/**
 * Macroscopic quantities and utilities
 */

/* Initialize weights and basis vectors, allocate memory for arrays. */
LatticeBoltzmann2D::LatticeBoltzmann2D(void){
    // weights
    w[0] = 1.0/3.0;
    w[1] = w[2] = w[3] = w[4] = 1.0/6.0;

    // basis vectors
    V[0][0]=0; //x
    V[1][0]=0; //y

    V[0][1]=1;   V[0][2]=0;   V[0][3]=-1;  V[0][4]=0;
    V[1][1]=0;   V[1][2]=1;   V[1][3]=0;   V[1][4]=-1;

    // f and f_new
    f = new double[SIZE];

    #if EVOLUTION_ALGORITHM == 2
    f_new = new double[SIZE];
    #endif // EVOLUTION_ALGORITHM
}

/* Free memory */
LatticeBoltzmann2D::~LatticeBoltzmann2D(){
    delete[] f;
    #if EVOLUTION_ALGORITHM == 2
    delete[] f_new;
    #endif // EVOLUTION_ALGORITHM
}

/* System density */
double LatticeBoltzmann2D::rho(int position){
    double r = 0;

    r += f[position + 0];

    r += f[position + 1];
    r += f[position + 2];
    r += f[position + 3];
    r += f[position + 4];

    return r;
}

/* Momentum field in the x axis. (i.e., U_x * rho) */
double LatticeBoltzmann2D::Jx(int position){
    double J_x = 0;

    J_x += f[position + 1];

    J_x -= f[position + 3];

    return J_x;
}

/* Momentum field in the y axis. (i.e., U_y * rho) */
double LatticeBoltzmann2D::Jy(int position){
    double J_y = 0;

    J_y += f[position + 2];

    J_y -= f[position + 4];

    return J_y;
}

void LatticeBoltzmann2D::save(std::string filename, double mult){
    std::ofstream file(filename);

    for(int ix=0; ix<Lx; ix+=(int)mult){
        for(int iy=0; iy<Ly; iy+=(int)mult){
            int pos = get_1D(ix, iy);

            double rho0 = rho(pos);
            double Ux0 = Jx(pos)/rho0;
            double Uy0 = Jy(pos)/rho0;

            file << ix << ',' << iy << ',' << mult*Ux0 << ',' << mult*Uy0 << ',' <<  rho0 << '\n';
        }
        file << '\n';
    }
    file << std::endl;
    file.close();
}
