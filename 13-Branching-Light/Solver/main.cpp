#include"branched_flow.h"

int main(void){
    BranchedFlow Branches;

    Branches.initialize("potential0.csv");

    Branches.rk4_solve();
    Branches.save("gaussian.csv");

    // ...

    return 0;
}

