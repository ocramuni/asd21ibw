#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define MIN_STRING_LENGTH           1000          // minimum size of strings to generate
#define MAX_STRING_LENGTH           500000        // maximum size of strings to generate
#define DIFFERENT_CHARS             3             // number of different characters of string
#define CHART_DATA_POINTS           100           // number of points to plot on chart
#define ERROR_MAX                   0.001         // maximum relative error
#define GENERATE_DISTRIBUTED_PERIOD 0             // generate a random string with period distributed on length
#define FILENAME                    "output.csv"  // name of output file
#define SAVE_TO_FILE                1             // save to FILENAME

/* Global variables */
double b;
long resolution;

/* Data point record */
struct Records {
    int length;
    double tmin_smart;
    double tmax_smart;
    double tn_smart;
    double tmin_naive;
    double tmax_naive;
    double tn_naive;
};

/**
 * Generate a random string
 * @param length length of random string
 * @return random string
 */
char *mkrndstr(ssize_t length) {
    char *randomString;

    if (length) {
        randomString = malloc(length +1);
        if (randomString) {
            int l;
            if (GENERATE_DISTRIBUTED_PERIOD == 1 ) {
                l = (int) (rand() % length ) + 1;
            } else {
                l = length;
            }
            for (ssize_t i = 0;i < l;i++) {
                /*
                 * Generate a float (randomNumber) that is between 0.0 and 1.0 and is inclusive.
                 * Multiply randomNumber with DIFFERENT_CHARS and take the Floor of the result. This will return an
                 *   integer (shift) that is between 0 and DIFFERENT_CHARS and is inclusive.
                 */
                float randomNumber;
                randomNumber = ((float) rand() / (float) (RAND_MAX)) * DIFFERENT_CHARS;
                double shift;
                shift = floorf(randomNumber);
                /*
                 * Add the shift integer to 97, which is the ASCII value of the character a. This will
                 *   return an inclusive value between 97 and 97 + DIFFERENT_CHARS, which will be the ASCII value of some character.
                 * Converting that value to a character will return a character.
                 * Repeat the above step as required to obtain a randomly generated string.
                 */
                randomString[i] = (char)(shift + 97);
            }
            if (GENERATE_DISTRIBUTED_PERIOD == 1 ) {
                /* Pad randomString with period */
                for (ssize_t j = l;j < length;j++) {
                    randomString[j] = randomString[ (j-1) % l + 1];
                }
            }
            /* Add NULL char to the end of string */
            randomString[length] = '\0';
        }
    }
    return randomString;
}

/**
 * Get string length from data point number (Nj=ab^j)
 * @param dp number for data point
 * @return string length
 */
int getStringLength(ssize_t dp) {
    int length;
    length = MIN_STRING_LENGTH * (pow (b, (double) dp));
    return length;
}

/**
 * Search longest border (smart algorithm)
 * @param s string
 * @param n s string length
 * @return max border length
 */
int searchLongestBorder(const char *s, int n) {

    int r[n];  /* create borders length array */
    r[0] = 0;  /* border length of first character is always 0 */

    int currentBorderLength = 0;
    for (ssize_t i = 1; i < n; ++i) {
        while (currentBorderLength > 0 && s[currentBorderLength] != s[i])
            currentBorderLength = r[currentBorderLength - 1];
        if (s[currentBorderLength] == s[i])
            ++currentBorderLength;

        r[i] = currentBorderLength;
    }
    return r[n-1];
}

/**
 * Search longest border (naive algorithm)
 * @param s string
 * @param n s string length
 * @return max border length
 */
int searchLongestBorderNaive(char *s, int n) { //
    char prefix[n];
    char suffix[n];
    int longestBorderLength = 0;

    int i = 1;
    while (i < n) {
        snprintf(prefix, n+1, "%.*s", i, &(s[0]));
        snprintf(suffix, n+1, "%s", &(s[n - i]));

        /* compare suffix and prefix */
        if (strcmp(prefix,suffix) == 0) {
            longestBorderLength = (int) strlen(prefix);
        }
        i++;

    }
    return longestBorderLength;
}

/**
 * Get system clock resolution
 * @return clock resolution in nano seconds
 */
long getResolution() {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while(start.tv_nsec == end.tv_nsec);
    return (end.tv_nsec - start.tv_nsec);
}

/**
 * Get period of a string length n with smart algorithm
 * @param n length of string
 * @param s string
 * @return period of longest border
 */
int PeriodSmart(char *s, int n) {
    /* Get longest border */
    int r = searchLongestBorder(s, n);

    /* Period */
    int p = n - r;

    return p;
}

/**
 * Get period of a string length n with naive algorithm
 * @param n length of string
 * @param s string
 * @return period of longest border
 */
int PeriodNaive(char *s, int n) {
    /* Get longest border */
    int r = searchLongestBorderNaive(s, n);

    /* Period */
    int p = n - r;

    return p;
}

/**
 * Search longest border of a string of length n and return average time
 * @param n string length
 * @param record data_point record
 * @param use_smart use smart or naive algo
 */
void get_period_time(int n, struct Records *record, int use_smart) {
    clock_t start, end, w_start;

    start = clock();
    /* Do the work. */
    ssize_t k = 0;
    double max_time = 0;
    double min_time = start;
    do {
        /* Reset start time on every loop */
        w_start = clock();
        /* Generate random string */
        char *mystring;
        mystring = mkrndstr(n);
        //printf("Mystring string: %s\n", mystrings);
        /* Get period of string */
        int p;
        if (use_smart == 1) {
            p = PeriodSmart(mystring, n);
        } else {
            p = PeriodNaive(mystring, n);
        }
        // TODO save list of period length
        // printf("Period of string length %d: %d\n", n, p);
        free(mystring);
        end = clock();
        /* Save longest period search time */
        if ((double) (end - w_start) > max_time) {
            max_time = (double) (end - w_start);
        };
        /* Save shortest period search time */
        if ((double) (end - w_start) < min_time) {
            min_time = (double) (end - w_start);
        };
        k++;
    } while ((double)(end - start) < ((double) resolution / ERROR_MAX + (double) resolution));
    /* Average time */
    double tn;
    tn = (double)(end - start) / (double) k;
    if (use_smart == 1) {
        record->tn_smart = (tn / CLOCKS_PER_SEC);
        record->tmin_smart = (min_time / CLOCKS_PER_SEC);
        record->tmax_smart = (max_time / CLOCKS_PER_SEC);
    } else {
        record->tn_naive = (tn / CLOCKS_PER_SEC);
        record->tmin_naive = (min_time / CLOCKS_PER_SEC);
        record->tmax_naive = (max_time / CLOCKS_PER_SEC);
    }
}

int main (void) {
    /* Initializes random number generator */
    time_t t;
    srand((unsigned) time(&t));

    /* Initialize global variables */

    /* Get b parameter needed to calculate string length based on position on x-axis */
    b = (double) exp(((double) log(MAX_STRING_LENGTH) - (double) log(MIN_STRING_LENGTH)) / (CHART_DATA_POINTS - 1));

    /* Get CPU clock resolution */
    resolution = getResolution();
    //printf("Resolution: %ld\n", resolution);

    struct Records data_points[CHART_DATA_POINTS];

    FILE *outfile;
    if (SAVE_TO_FILE == 1) {
        // open file for writing
        outfile = fopen (FILENAME, "w");
        if (outfile == NULL)
        {
            fprintf(stderr, "\nError open file\n");
            exit (1);
        }
        // Write csv column labels
        fprintf(outfile, "length,tmin_smart,tn_smart,tmax_smart,tmin_naive,tn_naive,tmax_naive\n");
    }

    /* Do the work. */
    for (ssize_t i = 0; i < CHART_DATA_POINTS; i++) {
        /* Get string length */
        int length;
        length = getStringLength(i);
        data_points[i].length = length;
        /* Search longest period on string of length n with smart algo */
        get_period_time(length, &data_points[i], 1);
        /* Search longest period on string of length n with naive algo */
        get_period_time(length, &data_points[i], 0);
        /* string length,time min smart,time average smart,time max smart,time min naive,time average naive,time max naive */
        if (SAVE_TO_FILE == 1) {
            fprintf(outfile,  "%d,%f,%f,%f,%f,%f,%f\n",
                    data_points[i].length,
                    data_points[i].tmin_smart,
                    data_points[i].tn_smart,
                    data_points[i].tmax_smart,
                    data_points[i].tmin_naive,
                    data_points[i].tn_naive,
                    data_points[i].tmax_naive);
        } else {
            printf("%d,%f,%f,%f,%f,%f,%f\n",
                   data_points[i].length,
                   data_points[i].tmin_smart,
                   data_points[i].tn_smart,
                   data_points[i].tmax_smart,
                   data_points[i].tmin_naive,
                   data_points[i].tn_naive,
                   data_points[i].tmax_naive);
        }
    }

    if (SAVE_TO_FILE == 1) {
        // Close file
        fclose(outfile);
    }
}