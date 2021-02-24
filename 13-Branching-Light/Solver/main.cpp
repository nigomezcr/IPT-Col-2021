#include<iostream>

#include"branched_flow.h"

int main(void){
    BranchedFlow Branches;

    // Branches.initialize("V_0.csv");

    // Branches.rk4_solve();
    // Branches.save("zero.csv");

    // std::cout << "First job done" << std::endl;

    // Branches.initialize("V_angled.csv", true);

    // Branches.rk4_solve();
    // Branches.save("angled.csv");

    // std::cout << "Second job done" << std::endl;

    Branches.initialize("V_periodic_2.csv");

    Branches.rk4_solve();
    Branches.save("periodic.csv");

    return 0;
}

