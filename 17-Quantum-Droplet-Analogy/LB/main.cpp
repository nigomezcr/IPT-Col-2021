#include"Fluids_LB_D3Q19.h"

#define TMAX 100

std::string filename(int t);

int main(void){
    Fluids Boltzmann;

    Boltzmann.initialize();

    for(int t=0; t<TMAX; t++){
        Boltzmann.collide();
        Boltzmann.impose_fields((double)t);
        Boltzmann.propagate();
    }

    Boltzmann.save_2D("final.txt", Lx/2);

    return 0;
}

std::string filename(int t){
    std::string name; std::stringstream t_s; t_s << t;
    name = t_s.str() + ".txt";
    return name;
}