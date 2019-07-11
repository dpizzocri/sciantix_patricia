///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.4                         //
//  Year   : 2019                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////
// Naming x:cross-section
//        f/c: fission/capture (n,y)
//        l: decay rate
//        a/b/e: alpha/beta/electronic capture

// Cross sections
extern double xnaO16;
extern double xn2nU238;
extern double xn3nU238;

extern double xfU234;
extern double xcU234;
extern double xfU235;
extern double xcU235;
extern double xfU236;
extern double xcU236;
extern double xfU237;
extern double xcU237;
extern double xfU238;
extern double xcU238;
extern double xfNp237;
extern double xcNp237;
extern double xfNp238;
extern double xcNp238;
extern double xfNp239;
extern double xcNp239;
extern double xfPu238;
extern double xcPu238;
extern double xfPu239;
extern double xcPu239;
extern double xfPu240;
extern double xcPu240;
extern double xfPu241;
extern double xcPu241;
extern double xfPu242;
extern double xcPu242;
extern double xfPu243;
extern double xcPu243;
extern double xfAm241;
extern double xcAm241;
extern double xfAm242;
extern double xcAm242;
extern double xfAm242m;
extern double xcAm242m;
extern double xfAm243;
extern double xcAm243;
extern double xfAm244;
extern double xcAm244;
extern double xfCm242;
extern double xcCm242;
extern double xfCm243;
extern double xcCm243;
extern double xfCm244;
extern double xcCm244;
extern double xfCm245;
extern double xcCm245;

// Decay rates
extern double lbTl207;
extern double lbTl208;
extern double lbPb210;
extern double lbPb211;
extern double lbPb212;
extern double lbPb214;
extern double lbBi210;
extern double laBi211;// neglect other decays <1%
extern double lbBi212;// equals to lambda_Bi212 * BR_b (=64.06%)
extern double laBi212;// equals to lambda_Bi212 * BR_a (=35.94%)
extern double lbBi214;// neglect other decays <1%
extern double laPo210;
extern double laPo212;
extern double laPo214;
extern double laPo215;// neglect other decays <1%
extern double laPo216;
extern double laPo218;// neglect other decays <1%
extern double laRn219;
extern double laRn220;
extern double laRn222;
extern double lbFr223;// neglect other decays <1%
extern double laRa223;
extern double laRa224;
extern double laRa226;
extern double lbRa228;
extern double lbAc227;// equals to lambda_Ac227 * BR_b (=98.62%)
extern double laAc227;// equals to lambda_Ac227 * BR_a (=1.38%)
extern double lbAc228;
extern double laTh227;
extern double laTh228;
extern double laTh230;
extern double lbTh231;
extern double laTh232;
extern double lbTh234;
extern double laPa231;
extern double lbPa234;
extern double laU234;
extern double laU235;
extern double laU236;// neglect other decays <1%
extern double lbU237;
extern double laU238;
extern double laNp237;// neglect other decays <1%
extern double lbNp238;
extern double lbNp239;
extern double laPu238;// neglect other decays <1%
extern double laPu239;// neglect other decays <1%
extern double laPu240;// neglect other decays <1%
extern double lbPu241;// neglect other decays <1%
extern double laPu242;// neglect other decays <1%
extern double lbPu243;
extern double laAm241;// neglect other decays <1%
extern double BR_Am241; // ok for PWR spectrum, need some thoughts on BWR/LMFBR
extern double lbAm242; // equals to lambda_Am242 * BR_b (=82.7%)
extern double leAm242; // equals to lambda_Am242 * (1-BR_b)
extern double litAm242m;// neglect other decays <1%
extern double laAm243;// neglect other decays <1%
extern double lbAm244;// neglect other decays <1%
extern double laCm242;// neglect other decays <1%
extern double laCm243;// neglect other decays <1%
extern double laCm244;// neglect other decays <1%
extern double laCm245;// neglect other decays <1%
