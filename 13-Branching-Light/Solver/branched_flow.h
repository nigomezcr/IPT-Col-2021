#include<iostream>
#include<complex>
#include<memory>
#include<vector>
#include<string>

#include"file_handler.h"
#include"constants.h"

class BranchedFlow{
    private:
        std::vector< std::vector<double> > potential;
        std::unique_ptr< std::unique_ptr<double>[] > film;
    public:
        BranchedFlow(std::string potential_file);
        // void rk4_step(int ix);
        // void rk4_solve(void);
        // void save(std::string filename);
};
