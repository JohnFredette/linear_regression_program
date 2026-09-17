#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct{
    double x;
    double y;
} Coordinate;

enum Choices {
    EXIT_PROGRAM,
    PRINT_DATA_TO_CONSOLE,
    PRINT_SUMS,
    PRINT_RESULTS,
    EXPORT_CSV
};

enum Calculation_Status {
    CALCULATED,
    NOT_CALCULATED
};

int Manual_Data_Input(Coordinate **points);
int CSV_Data_Input(char *filename, Coordinate **points);
void print_data(Coordinate *points, int quantity);
void calculate_sums( 
    Coordinate *points, int quantity, double *sum_x, double *sum_y, double *sum_x_squared,
    double *sum_y_squared, double *sum_xy);
void calculate_regression_results(
    int quantity, double sum_x, double sum_y, double sum_x_squared, double sum_y_squared,
    double sum_xy, double *slope, double *intercept, double *correlation_coefficient);
void print_sums(
    double sum_x, double sum_y, double sum_x_squared, double sum_y_squared, double sum_xy);
void print_results(double slope, double intercept, double correlation_coefficient);
int CSV_Data_Export(Coordinate *points, int quantity);

int main(int argc, char *argv[]) {
    Coordinate *data = NULL;
    int quantity;

    double sum_x;
    double sum_y;
    double sum_x_squared;
    double sum_y_squared;
    double sum_xy;

    double slope;
    double intercept;
    double correlation_coefficient;

    int choice;
    int status_of_calculation = NOT_CALCULATED;

    if (argc == 1) {
        quantity = Manual_Data_Input(&data);
        if (quantity < 0){
            free(data);
            data = NULL;
            return 1;
        }
    }
    else {
        quantity = CSV_Data_Input(argv[1], &data);
        if (quantity < 0) {
            free(data);
            return 1;
        }
    }

    while (true){
        printf("%d to Exit Program \n", EXIT_PROGRAM);
        printf("%d to print data\n", PRINT_DATA_TO_CONSOLE);
        printf("%d to print sums\n", PRINT_SUMS);
        printf("%d to print regression results\n", PRINT_RESULTS);
        if (argc == 1){
            printf("%d to export manual input to CSV\n", EXPORT_CSV);
        }
        scanf("%d", &choice);
    
        switch (choice) {
            case EXIT_PROGRAM: 
                printf("Exiting Program. \n");
                free(data);
                return 0;
            case PRINT_DATA_TO_CONSOLE:
                print_data(data, quantity);
                break;
            case PRINT_SUMS:
                if (status_of_calculation == NOT_CALCULATED){
                    calculate_sums(
                        data, quantity, &sum_x, &sum_y, &sum_x_squared, &sum_y_squared, &sum_xy);
                    calculate_regression_results(
                        quantity, sum_x, sum_y, sum_x_squared, sum_y_squared, sum_xy, &slope,
                        &intercept, &correlation_coefficient);
                    
                    status_of_calculation = CALCULATED;
                }
                print_sums(sum_x, sum_y, sum_x_squared, sum_y_squared, sum_xy);
                break;
            case PRINT_RESULTS:
                if (status_of_calculation == NOT_CALCULATED){
                    calculate_sums(
                        data, quantity, &sum_x, &sum_y, &sum_x_squared, &sum_y_squared, &sum_xy);
                    calculate_regression_results(
                        quantity, sum_x, sum_y, sum_x_squared, sum_y_squared, sum_xy, &slope,
                        &intercept, &correlation_coefficient);
                    
                    status_of_calculation = CALCULATED;
                }
                print_results(slope, intercept, correlation_coefficient);
                break;
            case EXPORT_CSV:
                if (argc != 1){
                    printf("Not a valid option. \n\n");
                    break;
                }
                int export_return = CSV_Data_Export(data, quantity);
                if (export_return == 1){
                    free(data);
                    return 1;
                }
                break; 
            default: 
                printf("Not a valid option. \n\n");
                break; 
        }
    }
}

int Manual_Data_Input(Coordinate **points) {
    int quantity;
    printf("How many data points? ");
    scanf("%d", &quantity);
    if (quantity < 1) {
        printf("Not a valid amount \n");
        return -1;
    }

    *points = malloc(quantity * sizeof(Coordinate));
    if (*points == NULL) { 
        printf("Error in memory allocation for manually entered data. \n");
        return -1;
    }

    printf("Enter each coord (x, y) seperated by a space but with NO comma. \n");
    for (int i = 0; i < quantity; i++){
        if (scanf("%lf %lf", &(*points)[i].x, &(*points)[i].y) != 2){
            printf("Error with scanf. \n");
            return -1;
        }
    }

    return quantity;
}

int CSV_Data_Input(char *filename, Coordinate **points) {
    FILE *file_pointer = fopen(filename, "r");
    if (file_pointer == NULL) {
        printf("Error in opening file. \n");
        return -1;
    }

    *points = malloc(2 * sizeof(Coordinate));
    if (*points == NULL){
        printf("Error in memory allocation. \n");
        fclose(file_pointer);
        return -1;
    }

    int quantity = 0;
    int capacity = 2; 

    while (true) {
        if (quantity == capacity){
            capacity = capacity*2;
            Coordinate *temp = realloc(*points, capacity * sizeof(Coordinate));
            if (temp == NULL) {
                printf("Error in memory reallocation. \n");
                fclose(file_pointer);
                return -1;
            }
        
            *points = temp;
        }

        int scan_return = fscanf(
            file_pointer, "%lf , %lf", &(*points)[quantity].x, &(*points)[quantity].y);
        if (scan_return == 2){
            quantity++;
        }
        else if (scan_return == EOF){
            break;
        }
        else{
            printf("Bad data in CSV file. \n");
            fclose(file_pointer);
            return -1;
        }
    }

    fclose(file_pointer);
    return quantity;
}

void print_data(Coordinate *points, int quantity) {
    for (int i = 0; i < quantity; i++) {
        printf("%f, %f\n", points[i].x, points[i].y); 
    }
    printf("\n");
}

void calculate_sums(
    Coordinate *points, int quantity, double *sum_x, double *sum_y, double *sum_x_squared,
    double *sum_y_squared, double *sum_xy){
    
    *sum_x = 0;
    *sum_y = 0;
    *sum_x_squared = 0;
    *sum_y_squared = 0;
    *sum_xy = 0;

    for (int i = 0; i < quantity; i++){
        *sum_x += points[i].x;
        *sum_y += points[i].y;
        *sum_x_squared += points[i].x * points[i].x;
        *sum_y_squared += points[i].y * points[i].y;
        *sum_xy += points[i].x * points[i].y;
    }
}

void calculate_regression_results(
    int quantity, double sum_x, double sum_y, double sum_x_squared, double sum_y_squared,
    double sum_xy, double *slope, double *intercept, double *correlation_coefficient){

    double denominator = (quantity * sum_x_squared - sum_x * sum_x);
    *slope = (quantity * sum_xy - sum_x * sum_y) / denominator;
    *intercept = (sum_y * sum_x_squared - sum_x * sum_xy) / denominator;
    
    *correlation_coefficient = (quantity * sum_xy - sum_x * sum_y) / 
    (sqrt(quantity*sum_x_squared - sum_x * sum_x) * 
     sqrt(quantity * sum_y_squared - sum_y * sum_y ));
}

void print_sums(
        double sum_x, double sum_y, double sum_x_squared, double sum_y_squared, double sum_xy){
    printf("The sum of X is: %f \n", sum_x);
    printf("The sum of Y is: %f \n", sum_y);
    printf("The sum of X^2 is: %f \n", sum_x_squared);
    printf("The sum of Y^2 is: %f \n", sum_y_squared);
    printf("The sum of X*Y is: %f \n\n", sum_xy);
}

void print_results(double slope, double intercept, double correlation_coefficient){
    printf("The following are the results of the regression analysis: \n");
    printf("The slope is: %f \n", slope);
    printf("The intercept is: %f \n", intercept);
    printf("The correlation_coefficient is: %f \n\n", correlation_coefficient);
}

int CSV_Data_Export(Coordinate *points, int quantity){
    char filename[50];

    printf("What do you want to call your file? (include .csv at end) ");
    scanf("%49s", filename);

    FILE *filepointer = fopen(filename, "w"); 
    if (filepointer == NULL) {
        printf("Error in creating file. \n");
        return 1;
    }
    
    for (int i = 0; i < quantity; i++){
        fprintf(filepointer, "%f,%f\n", points[i].x, points[i].y);
    }

    fclose(filepointer);
    return 0;
}
