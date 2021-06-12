#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 1000   // maximum size of a line of input

/**
 * Search longest border (smart algorithm)
 * @param s string
 * @param n s string length
 * @return max border length
 */
int searchLongestBorderSmart(const char *s, int n) {

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

int main () {
    char s[MAX_LINE_SIZE];
    scanf("%[^\n]s", s);
    int n = (int) strlen(s);

    // border
    int r = searchLongestBorderSmart(s, n);

    // period
    int p = n - r;

    printf("%d", p);
    return 0;
}