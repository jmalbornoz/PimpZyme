// MULTI4.H
// Declaracion de la clase MULTI4
// Las funciones miembro estan definidas en MULTI4.CPP
// Multimero

#include "Mono6.h"

// Previene inclusiones multiples del archivo de cabecera
#ifndef _MULTI4_H_
#define _MULTI4_H_

class Multi4{
public:
   // constructor por defecto: permite definir arreglos de multimeros
   Multi4(){};
   // destructor
   ~Multi4(){delete [] multi;}
   // define parametros del multimero
   // N, vmax_d, vmax_r, S_05_d, S_05_r, a_dir, a_rev, MM
   void setMulti(int = 4, float = 1, float = 0, float = 1, float = 1e6, float = 1, float = 1, float = 1);
   // avance de fase del multimero   
   // &nS, &nP, &nS_out, &nP_out
   void advanceMulti(int &, int &, int &, int &);
private:
   int N;
   float a_dir, a_rev;
   Mono6** multi;
};

#endif
