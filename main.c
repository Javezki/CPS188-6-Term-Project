#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_SIZE 10
#define DATA_COUNT 3193


// Accont's for header and skips over it
int counter = -1;

// Date 
char dt[DATA_COUNT][DATE_SIZE];
// Land Average Temperature 
double lat[DATA_COUNT];
// Land Average Temperature Uncertainty
double latu[DATA_COUNT];
// Land Max Temperature
double lmt[DATA_COUNT];
// Land Max Temperature Uncertainty
double lmtu[DATA_COUNT];
// Land Min Temperature
double lmit[DATA_COUNT];
// Land Min Temperature Uncertainty
double lmitu[DATA_COUNT];
// Land and Ocean Average Temperature
double loat[DATA_COUNT];
// Land and Ocean Average Temperature Uncertainty
double loatu[DATA_COUNT];
// Ocean Average Temperature
double oat[DATA_COUNT];
// Ocean Average Temperature Uncertainty
double oatu[DATA_COUNT];

/**
 * Function to get the count of data entries in a file.
 * This function reads a file named "GlobalTemperatures.csv" and counts the total entries of data.
 * It also prints out each line of data while counting.
 * @note Might remove this if global temp file is guaranteed a certain size 
 * @return void
 */
void setValuesFromFile() {
    FILE *file;
    file = fopen("GlobalTemperatures.csv", "r");
    if (file == NULL) {
        printf("Error: File not found\n");
        return 1;
    }
    // Line shouldn't be more than 1024 characters? (Idk maybe lol)
    char line[1024];
    while (fgets(line, 1024, file)) {
        // Skip header
        if (counter == -1) {
            counter++;
            continue;
        }
        // Split the line into tokens using comma as the delimiter
        char *token = strtok(line, ",");
        int index = 0;

        // Iterate through each token and assign values to the corresponding arrays
        while (token != NULL) {
            switch (index) {
                case 0:
                    // Copy the date string to the date array
                    strncpy(dt[counter], token, DATE_SIZE);
                    break;
                case 1:
                    // Convert the string to a double and assign it to lat array
                    lat[counter] = atof(token);
                    break;
                case 2:
                    // Convert the string to a double and assign it to latu array
                    latu[counter] = atof(token);
                    break;
                case 3:
                    // Convert the string to a double and assign it to lmt array
                    lmt[counter] = atof(token);
                    break;
                case 4:
                    // Convert the string to a double and assign it to lmtu array
                    lmtu[counter] = atof(token);
                    break;
                case 5:
                    // Convert the string to a double and assign it to lmit array
                    lmit[counter] = atof(token);
                    break;
                case 6:
                    // Convert the string to a double and assign it to lmitu array
                    lmitu[counter] = atof(token);
                    break;
                case 7:
                    // Convert the string to a double and assign it to loat array
                    loat[counter] = atof(token);
                    break;
                case 8:
                    // Convert the string to a double and assign it to loatu array
                    loatu[counter] = atof(token);
                    break;
                case 9:
                    // Convert the string to a double and assign it to oat array
                    oat[counter] = atof(token);
                    break;
                case 10:
                    // Convert the string to a double and assign it to oatu array
                    oatu[counter] = atof(token);
                    break;
                default:
                    break;
            }
            // Doesn't immediately set value to null, instead checks first string and moves onto next token
            // until there are no other tokens to view 
            token = strtok(NULL, ",");
            index++;
        }

        // Increment the counter after processing each line
        counter++;
    }
    fclose(file);
    printf("Data count: %d\n", counter);
}



int main(void) {
    // Call function to get data count
    setValuesFromFile();
    return 0;
}