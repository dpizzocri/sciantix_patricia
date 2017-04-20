############################################
##                                        ##
##            S C I A N T I X             ##
##            ---------------             ##
##                                        ##
##   Version: 0.1                         ##
##   Year   : 2016                        ##
##   Authors: D. Pizzocri and T. Barani   ##
##                                        ##
############################################
#    Makefile
#    @barat, 20/04/2017


#Initialization of useful variables

objects =       Burnup.o                    \
                FissionYield.o              \
                FuelDensity.o               \
                GasDiffusion.o              \
                GasDiffusionCoefficient.o   \
                GasProduction.o             \
                GlobalVariables.o           \
                GrainGrowth.o               \
                InertGasBehavior.o          \
                InputInterpolation.o        \
                InputStorage.o              \
                InterGranularGasBehavior.o  \
                IntraGranularGasBehavior.o  \
                MainSCIANTIX.o              \
                ManufacturedCoefficient.o   \
                ManufacturedSolution.o      \
                Solver.o                    \
                SolverVerification.o

INCLUDE_DIR  = include

SRC_DIR = src

vpath %.h /usr/include

vpath %.h $(INCLUDE_DIR)

vpath %.C $(SRC_DIR)

comp = g++

cflags = -Wall

cflags += $(addprefix -I ,$(INCLUDE_DIR))

lflag = -lm

RM = /bin/rm -f

Exe = sciantix.x

#vpath %.h include

.PHONY : clean

###########################################################################

#Beginning of the Makefile

$(Exe): $(objects)

	$(comp) $(lflag) -o $(Exe) $(objects)

clean:
			@echo "Cleaning up.."
			$(RM) $(objects) $(Exe)

#Part to edit if new files are included <------

Burnup.o: Burnup.C Burnup.h

	$(comp) $(cflags) -c $(SRC_DIR)/Burnup.C

FissionYield.o: FissionYield.C FissionYield.h

	$(comp) $(cflags) -c $(SRC_DIR)/FissionYield.C

FuelDensity.o: FuelDensity.C FuelDensity.h

	$(comp) $(cflags) -c $(SRC_DIR)/FuelDensity.C

GasDiffusion.o: GasDiffusion.C GasDiffusion.h

	$(comp) $(cflags) -c $(SRC_DIR)/GasDiffusion.C

GasDiffusionCoefficient.o: GasDiffusionCoefficient.C GasDiffusionCoefficient.h

	$(comp) $(cflags) -c $(SRC_DIR)/GasDiffusionCoefficient.C

GasProduction.o: GasProduction.C GasProduction.h

	$(comp) $(cflags) -c $(SRC_DIR)/GasProduction.C

GlobalVariables.o: GlobalVariables.C GlobalVariables.h

	$(comp) $(cflags) -c $(SRC_DIR)/GlobalVariables.C

GrainGrowth.o: GrainGrowth.C GrainGrowth.h

	$(comp) $(cflags) -c $(SRC_DIR)/GrainGrowth.C

InertGasBehavior.o: InertGasBehavior.C InertGasBehavior.h

	$(comp) $(cflags) -c $(SRC_DIR)/InertGasBehavior.C

InputInterpolation.o: InputInterpolation.C InputInterpolation.h

	$(comp) $(cflags) -c $(SRC_DIR)/InputInterpolation.C

InputStorage.o: InputStorage.C InputStorage.h

	$(comp) $(cflags) -c $(SRC_DIR)/InputStorage.C

InterGranularGasBehavior.o: InterGranularGasBehavior.C InterGranularGasBehavior.h

	$(comp) $(cflags) -c $(SRC_DIR)/InterGranularGasBehavior.C

IntraGranularGasBehavior.o: IntraGranularGasBehavior.C IntraGranularGasBehavior.h

	$(comp) $(cflags) -c $(SRC_DIR)/IntraGranularGasBehavior.C

MainSCIANTIX.o: MainSCIANTIX.C GlobalVariables.h SolverVerification.h InputStorage.h InputInterpolation.h GrainGrowth.h InertGasBehavior.h

	$(comp) $(cflags) -c $(SRC_DIR)/MainSCIANTIX.C

ManufacturedCoefficient.o: ManufacturedCoefficient.C ManufacturedCoefficient.h

	$(comp) $(cflags) -c $(SRC_DIR)/ManufacturedCoefficient.C

ManufacturedSolution.o: ManufacturedSolution.C ManufacturedSolution.h

	$(comp) $(cflags) -c $(SRC_DIR)/ManufacturedSolution.C

Solver.o: Solver.C Solver.h

	$(comp) $(cflags) -c $(SRC_DIR)/Solver.C

SolverVerification.o: SolverVerification.C SolverVerification.h

	$(comp) $(cflags) -c $(SRC_DIR)/SolverVerification.C

#.o: %.C

#	$(comp) -c $<

###########################################################################

#End of the Makefile
