// Simulacion de una reaccion enzimatica simple
// Caso bidireccional
// JM Albornoz Marzo 2011

// Maidenhead, 1 de Octubre 2011
// Monomero bidireccional listo
// Paso de tiempo definido en singleton
// Multimero

#include <iostream>
using std::cerr;
using std::endl;
using namespace std;

#include<fstream>
using std::ofstream;
#include <iomanip>
#include <cstdlib>
#include "Mono6.h" 
#include "Multi4.h"
#include "Timestep.h"
//#include <stdlib.h>
#include <time.h>
#include <math.h>

const float VSIM = 10.3e-18, NAVG = 6.02e23;

void rand_init();

main()
{
   float Vmax_dir = 8000.0, Vmax_rev = 8000.0, S_05_dir = 50.0, S_05_rev = 50.0, Mu = 40000.0, S, P;
   float vel_dir, vel_rev, v_teor, v_hill, m_enz, a;
   int n_S, n_P, nP_prod, nS_prod;
   
   const int niter = 500000, NENZ = 20, Nsub = 4;
   const float DT = 1.0e-6;
   const float tiempo = DT*niter;

   // Declara singleton con paso de tiempo
   Timestep::Instance().setStep(DT); 

   // Cambia semilla generador de numeros aleatorios   
   rand_init();

   // Abre archivos de salida
   ofstream myfile;
   myfile.open ("sim0.dat");

   myfile.setf(ios::showpoint);
   myfile.precision(6);
   myfile.setf(ios::fixed, ios::floatfield);

   // Declara arreglo de punteros a multimeros
   Multi4 enz[NENZ];

   // factor de interaccion del multimero
   a = 15;
   float h = 4;

   // Inicializa multimeros
   // N, vmax_d, vmax_r, S_05_d, S_05_r, a_dir, a_rev, MM
   for(int i = 0; i < NENZ; i++)
      enz[i].setMulti(Nsub, Vmax_dir, Vmax_rev, S_05_dir, S_05_rev, a, a, Mu);

   // Numero de moleculas de sustrato
   cout << "\n tiempo es " << tiempo << endl;

   // Masa de la enzima
   m_enz = NENZ*Mu*1.e3/NAVG;

   // Calculo de Ks
   float Ks = S_05_dir*pow(a, 1.5);
   cout << "\nS_05 es " << S_05_dir << endl;
   cout << "\nKs es " << Ks << endl;

   S = 0;	// Concentracion de sustrato en micromolares
   P = 50; 	// Concentracion de producto en micromolares
   float DeltaS = 1;   // incremento sustrato, micromolares
   float Smax = 180;   // maxima concentracion de sustrato, micromolares
   while(S <= Smax){

         n_P = P*1e-6*VSIM*NAVG;
         n_S = S*1e-6*VSIM*NAVG; // ADD
         
         nS_prod = 0;
         nP_prod = 0;
         for(int j = 0; j < niter; j++)
            for(int k = 0; k < NENZ; k++)
               enz[k].advanceMulti(n_S, n_P, nS_prod, nP_prod);

         vel_dir = nP_prod*1.e3*60./(NENZ*Mu*tiempo);		// Velocity in micromol/min-mg
         vel_rev = nS_prod*1.e3*60./(NENZ*Mu*tiempo);		// Velocity in micromol/min-mg

         //v_hill = Vmax_dir*pow(S,4.0)/(pow(S_05_dir,4.0) + pow(S,4.0));
         //v_teor = Vmax_dir*(S/Ks + 3.0*a*pow(S/Ks,2.0) + 3.0*pow(a,2.0)*b*pow(S/Ks,3.0) 
			   //+ pow(a,3.0)*pow(b,2.0)*c*pow(S/Ks,4.0))/(1.0 + 4.0*S/Ks + 6.0*a*pow(S/Ks,2.0)
			   //+ 4.0*pow(a,2.0)*b*pow(S/Ks,3.0) + pow(a,3.0)*pow(b,2.0)*c*pow(S/Ks,4.0));
         float sigma = S/S_05_dir;
         float pi = P/S_05_rev;
         float K = Vmax_dir*S_05_rev/(Vmax_rev*S_05_dir);
         float Gamma = P/S;
         float v_hill_rev = Vmax_dir*sigma*(1.0 - Gamma/K)*pow(sigma + pi, h - 1)/(1 + pow(sigma + pi, h));

         //cout << v_hill_rev << endl;

         
         myfile << S/Ks << '\t' << vel_dir - vel_rev << '\t' << v_hill_rev << '\t' << vel_dir <<  '\t' << vel_rev << endl;
         //myfile << n << '\t' << vel_dir - vel_rev << '\t' << v_teor << endl;
         //myfile << n << '\t' << nP_prod - nS_prod << '\t' << v_teor*Mu/60e3 << '\t' << nP_prod << '\t' << nS_prod << '\t' << (Vmax_dir*S/Km_dir)*Mu/((1 + S/Km_dir + P/Km_rev)*60e3) << '\t' <<  (Vmax_rev*P/Km_rev)*Mu/((1 + S/Km_dir + P/Km_rev)*60e3) << endl;
         //myfile << n << '\t' << vel_dir - vel_rev << '\t' << v_teor << '\t' << nP_prod << '\t' << nS_prod << endl;
         //n++;
         S += DeltaS;
   }
   myfile.close();
}


//************************************************************************

// Inicializa generador de numeros aleatorios 
void rand_init()
{
	int seed;
	time_t timenow;
	time(&timenow);
	seed=timenow % 100000;
        //printf("\nLa semilla es %d",seed);
	srand48(seed);
}

//************************************************************************



