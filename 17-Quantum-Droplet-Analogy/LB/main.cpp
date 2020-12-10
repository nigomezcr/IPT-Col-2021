#include"Fluids_LB_D3Q19.h"
#include"Diffusion_LB_D3Q19.h"

std::string filename(int t);

int main(void){
    //Fluids Boltzmann;
    Diffusion Boltzmann;
    int t_max = 1000;
    double rho0 = 1.0, v = 0.1;

    Boltzmann.initialize(rho0, 0, 0, 0);
    Boltzmann.save_2D("initial.txt", Lz/2, v);

    for(int t=0; t<t_max; t++){
        Boltzmann.collide();
        //Boltzmann.impose_fields(v);
        Boltzmann.propagate();
    }

    Boltzmann.save_2D("final.txt", Lz/2, v);

    return 0;
}

std::string filename(int t){
    std::string name; std::stringstream t_s; t_s << t;
    name = t_s.str() + ".txt";
    return name;
}