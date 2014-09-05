// MON03.H
// Declaration for class MONO
// Member functions declared in MONO3.CPP
// Multiple enzymes, reversible reaction
//
// Jose M Albornoz
// May 2009

// Previene inclusiones multiples del archivo de cabecera
#ifndef _MONO3_H_
#define _MONO3_H_

class Mono3 {
public:
   // vmax_d, vmax_r, km_d, km_r, mu
   void setenz(const float = 1.0, const float = 1.0, const float = 1.0, const float = 1.0, const float = 1.0);
   // &nS, &nP, &nS_out, &nP_out, &p1, &p2)
   void advancePhase(int &, int &, int &, int &, float &, float &);
   float getPhase();
private:
   float phase;
   //float step;
   float tau_d;
   float tau_r;
   int nM_d;
   int nM_r;
   int dir;
};

#endif
