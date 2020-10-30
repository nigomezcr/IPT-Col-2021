#ifndef __MD_SIMULATION_H_
#define __MD_SIMULATION_H_

#include <iostream>
#include "walker.h"

const double g = -9.81;
const int NSTEPS = 1000;
const double DT = 0.01;
const double K = 10;
const double f = 5;
const double a = 0.9;
const double b = 0.9;

// function declarations
void initial_conditions(Walker & body);
void compute_force(Walker & body);
void time_integration(Walker & body, const double & dt);
void start_integration(Walker & body, const double & dt);
void print(Walker & body, double time);

#endif // __MD_SIMULATION_H_
