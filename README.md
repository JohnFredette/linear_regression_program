# Linear Regression Program (CLI)
To-do: 
- Write documentation (readme)
- check for argc > 2 (multiple .csv docs)
- Improve memory managment (seperate into chuncks) 
- Create function to export regression results

## Description
This linear regression program is a CLI-based tool, written in the C programming language, created to perform linear regression on a set of data given by 2 points eg. (x,y). 

The data entry can be done either automatically by providing a .csv file containing pairs of floating point data seperated by a comma or manually if no CLI argument is provided. 
Note that for .csv data entry to work properly, it's necessary that the .csv file be stored in the same directory from whence the binary was launched.

When run, the program gives the user options for printing to the console the raw data, the sums used in the regression formulae, and the regression resuls, including the angular and linear coefficients and the correlation coefficient. Besides that, if data was entered manually, the program provies the user with the option to export the manual data to a .csv file.

## Derivation of Formulae

## Usage

## Installation
To install this program, it is necessary to compile the .c file. 
If using the gcc compiler, it may be necessary to link the math library (math.h) with the flag -lm as follows: 
``` gcc regression.c -lm ```
