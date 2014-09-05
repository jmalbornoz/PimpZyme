// MULTI1.CPP
// Definicion de las funciones miembro de la clase MULTI1
// Esta clase representa un monomero
// Multiples enzimas, reaccion reversible

#include <iostream>
#include <stdlib.h>
#include "Multi1.h" 
#include "Mono5.h"
#include "Timestep.h"
#include "assert.h" 
#include <math.h>
using namespace std; 

// define parametros del multimero
// N, vmax_d, vmax_r, S_05_d, S_05_r, a_dir, a_rev, MM
void Multi1::setMulti(int Nsub, float v_d, float v_r, float S_05_d, float S_05_r, float ad, float ar, float m)
{
    float MM;

    // numero de subunidades
    N = Nsub;

    // peso molecular dividido entre numero de subunidades
    MM = m/Nsub;

    // factores de interaccion, reacciones directa e inversa
    a_dir = ad;
    a_rev = ar;

    float k_d = S_05_d*pow(a_dir, 1.5);
    float k_r = S_05_r*pow(a_rev, 1.5);
   
    // declara arreglo de arreglos apuntando a monomeros 
    multi = new Mono5 *[N];

    for(int i = 0; i < N; i++){
       multi[i] = new Mono5; 
       multi[i]->setenz(v_d, v_r, k_d, k_r, MM); 
    }

}

// Avance de fase del multimero
void Multi1::advanceMulti(int& nS, int& nP, int& nS_out, int& nP_out)
{ 
 
   // determina cuantas subunidades estan ocupadas
   float f = 1;
   for(int j = 0; j < N; j++)
      if(multi[j]->getPhase() > 0)
         f *=a_dir;
   
   for(int i = 0; i < N; i++){
      multi[i]->setAlpha(f,1); 
      multi[i]->advancePhase(nS, nP, nS_out, nP_out);
   }

}

