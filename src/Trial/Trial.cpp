// Trial.cpp : Defines the entry point for the console application.
//
// Experiment/Trial purposes
// Shining <y.s.n@live.com>, 2014
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ChildClass.h"
#include <limits>

bool AreSame(double a, double b)
{
    return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
}


int find_char(char** strings, char c)
{
    char* s;
    while ((s = *strings++) != NULL) {
        while (*s != '\0') {
            if (*s++ == c) {
                return 1;
            }
        }
    }
    return 0;
}

int find_char2(char** strings, char c)
{
    while (*strings != NULL) {
        while (**strings != '\0') {
            if (*(*strings)++ == c) {
                return 1;
            }
        }
        strings++;
    }
    return 0;
}

int string_length(char* s)
{
    char* p = s;
    while (*p != '\0')
        p++;
    return p - s;
}

void swap(char* x, char* y)
{
    char c = *x;
    *x = *y;
    *y = c;
}

void resverse_string(char* s)
{
    int len = string_length(s);
    int m = len / 2;
    for (int i = 0; i < m; i++) {
        swap(s + i, s + len - 1 - i);
    }
}

void print_strings(char** s, int r)
{
    for (int i = 0; i < r; i++) {
        puts(*(s + i));
    }
}

//{{ Get max item from array recursively
template<class T>
T _find_max_recursively(T a[], int size, int index)
{
    if (index == size - 1) {
        return a[index];
    } else {
        T t = _find_max_recursively(a, size, index + 1);
        return a[index] > t ? a[index] : t;
    }
}

template<class T>
T find_max(T a[], int size)
{
    return _find_max_recursively(a, size, 0);
}

void test_case_find_max()
{
    int a[] = { 18, 21, 3, 4, 5, 62, 7, 83, 9 };
    printf("The max is: %d\n", find_max(a, sizeof(a) / sizeof(a[0])));
}
//}} Get max item from array recursively

void test_bit_fields()
{
    struct {
        unsigned char a : 4;
        unsigned char b : 4;
    } CHS;
    
    int n = 0;
    for (CHS.a = 1; CHS.a <= 9; CHS.a++) {
        for (CHS.b = 1; CHS.b <= 9; CHS.b++) {
            if (CHS.a % 3 != CHS.b % 3) {
                printf("%d: %d -- %d\n", ++n, CHS.a, CHS.b);
            }
        }
    }
}

void test_shift_operations()
{
    char c1 = 0x01;
    for (int i = 0; i < 32; i++) {
        printf("[%d, %u] ", c1 << i, c1 << i);
    }

    unsigned short s1 = 0xFFFF;
    for (int i = 0; i < 16; i++) {
        printf("[%d, %u] ", s1 >> i, s1 >> i);
    }
}

int remove_special_char(char* s)
{
    int n = 0;

    if (s) {
        while (*s) {
            if ((*s == '\t') || (*s == '\r') || (*s == '\n')) {
                n++;
            } else {
                if (n > 0) {
                    *(s - n) = *s;
                }
            }

            s++;
        }

        *(s - n) = '\0';
    }

    return n;
}

int main(int argc, char* argv[])
{
    int ret = -1;

    Calculator* pVObj = new CDerived();
    int n1 = pVObj->operator int();
    double d1 = pVObj->Calc(3.14, 2.0);

    /// Compare two floating point data
    if (d1 == 5.14) {
        ret = pVObj->operator int();
    }

    if (AreSame(d1, 5.14)) {
        ret = pVObj->operator int();
    }

    test_bit_fields();
    test_shift_operations();

#if 0
    char* s = _strdup("This is a string for testing.");
    puts(s);
    resverse_string(s);
    puts(s);
    free(s);
#else
    char str1[] = "Hello, world.";
    char str2[] = "perl -v";
    char str3[] = "linux-3.2.X.0-generic";
    char str4[] = "vim 7.4";
    char* strings[] = { str1, str2, str3, str4 };

    ret = find_char(strings, 'X');
    print_strings(strings, sizeof(strings) / sizeof(strings[0]));
    printf("\nFound: %s\n", ret ? "Yes" : "No");

    ret = find_char2(strings, 'X');
    print_strings(strings, sizeof(strings) / sizeof(strings[0]));
    printf("\nFound: %s\n", ret ? "Yes" : "No");
#endif

    test_case_find_max();

    char ss[] = "123\tyes\rabc\n\t{}109DHL.qbc\r\tAAA\n";
    printf("removed length: %d\n", remove_special_char(ss));
    printf("data: %s\n", ss);
    return 0;
}

