#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_SIZE 10


// Accont's for header and skips over it
int counter = -1;

// Data Array
char (*dt)[DATE_SIZE];
// Land Average Temperature
double *LAT;
// Land Average Temperature Uncertainty
double *LATU;
// Land Max Temperature
double *LMT;
// Land Max Temperature Uncertainty
double *LMTU;
// Land Min Temperature
double *LMIT;
// Land Min Temperature Uncertainty
double *LMITU;
// Land and Ocean Average Temperature
double *LOAT;
// Land and Ocean Average Temperature Uncertainty
double *LOATU;


/**
 * Function to get the count of data entries in a file.
 * This function reads a file named "GlobalTemperatures.csv" and counts the total entries of data.
 * It also prints out each line of data while counting.
 * @note Might remove this if global temp file is guarenteed a certain size 
 * @return void
 */
void initializeVariables() {
    // If we want dynamic allocation of memory this can get complicated so just stick with 1024 till it breaks
    char line[1024];
    
    FILE *file = fopen("GlobalTemperatures.csv", "r");

    // Checks if file exists
    if (file == NULL) {
        printf("Error: File not found\n");
        return(1);
    }

    // Counts total entries of data and prints out data (May remove print part later)
    while (fgets(line, sizeof(line), file)) {
        counter++;
        printf("%s", line);
    }
    // Manually allocates memory for each array based on the count of data entries and data type
    dt = malloc(counter * sizeof(char[DATE_SIZE]));
    LAT = malloc(sizeof(double) * counter);
    LATU = malloc(sizeof(double) * counter);
    LMT = malloc(sizeof(double) * counter);
    LMTU = malloc(sizeof(double) * counter);
    LMIT = malloc(sizeof(double) * counter);
    LMITU = malloc(sizeof(double) * counter);
    LOAT = malloc(sizeof(double) * counter);
    LOATU = malloc(sizeof(double) * counter);

}

int main(void) {
    // Call function to get data count
    initializeVariables();
    return 0;
}