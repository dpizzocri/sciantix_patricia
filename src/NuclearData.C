///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.4                         //
//  Year   : 2019                        //
//  Authors: D. Pizzocri and T. Barani   //
//           L. Cognini                  //
///////////////////////////////////////////

#include "NuclearData.h"

// Naming x:cross-section
//        f/c/na: fission/capture (n,y)/ (n,alpha)
//        l: decay rate
//        a/b/e/it: alpha/beta/electronic capture/isomeric transition

// Cross sections (u.d.m.)
double xnaO16(0.0);
double xn2nU238(0.0);
double xn3nU238(0.0);

double xfU234(0.0);
double xcU234(0.0);
double xfU235(0.0);
double xcU235(0.0);
double xfU236(0.0);
double xcU236(0.0);
double xfU237(0.0);
double xcU237(0.0);
double xfU238(0.0);
double xcU238(0.0);
double xfNp237(0.0);
double xcNp237(0.0);
double xfNp238(0.0);
double xcNp238(0.0);
double xfNp239(0.0);
double xcNp239(0.0);
double xfPu238(0.0);
double xcPu238(0.0);
double xfPu239(0.0);
double xcPu239(0.0);
double xfPu240(0.0);
double xcPu240(0.0);
double xfPu241(0.0);
double xcPu241(0.0);
double xfPu242(0.0);
double xcPu242(0.0);
double xfPu243(0.0);
double xcPu243(0.0);
double xfAm241(0.0);
double xcAm241(0.0);
double xfAm242(0.0);
double xcAm242(0.0);
double xfAm242m(0.0);
double xcAm242m(0.0);
double xfAm243(0.0);
double xcAm243(0.0);
double xfAm244(0.0);
double xcAm244(0.0);
double xfCm242(0.0);
double xcCm242(0.0);
double xfCm243(0.0);
double xcCm243(0.0);
double xfCm244(0.0);
double xcCm244(0.0);
double xfCm245(0.0);
double xcCm245(0.0);

// Decay rates (1/s)
double lbTl207(2.42e-03);
double lbTl208(3.78e-03);
double lbPb210(9.90e-10);
double lbPb211(3.20e-04);
double lbPb212(1.81e-05);
double lbPb214(4.31e-04);
double lbBi210(1.60e-06);
double laBi211(9.00e-05);// neglect other decays <1%
double lbBi212(1.22e-04);// equals to lambda_Bi212 * BR_b (=64.06%)
double laBi212(6.86e-05);// equals to lambda_Bi212 * BR_a (=35.94%)
double lbBi214(5.81e-04);// neglect other decays <1%
double laPo210(5.80e-08);
double laPo212(2.32e+08);
double laPo214(4.22e+03);
double laPo215(3.89e+02);// neglect other decays <1%
double laPo216(4.78);
double laPo218(2.24e+02);// neglect other decays <1%
double laRn219(1.75e-01);
double laRn220(1.25e-02);
double laRn222(2.10e-06);
double lbFr223(5.25e-04);// neglect other decays <1%
double laRa223(7.02e-07);
double laRa224(2.19e-06);
double laRa226(1.37e-11);
double lbRa228(3.82e-09);
double lbAc227(9.95e-10);// equals to lambda_Ac227 * BR_b (=98.62%)
double laAc227(1.39e-11);// equals to lambda_Ac227 * BR_a (=1.38%)
double lbAc228(3.13e-05);
double laTh227(4.29e-07);
double laTh228(1.15e-08);
double laTh230(2.91e-13);
double lbTh231(7.54e-06);
double laTh232(1.57e-18);
double lbTh234(3.33e-07);
double laPa231(6.71e-13);
double lbPa234(2.87e-05);
double laU234(8.95e-14);
double laU235(3.12e-17);
double laU236(9.38e-16);// neglect other decays <1%
double lbU237(1.19e-06);
double laU238(4.92e-18);
double laNp237(1.03e-14);// neglect other decays <1%
double lbNp238(3.79e-06);
double lbNp239(3.41e-06);
double laPu238(2.51e-10);// neglect other decays <1%
double laPu239(9.12e-13);// neglect other decays <1%
double laPu240(3.35e-12);// neglect other decays <1%
double lbPu241(1.54e-09);// neglect other decays <1%
double laPu242(5.86e-14);// neglect other decays <1%
double lbPu243(3.89e-05);
double laAm241(5.08e-11);// neglect other decays <1%
double BR_Am241(0.91); // ok for PWR spectrum, need some thoughts on BWR/LMFBR
double lbAm242(9.94e-06); // equals to lambda_Am242 * BR_b (=82.7%)
double leAm242(2.08e-06); // equals to lambda_Am242 * (1-BR_b)
double litAm242m(1.56e-10);// neglect other decays <1%
double laAm243(2.98e-12);// neglect other decays <1%
double lbAm244(4.18e-04);// neglect other decays <1%
double laCm242(4.93e-08);// neglect other decays <1%
double laCm243(7.55e-10);// neglect other decays <1%
double laCm244(1.21e-09);// neglect other decays <1%
double laCm245(2.61e-12);// neglect other decays <1%
