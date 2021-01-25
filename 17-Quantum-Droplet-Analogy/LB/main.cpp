#include "Fluids_LB_D3Q19.h"
#include "molecular_dynamics.h"

#define TMAX 8000
#define N 1
#define dt 1.6083e-4

#define R 4.0
#define m (4.0*M_PI*R*R*R/3.0)

std::string filename(int t);

int main(void){
    std::cout << "Simulation parameters:\n" 
        << "Lx: " << Lx << "\nLy: " << Ly << '\n'
        << "Lz: " << Lz << "\nTau: " << tau << '\n' 
        << "Time steps: " << TMAX << '\n' << std::endl;

    Fluids Boltzmann;
    Body *Drops = new Body[N];
    Collider Newton(N);

    for(int i=0; i<N; i++) Drops[i] = Body(N);

    double r[N*3], v[N*3], F[N*3];


    Drops[0].initialize(Lx/3.0, Ly/2.0, Lz + 1.4*R, 0,0,0, m, R);

    Boltzmann.initialize(r, R, N);
    Boltzmann.save_2D("initial.csv", Lx/2);

    std::cout << "LB initialized" << std::endl;

    std::ofstream file("drop.csv");

    for(int t=0; t<TMAX; t++){
        Boltzmann.collide((double) t, r, v, F, R, N);
        Boltzmann.propagate(r, R, N);

        Newton.move_with_pefrl(Drops, 1.0, Boltzmann);

        for(int i=0; i<N; i++){
            r[i] = Drops[i].get_x();  r[i+1] = Drops[i].get_y();  r[i+2] = Drops[i].get_z();
            v[i] = Drops[i].get_vx(); v[i+1] = Drops[i].get_vy(); v[i+2] = Drops[i].get_vz();
            F[i] = Drops[i].get_fx(); F[i+1] = Drops[i].get_fy(); F[i+2] = Drops[i].get_fz();
        }

        file << Drops[0].get_x() << ',' << Drops[0].get_y() << ',' << Drops[0].get_z() << '\n';
    }

    Boltzmann.save_2D("final.csv", Lx/2);

    delete[] Drops;

    return 0;
}

std::string filename(int t){
    std::string name; std::stringstream t_s; t_s << t;
    name = t_s.str() + ".txt";
    return name;
}