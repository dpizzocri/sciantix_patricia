///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.4                         //
//  Year   : 2019                        //
//  Authors: S. Altieri                  //
//           D. Pizzocri and T. Barani   //
///////////////////////////////////////////

#include "CrossSectionLookupTable.h"

void CrossSectionLookupTable() {
  burnup = Burn_up[0] / U_UO2;

  b1 = (int)floor(burnup / burnup_width);
  b2 = (int)floor((burnup + burnup_width) / burnup_width);
  e1 = (int)floor((enrichment - e_min) / enrichment_width);
  e2 = (int)floor((enrichment + enrichment_width - e_min) / enrichment_width);

  if (burnup < burnup_discretization[bu_dim - 1]) {

    const double db1 =
        std::abs(burnup - burnup_discretization[b1]) / burnup_width;
    const double de1 =
        std::abs(enrichment - enrichment_discretization[e1]) / enrichment_width;
    const double de2 =
        std::abs(enrichment - enrichment_discretization[e2]) / enrichment_width;
    const double db2 =
        std::abs(burnup - burnup_discretization[b2]) / burnup_width;

    const double area11 = db1 * de1;
    const double area21 = db2 * de1;
    const double area12 = db1 * de2;
    const double area22 = db2 * de2;

    const double norm = area11 + area12 + area21 + area22; // metric norm

    const double weight11 = area22 / norm;
    const double weight21 = area12 / norm;
    const double weight12 = area21 / norm;
    const double weight22 = area11 / norm;

    xnaO16 =
        xsec_na_table[e1][b1] * weight11 + xsec_na_table[e1][b2] * weight21 +
        xsec_na_table[e2][b1] * weight12 + xsec_na_table[e2][b2] * weight22;

    xn2nU238 =
        xsec_n2n_table[e1][b1] * weight11 + xsec_n2n_table[e1][b2] * weight21 +
        xsec_n2n_table[e2][b1] * weight12 + xsec_n2n_table[e2][b2] * weight22;

    xn3nU238 =
        xsec_n3n_table[e1][b1] * weight11 + xsec_n3n_table[e1][b2] * weight21 +
        xsec_n3n_table[e2][b1] * weight12 + xsec_n3n_table[e2][b2] * weight22;

    xfU234 = xsec_fiss_table[0][e1][b1] * weight11 +
             xsec_fiss_table[0][e1][b2] * weight21 +
             xsec_fiss_table[0][e2][b1] * weight12 +
             xsec_fiss_table[0][e2][b2] * weight22;
    xcU234 = xsec_capt_table[0][e1][b1] * weight11 +
             xsec_capt_table[0][e1][b2] * weight21 +
             xsec_capt_table[0][e2][b1] * weight12 +
             xsec_capt_table[0][e2][b2] * weight22;
    xfU235 = xsec_fiss_table[1][e1][b1] * weight11 +
             xsec_fiss_table[1][e1][b2] * weight21 +
             xsec_fiss_table[1][e2][b1] * weight12 +
             xsec_fiss_table[1][e2][b2] * weight22;
    xcU235 = xsec_capt_table[1][e1][b1] * weight11 +
             xsec_capt_table[1][e1][b2] * weight21 +
             xsec_capt_table[1][e2][b1] * weight12 +
             xsec_capt_table[1][e2][b2] * weight22;
    xfU236 = xsec_fiss_table[2][e1][b1] * weight11 +
             xsec_fiss_table[2][e1][b2] * weight21 +
             xsec_fiss_table[2][e2][b1] * weight12 +
             xsec_fiss_table[2][e2][b2] * weight22;
    xcU236 = xsec_capt_table[2][e1][b1] * weight11 +
             xsec_capt_table[2][e1][b2] * weight21 +
             xsec_capt_table[2][e2][b1] * weight12 +
             xsec_capt_table[2][e2][b2] * weight22;
    xfU237 = xsec_fiss_table[3][e1][b1] * weight11 +
             xsec_fiss_table[3][e1][b2] * weight21 +
             xsec_fiss_table[3][e2][b1] * weight12 +
             xsec_fiss_table[3][e2][b2] * weight22;
    xcU237 = xsec_capt_table[3][e1][b1] * weight11 +
             xsec_capt_table[3][e1][b2] * weight21 +
             xsec_capt_table[3][e2][b1] * weight12 +
             xsec_capt_table[3][e2][b2] * weight22;
    xfU238 = xsec_fiss_table[4][e1][b1] * weight11 +
             xsec_fiss_table[4][e1][b2] * weight21 +
             xsec_fiss_table[4][e2][b1] * weight12 +
             xsec_fiss_table[4][e2][b2] * weight22;
    xcU238 = xsec_capt_table[4][e1][b1] * weight11 +
             xsec_capt_table[4][e1][b2] * weight21 +
             xsec_capt_table[4][e2][b1] * weight12 +
             xsec_capt_table[4][e2][b2] * weight22;

    xfNp237 = xsec_fiss_table[5][e1][b1] * weight11 +
              xsec_fiss_table[5][e1][b2] * weight21 +
              xsec_fiss_table[5][e2][b1] * weight12 +
              xsec_fiss_table[5][e2][b2] * weight22;
    xcNp237 = xsec_capt_table[5][e1][b1] * weight11 +
              xsec_capt_table[5][e1][b2] * weight21 +
              xsec_capt_table[5][e2][b1] * weight12 +
              xsec_capt_table[5][e2][b2] * weight22;
    xfNp238 = xsec_fiss_table[6][e1][b1] * weight11 +
              xsec_fiss_table[6][e1][b2] * weight21 +
              xsec_fiss_table[6][e2][b1] * weight12 +
              xsec_fiss_table[6][e2][b2] * weight22;
    xcNp238 = xsec_capt_table[6][e1][b1] * weight11 +
              xsec_capt_table[6][e1][b2] * weight21 +
              xsec_capt_table[6][e2][b1] * weight12 +
              xsec_capt_table[6][e2][b2] * weight22;
    xfNp239 = xsec_fiss_table[7][e1][b1] * weight11 +
              xsec_fiss_table[7][e1][b2] * weight21 +
              xsec_fiss_table[7][e2][b1] * weight12 +
              xsec_fiss_table[7][e2][b2] * weight22;
    xcNp239 = xsec_capt_table[7][e1][b1] * weight11 +
              xsec_capt_table[7][e1][b2] * weight21 +
              xsec_capt_table[7][e2][b1] * weight12 +
              xsec_capt_table[7][e2][b2] * weight22;

    xfPu238 = xsec_fiss_table[8][e1][b1] * weight11 +
              xsec_fiss_table[8][e1][b2] * weight21 +
              xsec_fiss_table[8][e2][b1] * weight12 +
              xsec_fiss_table[8][e2][b2] * weight22;
    xcPu238 = xsec_capt_table[8][e1][b1] * weight11 +
              xsec_capt_table[8][e1][b2] * weight21 +
              xsec_capt_table[8][e2][b1] * weight12 +
              xsec_capt_table[8][e2][b2] * weight22;
    xfPu239 = xsec_fiss_table[9][e1][b1] * weight11 +
              xsec_fiss_table[9][e1][b2] * weight21 +
              xsec_fiss_table[9][e2][b1] * weight12 +
              xsec_fiss_table[9][e2][b2] * weight22;
    xcPu239 = xsec_capt_table[9][e1][b1] * weight11 +
              xsec_capt_table[9][e1][b2] * weight21 +
              xsec_capt_table[9][e2][b1] * weight12 +
              xsec_capt_table[9][e2][b2] * weight22;
    xfPu240 = xsec_fiss_table[10][e1][b1] * weight11 +
              xsec_fiss_table[10][e1][b2] * weight21 +
              xsec_fiss_table[10][e2][b1] * weight12 +
              xsec_fiss_table[10][e2][b2] * weight22;
    xcPu240 = xsec_capt_table[10][e1][b1] * weight11 +
              xsec_capt_table[10][e1][b2] * weight21 +
              xsec_capt_table[10][e2][b1] * weight12 +
              xsec_capt_table[10][e2][b2] * weight22;
    xfPu241 = xsec_fiss_table[11][e1][b1] * weight11 +
              xsec_fiss_table[11][e1][b2] * weight21 +
              xsec_fiss_table[11][e2][b1] * weight12 +
              xsec_fiss_table[11][e2][b2] * weight22;
    xcPu241 = xsec_capt_table[11][e1][b1] * weight11 +
              xsec_capt_table[11][e1][b2] * weight21 +
              xsec_capt_table[11][e2][b1] * weight12 +
              xsec_capt_table[11][e2][b2] * weight22;
    xfPu242 = xsec_fiss_table[12][e1][b1] * weight11 +
              xsec_fiss_table[12][e1][b2] * weight21 +
              xsec_fiss_table[12][e2][b1] * weight12 +
              xsec_fiss_table[12][e2][b2] * weight22;
    xcPu242 = xsec_capt_table[12][e1][b1] * weight11 +
              xsec_capt_table[12][e1][b2] * weight21 +
              xsec_capt_table[12][e2][b1] * weight12 +
              xsec_capt_table[12][e2][b2] * weight22;
    xfPu243 = xsec_fiss_table[13][e1][b1] * weight11 +
              xsec_fiss_table[13][e1][b2] * weight21 +
              xsec_fiss_table[13][e2][b1] * weight12 +
              xsec_fiss_table[13][e2][b2] * weight22;
    xcPu243 = xsec_capt_table[13][e1][b1] * weight11 +
              xsec_capt_table[13][e1][b2] * weight21 +
              xsec_capt_table[13][e2][b1] * weight12 +
              xsec_capt_table[13][e2][b2] * weight22;

    xfAm241 = xsec_fiss_table[14][e1][b1] * weight11 +
              xsec_fiss_table[14][e1][b2] * weight21 +
              xsec_fiss_table[14][e2][b1] * weight12 +
              xsec_fiss_table[14][e2][b2] * weight22;
    xcAm241 = xsec_capt_table[14][e1][b1] * weight11 +
              xsec_capt_table[14][e1][b2] * weight21 +
              xsec_capt_table[14][e2][b1] * weight12 +
              xsec_capt_table[14][e2][b2] * weight22;
    xfAm242 = xsec_fiss_table[15][e1][b1] * weight11 +
              xsec_fiss_table[15][e1][b2] * weight21 +
              xsec_fiss_table[15][e2][b1] * weight12 +
              xsec_fiss_table[15][e2][b2] * weight22;
    xcAm242 = xsec_capt_table[15][e1][b1] * weight11 +
              xsec_capt_table[15][e1][b2] * weight21 +
              xsec_capt_table[15][e2][b1] * weight12 +
              xsec_capt_table[15][e2][b2] * weight22;
    xfAm242m = xsec_fiss_table[16][e1][b1] * weight11 +
               xsec_fiss_table[16][e1][b2] * weight21 +
               xsec_fiss_table[16][e2][b1] * weight12 +
               xsec_fiss_table[16][e2][b2] * weight22;
    xcAm242m = xsec_capt_table[16][e1][b1] * weight11 +
               xsec_capt_table[16][e1][b2] * weight21 +
               xsec_capt_table[16][e2][b1] * weight12 +
               xsec_capt_table[16][e2][b2] * weight22;
    xfAm243 = xsec_fiss_table[17][e1][b1] * weight11 +
              xsec_fiss_table[17][e1][b2] * weight21 +
              xsec_fiss_table[17][e2][b1] * weight12 +
              xsec_fiss_table[17][e2][b2] * weight22;
    xcAm243 = xsec_capt_table[17][e1][b1] * weight11 +
              xsec_capt_table[17][e1][b2] * weight21 +
              xsec_capt_table[17][e2][b1] * weight12 +
              xsec_capt_table[17][e2][b2] * weight22;
    xfAm244 = xsec_fiss_table[18][e1][b1] * weight11 +
              xsec_fiss_table[18][e1][b2] * weight21 +
              xsec_fiss_table[18][e2][b1] * weight12 +
              xsec_fiss_table[18][e2][b2] * weight22;
    xcAm244 = xsec_capt_table[18][e1][b1] * weight11 +
              xsec_capt_table[18][e1][b2] * weight21 +
              xsec_capt_table[18][e2][b1] * weight12 +
              xsec_capt_table[18][e2][b2] * weight22;

    xfCm242 = xsec_fiss_table[19][e1][b1] * weight11 +
              xsec_fiss_table[19][e1][b2] * weight21 +
              xsec_fiss_table[19][e2][b1] * weight12 +
              xsec_fiss_table[19][e2][b2] * weight22;
    xcCm242 = xsec_capt_table[19][e1][b1] * weight11 +
              xsec_capt_table[19][e1][b2] * weight21 +
              xsec_capt_table[19][e2][b1] * weight12 +
              xsec_capt_table[19][e2][b2] * weight22;
    xfCm243 = xsec_fiss_table[20][e1][b1] * weight11 +
              xsec_fiss_table[20][e1][b2] * weight21 +
              xsec_fiss_table[20][e2][b1] * weight12 +
              xsec_fiss_table[20][e2][b2] * weight22;
    xcCm243 = xsec_capt_table[20][e1][b1] * weight11 +
              xsec_capt_table[20][e1][b2] * weight21 +
              xsec_capt_table[20][e2][b1] * weight12 +
              xsec_capt_table[20][e2][b2] * weight22;
    xfCm244 = xsec_fiss_table[21][e1][b1] * weight11 +
              xsec_fiss_table[21][e1][b2] * weight21 +
              xsec_fiss_table[21][e2][b1] * weight12 +
              xsec_fiss_table[21][e2][b2] * weight22;
    xcCm244 = xsec_capt_table[21][e1][b1] * weight11 +
              xsec_capt_table[21][e1][b2] * weight21 +
              xsec_capt_table[21][e2][b1] * weight12 +
              xsec_capt_table[21][e2][b2] * weight22;
    xfCm245 = xsec_fiss_table[22][e1][b1] * weight11 +
              xsec_fiss_table[22][e1][b2] * weight21 +
              xsec_fiss_table[22][e2][b1] * weight12 +
              xsec_fiss_table[22][e2][b2] * weight22;
    xcCm245 = xsec_capt_table[22][e1][b1] * weight11 +
              xsec_capt_table[22][e1][b2] * weight21 +
              xsec_capt_table[22][e2][b1] * weight12 +
              xsec_capt_table[22][e2][b2] * weight22;
  }

  else {

    double weight11 = 0.0;
    double weight22 = 0.0;
    const double dist11 =
        std::abs(enrichment - enrichment_discretization[e1]) / enrichment_width;
    const double dist22 =
        std::abs(enrichment - enrichment_discretization[e2]) / enrichment_width;
    const double norm = dist11 + dist22; // metric norm

    weight11 = dist22 / norm;
    weight22 = dist11 / norm;

    xnaO16 = xsec_na_table[e1][bu_dim - 1] * weight11 +
             xsec_na_table[e2][bu_dim - 1] * weight22;

    xn2nU238 = xsec_n2n_table[e1][bu_dim - 1] * weight11 +
               xsec_n2n_table[e2][bu_dim - 1] * weight22;

    xn2nU238 = xsec_n3n_table[e1][bu_dim - 1] * weight11 +
               xsec_n3n_table[e2][bu_dim - 1] * weight22;

    xfU234 = xsec_fiss_table[0][e1][bu_dim - 1] * weight11 +
             xsec_fiss_table[0][e2][bu_dim - 1] * weight22;
    xcU234 = xsec_capt_table[0][e1][bu_dim - 1] * weight11 +
             xsec_capt_table[0][e2][bu_dim - 1] * weight22;
    xfU235 = xsec_fiss_table[1][e1][bu_dim - 1] * weight11 +
             xsec_fiss_table[1][e2][bu_dim - 1] * weight22;
    xcU235 = xsec_capt_table[1][e1][bu_dim - 1] * weight11 +
             xsec_capt_table[1][e2][bu_dim - 1] * weight22;
    xfU236 = xsec_fiss_table[2][e1][bu_dim - 1] * weight11 +
             xsec_fiss_table[2][e2][bu_dim - 1] * weight22;
    xcU236 = xsec_capt_table[2][e1][bu_dim - 1] * weight11 +
             xsec_capt_table[2][e2][bu_dim - 1] * weight22;
    xfU237 = xsec_fiss_table[3][e1][bu_dim - 1] * weight11 +
             xsec_fiss_table[3][e2][bu_dim - 1] * weight22;
    xcU237 = xsec_capt_table[3][e1][bu_dim - 1] * weight11 +
             xsec_capt_table[3][e2][bu_dim - 1] * weight22;
    xfU238 = xsec_fiss_table[4][e1][bu_dim - 1] * weight11 +
             xsec_fiss_table[4][e2][bu_dim - 1] * weight22;
    xcU238 = xsec_capt_table[4][e1][bu_dim - 1] * weight11 +
             xsec_capt_table[4][e2][bu_dim - 1] * weight22;

    xfNp237 = xsec_fiss_table[5][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[5][e2][bu_dim - 1] * weight22;
    xcNp237 = xsec_capt_table[5][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[5][e2][bu_dim - 1] * weight22;
    xfNp238 = xsec_fiss_table[6][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[6][e2][bu_dim - 1] * weight22;
    xcNp238 = xsec_capt_table[6][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[6][e2][bu_dim - 1] * weight22;
    xfNp239 = xsec_fiss_table[7][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[7][e2][bu_dim - 1] * weight22;
    xcNp239 = xsec_capt_table[7][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[7][e2][bu_dim - 1] * weight22;

    xfPu238 = xsec_fiss_table[8][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[8][e2][bu_dim - 1] * weight22;
    xcPu238 = xsec_capt_table[8][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[8][e2][bu_dim - 1] * weight22;
    xfPu239 = xsec_fiss_table[9][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[9][e2][bu_dim - 1] * weight22;
    xcPu239 = xsec_capt_table[9][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[9][e2][bu_dim - 1] * weight22;
    xfPu240 = xsec_fiss_table[10][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[10][e2][bu_dim - 1] * weight22;
    xcPu240 = xsec_capt_table[10][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[10][e2][bu_dim - 1] * weight22;
    xfPu241 = xsec_fiss_table[11][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[11][e2][bu_dim - 1] * weight22;
    xcPu241 = xsec_capt_table[11][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[11][e2][bu_dim - 1] * weight22;
    xfPu242 = xsec_fiss_table[12][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[12][e2][bu_dim - 1] * weight22;
    xcPu242 = xsec_capt_table[12][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[12][e2][bu_dim - 1] * weight22;
    xfPu243 = xsec_fiss_table[13][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[13][e2][bu_dim - 1] * weight22;
    xcPu243 = xsec_capt_table[13][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[13][e2][bu_dim - 1] * weight22;

    xfAm241 = xsec_fiss_table[14][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[14][e2][bu_dim - 1] * weight22;
    xcAm241 = xsec_capt_table[14][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[14][e2][bu_dim - 1] * weight22;
    xfAm242 = xsec_fiss_table[15][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[15][e2][bu_dim - 1] * weight22;
    xcAm242 = xsec_capt_table[15][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[15][e2][bu_dim - 1] * weight22;
    xfAm242m = xsec_fiss_table[16][e1][bu_dim - 1] * weight11 +
               xsec_fiss_table[16][e2][bu_dim - 1] * weight22;
    xcAm242m = xsec_capt_table[16][e1][bu_dim - 1] * weight11 +
               xsec_capt_table[16][e2][bu_dim - 1] * weight22;
    xfAm243 = xsec_fiss_table[17][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[17][e2][bu_dim - 1] * weight22;
    xcAm243 = xsec_capt_table[17][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[17][e2][bu_dim - 1] * weight22;
    xfAm244 = xsec_fiss_table[18][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[18][e2][bu_dim - 1] * weight22;
    xcAm244 = xsec_capt_table[18][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[18][e2][bu_dim - 1] * weight22;

    xfCm242 = xsec_fiss_table[19][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[19][e2][bu_dim - 1] * weight22;
    xcCm242 = xsec_capt_table[19][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[19][e2][bu_dim - 1] * weight22;
    xfCm243 = xsec_fiss_table[20][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[20][e2][bu_dim - 1] * weight22;
    xcCm243 = xsec_capt_table[20][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[20][e2][bu_dim - 1] * weight22;
    xfCm244 = xsec_fiss_table[21][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[21][e2][bu_dim - 1] * weight22;
    xcCm244 = xsec_capt_table[21][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[21][e2][bu_dim - 1] * weight22;
    xfCm245 = xsec_fiss_table[22][e1][bu_dim - 1] * weight11 +
              xsec_fiss_table[22][e2][bu_dim - 1] * weight22;
    xcCm245 = xsec_capt_table[22][e1][bu_dim - 1] * weight11 +
              xsec_capt_table[22][e2][bu_dim - 1] * weight22;
  }
}
