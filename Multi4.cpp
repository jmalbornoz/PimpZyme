// MULTI4.CPP
// Definicion de las funciones miembro de la clase MULTI4
// Esta clase representa un multimero reversible
// La direccion de la reaccion en las subunidades es determinada
// por la primera subunidad en adquirir sustrato

#include <iostream>
#include <stdlib.h>
#include "Multi4.h" 
#include "Mono6.h"
#include "Timestep.h"
#include "assert.h" 
#include <math.h>
using namespace std; 

// define parametros del multimero
// N, vmax_d, vmax_r, S_05_d, S_05_r, a_dir, a_rev, MM
void Multi4::setMulti(int Nsub, float v_d, float v_r, float S_05_d, float S_05_r, float ad, float ar, float m)
{
    float MM;

    // numero de subunidades
    N = Nsub;

    // peso molecular dividido entre numero de subunidades
    MM = m/Nsub;

    // factores de interaccion, reacciones directa e inversa
    a_dir = ad;
    a_rev = ar;

    float k_d = S_05_d*pow(a_dir,(1 + (N - 3.0)/2.0));
    float k_r = S_05_r*pow(a_rev,(1 + (N - 3.0)/2.0));
   
    // declara arreglo de arreglos apuntando a monomeros 
    multi = new Mono6 *[N];

    for(int i = 0; i < N; i++){
       multi[i] = new Mono6; 
       multi[i]->setenz(v_d, v_r, k_d, k_r, MM); 
    }

}

// Avance de fase del multimero
void Multi4::advanceMulti(int& nS, int& nP, int& nS_out, int& nP_out)
{ 
   int sum = 0;

   // determina sentido de la reaccion
   for(int i = 1; i < N; i++)
      sum += multi[i]->getDir();

   cout << "\nsum = " << sum << endl;

   // hace que las demas subunidades sigan el mismo sentido
   if(sum == 1 || sum == -1)
      for(int i = 1; i < N; i++)
          if(multi[i]->getDir() == 0)
              multi[i]->setDir(sum);
	    
   // determina cuantas subunidades estan ocupadas
   float f = 1;
   for(int j = 0; j < N; j++)
      if(multi[j]->getPhase() > 0)
         f *=a_dir;

   for(int i = 0; i < N; i++){
      multi[i]->setAlpha(f,f);
      multi[i]->advancePhase(nS, nP, nS_out, nP_out);
   }

   /*int count = 0;
   int direction;
   for(int j = 0; j < N; j++)
      if(multi[j]->getPhase() > 0){
         if(count == 0){
             direction = multi[j]->getDir();
             ++count;
             //cout << "\ndir = " << direction << endl;
         } 
         f *=a_dir;
   }
   

   for(int i = 0; i < N; i++){
      if(direction == 1)
         multi[i]->setAlpha(f,0);
      else if(direction == -1)
         multi[i]->setAlpha(0,f); 
      multi[i]->advancePhase(nS, nP, nS_out, nP_out);
   }*/

}

