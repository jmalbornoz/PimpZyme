// TIMESTEP.H
// Declaration of singleton class TIMESTEP
// Member functions are defined in TIMESTEP.CPP
// This singleton is used to define the time step to be used
// in the simulation

// Previene inclusiones multiples del archivo de cabecera
#ifndef _TIMESTEP_H_
#define _TIMESTEP_H_

class Timestep {
private:
   // timestep for the simulation
   float step;
   // Private constructors
   Timestep(){};
   Timestep(const Timestep&);
   // Private assignment operator 
   Timestep& operator= (const Timestep&);
public:
   // instantiates a single instance of the Timestep class
   static Timestep& Instance();
   // get and set functions
   float getStep(){return step;}
   void setStep(float = 1e-6);
};

#endif
