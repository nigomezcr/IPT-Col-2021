#include "Fluids_LB_D3Q19.h"

void Fluids::collide(void){
    for(unsigned int pos=0; pos<size; pos+=Q){
        double rho0 = rho(pos);

        double Ux = Jx(pos)/rho0;
        double Uy = Jy(pos)/rho0;
        double Uz = (Jz(pos)/rho0) - gravity*(1.0 - (pos%z_mult)/Lz);

        double U2 = Ux*Ux + Uy*Uy + Uz*Uz;

        for(int i=0; i<Q; i++){
            double UdotVi = Ux*V[0][i] + Uy*V[1][i] + Uz*V[2][i];
            f_new[pos + i] = UmUtau*f[pos + i] + Utau*f_eq(rho0, UdotVi, U2, i);
        }
    }
}

void Fluids::propagate(void){
    unsigned int streamed_pos, x, y, z, pos;

    #pragma omp parallel for private(streamed_pos, x, y, z, pos)
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=0; iz<Lz; iz++){
                unsigned int pos = get_1D(ix, iy, iz);

                for(int i=0; i<Q; i++){
                    unsigned int x = ix + V[0][i];
                    unsigned int y = iy + V[1][i];
                    unsigned int z = iz + V[2][i];

                    if( // Walls
                        (0 < x < Lxm1) || (0 < y < Lym1) || (0 < z < Lzm1)
                        // || (is_fluid(drops, x, y, z, N) == false)
                    ){
                        f_new[pos + opposite_of[i]] = f[pos+i];
                    }
                    else{ // Fluid site
                        unsigned int streamed_pos = get_1D(x, y, z);
                        f[streamed_pos + i] = f_new[pos + 1];
                    }
                }
            }
}

void Fluids::impose_fields(double t){
    unsigned int pos; double rho0, v = vel*std::sin(omega*t), v2 = v*v;

    #pragma omp parallel for private(pos, rho0) public(v)
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++){ // Oscillation in z
                pos = get_1D(iy, iy, 1);

                rho0 = rho(pos);
                for(int i=0; i<Q; i++){
                    double UdotVi = v*V[2][i];
                    f_new[pos + i] = f_eq(rho0, UdotVi, v2, i);
                }
        }
}

// Initialize population using the Mei  et al. scheme
void Fluids::initialize(Body *drops, int N){
    #define STEPS 100
    #define V0 0.0
    #define rho0 1.0

    // Load initial density
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=0; iz<2*Lz/3; iz++){
                unsigned int pos = get_1D(ix, iy, iz);

                for(int i=0; i<Q; i++) f[pos + i] = f_eq(rho0, V0, V0, i);
            }

    #undef rho0
    #define rho0 0.0
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=2*Lz/3; iz<Lz; iz++){
                unsigned int pos = get_1D(ix, iy, iz);

                for(int i=0; i<Q; i++) f[pos + i] = f_eq(rho0, V0, V0, i);
            }
    #undef rho0

    // Collide & propagate just the density
    for(int t=0; t<STEPS; t++){
        for(unsigned int pos=0; pos<size; pos+=Q){
            double rho0 = rho(pos);

            for(int i=0; i<Q; i++) f_new[pos + i] = UmUtau*f[pos + i] + Utau*f_eq(rho0, V0, V0, i);
        }
        propagate(drops, N);
    }
    #undef V0
    #undef STEPS
}


void Fluids::save(std::string filename){
    std::ofstream file(filename);

    for(int ix=0; ix<Lx; ix+=4){
        for(int iy=0; iy<Ly; iy+=4){
            for(int iz=0; iz<Lz; iz+=4){
                unsigned int pos = get_1D(ix, iy, iz);

                double rho0 = rho(pos);
                double Ux0 = 0, Uy0 = 0, Uz0 = 0;

                if(rho0 != 0.0){
                    Ux0 = Jx(pos)/rho0; Uy0 = Jy(pos)/rho0; Uz0 = Jz(pos)/rho0;
                }

                file << ix << '\t' << iy << '\t' << iz << '\t' << 4*Ux0 << '\t'
                << 4*Uy0 << '\t' << 4*Uz0 << '\n';
            }
            file << '\n';
        }
        file << '\n';
    }

    file.close();
}

// Saves a 2D view from a fixed x position
void Fluids::save_2D(std::string filename, int x_pos){
    std::ofstream file(filename);

    for(int iy=0; iy<Ly; iy+=4){
        for(int iz=0; iz<Lz; iz++){
            unsigned int pos = get_1D(x_pos, iy, iz);

            double rho0 = rho(pos);
            double Uy0 = 0, Uz0 = 0;

            if(rho0 != 0.0){
                Uy0 = Jy(pos)/rho0; Uz0 = Jz(pos)/rho0;
            }

            file << iy << '\t' << iz << '\t' << 4*Uy0 << '\t' << 4*Uz0 << '\t' << rho0 << '\n';
            //file << iy << '\t' << iz << '\t' << Uy0 << '\t' << Uz0 << '\t' << rho0 << '\n';
        }
        file << '\n';
    }

    file.close();
}

