// MONO3_0.CPP
// Definicion de las funciones miembro de la clase Mono3
// Esta clase representa un monomero
// Multiples enzimas, reaccion reversible
// La variable "step" es una variable global

#include <iostream>
#include<stdlib.h>
#include "Mono3.h" 
#include "assert.h" 
#include "Timestep.h"
using namespace std;

#define VSIM 10.3e-18	// volumen de la simulacion
#define NAVG 6.02e23 	// numero de Avogadro


void Mono3::setenz(const float vmax_d, const float vmax_r, const float km_d, const float km_r, const float mu) 
{
   // obtiene paso de la simulacion desde singleton instanciado en main()
   float step = Timestep::Instance().getStep();
   
   phase = 0.0;

   if(vmax_d != 0)
      tau_d = 60/(vmax_d*mu*1.0e-3);
   else
      tau_d = 1e60;

   if(vmax_r != 0)
      tau_r = 60/(vmax_r*mu*1.0e-3);
   else
      tau_r = 1e60;

   nM_d = km_d*VSIM*NAVG*1e-6;
   nM_r = km_r*VSIM*NAVG*1e-6;
   //cout << "\n tau_d es " << tau_d << endl;
   //cout << "\n tau_r es " << tau_r << endl;
   dir = 0;
   //cout << "\n tau/step es " << tau/step << endl;
   //cout << "\n nM es " << nM << endl;
   assert(tau_d > step);	
   assert(tau_r > step);	
}

void Mono3::advancePhase(int& nS, int& nP, int& nS_out, int& nP_out, float& p1, float& p2)
{ 
   // obtiene paso de la simulacion desde singleton instanciado en main()
   float step = Timestep::Instance().getStep();
   
   float z, p, p_d, p_r, z1, z2;

   if(phase == 0){

      // Calcula probabilidad
      p_d = (step/tau_d)*((float)nS/(float)nM_d);
      p_r = (step/tau_r)*((float)nP/(float)nM_r);
      p1 = p_d;
      p2 = p_r;
      /*if(dir != 0){
         cout << "\np_d es " << p_d << endl;
         //cout << "\nmiro es " <<  (step/tau_d) << endl;
         cout << "\np_r es " << p_r << endl;
      }*/
      //************p1********p2************

      /*z = drand48();
          
      if(p_d != 0 && p_r != 0){     // la enzima es bidireccional
         if(dir == 0){
            if(p_d > p_r){
               dir = 1;
               p = p_d;
            }
            else{
               dir = -1;
               p = p_r;
            }
         }
         else if(dir == 1){
            dir = -1;
            p = p_r;
         }
         else if(dir == -1){
            dir = 1;
            p = p_d;
         }
      }
      else if(p_r == 0){         // la enzima es unidireccional, reaccion directa
         p = p_d;
         dir = 1;
      }
      else if(p_d == 0){        // la enzima es unidireccional, reaccion inversa
         p = p_r;
         dir = -1;
      }*/

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

      if(z < p && dir == 1){
         phase += step;
         //nS--;
         return;
      }
      else if(z < p && dir == -1){
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
   }
   else if(dir == -1 && phase >= tau_r){
      nS_out++;
      phase = 0.0;
      dir = 0;
   }
}

float Mono3::getPhase()
   {return phase;}

