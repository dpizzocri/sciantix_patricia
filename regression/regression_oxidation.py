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

""" UO2 stiochiometry deviation: calculations and experimental data """
def regression_oxidation(wpath, mode_oxidation, mode_gold, mode_plot, folderList, number_of_tests, number_of_tests_failed):
  if mode_oxidation == '1':
    for file in os.listdir(wpath):
      if "oxidation" in file and os.path.isdir(file) is True:
        folderList.append((file))
        os.chdir(file)

        print(f"Now in folder {file}...")
        number_of_tests += 1

        if mode_gold == '0' or mode_gold == '1':

          # copying and executing sciantix.exe into cwd
          shutil.copy("..\sciantix.exe", os.getcwd())
          shutil.copy("..\input_scaling_factors.txt", os.getcwd())
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
            shutil.copy('output.txt', 'output_gold.txt')

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
            # print(f"output.txt not found in {file}")
            data = data_gold

        if mode_gold == '3':
          print(f"...golding existing results.")
          os.remove('output_gold.txt')
          os.rename('output.txt', 'output_gold.txt')

        # output.txt
        # find indexes
        timePos = findSciantixVariablePosition(data, "Time (h)")
        temperaturePos = findSciantixVariablePosition(data, "Temperature (K)")
        stiochiometryDeviationPos = findSciantixVariablePosition(data, "Stoichiometry deviation (/)")

        # arrays
        time = data[1:,timePos].astype(float)
        temperature = data[1:,temperaturePos].astype(float)
        stiochiometryDeviation = data[1:,stiochiometryDeviationPos].astype(float)

        try : 
          stiochiometryDeviationData = import_data('data.txt')
        except :
          stiochiometryDeviationData = np.zeros_like(stiochiometryDeviation)


        """ Plot: Stoichiometry deviation """
        if mode_plot == '1':

          fig, ax = plt.subplots()

          ax.plot(stiochiometryDeviationData[1:,0].astype(float), stiochiometryDeviationData[1:,1].astype(float), 'k.', label='Data')
          ax.plot(time, stiochiometryDeviation, 'g.', label='SCIANTIX 2.0')

          axT = ax.twinx()
          axT.set_ylabel('Temperature (K)')
          axT.plot(time, temperature, label="Temperature",  color='orange')

          ax.set_title(file + ' - Stoichiometry deviation')
          ax.set_xlabel('Time (h)')
          ax.set_ylabel('Stoichiometry deviation (/)')
          h1, l1 = ax.get_legend_handles_labels()
          h2, l2 = axT.get_legend_handles_labels()
          ax.legend(h1+h2, l1+l2)

          plt.savefig(file + ' - Stoichiometry deviation.png')
          plt.show()
        
        os.chdir('..')
        
  return folderList, number_of_tests, number_of_tests_failed
