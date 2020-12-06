#include "system.hpp"
#include<cmath>

void initial_conditions(Walker & body)
{
  body.Rx = 60.;
  body.Ry = 1.0;       //in mm
  body.Rz = 0.0;       //in mm
  body.Vx = 0.01;       //in mm/ms = m/s
  body.Vy = 0.0;       //in mm/ms = m/s
  body.Vz = -0.002;       //in mm/ms = m/s

  body.rad = 0.43;    //in mm
  body.mass = 1;      //in 1e-6 kg
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
  body.Fy += delta*k;
  }

  //driving force
  body.Fx += a*std::sin(f*body.Vx);
  body.Fz += a*std::sin(f*body.Vz);

  //damping force
  body.Fx -= b*body.Vx;
  body.Fz -= b*body.Vz;

  //Left wall
  double Lx = -100;
  delta = body.rad - body.Rx + Lx;
  if (delta > 0) {
  body.Fx = K*delta;
  }

  //Right wall
  Lx = 100;
  delta = body.rad + body.Rx - Lx;

  if (delta > 0) {
  body.Fx -= K*delta;
  }

  //back wall
  double Lz = -100;
  delta = body.rad - body.Rz + Lz;
  if (delta > 0) {
  body.Fz += K*delta;
  }

  //front wall
  Lz = 100;
  delta = body.rad + body.Rz - Lz;

  if (delta > 0) {
  body.Fz -= K*delta;
  }

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
  //        << body.Vx << "  "
  //        << body.Vy << "  "
  //        << body.Vz << "  "
            << "\n";
}
