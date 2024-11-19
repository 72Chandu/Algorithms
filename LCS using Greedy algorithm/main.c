#include <stdio.h>
#include <string.h>
void greedyLCS(char* str1, char* str2) {
    int i = 0, j = 0; // Pointers to iterate over both strings
    int len1 = strlen(str1), len2 = strlen(str2);
    char lcs[100];    // Array to store LCS
    int lcsIndex = 0;

    // Iterate over both strings
    while (i < len1 && j < len2) {
        if (str1[i] == str2[j]) {
            // If characters match, add to LCS
            lcs[lcsIndex++] = str1[i];
            i++;
            j++;
        } else {
            // Move the pointer of the string with a smaller value
            if (str1[i] < str2[j]) {
                i++;
            } else {
                j++;
            }
        }
    }

    // Null-terminate the LCS string
    lcs[lcsIndex] = '\0';
    printf("LCS (Greedy Approach): %s\n", lcs);
}
int main() {
    char str1[] = "ABCBDAB";
    char str2[] = "BDCAB";

    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);
    greedyLCS(str1, str2);

    return 0;
}
/*
String 1: ABCBDAB
String 2: BDCAB
LCS (Greedy Approach): BCAB

*/
