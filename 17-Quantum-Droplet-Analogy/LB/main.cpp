#include "Fluids_LB_D3Q19.h"
#include "molecular_dynamics.h"

#define TMAX 10000
#define TEQ 10
#define N 1
#define dt 1.6083e-4

#define R 1.5
#define m (4.0*M_PI*R*R*R/3.0)

std::string filename(int t);

int main(void){
    std::cout << "Simulation parameters:\n" 
        << "Lx: " << Lx << "\nLy: " << Ly << '\n'
        << "Lz: " << Lz << "\nTau: " << tau << '\n' 
        << "Time steps equilibrium: " << TEQ << '\n'
        << "Time steps interaction: " << TMAX << '\n' << std::endl;

    Fluids Boltzmann;
    Body *Drops = new Body[N];
    Collider Newton(N);

    for(int i=0; i<N; i++) Drops[i] = Body(N);

    Drops[0].initialize(Lx/2.0, Ly/2.0, Lz + 1.4*R, 0,0,0, m, R);

    Boltzmann.initialize(Drops, N);
    Boltzmann.save_2D("initial.csv", Lx/2);

    std::cout << "LB initialized" << std::endl;

    for(int t=0; t<TEQ; t++){
        Boltzmann.collide((double) t, Drops, N);
        Boltzmann.propagate(Drops, N);
    }

    Boltzmann.save_2D("equilibrium.csv", Lx/2);

    std::cout << "LB in equilibrium" << std::endl;

    std::ofstream file3d("drop_3D.csv");
    std::ofstream file2d("drop_2D.csv");

    for(int t=0; t<TMAX; t++){
        Boltzmann.collide((double) t, Drops, N);
        Boltzmann.propagate(Drops, N);
        Newton.move_with_pefrl(Drops, 1.0, Boltzmann);

        file3d << Drops[0].get_x() << ',' << Drops[0].get_y() << ',' << Drops[0].get_z() + R << '\n';
        file2d << Drops[0].get_x() << ',' << Drops[0].get_y() << '\n';
    }

    file3d.close();
    file2d.close();

    Boltzmann.save_2D("final.csv", Lx/2);

    delete[] Drops;

    return 0;
}

std::string filename(int t){
    std::string name; std::stringstream t_s; t_s << t;
    name = t_s.str() + ".txt";
    return name;
}