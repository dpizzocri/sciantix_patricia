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

#include "CrossSectionChooser.h"

void CrossSectionChooser() {
  switch (ifuel_reactor_type) {
  // UO2 & PWR
  case 0:
    e_dim = 5;
    bu_dim = 31;
    e_min = 1;
    enrichment = Sciantix_variables[91];
    burnup_width = 5.0 / U_UO2;
    enrichment_width = 1.0;

    for (int b = 0; b < bu_dim; b++) {
      burnup_discretization[b] = burnup_width * b;
    }
    for (int e = 0; e < e_dim; e++) {
      enrichment_discretization[e] = e_min + enrichment_width * double(e);
    }

    for (int i = 0; i < 21; i++) {
      for (int j = 0; j < e_dim; j++) {
        for (int z = 0; z < bu_dim; z++) {
          xsec_fiss_table[i][j][z] = xsec_fiss_table_UO2_PWR[i][j][z];
          xsec_capt_table[i][j][z] = xsec_capt_table_UO2_PWR[i][j][z];
        }
      }
    }

    for (int j = 0; j < e_dim; j++) {
      for (int z = 0; z < bu_dim; z++) {
        xsec_na_table[j][z] = xsec_na_table_UO2_PWR[j][z];
      }
    }
    break;
  // MOX & PWR
  case 1:
    e_dim = 6;
    bu_dim = 31;
    e_min = 5;
    enrichment = Sciantix_variables[93];
    burnup_width = 5.0 / U_UO2;
    enrichment_width = 1.0;

    for (int b = 0; b < bu_dim; b++) {
      burnup_discretization[b] = burnup_width * b;
    }
    for (int e = 0; e < e_dim; e++) {
      enrichment_discretization[e] = e_min + enrichment_width * double(e);
    }

    for (int i = 0; i < 23; i++) {
      for (int j = 0; j < e_dim; j++) {
        for (int z = 0; z < bu_dim; z++) {
          xsec_fiss_table[i][j][z] = xsec_fiss_table_MOX_PWR[i][j][z];
          xsec_capt_table[i][j][z] = xsec_capt_table_MOX_PWR[i][j][z];
        }
      }
    }
    for (int j = 0; j < e_dim; j++) {
      for (int z = 0; z < bu_dim; z++) {
        xsec_na_table[j][z] = xsec_na_table_MOX_PWR[j][z];
        xsec_n2n_table[j][z] = xsec_n2n_table_MOX_PWR[j][z];
        xsec_n3n_table[j][z] = xsec_n3n_table_MOX_PWR[j][z];
      }
    }
    break;
  // MOX & LFR
  case 2: // not yet available the corresponding xsections, just a place holder
    e_dim = 6;
    bu_dim = 31;
    enrichment = Sciantix_variables[92];
    burnup_width = 5.0 / U_UO2;
    enrichment_width = 1.0;
    for (int b = 0; b < bu_dim; b++) {
      burnup_discretization[b] = burnup_width * b;
    }
    for (int e = 0; e < e_dim; e++) {
      enrichment_discretization[e] = e_min + enrichment_width * double(e);
    }
    for (int i = 0; i < 21; i++) {
      for (int j = 0; j < e_dim; j++) {
        for (int z = 0; z < bu_dim; z++) {
          xsec_fiss_table[i][j][z] = xsec_fiss_table_MOX_LFR[i][j][z];
          xsec_capt_table[i][j][z] = xsec_capt_table_MOX_LFR[i][j][z];
        }
      }
    }
    for (int j = 0; j < e_dim; j++) {
      for (int z = 0; z < bu_dim; z++) {
        xsec_na_table[j][z] = xsec_na_table_MOX_LFR[j][z];
      }
    }
    break;
  }
}