#include "md-simulation.h"
#include<cmath>

void initial_conditions(Walker & body)
{
  body.Ry = 1.0;
  body.Rz = 0.0;
  body.Vx = 0.0;
  body.Vy = 0.0;
  body.Vz = 0.0;

  body.rad = 0.1;
  body.mass = 0.1;
}

void compute_force(Walker & body)
{
  // reset force
  body.Fx = body.Fy = body.Fz = 0.0;

  // gravitational force
  body.Fy += body.mass*g;

  //Elastic force
  double delta = body.rad - body.Ry;
  if(delta > 0){
  body.Fy += delta*K;
  }

  //driving force
  //body.Fy += a*std::sin(f*body.Vy);

  //damping force
  //body.Fx
}


void start_integration(Walker & body, const double & dt)
{
  body.Vx -= body.Fx*dt/(2*body.mass);
  body.Vy -= body.Fy*dt/(2*body.mass);
  body.Vz -= body.Fz*dt/(2*body.mass);
}

  void time_integration(Walker & body, const double & dt)
{
  // leap-frog
  body.Vx += body.Fx*dt/(body.mass);
  body.Vy += body.Fy*dt/(body.mass);
  body.Vz += body.Fz*dt/(body.mass);
  body.Rx += body.Vx*dt;
  body.Ry += body.Vy*dt;
  body.Rz += body.Vz*dt;
}


void print(Walker & body, double time)
{
  std::cout << time << "  "
            << body.Rx << "  "
            << body.Ry << "  "
            << body.Rz << "  "
            << body.Vx << "  "
            << body.Vy << "  "
            << body.Vz << "  "
            << "\n";
}
