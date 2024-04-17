#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>

const int n = 250;

void strdob(const char* src, char* dest, int start, int end) {
    int k = 0;
    while (dest[k] != '\0') k++;
    for (int i = start; i < end; i++) {
            dest[k++] = src[i];
    }
    dest[k++] = ' ';
    dest[k] = '\0';
}


char* func(const char* str) {
    char* dest = new char[n];
    dest[0] = '\0';
    for (int i = 1; i < n; i++) {
        int count = 0;
        for (int j = 0; j <= strlen(str); j++) {
          //  printf("%d |", count);
            if (!strchr(" \n", str[j]) && str[j] != '\0') {
                count++;
            }
            else {
                if (count == i) {
                  //  printf("%d %d %d\n", i, j, count);
                    strdob(str, dest, j - count, j);
                    break;
                }
                count = 0;
            }
        }
    }
    return dest;
}


int main() {
    char str[n];
    fgets(str, n, stdin);
    char* newstr = func(str);
    puts(newstr);
    return 0;
}
