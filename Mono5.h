// MON05.H
// Declaration for class MONO
// Member functions declared in MONO5.CPP
// Multiple enzymes, reversible reaction
//
//
//

// Previene inclusiones multiples del archivo de cabecera
#ifndef _MONO5_H_
#define _MONO5_H_

class Mono5 {
public:
   // constructor por defecto, permite construir arreglos de monomeros
   Mono5(){};	
   // define parametros para el monomero
   // vmax_d, vmax_r, km_d, km_r, mu
   void setenz(const float = 1.0, const float = 1.0, const float = 1.0, const float = 1.0, const float = 1.0);
   // avance de fase del monomero
   // &nS, &nP, &nS_out, &nP_out
   void advancePhase(int &, int &, int &, int &);
   // define factores de interaccion
   inline void setAlpha(const float&  a = 1, const float& b = 1){alpha_d = a; alpha_r = b;};
   //inline float const getAlpha_d(){return alpha_d;}
   //inline float const getAlpha_d(){return alpha_r;}
   inline float getPhase() const {return phase;}
   inline int getDir() const {return dir;}
private:
//protected:  
   float phase;
   float tau_d;
   float tau_r;
   float alpha_d;
   float alpha_r;
   int nM_d;
   int nM_r;
   int dir;
};

#endif
