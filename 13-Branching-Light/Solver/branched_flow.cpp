#include"branched_flow.h"

void BranchedFlow::initialize(std::string potential_file){
    FileHandler file(potential_file);

    int Lx_new = (int)file.content[file.get_rows()-1][0] + 1;
    int Ly_new = (int)file.content[file.get_rows()-1][1] + 1;

    potential = file.content;

    if(Lx != 0 && Ly != 0){
        delete[] film;
    }

    film = new double[Lx_new*Ly_new];

    Lx = Lx_new; Ly = Ly_new;
}

BranchedFlow::~BranchedFlow(){
    delete[] film;
}
