#include"branched_flow.h"

int main(void){
    BranchedFlow Branches;

    Branches.initialize("potential1.csv");

    Branches.rk4_solve();
    // Branches.save("branches_1.csv");

    Branches.initialize("potential2.csv");

    // ...

    return 0;
}

