// TIMESTEP.CPP
// Definition of member functions for class TIMESTEP

#include <iostream>
#include <stdlib.h>
#include "Timestep.h" 
using namespace std;

Timestep& Timestep::Instance()
{
   static Timestep only_copy;
   return only_copy;
}

void Timestep::setStep(float st)
{step = st;}


