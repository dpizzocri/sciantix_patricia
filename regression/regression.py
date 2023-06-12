"""

This is a python script to execute the regression (running the validation database) of sciantix.

@author G. Zullo

"""

import os
import subprocess
import numpy as np
import matplotlib.pyplot as plt
import shutil

from regression_baker import regression_baker
from regression_white import regression_white
from regression_talip import regression_talip
from regression_contact import regression_contact
from regression_oxidation import regression_oxidation

""" Setting the properties of this script """
# get the directory of this script
wpath = os.path.dirname(os.path.realpath(__file__))
os.chdir(wpath)

folderList = []

print(f"This script executes SCIANTIX into the validation cases.\n")
print(f"Pleast select one option:\n")
print(f"\tMODE GOLD == 0: use SCIANTIX, check new results.\n")
print(f"\tMODE GOLD == 1: use SCIANTIX, gold new results.\n ")
print(f"\tMODE GOLD == 2: do not use SCIANTIX, check existing results.\n ")
print(f"\tMODE GOLD == 3: do not use SCIANTIX, gold existing results.\n ")

mode_gold = input("Enter MODE GOLD (0, 1, 2, 3)= ")
mode_plot = input("Enter MODE PLOT (0 or 1)= ")
mode_Baker = input("Enter MODE Baker (0 or 1)= ")
mode_White = input("Enter MODE White (0 or 1)= ")
mode_Talip = input("Enter MODE Talip (0 or 1)= ")
mode_CONTACT = input("Enter MODE CONTACT (0 or 1)= ")
mode_oxidation = input("Enter MODE oxidation (0 or 1)= ")

print(f"\nMODE GOLD ==", mode_gold, "selected.\n")

number_of_tests = 0
number_of_tests_failed = 0

folderList, number_of_tests, number_of_tests_failed = regression_baker(wpath, mode_Baker, mode_gold, mode_plot, folderList, number_of_tests, number_of_tests_failed)
folderList, number_of_tests, number_of_tests_failed = regression_white(wpath, mode_White, mode_gold, mode_plot, folderList, number_of_tests, number_of_tests_failed)
folderList, number_of_tests, number_of_tests_failed = regression_talip(wpath, mode_Talip, mode_gold, mode_plot, folderList, number_of_tests, number_of_tests_failed)
folderList, number_of_tests, number_of_tests_failed = regression_contact(wpath, mode_CONTACT, mode_gold, mode_plot, folderList, number_of_tests, number_of_tests_failed)
folderList, number_of_tests, number_of_tests_failed = regression_oxidation(wpath, mode_oxidation, mode_gold, mode_plot, folderList, number_of_tests, number_of_tests_failed)

print(f"SUMMARY")
print(f"-------")
print(f"- MODE GOLD == ", mode_gold, "\n")
print(f"- List of tests performed:\n", folderList, "\n")
print(f"! Number of tests = ", number_of_tests)
print(f"! Number of tests passed = ", number_of_tests - number_of_tests_failed)
print(f"! Number of tests failed = ", number_of_tests_failed, "\n")