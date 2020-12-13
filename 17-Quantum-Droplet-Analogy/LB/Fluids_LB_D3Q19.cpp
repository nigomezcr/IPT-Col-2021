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
    unsigned int pos_new, x_pos, y_pos, z_pos, pos;

    #pragma omp parallel for private(pos_new, x_pos, y_pos, z_pos, pos)
    for(int ix=1; ix<Lxm1; ix++)
        for(int iy=1; iy<Lym1; iy++)
            for(int iz=1; iz<Lzm1; iz++){
                pos_new = get_1D(ix, iy, iz);

                for(int i=0; i<Q; i++){
                    x_pos = ix + V[0][i]; y_pos = iy + V[1][i]; z_pos = iz + V[2][i];
                    pos = get_1D(x_pos, y_pos, z_pos);

                    if( // Walls
                        (ix == 1) || (iy == 1) || (iz == 1) || (ix == Lxm1) || (iy == Lym1) || (iz == Lzm1)
                    ){
                        f_new[pos + opposite_of[i]] = f_new[pos + i];
                    }
                    else{ // Fluid site
                        f[pos + i] = f_new[pos_new + i];
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
    double U2 = 0, UdotVi = 0, rho0 = 1.0;
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=0; iz<2*Lz/3; iz++){
                unsigned int pos = get_1D(ix, iy, iz);

                if( (ix == 0) || (iy == 0) || (iz == 0) ) rho0 = 0.0;
                else rho0 = 1.0;

                for(int i=0; i<Q; i++) f[pos + i] = f_eq(rho0, UdotVi, U2, i);
            }

    rho0 = 0;
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=2*Lz/3; iz<Lz; iz++){
                unsigned int pos = get_1D(ix, iy, iz);
                double U2 = 0, UdotVi = 0;

                for(int i=0; i<Q; i++) f[pos + i] = f_eq(rho0, UdotVi, U2, i);
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

            //file << iy << '\t' << iz << '\t' << 4*Uy0 << '\t' << 4*Uz0 << '\n';
            file << iy << '\t' << iz << '\t' /*<< Uy0 << '\t' << Uz0 << '\t'*/ << rho0 << '\n';
        }
        file << '\n';
    }

    file.close();
}

