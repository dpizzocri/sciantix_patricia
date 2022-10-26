"""
Created on Wed Feb  3 11:54:51 2021
sciantix.py is a python module made to handle the sciantix (standalon) postprocessing.
the purposes are:
    - to plot variables, choosing both x- and y- axes.

@author: Giovanni Zullo

Instructions:
use help(sciantix) to get a summary of what the module provides
if one makes changes to the sciantix.py, one can reload the module using importlib.reload(sciantix)

Example:
import sciantix
sciantix.getDictionary()
sciantix.plot(0,25)
sciantix.plot_range(0,5,11)

"""

import matplotlib.pyplot as plt
import numpy as np
import os
import importlib

# initialization of variables
output_filename = "output.txt"
data = np.genfromtxt(output_filename, dtype= 'str', delimiter='\t')

# with this lines, sciantix.py is also usable as a script
# -> python sciantix.py
if __name__ == "__main__":
    import sys
    fib(int(sys.argv[1]))

#def __init__(self):
#    """
#    The __init__ method is the Python equivalent of the C++ constructor in an object-oriented approach.
#    The __init__  function is called every time an object is created from a class.
#    The __init__ method lets the class initialize the object’s attributes and serves no other purpose.
#    It is only used within classes. 
#    """

def working_dir(path):
    """
    This function receives the path of the folder that contains the sciantix file "output.txt".
    If output.txt is in the same folder of sciantix.py, it is not necessary to use this function.
    """
    os.chdir(path)
    return None

def getDictionary(output_filename = 'output.txt'):
    """
    ----------------
    Input parameters
    ----------------

    output_filename : TYPE = str

        name of the output file (e.g. 'output.txt')
        the output file must be in the sciantix.py directory or
        the path must de defined by sciantix.working_dir(path).
        
        default name = 'output.txt'

    -------
    Returns
    -------
    The names of the sciantix quantities in output.txt that can be plotted
    and the corresponding values for the plot positions.
    """

    # verify if output file exists
    try:
        f = open(output_filename)
    except IOError:
        print("ERROR: ", output_filename, " not found!")
    finally:
        f.close()
    
    data = np.genfromtxt(output_filename, dtype= 'str', delimiter='\t')
    output_tags = data[0,:]

    data_shape = data.shape
    # data_shape[0] = number of rows
    # data_shape[1] = number of columns

    # array with the index of the output file header
    tag_positions = np.linspace(0, data_shape[1] - 2, data_shape[1] - 1)

    print("The file ", output_filename, "contains the following variables:")
    print("")    
    # print(output_tags)
    for i in range(0, data_shape[1] - 1):
        print("Position #", tag_positions[i].astype(int), ", variable = ", output_tags[i])

def plot(col_x, col_y, output_filename = "output.txt"):
    """
    Parameters
    ----------
    output_filename : TYPE = str
        name of the output file (e.g. 'output.txt')
        the output file must be in the sciantix.py directory or
        the path must de defined by sciantix.working_dir(path)
    col_x : TYPE = int
        number of column set as x-axis
    col_y : TYPE
        number of column set as y-axis

    Returns
    -------
    Plot of col_x - col_y
    """

    # verify if output file exists
    try:
        f = open(output_filename)
    except IOError:
        print("ERROR: ", output_filename, " not found!")
    finally:
        f.close()
    
    # Reading the output file and saving into data variable
    data = np.genfromtxt(output_filename, dtype = 'str', delimiter ='\t')
        
    x = data[1:,col_x].astype(float)
    y = data[1:,col_y].astype(float)
    
    # Setting the plot
    fig, ax = plt.subplots()

    ax.plot(x, y, color = 'blue')
    ax.set_xlabel(data[0, col_x])
    ax.set_ylabel(data[0, col_y])
    ax.grid()
    
    plt.show()

def plot_range(col_x, col_y1, col_y2, output_filename = "output.txt"):
    """
    Parameters
    ----------
    output_filename : TYPE = str
        name of the output file (e.g. 'output.txt')
        the output file must be in the sciantix.py directory or
        the path must de defined by sciantix.working_dir(path)
    col_x : TYPE = int
        number of column set as x-axis
    col_y1 : TYPE = int
        number of first column to be plotted
    col_y2 : TYPE = int
        number of the second column to be plotted

    Returns
    -------
    Plot of quantities in range col_y1, col_y2 as a function of col_x

    """

    # verify if output file exists
    try:
        f = open(output_filename)
    except IOError:
        print("ERROR: ", output_filename, " not found!")
    finally:
        f.close()

    # Reading the output file and saving into data variable
    data = np.genfromtxt(output_filename, dtype = 'str', delimiter ='\t')
        
    x = data[1:,col_x].astype(float)
    
    # Setting the plot
    fig, ax = plt.subplots()

    legend = []; # start with empty list
    for ith_col in range(col_y1, col_y2):
        ith_data = data[1:,ith_col].astype(float)
        ax.plot(x, ith_data)
        legend.append(data[0,ith_col])

    ax.grid()
    ax.set_xlabel(data[0, col_x])
    ax.legend(legend)
    plt.show()

    print(legend)

def validation(reference_output_file = 'output_gold.txt', test_output_file = 'output.txt'):
    """
    This function reads a reference output.txt file (ref_output.txt) and an
    output to be tested against it (temp_output.txt).

    Raises
    ------
    Exception     
        If the number of time-step is different among the two
        output files, an Exception is raised.

    Returns
    -------
    col_i : TYPE = array of integer values
        Number of columns to be controlled.

    """
    
    data_ref = np.genfromtxt(reference_output_file, dtype= 'str', delimiter='\t')
    data_temp = np.genfromtxt(test_output_file, dtype= 'str', delimiter= '\t')

    size_ref = data_ref.shape
    size_temp = data_temp.shape

    # checking the sizes
    if(data_ref.shape[0] != data_temp.shape[0]):
        raise Exception("Input history error: different time-step number!\n")

    if(data_ref.shape[1] != data_temp.shape[1]):
        print("Warning: different number of columns!\n")
    
    control = np.zeros(min(size_temp[1], size_ref[1]))
    for i in range(0, min(size_temp[1], size_ref[1])):
        if(np.all(data_ref[1:,i] == data_temp[1:,i])):
            control[i] = True
        else:
            control[i] = False
    
    col_i = np.empty((0,), int)
    for i in range(len(control)):
        if(control[i] == 0):
            col_i = np.append(col_i, np.array([i]), axis=0)
            print ('Please check variable ( col = ',i,'): ', data_temp[0,i])
    
    for i in range(len(col_i)):
        plot_cross(col_i[i], reference_output_file, test_output_file)
    return col_i

# plot of the same quantity of ref_output and temp_output
# if the bisector of first quadrant is plotted we are happy
def plot_cross(col, reference_output_file = 'output_gold.txt', test_output_file = 'output.txt'):
    
    data_ref = np.genfromtxt(reference_output_file, dtype = 'str', delimiter='\t')
    data_temp = np.genfromtxt(test_output_file, dtype = 'str', delimiter= '\t')
        
    x = data_ref[1:,col].astype(float)
    y = data_temp[1:,col].astype(float)
    
    fig, ax = plt.subplots()
    ax.plot(x, y, 'bo')
    ax.set_xlabel(data_ref[0,col])
    ax.set_ylabel(data_ref[0,col])
    ax.grid()
        
