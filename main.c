#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

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

// Land Average Temperature Yearly Averages
double latYearlyAverage[NUM_YEARS];

// Land Max Temperature Yearly Averages
double lmtYearlyAverage[NUM_YEARS];

// Land Min Temperature Yearly Averages
double lmitYearlyAverage[NUM_YEARS];

// Land and Ocean Average Temperature Yearly Averages
double loatYearlyAverage[NUM_YEARS];

// Array of pointers to the yearly averages
// 0 is LAT
// 1 is LMT
// 2 is LMIT
// 3 is LOAT
double *yearlyAverages[] = {
    latYearlyAverage,
    lmtYearlyAverage,
    lmitYearlyAverage,
    loatYearlyAverage};

// Array of pointers to the data arrays
// 0 is LAT
// 1 is LMT
// 2 is LMIT
// 3 is LOAT
double *data[] = {
    lat,
    lmt,
    lmit,
    loat};

// Global array of file names
char fileNames[10][50] = {
    "Question-6.dat",
    "Question-7-1800.dat",
    "Question-7-1900.dat",
    "Question-8-lat.dat",
    "Question-8-lmt.dat",
    "Question-8-lmit.dat",
    "Question-9.dat",
    "Question-10.dat",
    "Question-11-Land.dat",
    "Question-11-Land and Ocean.dat"};
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

int getYearlyArrPosition(int year)
{
    return year - 1750;
}

/**
 * Calculates the yearly averages of the latitudes.
 * The function iterates over each year and calculates the average latitude for that year.
 * The average latitude is calculated by summing up the latitudes for each month in the year and dividing by 12.
 * The calculated yearly averages are stored in the `yearlyAverages` array.
 */
void calcYearlyAverages(double *values, double *yearlyAverages)
{
    // FILE* debugFile = fopen("debug.txt", "a");
    double sum = 0;
    for (int i = 0; i <= NUM_YEARS; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            sum += values[i * 12 + j];
        }
        yearlyAverages[i] = sum / 12;
        // fprintf(debugFile, "Year: %d, Average: %f\n", i + 1750, yearlyAverages[i]);
        sum = 0;
    }
    // fclose(debugFile);
}
/**
 * Computes the yearly average for different variables.
 * Calls the `calcYearlyAverages` function for each variable.
 */
void computeYearlyAverage()
{
    calcYearlyAverages(lat, latYearlyAverage);
    calcYearlyAverages(lmt, lmtYearlyAverage);
    calcYearlyAverages(lmit, lmitYearlyAverage);
    calcYearlyAverages(loat, loatYearlyAverage);
}

/**
 * Writes data to a file in GNUPlot format.
 * 
 * @deprecated Use writeColumns() instead
 * @param xvalues An array of integers representing the x-values.
 * @param yvalues An array of doubles representing the y-values.
 * @param xName The name of the x-axis.
 * @param yName The name of the y-axis.
 * @param size The size of the arrays.
 * @param fileName The name of the file to write the data to.
 * @param isAppended A flag indicating whether to append to an existing file (1) or create a new file (0).

 */
void writeGNUPlot(int *xvalues, double *yvalues, char *xName, char *yName, int size, char *fileName, int isAppended)
{
    FILE *file;
    // printf("Testing xValues 0 %d\n", xvalues[0]);
    // printf("Testing yValues 0 %lf\n", yvalues[0]);
    // printf("Testing xValues 1 %d\n", xvalues[1]);
    // printf("Testing yValues 1 %lf\n", yvalues[1]);
    switch (isAppended)
    {
    case 0:
        file = fopen(fileName, "w");
        break;
    case 1:
        file = fopen(fileName, "a");
        break;
    default:
        perror("Invalid file mode");
        return;
    }
    fprintf(file, "# %s vs %s\n", xName, yName);
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d %lf\n", xvalues[i], yvalues[i]);
    }
    fclose(file);
    printf("File written: %s\n", fileName);
}

/**
 * Writes data to a file in column format.
 *
 * @param size The number of elements in the arrays.
 * @param fileName The name of the file to write to.
 * @param isAppended Flag indicating whether to append to an existing file (1) or create a new file (0).
 * @param numColumns The number of columns in the data.
 * @param columnNames An array of strings representing the column names.
 * @param xValues An array of integers representing the x-values.
 * @param columns An array of arrays representing the data columns.
 * @param ... Optional additional columns to write.
 */
void writeColumns(int size, char *fileName, int isAppended, int numColumns, int xValues[], double columns[], ...)
{
    FILE *file;
    switch (isAppended)
    {
    case 0:
        file = fopen(fileName, "w");
        break;
    case 1:
        file = fopen(fileName, "a");
        break;
    default:
        perror("Invalid file mode");
        return;
    }
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    va_list args;
    va_start(args, columns);
    double *allArrays[numColumns];
    for (int i = 0; i < numColumns - 2; i++)
    {

        allArrays[i] = va_arg(args, double *);
    }
    va_end(args);
    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d ", xValues[i]);
        fprintf(file, "%lf ", columns[i]);
        for (int j = 0; j < numColumns - 2; j++)
        {
            fprintf(file, "%lf ", allArrays[j][i]);
        }
        fprintf(file, "\n");
    }
    printf("File written: %s\n", fileName);
}
/**
 * Based on the land average temperature column, calculate the yearly averages for each year
 * between 1760 and 2015 (the average of the twelve months of each year).
 * One average per year. Ignore the years 1750-1759.
 */
void q1()
{
    // 10 is the year 1760
    for (int i = getYearlyArrPosition(1760); i <= NUM_YEARS; i++)
    {
        printf("Year: %d, Average: %f\n", i + 1750, latYearlyAverage[i]);
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
    printf("19th century average land temperature: %f\n", avg_temp_19th / 1200);

    // 20th century (1900-1999)
    for (int i = getArrPosition("1900-01-01"); i < getArrPosition("1999-12-01"); i++)
    {
        avg_temp_20th += lat[i];
    }
    // Print the average land temperature for the 20th century
    printf("20th century average land temperature: %f\n", avg_temp_20th / 1200);

    // 21st century (2000-2015)
    for (int i = getArrPosition("2000-01-01"); i < getArrPosition("2015-12-01"); i++)
    {
        avg_temp_21th += lat[i];
    }
    // Print the average land temperature for the 21th century
    printf("21st century average land temperature: %f\n", avg_temp_21th / 191);
}

/**
 * Based on the land average temperature column, calculate the monthly averages
 * for each month for all years combined between 1900 and 2015. A total of twelve
 * averages. One average per month.
 */
void q3()
{
    // Declaring the variables sum and month
    double sum;

    // This loop will go through the 12 months of the year (January, Febuary, ......)
    for (int i = 0; i < 12; i++)
    {
        sum = 0;

        // This loops through the years between 1900 and 2015
        for (int j = getArrPosition("1900-01-01") + i; j < getArrPosition("2015-12-01"); j += 12)
        {
            sum += lat[j];
        }

        // This prints out the month average over the years of 1900 2015
        printf("This is the average from 1900 to 2015 for the month ");

        switch (i)
        {
        case 0:
            printf("January ");
            break;
        case 1:
            printf("February ");
            break;
        case 2:
            printf("March ");
            break;
        case 3:
            printf("April ");
            break;
        case 4:
            printf("May ");
            break;
        case 5:
            printf("June ");
            break;
        case 6:
            printf("July ");
            break;
        case 7:
            printf("August ");
            break;
        case 8:
            printf("September ");
            break;
        case 9:
            printf("October ");
            break;
        case 10:
            printf("November ");
            break;
        case 11:
            printf("December ");
            break;
        }
        printf("%lf\n", (sum / 116));
    }
}
/**
 * Based on the land average temperature column, what was the
 * hottest month recorded and what was the coldest month
 * recorded (month and year in each case). In case of a tie, mention
 * only one (doesn't matter which one).
 */
void q4()
{
    int hottestMonthPos = 0;
    int coldestMonthPos = 0;

    for (int i = 0; i < DATA_COUNT; i++)
    {
        if (lat[i] > lat[hottestMonthPos])
        {
            hottestMonthPos = i;
        }
        if (lat[i] < lat[coldestMonthPos])
        {
            coldestMonthPos = i;
        }
    }

    printf("Hottest month: %s, Temperature: %f\n", dt[hottestMonthPos], lat[hottestMonthPos]);
    printf("Coldest month: %s, Temperature: %f\n", dt[coldestMonthPos], lat[coldestMonthPos]);
}

/**
 * Based on your answer in question 1, what year was the hottest and what year was the coldest?
 */
void q5()
{
    int hottestYearPos = 0;
    int coldestYearPos = 0;

    // Use max and min double values to ensure the first
    // value is always greater or less than the current value
    double hottestYear = __DBL_MIN__;
    double coldestYear = __DBL_MAX__;
    for (int i = 10; i <= NUM_YEARS; i++)
    {
        if (latYearlyAverage[i] > hottestYear)
        {
            hottestYear = latYearlyAverage[i];
            hottestYearPos = i;
        }
        if (latYearlyAverage[i] < coldestYear)
        {
            coldestYear = latYearlyAverage[i];
            coldestYearPos = i;
        }
    }

    printf("Hottest year: %d, Temperature: %f\n", hottestYearPos + 1750, hottestYear);
    printf("Coldest year: %d, Temperature: %f\n", coldestYearPos + 1750, coldestYear);
}
/**
 * Based on your answer in question 1, generate a GNUPlot data file and use GNUPlot to
 * make a graph (line plot) of the yearly temperatures for the years 1760 to 2015.
 * Label the axes clearly and add a title and legend to your graph.
 */
void q6()
{
    int xvalues[NUM_YEARS];
    for (int i = 10; i <= NUM_YEARS; i++)
    {
        xvalues[i - 10] = i + 1750;
    }
    // Subtract 10 to avoid the last 10 years after 2015
    writeColumns(NUM_YEARS - 9, "Question-6.dat", 0, 2, xvalues, latYearlyAverage);
}

/**
 * Generate a GNUPlot data file and use GNUPlot to make a graph (line plots) of the average land temperatures for the 19th and 20th centuries.
 * Put both lines on the same figure. Ensure that you have the same x-axis scale (for example 1852 and 1952 would both have an x-value of 52).
 * Have your two line plots with different colours. Label the axes clearly and add a title and legend to your graph.
 */
void q7()
{
    int xvalues[101];
    double yvalues[101];
    double yvalues2[101];
    for (int i = 0; i <= 100; i++)
    {
        xvalues[i] = i;
        yvalues[i] = latYearlyAverage[getYearlyArrPosition(1800 + i)];
        yvalues2[i] = latYearlyAverage[getYearlyArrPosition(1900 + i)];
    }
    writeColumns(101, "Question-7-1800.dat", 0, 2, xvalues, yvalues);
    writeColumns(101, "Question-7-1900.dat", 0, 2, xvalues, yvalues2);
}

/**
 * Using the columns LandAverageTemperature, LandMaxTemperature and LandMinTemperature, generate a GNUPlot data file and use GNUPlot to make
 * line plots that show all three temperatures on the same figure. Use the years for the x-axis (use only the years between 1850 and 2015)
 * and the yearly averages for the y-axis. Use three different colours (or different line styles) for the three lines.
 * Make sure that the line plotting LandAverageTemperature stands out from the other two (ex: make that line thicker).
 * Make sure your graph has a title, axes labels and a legend that explicitly tells which line is which.

*/
void q8()
{
    int numYears = 2015 - 1850 + 1;
    int xvalues[numYears];
    double adjustedLatYearlyAverage[numYears];
    double adjustedLmtYearlyAverage[numYears];
    double adjustedLmitYearlyAverage[numYears];
    for (int i = 1850; i <= 2015; i++)
    {
        xvalues[i - 1850] = i;
        adjustedLatYearlyAverage[i - 1850] = latYearlyAverage[getYearlyArrPosition(i)];
        adjustedLmtYearlyAverage[i - 1850] = lmtYearlyAverage[getYearlyArrPosition(i)];
        adjustedLmitYearlyAverage[i - 1850] = lmitYearlyAverage[getYearlyArrPosition(i)];
        // printf("Year: %d, Adjusted Lat: %f, Adjusted Lmt: %f, Adjusted Lmit: %f\n", i,
        //     adjustedLatYearlyAverage[i - 1850],
        //     adjustedLmtYearlyAverage[i - 1850],
        //     adjustedLmitYearlyAverage[i - 1850]);
    }
    writeColumns(numYears, "Question-8-lat.dat", 0, 2, xvalues, adjustedLatYearlyAverage);
    writeColumns(numYears, "Question-8-lmt.dat", 0, 2, xvalues, adjustedLmtYearlyAverage);
    writeColumns(numYears, "Question-8-lmit.dat", 0, 2, xvalues, adjustedLmitYearlyAverage);
}

/**
 * Using the columns LandAverageTemperature, LandMaxTemperature and LandMinTemperature, generate a GNUPlot data file and use GNUPlot to make four bar
 * plots (box or histogram plos) that show the average, low and high temperatures for each of the four centuries.
 * Put all 4 century plots on the same figure displayed as subplots (multiplots).
 * Each plot will show the boxes with different colours (one colour per century).
 * Have a title to your figure and have the name of the century on each subplot. Have a legend on each subplot.
 */
void q9()
{
    int century[3] = {19, 20, 21};
    double latavg[3], max[3], min[3];
    double latTot = 0;
    int i;

    // 1800-1899
    latTot = 0;
    // summing the yearly average temperatures for the 19th century, then finding the average
    for (int i = getYearlyArrPosition(1800); i < getYearlyArrPosition(1900); i++)
    {
        latTot += latYearlyAverage[i];
    }
    latavg[0] = latTot / 100;
    // setting the first entry for land max/min temperatures as the highest/lowest value for comparison
    max[0] = lmt[getArrPosition("1850-01-01")];
    // checking the next temperature data entry and comparing to current max/min
    for (i = getArrPosition("1850-01-01"); i < getArrPosition("1900-01-01"); i++)
    {
        if (max[0] < lmt[i])
            max[0] = lmt[i];
    }
    min[0] = lmit[getArrPosition("1850-01-01")];

    for (i = getArrPosition("1850-01-01"); i < getArrPosition("1900-01-01"); i++)
    {
        if (min[0] > lmit[i])
            min[0] = lmit[i];
    }

    // 1900-1999
    latTot = 0;
    // summing the yearly average temperatures for the 20th century, then finding the average
    for (i = getYearlyArrPosition(1900); i < getYearlyArrPosition(2000); i++)
    {
        latTot += latYearlyAverage[i];
    }
    latavg[1] = latTot / 100;
    // setting the first entry for land max/min temperatures as the highest/lowest value for comparison
    max[1] = lmt[getArrPosition("1900-01-01")];
    for (i = getArrPosition("1900-01-01"); i < getArrPosition("2000-01-01"); i++)
    {
        if (max[1] < lmt[i])
            max[1] = lmt[i];
    }
    // checking the next temperature data entry and comparing to current max/min
    min[1] = lmit[getArrPosition("1900-01-01")];
    for (i = getArrPosition("1900-01-01"); i < getArrPosition("2000-01-01"); i++)
    {
        if (min[1] > lmit[i])
            min[1] = lmit[i];
    }

    // 2000-2015
    latTot = 0;
    // summing the yearly average temperatures for the 21st century, then finding the average
    for (i = getYearlyArrPosition(2000); i <= getYearlyArrPosition(2015); i++)
    {
        latTot += latYearlyAverage[i];
    }
    latavg[2] = latTot / 16;
    // setting the first entry for land max/min temperatures as the highest/lowest value for comparison
    max[2] = lmt[getArrPosition("2000-01-01")];
    for (i = getArrPosition("2000-01-01"); i <= getArrPosition("2015-12-01"); i++)
    {
        if (max[2] < lmt[i])
            max[2] = lmt[i];
    }
    // checking the next temperature data entry and comparing to current max/min
    min[2] = lmit[getArrPosition("2000-01-01")];
    for (i = getArrPosition("2000-01-01"); i <= getArrPosition("2015-12-01"); i++)
    {
        if (min[2] > lmit[i])
            min[2] = lmit[i];
    }
    // generating .dat file for gnuplot script
    writeColumns(3, "Question-9.dat", 0, 4, century, latavg, max, min);
}

/**
 * For the years 2000 to 2015, generate a GNUPlot data file and use GNUPlot to
 * make an error bar plot of the average land temperature by month. Use the
 * uncertainty column for land temperatures to draw the error bars.
 *
 */
void q10()
{
    // Declares variables for the x, y, and z values
    int x_values[192];
    double yvalues[192];
    double zvalues[192];

    // This loop will go through the 192 months of the year, the amount of months in 15 years
    for (int i = 0; i < 192; i++)
    {
        x_values[i] = i + 1;
    }

    // This loop goes through 192 months for 15 years getting the average land temperature and the uncertainty
    for (int i = 0; i < 192; i++)
    {
        yvalues[i] = lat[getArrPosition("2000-01-01") + i];
        zvalues[i] = latu[getArrPosition("2000-01-01") + i];
    }

    // This write the amount of months, average land temperature, and uncertainty to a file
    writeColumns(192, "Question-10.dat", 0, 3, x_values, yvalues, zvalues);
}
/**
 * Generate a GNUPlot data file and use GNUPlot to do a plot similar to what you
 * did in question 6 but only for the years 1850 to 2015 and add the data for the
 * land and ocean average temperatures columns. Have the three lines on the same
 * figure. Label the axes clearly and add a title and legend to your graph..
 */
void q11()
{
    int xvalues[166];
    double yvalues[166];
    double zvalues[166];

    for (int i = 0; i < 166; i++)
    {
        xvalues[i] = i + 1850;
        yvalues[i] = lmtYearlyAverage[i + 100];
        zvalues[i] = loatYearlyAverage[i + 100];
    }
    writeColumns(166, "Question-11-Land.dat", 0, 2, xvalues, yvalues);
    writeColumns(166, "Question-11-Land and Ocean.dat", 0, 2, xvalues, zvalues);
}
/**
 * @brief Cleans up files using the global array of file names.
 *
 * This function iterates over the global array of file names and removes each file using the `remove()` function.
 * The array size is assumed to be 10.
 */
void cleanup()
{
    // Remove files using the global array of file names
    for (int i = 0; i < 10; i++)
    {
        remove(fileNames[i]);
    }
}

int main(void)
{
    cleanup();
    // remove("debug.txt");
    // Some updates here and there lololollolol
    // Call function to get data count
    setValuesFromFile();
    // Calculate the yearly averages
    computeYearlyAverage();
    q1();
    q2();
    q3();
    q4();
    q5();
    q6();
    q7();
    q8();
    q9();
    q10();
    q11();
    // int arrPos = getYearlyArrPosition(1850);
    // printf("LAT 1850: %f, LMT 1850: %f, LMIT 1850: %f\n", latYearlyAverage[arrPos], lmtYearlyAverage[arrPos], lmitYearlyAverage[arrPos]);
    return 0;
}
