#include "Fluids_LB_D3Q19.h"

void Fluids::collide(void){
    double rho0, Ux0, Uy0, Uz0, U2; unsigned int pos;

    #pragma omp parallel for private(pos, rho0, Ux0, Uy0, Uz0, U2)
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=0; iz<Lz; iz++){
                pos = get_1D(ix, iy, iz);

                rho0 = rho(pos);

                if(rho0 != 0.0){
                    Ux0 = Jx(pos)/rho0, Uy0 = Jy(pos)/rho0, Uz0 = (Jz(pos)/rho0)-gravity;

                    U2 = Ux0*Ux0 + Uy0*Uy0 + Uz0*Uz0;

                    for(int i=0; i<Q; i++){
                        double UdotVi = Ux0*V[0][i] + Uy0*V[1][i] + Uz0*V[2][i];
                        f_new[pos + i] = UmUtau*f[pos + i] + Utau*f_eq(rho0, UdotVi, U2, i);
                    }
                }
                else
                    for(int i=0; i<Q; i++) f_new[pos + i] = UmUtau*f[pos + i] + Utau*f_eq(rho0, 0.0, 0.0, i);
            }
}

void Fluids::propagate(void){
    unsigned int streamed_pos, x, y, z, pos;

    #pragma omp parallel for private(streamed_pos, x, y, z, pos)
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=0; iz<Lz; iz++){
                pos = get_1D(ix, iy, iz);
                for(int i=1; i<Q; i++){
                    x = (Lx+ix+V[0][i])%Lx; y = (Ly+iy+V[1][i])%Ly; z = (Lz+iy+V[2][i])%Lz;
                    if( // Walls
                        (x == 0) || (y == 0) || (z == 0) || (x == Lxm1) || (y == Lym1) || (z == Lzm1)
                    ){
                        f_new[pos + opposite_of[i]] = f[pos+i];
                    }
                    else{ // Fluid site
                        streamed_pos = get_1D(x, y, z);
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

void Fluids::initialize(void){
    double rho0 = 1.0;
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=0; iz<2*Lz/3; iz++){
                unsigned int pos = get_1D(ix, iy, iz);

                double rho_x = rho0 + gravity*std::sqrt(3.0)*(1.0 - iz/Lz);

                for(int i=0; i<Q; i++) f[pos + i] = f_eq(rho_x, 0.0, 0.0, i);
            }

    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=2*Lz/3; iz<Lz; iz++){
                unsigned int pos = get_1D(ix, iy, iz);

                double rho_x = gravity*std::sqrt(3.0)*(1.0 - iz/Lz);

                for(int i=0; i<Q; i++) f[pos + i] = f_eq(rho_x, 0.0, 0.0, i);
            }
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

