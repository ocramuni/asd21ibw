#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define MIN_STRING_LENGTH 1000   // minimum size of string to generate
#define MAX_STRING_LENGTH 500000 // maximum size of string to generate
#define DIFFERENT_CHARS   3      // number of different character of string
#define CHART_DATA_POINTS 100    // number of points to plot on chart
#define ERROR_MAX         0.001  // maximum relative error

/* Global variables */
double b;
long resolution;

/**
 * Generate a random string with period ~ length
 * @param length length of random string
 * @return random string
 */
char *mkrndstr(size_t length) {
    char *randomString;

    if (length) {
        randomString = malloc(length +1);
        if (randomString) {
            for (size_t i = 0;i < length;i++) {
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
            /* Add NULL char to the end of string */
            randomString[length] = '\0';
        }
    }
    return randomString;
}

/**
 * Generate a random string with period distributed on length
 * @param length length of random string
 * @return random string
 */
char *mkrndstrdistrib(size_t length) {
    char *randomString;

    if (length) {
        randomString = malloc(length +1);
        if (randomString) {
            int q;
            q = (int) (rand() % length ) + 1;
            for (size_t i = 0;i < q;i++) {
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
            for (size_t j = q;j < length;j++) {
                randomString[j] = randomString[ (j-1) % q + 1];
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
int getStringLength(size_t dp) {
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
    for (size_t i = 1; i < n; ++i) {
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
 * Search longest border (with smart algo) of a string of length n and return average time
 * @param n string length
 * @return average time
 */
double get_average_time_smart(int n) {
    clock_t start, end;

    start = clock();
    /* Do the work. */
    size_t k = 0;
    do {
        /* Generate random string */
        char *mystring;
        mystring = mkrndstrdistrib(n);
        //printf("Mystring string: %s\n", mystrings);
        /* Get period of string */
        int p;
        p = PeriodSmart(mystring, n);
        //printf("Period of string length %d: %d\n", n, p);
        free(mystring);
        end = clock();
        k++;
    } while ((double)(end - start) < ((double)resolution /ERROR_MAX + (double)resolution));
    /* Average time */
    double tn;
    tn = (double)(end - start) / (double) k;
    return (tn / CLOCKS_PER_SEC);
}

/**
 * Search longest border (with naive algo) of a string of length n and return average time
 * @param n string length
 * @return average time
 */
double get_average_time_naive(int n) {
    clock_t start, end;

    start = clock();
    /* Do the work. */
    size_t k = 0;
    do {
        /* Generate random string */
        char *mystring;
        mystring = mkrndstrdistrib(n);
        //printf("Mystring string: %s\n", mystrings);
        /* Get period of string */
        int p;
        p = PeriodNaive(mystring, n);
        //printf("Period of string length %d: %d\n", n, p);
        free(mystring);
        end = clock();
        k++;
    } while ((double)(end - start) < ((double)resolution /ERROR_MAX + (double)resolution));
    /* Average time */
    double tn;
    tn = (double)(end - start) / (double) k;
    return (tn / CLOCKS_PER_SEC);
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

    /* Do the work. */
    for (size_t i = 0; i < CHART_DATA_POINTS; i++) {
        /* Get string length */
        int length;
        length = getStringLength(i);
        /* Search longest period on string of length n and return average time */
        double average_time_smart;
        double average_time_naive;
        average_time_smart = get_average_time_smart(length);
        average_time_naive = get_average_time_naive(length);
        printf("String length: %d - Average time smart: %f\n", length, average_time_smart);
        printf("String length: %d - Average time naive: %f\n", length, average_time_naive);
    }
}