#include"branched_flow.h"

BranchedFlow::BranchedFlow(std::string potential_file){
    FileHandler file(potential_file);

    int Lx = file.content[file.get_rows()-1][0];
    int Ly = file.content[file.get_rows()-1][1];

    potential = file.content;

    film = std::unique_ptr< std::unique_ptr<double>[] >(new std::unique_ptr<double>[Lx]);

    for(int i=0; i<Lx; i++)
        film[i] = std::unique_ptr<double>(new double[Ly]);

    file.~FileHandler();
}
