#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_SIZE 11
#define DATA_COUNT 3192
#define NUM_YEARS 265 // 2015 - 1750

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

double yearlyAverages[NUM_YEARS];

/**
 * Function to get the count of data entries in a file.
 * This function reads a file named "GlobalTemperatures.csv" and counts the total entries of data.
 * It also prints out each line of data while counting.
 * @note Might remove this if global temp file is guaranteed a certain size
 * @return void
 */
void setValuesFromFile()
{
    FILE *file;
    file = fopen("GlobalTemperatures.csv", "r");
    if (file == NULL)
    {
        printf("Error: File not found\n");
        exit(1);
    }
    // Line shouldn't be more than 1024 characters? (Idk maybe lol)
    char line[1024];
    while (fgets(line, 1024, file))
    {
        // Skip header
        if (counter == -1)
        {
            counter++;
            continue;
        }
        // Split the line into tokens using comma as the delimiter
        char *token = strtok(line, ",");
        int index = 0;

        // Iterate through each token and assign values to the corresponding arrays
        while (token != NULL)
        {
            switch (index)
            {
            case 0:
                // Copy the date string to the date array
                strncpy(dt[counter], token, DATE_SIZE);
                dt[counter][DATE_SIZE - 1] = '\0'; // Null terminate the string
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

/**
 * This function uses fscanf to sort the values
 * Probably need to format the date using ints and storing the values overall is gonna be a huge hassle
 * but I can try getting this to work sometime later
 */
void setValuesFromFile2()
{
    FILE *file;
    file = fopen("GlobalTemperatures.csv", "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    while (fscanf(file, "%s,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", dt[counter], &lat[counter], &latu[counter], &lmt[counter], &lmtu[counter], &lmit[counter], &lmitu[counter], &loat[counter], &loatu[counter]) != EOF)
    {
        // Skip header
        if (counter == -1)
        {
            counter++;
            continue;
        }
        dt[counter][DATE_SIZE - 1] = '\0'; // Null terminate the string
        counter++;
    }
    fclose(file);
}
/**
 * Function to print the arrays
 * TESTING PURPOSES COMMENT OUT ON PRODUCTION
 */
void printArrays()
{
    for (int i = 0; i < counter; i++)
    {
        printf("Date: %s\n", dt[i]);
        printf("Land Average Temperature: %f\n", lat[i]);
        printf("Land Average Temperature Uncertainty: %f\n", latu[i]);
        printf("Land Max Temperature: %f\n", lmt[i]);
        printf("Land Max Temperature Uncertainty: %f\n", lmtu[i]);
        printf("Land Min Temperature: %f\n", lmit[i]);
        printf("Land Min Temperature Uncertainty: %f\n", lmitu[i]);
        printf("Land and Ocean Average Temperature: %f\n", loat[i]);
        printf("Land and Ocean Average Temperature Uncertainty: %f\n", loatu[i]);
    }
}

/**
 * Retrieves the position of an array based on a given date string.
 *
 * @param date The date string in the format "YYYY-MM-DD".`
 * @return The position in the array.
 */
int getArrPosition(char *date)
{
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3)
    {
        printf("Error: Invalid date format\n");
        exit(1);
    }
    return (year - 1750) * 12 + month - 1;
}

/**
 * Calculates the yearly averages of the latitudes.
 * The function iterates over each year and calculates the average latitude for that year.
 * The average latitude is calculated by summing up the latitudes for each month in the year and dividing by 12.
 * The calculated yearly averages are stored in the `yearlyAverages` array.
 */
void calcYearlyAverages()
{
    double sum = 0;
    for (int i = 0; i <= NUM_YEARS; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            sum += lat[i * 12 + j];
        }
        yearlyAverages[i] = sum / 12;
        sum = 0;
    }
}

/**
 * Based on the land average temperature column, calculate the yearly averages for each year
 * between 1760 and 2015 (the average of the twelve months of each year).
 * One average per year. Ignore the years 1750-1759.
 */
void q1()
{
    // 10 is the year 1760
    for (int i = 10; i <= NUM_YEARS; i++)
    {
        printf("Year: %d, Average: %f\n", i + 1750, yearlyAverages[i]);
    }
}
/**
 * Based on the land average temperature column, calculate the average land
 * temperature for the different centuries: 18th century (1760-1799), 19th century
 * (1800-1899), 20th century (1900-1999) and 21st century (2000-2015). One
 * average per century.ss
 *
 */
void q2()
{
    double avg_temp_18th, avg_temp_19th, avg_temp_20th, avg_temp_21th;

    // 18th century (1760-1799)
    for (int i = getArrPosition("1760-01-01"); i < getArrPosition("1799-12-01"); i++)
    {
        avg_temp_18th += lat[i];
    }
    // Print the average land temperature for the 18th century
    printf("18th century average land temperature: %f\n", avg_temp_18th / 480);

    // 19th century (1800-1899)
    for (int i = getArrPosition("1800-01-01"); i < getArrPosition("1899-12-01"); i++)
    {
        avg_temp_19th += lat[i];
    }
    // Print the average land temperature for the 19th century
    printf("18th century average land temperature: %f\n", avg_temp_19th / 1200);

    // 20th century (1900-1999)
    for (int i = getArrPosition("1900-01-01"); i < getArrPosition("1999-12-01"); i++)
    {
        avg_temp_20th += lat[i];
    }
    // Print the average land temperature for the 20th century
    printf("18th century average land temperature: %f\n", avg_temp_20th / 1200);

    // 21st century (2000-2015)
    for (int i = getArrPosition("2000-01-01"); i < getArrPosition("2015-12-01"); i++)
    {
        avg_temp_21th += lat[i];
    }
    // Print the average land temperature for the 21th century
    printf("18th century average land temperature: %f\n", avg_temp_21th / 191);
}
void q3()
{
    printf("Whatever q3 is ");
    // A little bit of trolling lmao
    //adadadadadad
}

int main(void)
{
    // Some updates here and there lololollolol
    // Call function to get data count
    setValuesFromFile();
    // Calculate the yearly averages
    calcYearlyAverages();
    q1();
    q2();
    return 0;
}