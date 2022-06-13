# **Input file example**

In this folder are reported the three essential input files required from SCIANTIX

 - `input_settings.txt` contains the choice of the models and numerical solvers employed in the simulation
 - `input_history.txt` containes the temperature (K), fission rate (fiss / m3-s)$, and hydrostatic stress (MPa) as a function of time (hr)
 - `input_initial_conditions.txt` provides the code with several initial conditions

Below we detail each file content.

# Input settings

The provided input settings are the **recommended** choice for standard simulations of uranium dioxide.

0 # verification -- The embedded verification procedure of SCIANTIX solvers is **disabled**.

1 # grain growth -- The model for grain growth according to *Ainscough et al., J. Nucl. Mater. 49 (1978) 117* is selected.

1 #  inert gas behavior -- Inert gas behaviour is **considered**.

1 #  gas diff coeff -- The selected correlation for single gas atom intra-granular diffusion coefficient is the one by *J.A.Turnbull et al., IWGFPT--32, 1988*. It considers three terms contributing to gas diffusivity, representing thermally activated, irradiation-enhanced, and a-thermal mechanism.

1 #  intra bbl evo -- Selection of mechanistic intra-granular inert gas behaviour model, featuring a direct description of intra-granular bubble nucleation, re-solution, gas trapping into intra-granular bubbles and diffusion towards grain boundaries. The model is taken from *Pizzocri et al., J. Nucl. Mater. 502 (2018) 323*.

1 #  intra bubble_radius -- Intra-granular bubble radius calculated as a function of the average number of gas atoms per bubble, obtained through the above mentioned model.

1 #  re-solution -- Heterogeneous bubble re-solution mechanism, i.e. *en-bloc* destruction of bubbles  interacting with fission fragments. The re-solution rate is calculated according to *J.A. Turnbull, J. Nucl. Mater. 38 (1971), 203*.

1 #  trapping -- Trapping rate of single gas atoms into intra-granular bubbles according to the formulation of *F.S. Ham, J. Phys. Chem. Sol., 6 (1958) 335*.

1 #  nucleation -- Heterogeneous nucleation of intra-granular bubbles, i.e. a number of bubbles are created in the wake of fission fragments trails. The rate is calculated according to *Olander and Wongsawaeng, J. Nucl. Mater. 354 (2006), 94*.

1 #  DiffSolver -- Intra-granular diffusion equation is solved through a Spectral Diffusion Algoritm. This formulation entails the solution of a single equation for gas populations in the grain, enforcing the so-called effective diffusion coefficient (cfr. *M.V. Speight, Nucl. Sci. Eng. 37 (1969) 180*).

1 #  format_out -- The output of the simulation is provided in a text file (`output.txt`), in which values are separated by **tabs**.

1 #  gb vac diff coeff -- Grain-boundary diffusion coefficient of vacancies evaluated according to *G.L.Reynolds and B.Burton, J. Nucl. Mater. 82 (1979) 22*.

1 #  gb behavior -- Mechanistic model of inert gas behaviour at grain boundaries. The model is taken from *Pastore et al., Nucl. Eng. Des. 256 (2013) 75* and *Barani et al., J. Nucl. Mater. 486 (2017) 96*. A direct description of lenticular-shaped grain-boundary bubbles is enforced, encompassing their growth due to gas and vacancies inflow, interconnection, and describing as inherently coupled gaseous swelling and fission gas release.

1 #  gb micro-cracking -- Burst release of fission gas during temperature transients is considered, according to the model by *Barani et al., J. Nucl. Mater. 486 (2017) 96*. The model features a semi-empirical description of grain-boundary micro-cracking  and is nested on the general grain-boundary gas behaviour model.

0 #  hbs formation -- The formation and effects of high burnup structure is not accounted for.

0 # fuel/reactor couple -- Selects the fuel and reactor types (materials and spectrum) for burnup calculations. This settings is for UO2 - PWR combination.
***
# Input initial conditions

In this file, the user can provide initial conditions to some of the SCIANTIX state variables.

5e-6 # Value of the initial grain radius, in micrometers.

0 # Initial value of gas (Xe, Kr) produced, useful to simulate experiments of pre-irradiated fuel samples.

0 # Initial value of the gas concentration in the grain, considering dissolved and gas in intra-granular bubbles.

0 # Initial value of gas dissolved in the fluorite phase of uranium dioxide.

0 # Initial value of gas in intra-granular bubbles.

0 # Initial value of gas stored in grain-boundary bubbles.

0 # Initial value of already released gas.

0 # Initial value of fuel burnup in **MWd/kgUO2**.

0 # Initial value of effective (i.e., burnup integrated below 1000 °C) fuel burnup **MWd/kgUO2**.

10970 # Initial value of fuel density.

2 # Initial oxygen-to-metal ratio.

0 # Initial value of He produced, useful to simulate experiments of pre-irradiated fuel samples.

0 # Initial value of the He concentration in the grain, considering dissolved and gas in intra-granular bubbles.

0 # Initial value of He dissolved in the fluorite phase of uranium dioxide. Note that a certain amount of He may be in **solution**.

0 # Initial value of He in intra-granular bubbles.

0 # Initial value of He stored in grain-boundary bubbles.

0 # Initial value of already released He.
***
**PLEASE NOTE** that from the quantities below, it is **mandatory** to put the comment symbol (#) **below** each data series.
***
0 1 0 0 99

\# Initial enrichment of the fuel in 234U, 235U, 236U, 237U, and 238U. The enrichment **is** expressed in % of i-th nuclied atoms over the total number of **heavy metal** atoms.

0 0 0

\# Initial enrichment of the fuel in  237Np, 238Np, 239Np.

0 0 0 0 0 0

\# Initial enrichment in 238Pu, 239Pu, 240Pu, 241Pu, 242Pu, and 243Pu.

0 0 0 0 0

\# Initial enrichment in 241Am, 242Am (ground state), 242Am (metastable state), 243Am, and 244Am.

0 0 0 0

\# Initial enrichment in 242Cm, 243Cm, 244Cm, and 245Cm
***
# Input intial conditions

In this file, a simplified temperature, fission rate (power), and hydrostatic stress history is contained. SCIANTIX interpolates the quantities among two consecutive values of each type, if differents. Every time step is internally subdivided in 100 intervals, at which the calculations are executed and outputs are provided. To change this value, the user must modify the source code.
**TIP**: this list of quantities **should not** terminate with a blank line. It can cause troubles to the input reading especially on UNIX OS. In case you will obtain a blank output file, this is most probably the issue.
***

In case of any trouble with those files, please contact the main developers (D. Pizzocri and T. Barani).
