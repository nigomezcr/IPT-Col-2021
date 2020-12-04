#ifndef __SYSTEM_HPP_
#define __SYSTEM_HPP_

#include <iostream>
#include "walker.hpp"

const double g = -0.00981;  // in mm /ms^2
const int NSTEPS = 10000;   // in ms
const double DT = 0.01;     // in ms
const double K = 1;         // in 1e-6 N/m
const double f = 1;         // in 1e-6 s/m
const double a = 1.5;       // in 1e-6 N
const double b = 1;         // in 1e-6 Nm/s

// function declarations
void initial_conditions(Walker & body);
void compute_force(Walker & body);
void time_integration(Walker & body, const double & dt);
void start_integration(Walker & body, const double & dt);
void print(Walker & body, double time);

#endif // __SYSTEM_HPP_
