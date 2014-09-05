// MONO5.CPP
// Definicion de las funciones miembro de la clase Mono5
// Esta clase representa un monomero
// Multiples enzimas, reaccion reversible

#include <iostream>
#include <stdlib.h>
#include "Mono5.h" 
#include "assert.h" 
#include "Timestep.h"
using namespace std;

extern const float VSIM = 10.3e-18, NAVG = 6.02e23;

// define parametros para el monomero
void Mono5::setenz(const float vmax_d, const float vmax_r, const float km_d, const float km_r, const float mu) 
{
   // obtiene paso de la simulacion desde singleton instanciado en main()
   float step = Timestep::Instance().getStep();
  
   // inicializa fase del monomero 
   phase = 0.0;

   // calcula tiempo de recambio
   if(vmax_d != 0)
      tau_d = 60/(vmax_d*mu*1.0e-3);
   else
      tau_d = 1e60;     // reaccion unidireccional

   if(vmax_r != 0)
      tau_r = 60/(vmax_r*mu*1.0e-3);
   else
      tau_r = 1e60;	// reaccion unidireccional

   assert(tau_d > step);	
   assert(tau_r > step);	

   // calcula numero de moleculas correspondiente a Km
   nM_d = km_d*VSIM*NAVG*1e-6;
   nM_r = km_r*VSIM*NAVG*1e-6;

   // inicializa direccion de la reaccion
   dir = 0;

   // inicializa factores de interaccion reaccion directa e inversa
   alpha_d = 1;
   alpha_r = 1;
}

// Avance de fase del monomero
void Mono5::advancePhase(int& nS, int& nP, int& nS_out, int& nP_out)
{ 
   // obtiene paso de la simulacion desde singleton instanciado en main()
   float step = Timestep::Instance().getStep();
   
   float p, p_d, p_r, z1, z2;

   // monomero no ha adherido sustrato
   if(phase == 0){

      // Calcula probabilidad de adhesion de sustrato
      p_d = alpha_d*(step/tau_d)*nS/nM_d;
      p_r = alpha_r*(step/tau_r)*nP/nM_r;

      //cout << "\np_d " << p_d << endl;
      //cout << "\np_r = " << p_r << endl;
 
      // determina direccion de la reaccion y adhiere sustrato
      z1 = drand48();
      z2 = drand48();

      if(z1 < p_d && z2 > p_r){
         dir = 1;
         p = p_d;
      }
      else if(z1 > p_d && z2 < p_r){
         dir = -1;
         p = p_r;
      }
      else
         return;

      // avance de la reaccion
      if(dir == 1){
         phase += step;
         //nS--;
         return;
      }
      else if(dir == -1){
         phase += step;
         //nP--;
         return;
      }
      else
         return;
   }
   else if(dir == 1 && phase > 0 && phase < tau_d)
      phase += step;
   else if(dir == -1 && phase > 0 && phase < tau_r)
      phase += step;
   else if(dir == 1 && phase >= tau_d)
   {
      nP_out++;
      phase = 0.0;
      dir = 0;
      //cout << "\nAdelante" << endl; 
   }
   else if(dir == -1 && phase >= tau_r){
      nS_out++;
      phase = 0.0;
      dir = 0;
      //cout << "\nAtras" << endl; 
   }
}


