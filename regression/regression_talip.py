"""

This is a python script to execute the regression (running the validation database) of sciantix.

@author G. Zullo

"""

import os
import subprocess
import numpy as np
import matplotlib.pyplot as plt
import shutil
from regression_functions import *

""" Helium release and release rate measurements  from Talip et al. (2014) measurements """
def regression_talip(wpath, mode_Talip, mode_gold, mode_plot, folderList, number_of_tests, number_of_tests_failed):
  if mode_Talip == '0':
    return folderList, number_of_tests, number_of_tests_failed

  else:
    for file in os.listdir(wpath):
      if "Talip" in file and os.path.isdir(file) is True:
        folderList.append((file))
        os.chdir(file)

        print(f"Now in folder {file}...")
        number_of_tests += 1

        if mode_gold == '0' or mode_gold == '1':

          # copying and executing sciantix.exe into cwd
          shutil.copy("..\sciantix.exe", os.getcwd())
          os.system("sciantix.exe")

          # removing useless file
          os.remove("sciantix.exe")
          os.remove("execution.txt")
          os.remove("input_check.txt")
          # os.remove("overview.txt")
        
        try : 
          data = import_data("output.txt")
        except :
          print(f"output.txt not found in {file}")
          data = np.zeros(shape=(1, 1))
        
        try : 
          data_gold = import_data("output_gold.txt")
        except :
          print(f"output_gold.txt not found in {file}")
          data_gold = np.ones(shape=(1, 1))
          
        if mode_gold == '0':
          if are_files_equal('output.txt', 'output_gold.txt') == True:
            print(f"Test passed!\n")
          else:
            print(f"Test failed!\n")
            number_of_tests_failed += 1

        if mode_gold == '1':
          
          try :
            os.path.exists('output.txt')

            print(f"...golding results.")
            os.remove('output_gold.txt')
            os.rename('output.txt', 'output_gold.txt')

          except :
            print(f"output.txt not found in {file}")

        if mode_gold == '2':

          if are_files_equal('output.txt', 'output_gold.txt') == True:
            print(f"Test passed!\n")
          else:
            print(f"Test failed!\n")
            number_of_tests_failed += 1

          try : 
            data = import_data("output.txt")
          except :
            print(f"output.txt not found in {file}")
            data = data_gold

        if mode_gold == '3':
          print(f"...golding existing results.")
          os.remove('output_gold.txt')
          os.rename('output.txt', 'output_gold.txt')

        try : 
          data_Cognini = import_data("output_Cognini.txt")
        except :
          print(f"output_Cognini.txt not found in {file}")
          data_Cognini = np.zeros(shape=(1, 1))

        heReleasedTalip14000_data = np.genfromtxt("Talip2014_release_data.txt")
        heReleasedRateTalip14000_data = np.genfromtxt("Talip2014_rrate_data.txt")

        # output.txt
        # find indexes
        timePos = findSciantixVariablePosition(data, "Time (h)")
        temperaturePos = findSciantixVariablePosition(data, "Temperature (K)")
        heReleasedPos = findSciantixVariablePosition(data, "He fractional release (/)")
        heReleasedRatePos = findSciantixVariablePosition(data, "He release rate (at/m3 s)")

        # arrays
        time = data[1:,timePos].astype(float)
        temperature = data[1:,temperaturePos].astype(float)
        heReleasedFrac = data[1:,heReleasedPos].astype(float)
        heReleaseRate = data[1:,heReleasedRatePos].astype(float)

        # output_gold.txt
        # find indexes
        timePosG = findSciantixVariablePosition(data_Cognini, "Time (h)")
        heReleasedPosG = findSciantixVariablePosition(data_Cognini, "He fractional release (/)")
        heReleasedRatePosG = findSciantixVariablePosition(data_Cognini, "He release rate (at/m3 s)")
        temperaturePosG = findSciantixVariablePosition(data_Cognini, "Temperature (K)")

        # arrays
        timeG = data_Cognini[1:,timePos].astype(float)
        heReleasedFracG = data_Cognini[1:,heReleasedPosG].astype(float)
        temperatureG = data_Cognini[1:,temperaturePosG].astype(float)
        heReleaseRateG = data_Cognini[1:,heReleasedRatePosG].astype(float)

        """ Plot: Helium fractional release """
        if mode_plot == '1':

          fig, ax = plt.subplots(1,2)

          plt.subplots_adjust(left=0.1,
                    bottom=0.1,
                    right=0.9,
                    top=0.9,
                    wspace=0.34,
                    hspace=0.4)

          ax[0].scatter(heReleasedTalip14000_data[:,0], heReleasedTalip14000_data[:,1], marker = '.', c = '#B3B3B3', label='Data from Talip et al. (2014)')
          ax[0].plot(timeG, heReleasedFracG, 'k', label='Cognini et al. (2021)')
          ax[0].plot(time, heReleasedFrac, color = '#98E18D', label='SCIANTIX 2.0')

          axT = ax[0].twinx()
          axT.set_ylabel('Temperature (K)')
          axT.plot(time, temperature, 'r', linewidth=1, label="Temperature")

          # ax.set_title(file + ' - Fractional release')
          ax[0].set_xlabel('Time (h)')
          ax[0].set_ylabel('Helium fractional release (/)')
          h1, l1 = ax[0].get_legend_handles_labels()
          h2, l2 = axT.get_legend_handles_labels()
          ax[0].legend(h1+h2, l1+l2)

          """ Plot: Helium release rate """
          ax[1].scatter(heReleasedRateTalip14000_data[:,0], heReleasedRateTalip14000_data[:,1], marker = '.', c = '#B3B3B3', label='Data from Talip et al. (2014)')
          ax[1].plot(temperatureG, heReleaseRateG, 'k', label='Cognini et al. (2021)')
          ax[1].plot(temperature, heReleaseRate, color = '#98E18D', label='SCIANTIX 2.0')

          # ax.set_title(file + ' - Release rate')
          ax[1].set_xlabel('Temperature (K)')
          ax[1].set_ylabel('Helium release rate (at m${}^{-3}$ s${}^{-1}$)')
          ax[1].legend()

          # plt.savefig(file + '.png')
          plt.show()
        
        os.chdir('..')
        
  return folderList, number_of_tests, number_of_tests_failed
