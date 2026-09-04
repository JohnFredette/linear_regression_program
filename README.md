# Linear Regression Program (CLI)
To-do: 
- Write documentation (readme)
- Add stdbool.h and use true/false
- Parse input for csv export && check for .csv extension
- check for argc > 2 (multiple .csv docs)
- Improve memory managment (seperate into chunks) 
- Create function to export regression results

## Description
This linear regression program is a CLI-based tool, written in the C programming language, created to perform linear regression on a set of data given by 2 points eg. (x,y). 

The data entry can be done either automatically by providing a .csv file containing pairs of floating point data seperated by a comma or manually if no other command line argument (CLA) is provided. 
Note that for .csv data entry to work properly, it's necessary that the .csv file be stored in the same directory from whence the binary was launched.

When run, the program presents the user options for printing to the console the following items:
- The raw data
- The sums used in the regression formulae
- The regression resuls (angular and linear coefficients aka. slope and intercept) 
- Correlation coefficient

Besides that, if data was entered manually, the program provies the user with the option to export the data to a .csv file.

## Usage
As mentioned in the description, there are two methods for data entry with this program: csv and manual imput. 
As the program flow is based on this initial choice, each method will be explained seperately. 

### CSV Data Entry
To run the program with CSV data entry, the user must provide the name of the .csv file as the second command line argument when calling the program as follows: 

```./a.out data.csv```

The user will then be presented with the following options:

```
0 to Exit Program
1 to print data
2 to print sums
3 to print regression results
```

If the user types 0 and then \<enter\>, the program ends. 
If the user types 1 and then \<enter\>, the raw data from the provided .csv file is printed to the console.
If the user types 2 and then \<enter\>, the sums used the the regression formulae are printed to the console.
If the user tyeps 3 and then \<enter\>, the angular and linear coeffients, also known as the slope and intercept, as well as the correlation coefficient are printed to the console.

### Manual Data Entry
To run the program with manual data entry, the user need only to provide the name of the binary as a command line argument to lanuch the program.

Then, the user will be asked for the number of data points to be entered. After provding that number, the user will be prompted to provide each coordinate (x,y) of each data point separted by a space but with **NO** comma. The user should press \<enter\> after typing each data point as each point must be entered seperately. 

Once the manual data entry is complete, the user is presented with the following options:

```
0 to Exit Program
1 to print data
2 to print sums
3 to print regression results
4 to export manual input to CSV
```

Options 0, 1, 2, and 3 function identically as they do when entering data via CSV. 
If the user types 4 and then \<enter\>, the user is prompted to prove a name for the CSV file containing the data entered manually. The user is also reminded that that file should contain a .csv extension.

After providing a name for the .csv extension, the user is brought back to the main menu and presented witht the 4 options again.

## Installation
To install this program, it is necessary to compile the .c file. 
If using the gcc compiler, it may be necessary to link the math library (math.h) with the flag -lm as follows: 
``` gcc regression.c -lm ```

The programmer has chosen to use the following command for comilation:

``` gcc -Wall -Wextra -g regression.c -o main -lm ```
## Derivation of Formulae

## Code Explaination
