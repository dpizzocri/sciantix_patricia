#!/usr/bin/env python

###########################################
##                                       ##
##           S C I A N T I X             ##
##           ---------------             ##
##                                       ##
##  Version: 1.0                         ##
##  Year   : 2018                        ##
##  Authors: D. Pizzocri and T. Barani   ##
##  @barat, 03/07/2018                   ##
###########################################

# Verification of the Bateman equations (src/NuclidesEvolution.C)
# This script provides the verification for the Bateman equations
# implemented in the code, solving the evolution system with null
# neutronic flux and considering initial concentrations of some
# nuclides. This version considers an initial loading of 4% U235
# and remainder U238, but one can in general include as many other
# nuclides as he can imagine.
# The fuel reference density is 10970 kg/m3.
# The solution requires |scipy|, please verify you have this module
# available on your machine, otherwise google it and/or contact
# the developers.

# @barat, 19/04/2019: need to be updated to account for new nuclides
# from !MR 24

from scipy.integrate import solve_ivp #module for integration of ODE
import numpy as np #numerical methods module
import csv #csv handling module

lbTl207 =2.42e-03
lbTl208 =3.78e-03
lbPb210 =9.90e-10
lbPb211 =3.20e-04
lbPb212 =1.81e-05
lbPb214 =4.31e-04
lbBi210 =1.60e-06
laBi211 =9.00e-05 # neglect other decays <1%
lbBi212 =1.22e-04 # equals to lambda_Bi212 * BR_b==64.06%)
laBi212 =6.86e-05 # equals to lambda_Bi212 * BR_a==35.94%)
lbBi214 =5.81e-04 # neglect other decays <1%
laPo210 =5.80e-08
laPo212 =2.32e+08
laPo214 =4.22e+03
laPo215 =3.89e+02 # neglect other decays <1%
laPo216 =4.78
laPo218 =2.24e+02 # neglect other decays <1%
laRn219 =1.75e-01
laRn220 =1.25e-02
laRn222 =2.10e-06
lbFr223 =5.25e-04 # neglect other decays <1%
laRa223 =7.02e-07
laRa224 =2.19e-06
laRa226 =1.37e-11
lbRa228 =3.82e-09
lbAc227 =9.95e-10 # equals to lambda_Ac227 * BR_b==98.62%)
laAc227 =1.39e-11 # equals to lambda_Ac227 * BR_a==1.38%)
lbAc228 =3.13e-05
laTh227 =4.29e-07
laTh228 =1.15e-08
laTh230 =2.91e-13
lbTh231 =7.54e-06
laTh232 =1.57e-18
lbTh234 =3.33e-07
laPa231 =6.71e-13
lbPa234 =2.87e-05
laU234 =8.95e-14
laU235 =3.12e-17
laU236 =9.38e-16 # neglect other decays <1%
laU238 =4.92e-18
laNp237 =1.03e-14 # neglect other decays <1%
lbNp238 =3.79e-06
lbNp239 =3.41e-06
laPu238 =2.51e-10 # neglect other decays <1%
laPu239 =9.12e-13 # neglect other decays <1%
laPu240 =3.35e-12 # neglect other decays <1%
lbPu241 =1.54e-09 # neglect other decays <1%
laPu242 =5.86e-14 # neglect other decays <1%
lbPu243 =3.89e-05
laAm241 =5.08e-11 # neglect other decays <1%
BR_Am241 =0.91  # ok for PWR spectrum  need some thoughts on BWR/LMFBR
lbAm242 =9.94e-06  # equals to lambda_Am242 * BR_b==82.7%)
leAm242 =2.08e-06  # equals to lambda_Am242 *=1-BR_b)
litAm242m =1.56e-10 # neglect other decays <1%
laAm243 =2.98e-12 # neglect other decays <1%
lbAm244 =1.91e-05 # neglect other decays <1%
laCm242 =4.93e-08 # neglect other decays <1%
laCm243 =7.55e-10 # neglect other decays <1%
laCm244 =1.21e-09 # neglect other decays <1%
laCm245 =2.61e-12 # neglect other decays <1%

def bateman(t, y):
    return [+laBi211 * y[10] - lbTl207 * y[0], #0
 +laBi212 * y[11] -lbTl208 * y[1], #1
 +laPo210 * y[13], #2
 +lbTl207 * y[0],#3
 +laPo212 * y[14] +lbTl208 * y[1], #4
 +laPo214 * y[15] -lbPb210 * y[5], #5
 +laPo215 * y[16] -lbPb211 * y[6], #6
 +laPo216 * y[17]-lbPb212 * y[7], #7
 +laPo218 * y[18] -lbPb214 * y[8], #8
 +lbPb210 * y[5] -lbBi210 * y[9], #9
 +lbPb211 * y[6] -laBi211 * y[10], #10
 +lbPb212 * y[7] -lbBi212 * y[11] - laBi212 * y[11], #11
 +lbPb214 * y[8] -lbBi214 * y[12], #12
 +lbBi210 * y[9] -laPo210 * y[13], #13
 +lbBi212 * y[11] -laPo212 * y[14], #14
 +lbBi214 * y[12] -laPo214 * y[15], #15
 +laRn219 * y[19] -laPo215 * y[16], #16
 +laRn220 * y[20] -laPo216 * y[17], #17
 +laRn222 * y[21] -laPo218 * y[18], #18
 +laRa223 * y[23] -laRn219 * y[19], #19
 +laRa224 * y[24] -laRn220 * y[20], #20
 +laRa226 * y[25] -laRn222 * y[21], #21
 +laAc227 * y[27] -lbFr223 * y[22], #22
 +laTh227 * y[29] +lbFr223 * y[22] -laRa223 * y[23], #23
 +laTh228 * y[30] -laRa224 * y[24], #24
 +laTh230 * y[31] -laRa226 * y[25], #25
 +laTh232 * y[33] -lbRa228 * y[26], #26
 +laPa231 * y[35] -(laAc227 + lbAc227) * y[27], #27
 +lbRa228 * y[26] -lbAc228 * y[28], #28
 +lbAc227 * y[27] -laTh227 * y[29], #29
 +lbAc228 * y[28] -laTh228 * y[30], #30
 +laU234 * y[37] -laTh230 * y[31], #31
 +laU235 * y[38] -lbTh231 * y[32], #32
 +laU236 * y[39] -laTh232 * y[33], #33
 +laU238 * y[40] -lbTh234 * y[34], #34
 +lbTh231 * y[32] -laPa231 * y[35], #35
 +lbTh234 * y[34] -lbPa234 * y[36], #36
 +lbPa234 * y[36] -laU234 * y[37], #37
 +laPu239 * y[45] -laU235 * y[38], #38
 +laPu240 * y[46] -laU236 * y[39], #39
 +laPu242 * y[48] -laU238 * y[40], #40
 +laAm241 * y[50] -laNp237 * y[41], #41
 -lbNp238 * y[42], #42
 +laAm243 * y[53] -lbNp239 * y[43], #43
 -laPu238 * y[44] +laCm242 * y[55] + lbNp238 * y[42], #44
 +laCm243 * y[56] -laPu239 * y[45] + lbNp239 * y[43], #45
 +laCm244 * y[57] -laPu240 * y[46], #46
 -lbPu241 * y[47] +laCm245 * y[58], #47
 +leAm242 * y[51] -laPu242 * y[48], #48
 -lbPu243 * y[49], #49
 +lbPu241 * y[47] -laAm241 * y[50], #50
 -lbAm242 * y[51] +litAm242m * y[52], #51
 -litAm242m * y[52], #52
 +lbPu243 * y[49] -laAm243 * y[53], #53
 -lbAm244 * y[54], #54
 +lbAm242 * y[51] -laCm242 * y[55], #55
 -laCm243 * y[56], #56
 +lbAm244 * y[54] -laCm244 * y[57], #57
 -laCm245 * y[58], #58
 +laBi211 * y[10] +laBi212 * y[11] +laPo210 * y[13] +laPo212 * y[14] +laPo214 * y[15] +laPo215 * y[16] +laPo216 * y[17] +laPo218 * y[18] +laRn219 * y[19] +laRn220 * y[20]
 +laRn222 * y[21] +laRa223 * y[23] +laRa224 * y[24] +laRa226 * y[25] +laAc227 * y[27] +laTh227 * y[29] +laTh228 * y[30] +laTh230 * y[31] +laTh232 * y[33] +laPa231 * y[35]
 +laU234  * y[37] +laU235 * y[38] +laU236 * y[39] +laU238 * y[40] +laNp237 * y[41] +laPu238 * y[44] +laPu239 * y[45] +laPu240 * y[46] +laPu242 * y[48] +laAm241 * y[50]
 +laAm243 * y[53] +laCm242 * y[55] +laCm243 * y[56] +laCm244 * y[57] +laCm245 * y[58]] #59

ic = np.zeros(60) #initialize the initial conditions
ic[38] = 9.91033e+26 #4% di U235 -- TD density: 10970 kg/m3
ic[40] = 2.3484e+28  #96% U238

t_span = [0., 1.e+6*3600.] #1 million hours
res = solve_ivp(bateman, t_span, ic, method='BDF') #other options for the numerical method 'RK45' (strongly not reccomended), 'Radau' (fully implicit, third order error check, ok also for this case)

print(res.message) #cline output

# Write to csv the results

fid = open("results.csv", 'wt') #file on which results are collected
names = ["t", "Tl207",
"Tl208",
"Pb206",
"Pb207",
"Pb208",
"Pb210",
"Pb211",
"Pb212",
"Pb214",
"Bi210",
"Bi211",
"Bi212",
"Bi214",
"Po210",
"Po212",
"Po214",
"Po215",
"Po216",
"Po218",
"Rn219",
"Rn220",
"Rn222",
"Fr223",
"Ra223",
"Ra224",
"Ra226",
"Ra228",
"Ac227",
"Ac228",
"Th227",
"Th228",
"Th230",
"Th231",
"Th232",
"Th234",
"Pa231",
"Pa234",
"U234",
"U235",
"U236",
"U238",
"Np237",
"Np238",
"Np239",
"Pu238",
"Pu239",
"Pu240",
"Pu241",
"Pu242",
"Pu243",
"Am241",
"Am242",
"Am242m",
"Am243",
"Am244",
"Cm242",
"Cm243",
"Cm244",
"Cm245",
"He4"] #time + all isotopes considered for header writing

writer = csv.writer(fid) # naming method to write on csv file
writer.writerow(names) # write name list

# res.t[i]     Collects the time at which the solution has been evaluated, with i being the corresponding time step
# res.y[j][i]  Collects the j-th equation integrated and evaluated at the i-th time step

#write the results
for i in range(0,res.t.size):
    rw = res.t[i]
    for j in range(0, ic.size):
        rw = np.append(rw, res.y[j][i])
    writer.writerow(rw)
fid.close() #close files
