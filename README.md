# Linear Regression Program (CLI)
To-do: 
- Write documentation (readme)
- Add stdbool.h and use true/false
- If there is an error with scanf on line 148, the program should quit
    or else implement a loop where the next time the user tries to input data it doesn't mess up the seuqence in the array. (eg. if only one data point got put into memory, the next one should over write it aka. no bad data should be writte) 
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

Besides that, if the data was entered manually, the program provies the user with the option to export the data to a .csv file.

## Usage
As mentioned in the description, there are two methods for data entry with this program: csv and manual imput. 
As the program flow is based on this initial choice, each method will be explained seperately. 

### CSV Data Entry
To run the program with CSV data entry, the user must provide the name of the .csv file as the second command line argument when calling the program, as exemplified in the following command: 

```./a.out data.csv```

The user is then presented with the following options:

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
To run the program with manual data entry, the user need only provide the name of the binary as a command line argument to lanuch the program.

After launch, the user is first asked for the number of data points to be entered. After provding that number, the user is prompted to provide each coordinate (x,y) of each data point separted by a space but with **NO** comma. The user should press \<enter\> after typing each data point as each point is expected to be entered seperately. 

Once the manual data entry is complete, the user is presented with the following options:

```
0 to Exit Program
1 to print data
2 to print sums
3 to print regression results
4 to export manual input to CSV
```

Options 0 to 3 function identically as they do when entering data via CSV. 
If the user types 4 and then \<enter\>, the user is prompted to prove a name for the CSV file to be exported containing the data entered manually. The user is also reminded that that file should contain a .csv extension.

After providing a name for the .csv extension, the user is brought back to the main menu and presented witht the 4 options again.

### Error Messages
The creator of this program has coded error messages into the program so that in the event of any unexpected behaviour or a crash, the user can receive insight to the reason why.

```Not a valid option. ```

This means that the user has tried to select an option from the menu that is not avaliable.

```Not a valid amount. ```

This means that the user has tried to enter either 0 or a negative number for the quantity of data points.

```Error in memory allocation for manually entered data. ```

This means that after the user provided a quantity the program tried to allocate memory for that quantity of data points but that there was a memory allocation issue in which malloc() returned NULL.

```Error with scanf. ```

This means that while the user was entering data manully, the scanf function did not scan a total of 2 numbers of type "long float". This can occur if the user provies no numbers, one number, or more than 2 numbers. It might also occur if the entry is poorly formated. 

```Error in opening file. ```

This means that after the program tried to open the file provided as the second command line argument for inputing data with a CSV file, the file_pointer pointer was NULL. This may happen if the name provided for the CSV file does not exist or is not located in the same directory from whence the binary was launched.

```Error in memory allocation. ```

This means that during the first allocation of memory for the data during CSV data input, the pointer was NULL.

```Error in memory reallocation. ```

This means that at some point during the execution of the program, there was a memory allocation issue in which realloc() returned NULL.

```Bad data in CSV file. ```

This means that the data stored in the CSV file provided by the user was not formatted correctly. The most likely reason this may occur is due to the lack of a comma on the line from whence fscanf() is reading. It could also occur if there is either no, one, or more than 2 numbers on a line.

```Error in creating file. ```

This means that filepointer was NULL after the program attempted to create the CSV file for exporting the data entered manually. 

## Installation
To install this program, it is necessary to compile the .c file. 
If using the gcc compiler, it may be necessary to link the math library (math.h) with the flag -lm as follows: 
``` gcc regression.c -lm ```

The creator of this program has chosen to use the following command for comilation:

``` gcc -Wall -Wextra -g regression.c -o main -lm ```

## Derivation of Formulae
Linear regression works by finding the line that best fits the data by using the least squares method. The least squares method consists of minimizing the sum of the squares of the errors. The error for each data point is defined as the vertical seperation (distance) from the line. 

Mathematically, given a set of $n$ data points ($x_k$, $y_k$), where the function that relates the two coordinates of each datum is $y_k = \phi(x_k)$ for each $x_k$, where $k$ is the index of each point, the linear function that best approximates $\phi$ is a function $f(x) = mx + b$ where $m$ is the angular coefficient/slope and $b$ is the linear coefficient/intercept.

Since the error for each data point is defined as the vertical distance between each data point and the line, the error is $|f(x_k) - \phi(x_k)|$. The least squares method requires the minimization of the sum of the squares of the error. Mathematically the function that must be minimized is: 

$$
\begin{aligned}
E &= \sum_{k=1}^n [f(x_k) - \phi(x_k)]^2 \\
E(m,b) &= \sum_{k=1}^n [mx_k + b - y_k]^2
\end{aligned}
$$

Where the function $E$ depends on $m$ and $b$, the coefficients of the line f(x), and where $n$ is the number of data points.

To minimize the function, the partial derivates with respect to each of the coefficients must be set equal to 0. 

$$
\begin{aligned}
&\frac{\partial E}{\partial m} = 2\sum_{k=1}^n [mx_k + b -y_k](x_k) = 0 \\
&\frac{\partial E}{\partial b} = 2\sum_{k=1}^n [mx_k + b -y_k](1) = 0
\end{aligned}
$$

This results in the following system of linear equations: 

$$
\begin{aligned}
&\sum_{k=1}^n mx_k^2 + \sum_{k=1}^n bx_k - \sum_{k=1}^n x_ky_k = 0 \\
&\sum_{k=1}^n mx_k + \sum_{k=1}^n b - \sum_{k=1}^n y_k = 0
\end{aligned}
$$

Which simplifies to: 

$$
\begin{aligned}
&m\sum_{k=1}^n x_k^2 + b\sum_{k=1}^n x_k = \sum_{k=1}^n x_ky_k \\
&m\sum_{k=1}^n x_k + bn = \sum_{k=1}^n y_k
\end{aligned}
$$

Which can be represented in Matrix form (A $\vec{x} = b$) as: 

$$
\begin{bmatrix}
\sum_{k=1}^n x_k^2 & \sum_{k=1}^n x_k \\
\sum_{k=1}^n x_k & n
\end{bmatrix}
\begin{bmatrix}
m \\
b
\end{bmatrix}
=
\begin{bmatrix}
\sum_{k=1}^n x_ky_k\\
\sum_{k=1}^n y_k
\end{bmatrix}
$$

After applying the inverse matrix to both sides of the equation the following statement can be made: 

$$
\begin{bmatrix}
m\\
b
\end{bmatrix}
=
\frac{1}{n\sum_{k=1}^n x_k^2 - (\sum_{k=1}^n x_k)^2}
\begin{bmatrix}
n & -\sum_{k=1}^n x_k \\
-\sum_{k=1}^n x_k & \sum_{k=1}^n x_k^2
\end{bmatrix}
\begin{bmatrix}
\sum_{k=1}^n x_ky_k\\
\sum_{k=1}^n y_k
\end{bmatrix}
$$

After performing the Matrix-Vector product operation on the right side of the equation one is left with:

$$
\begin{bmatrix}
m\\
b
\end{bmatrix}
=
\frac{1}{n\sum_{k=1}^n x_k^2 - (\sum_{k=1}^n x_k)^2}
\begin{bmatrix}
n\sum_{k=1}^n x_ky_k -\sum_{k=1}^n x_k \sum_{k=1}^n y_k \\
\sum_{k=1}^n x_k^2 \sum_{k=1}^n y_k -\sum_{k=1}^n x_k \sum_{k=1}^n x_ky_k 
\end{bmatrix}
$$

Which finally results in the expressions for the angular and linear coefficients of the line: 

$$ 
\begin{aligned}
m = \frac{n\sum_{k=1}^n x_ky_k - \sum_{k=1}^n x_k \sum_{k=1}^n y_k}{n\sum_{k=1}^n x_k^2 - (\sum_{k=1}^n x_k)^2} \\
b = \frac{\sum_{k=1}^n x_k^2 \sum_{k=1}^n y_k - \sum_{k=1}^n x_k \sum_{k=1}^n x_ky_k}{n\sum_{k=1}^n x_k^2 - (\sum_{k=1}^n x_k)^2}
\end{aligned}
$$

In the code, after all the data has been loaded into memory, each of the sums is calculated first and the value for each is saved. Then the denominator is caculated seperately as it is the same for both coefficients. Then the final computation for each of the coefficients is made.

## Code Explaination
