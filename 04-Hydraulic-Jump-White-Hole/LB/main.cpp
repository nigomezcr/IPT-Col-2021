#include"Fluids_LB_D2Q9.h"

std::string filename(int t);

#define TMAX 100000

int main(void){
    Fluids Boltzmann;

    Boltzmann.initialize();
    Boltzmann.save("initial.csv");

    for(int t=0; t<TMAX; t++){
        Boltzmann.collide();
        Boltzmann.propagate();
    }

    Boltzmann.save("final.csv");

    return 0;
}

std::string filename(int t){
    std::string name; std::stringstream t_s; t_s << t;
    name = t_s.str() + ".txt";
    return name;
}
