#include "Fluids_LB_D2Q9.h"


void Fluids::collide(void){
    for(int ix=0; ix<Lx; ix++){
        for(int iy=0; iy<Ly; iy++){
            unsigned pos = get_1D(ix, iy);

            double rho0 = rho(pos);
            double Ux = Jx(pos)/rho0; 
            double Uy = Jy(pos)/rho0;

            if(
                (ix<5) && (iy > 1)
            ){
                //Ux += 0.008669718407546132;
                Uy -= 0.005;
                Ux += 0.00001;
            }

            double U2 = Ux*Ux + Uy*Uy;

            for(int i=0; i<Q; i++){
                double UdotVi = Ux*V[0][i] + Uy*V[1][i];
                f_new[pos + i] = UmUtau*f[pos + i] + Utau*f_eq(rho0, UdotVi, U2, i);
            }
        }
    }
}

void Fluids::propagate(void){
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++){
            unsigned int pos = get_1D(ix, iy);

            for(int i=0; i<Q; i++){
                    unsigned int x = ix + V[0][i];
                    unsigned int y = iy + V[1][i];

                    if( // Walls
                        (x > Lxm1) || (y > Lym1)
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

// Initialize population using the Mei  et al. scheme
void Fluids::initialize(void){
    #define V0 0.0
    #define rho0 1.0
    #define top 2

    // Load initial density
    for(int ix=0; ix<top; ix++){
        for(int iy=0; iy<Ly-top; iy++){
            unsigned int pos = get_1D(ix, iy);

            for(int i=0; i<Q; i++) f[pos + i] = f_eq(rho0, V0, V0, i);
        }
        for(int iy=Ly-top; iy<Ly; iy++){
            unsigned int pos = get_1D(ix, iy);

            for(int i=0; i<Q; i++) f[pos + i] = f_eq(rho0/0.5, V0, V0, i);
        }
    }
    #undef rho0

    // Collide & propagate just the density
    #define STEPS 100
    for(int t=0; t<STEPS; t++){
        for(unsigned int pos=0; pos<size; pos+=Q){
                double rho0 = rho(pos);

                for(int i=0; i<Q; i++) f_new[pos + i] = UmUtau*f[pos + i] + Utau*f_eq(rho0, V0, V0, i);
        }
        propagate();
    }
    #undef V0
    #undef STEPS
}

void Fluids::save(std::string filename){
    std::ofstream File(filename); double rho0, Ux0, Uy0, Uz0;
    for(int ix=0; ix<Lx; ix+=4){
        for(int iy=0; iy<Ly; iy++){
            int pos = get_1D(ix, iy);

            rho0 = rho(pos);
            Ux0 = Jx(pos)/rho0; Uy0 = Jy(pos)/rho0;
            File << ix << ',' << iy << ',' << 10*Ux0 << ',' << 10*Uy0 << ',' <<  rho0 << '\n';
        }
        File << '\n';
    }
    File << std::endl;
    File.close();
}
