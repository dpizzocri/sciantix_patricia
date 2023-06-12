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
import scipy.stats as stats
from sklearn.linear_model import LinearRegression

""" Validation database: intragranular swelling due to fission gases """
def regression_baker(wpath, mode_Baker, mode_gold, mode_plot, folderList, number_of_tests, number_of_tests_failed):

  if mode_Baker == '0':
    return folderList, number_of_tests, number_of_tests_failed

  igSwelling2 = []
  gold = []
  FGR2 = []

  # Intergranular gaseous swelling database from Baker 1977 experiments
  igSwellingBaker = [0.06, 0.07, 0.08, 0.09, 0.12, 0.15, 0.18, 0.24, 0.31]
  # Data from SCIANTIX 1.0 
  igSwelling1 = [0.033, 0.048, 0.062, 0.073, 0.079, 0.082, 0.083, 0.084, 0.086]

  sample_number = len(igSwelling1)

  for file in os.listdir(wpath):

    if "Baker" in file and os.path.isdir(file) is True:
      folderList.append((file))
      os.chdir(file)

      # copying input files from the regression folder into the current folder
      shutil.copy("..\input_settings.txt", os.getcwd())
      shutil.copy("..\input_scaling_factors.txt", os.getcwd())

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
        try : 
          data_gold = import_data("output_gold.txt")
        except :
          print(f"output_gold.txt not found in {file}")

      if mode_gold == '3':
        print(f"...golding existing results.")
        os.remove('output_gold.txt')
        os.rename('output.txt', 'output_gold.txt')

      FGRPos = findSciantixVariablePosition(data, "Fission gas release (/)")
      FGR2.append(100*data[-1,FGRPos].astype(float))

      intraGranularSwellingPos = findSciantixVariablePosition(data, "Intragranular gas swelling (/)")
      igSwelling2.append(100*data[-1,intraGranularSwellingPos].astype(float))
      intraGranularSwellingGoldPos = findSciantixVariablePosition(data_gold, "Intragranular gas swelling (/)")
      gold.append(100*data_gold[-1,intraGranularSwellingGoldPos].astype(float))
      os.chdir('..')

  if mode_plot == '1':

    fig, ax = plt.subplots()

    ax.scatter(igSwellingBaker, igSwelling1, c = '#FA82B4', edgecolors= '#999AA2', marker = 'o', s=20, label='SCIANTIX 1.0')
    ax.scatter(igSwellingBaker, igSwelling2, c = '#98E18D', edgecolors= '#999AA2', marker = 'o', s=20, label='SCIANTIX 2.0')

    ax.plot([1e-3, 1e2],[1e-3, 1e2], '-', color = '#757575')
    ax.plot([1e-3, 1e2],[2e-3, 2e2],'--', color = '#757575')
    ax.plot([1e-3, 1e2],[5e-4, 5e1],'--', color = '#757575')
    ax.set_xlim(1e-2, 1e1)
    ax.set_ylim(1e-2, 1e1)

    ax.set_xscale('log')
    ax.set_yscale('log')

    # ax.set_title('Intragranular gaseous swelling')
    ax.set_xlabel('Experimental (%)')
    ax.set_ylabel('Calculated (%)')
    ax.legend()

    # plt.savefig('Baker1977.png')
    plt.show()


    # GOLD vs. SCIANTIX 2.0
    fig, ax = plt.subplots()

    ax.scatter(igSwellingBaker, gold, c = '#C9C954', edgecolors= '#999AA2', marker = 'o', s=20, label='Gold')
    ax.scatter(igSwellingBaker, igSwelling2, c = '#98E18D', edgecolors= '#999AA2', marker = 'o', s=20, label='SCIANTIX 2.0')

    ax.plot([1e-3, 1e2],[1e-3, 1e2], '-', color = '#757575')
    ax.plot([1e-3, 1e2],[2e-3, 2e2],'--', color = '#757575')
    ax.plot([1e-3, 1e2],[5e-4, 5e1],'--', color = '#757575')

    ax.set_xlim(1e-2, 1e1)
    ax.set_ylim(1e-2, 1e1)

    ax.set_xscale('log')
    ax.set_yscale('log')

    # ax.set_title('Intergranular gaseous swelling')
    ax.set_xlabel('Experimental (%)')
    ax.set_ylabel('Calculated (%)')
    ax.legend()

    # plt.savefig('White2004.png')
    plt.show()

    # SCIANTIX 2.0
    fig, ax = plt.subplots()

    ax.scatter(igSwellingBaker, igSwelling2, c = '#98E18D', edgecolors= '#999AA2', marker = 'o', s=20, label='SCIANTIX')

    ax.plot([1e-3, 1e2],[1e-3, 1e2], '-', color = '#757575')
    ax.plot([1e-3, 1e2],[2e-3, 2e2],'--', color = '#757575')
    ax.plot([1e-3, 1e2],[5e-4, 5e1],'--', color = '#757575')

    ax.set_xlim(1e-2, 1e1)
    ax.set_ylim(1e-2, 1e1)

    ax.set_xscale('log')
    ax.set_yscale('log')

    # ax.set_title('Intergranular gaseous swelling')
    ax.set_xlabel('Experimental (%)')
    ax.set_ylabel('Calculated (%)')
    ax.legend()

    # plt.savefig('White2004.png')
    plt.show()

		# FGR plot
    fig, ax = plt.subplots()
    ax.scatter(igSwelling2, FGR2, c = '#98E18D', edgecolors= '#999AA2', marker = 'o', s=20, label='FGR SCIANTIX 2.0')

    ax.set_xscale('log')
    ax.set_yscale('log')

    ax.set_xlabel('Swelling (%)')
    ax.set_ylabel('FGR (%)')
    ax.legend()

    plt.show()


  """ Statistical analysis """
  # Experimental data: mean, median, ...
  print(f"Experimental data - mean: ", np.mean(igSwellingBaker))
  print(f"Experimental data - median: ", np.median(igSwellingBaker))
  print(f"Experimental data - Q1: ", np.percentile(igSwellingBaker, 25, interpolation = 'midpoint'))
  print(f"Experimental data - Q3: ", np.percentile(igSwellingBaker, 75, interpolation = 'midpoint'))

  # SCIANTIX 1.0: mean, median, ...
  print(f"SCIANTIX 1.0 - mean: ", np.mean(igSwelling1))
  print(f"SCIANTIX 1.0 - median: ", np.median(igSwelling1))
  print(f"SCIANTIX 1.0 - Q1: ", np.percentile(igSwelling1, 25, interpolation = 'midpoint'))
  print(f"SCIANTIX 1.0 - Q3: ", np.percentile(igSwelling1, 75, interpolation = 'midpoint'))

  # SCIANTIX 2.0: mean and median
  print(f"SCIANTIX 2.0 - mean: ", np.mean(igSwelling2))
  print(f"SCIANTIX 2.0 - median: ", np.median(igSwelling2))
  print(f"SCIANTIX 2.0 - median: ", np.percentile(igSwelling2, 25, interpolation = 'midpoint'))
  print(f"SCIANTIX 2.0 - median: ", np.percentile(igSwelling2, 75, interpolation = 'midpoint'))

  # SCIANTIX 1.0 and 2.0 - Median absolute deviatiosns
  deviations_1 = abs(np.array(igSwellingBaker) - igSwelling1)
  deviations_2 = abs(np.array(igSwellingBaker) - igSwelling2)
  print(f"SCIANTIX 1.0 - MAD: ", np.median(deviations_1))
  print(f"SCIANTIX 2.0 - MAD: ", np.median(deviations_2))
  # RMSE
  print(f"SCIANTIX 1.0 - RMSE: ", np.mean(np.array(igSwellingBaker) - igSwelling1)**2)
  print(f"SCIANTIX 2.0 - RMSE: ", np.mean(np.array(igSwellingBaker) - igSwelling2)**2)
  print("\n")

  return folderList, number_of_tests, number_of_tests_failed