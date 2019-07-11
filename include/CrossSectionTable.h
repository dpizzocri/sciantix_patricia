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

extern int b1;
extern int b2;
extern int e1;
extern int e2;
extern int e_dim;
extern int bu_dim;
extern double e_min;
extern double burnup;
extern double enrichment;
extern double burnup_width;
extern double enrichment_width;
extern double burnup_discretization[31];
extern double enrichment_discretization[6];

extern double xsec_fiss_table[23][6][31];
extern double xsec_capt_table[23][6][31];
extern double xsec_na_table[6][31];
extern double xsec_n2n_table[6][31];
extern double xsec_n3n_table[6][31];

extern const double xsec_fiss_table_UO2_PWR[21][5][31];
extern const double xsec_capt_table_UO2_PWR[21][5][31];
extern const double xsec_na_table_UO2_PWR[5][31];

extern const double xsec_fiss_table_MOX_PWR[23][6][31];
extern const double xsec_capt_table_MOX_PWR[23][6][31];
extern const double xsec_na_table_MOX_PWR[6][31];
extern const double xsec_n2n_table_MOX_PWR[6][31];
extern const double xsec_n3n_table_MOX_PWR[6][31];

extern const double xsec_fiss_table_MOX_LFR[21][6][31];
extern const double xsec_capt_table_MOX_LFR[21][6][31];
extern const double xsec_na_table_MOX_LFR[6][31];
