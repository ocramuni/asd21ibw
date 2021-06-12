#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 1000   // maximum size of a line of input

/**
 * Search longest border (naive algorithm)
 * @param s string
 * @param n s string length
 * @return max edge size
 */
int searchLongestBorderNaive(char *s, int n) {
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

int main () {
    char s[MAX_LINE_SIZE];
    scanf("%[^\n]s", s);
    int n = (int) strlen(s);

    // border
    int r = searchLongestBorderNaive(s, n);

    // period
    int p = n - r;

    printf("%d", p);
    return 0;
}