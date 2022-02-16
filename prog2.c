#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "prog2.h"

#include <string.h>
#include <time.h>
/**
* 
*  Function "stubs" for Assignment 2 exercises.
*
*  See prog2.h for specifications of function behavior.
*
*/



/***********************************************
*                                             **
*   MATRIX FUNCTIONS                          **
*                                             **
*   NOTE:  parameter n ALWAYS expresses the   **
*     dimensions of the square matrix in      **
*     question.                               **
*                                             **
***********************************************/
char ** alloc_square_mtx(int n) {
    char** square = (char**)malloc(n*sizeof(char*));
    for (int i = 0; i < n; i++) {
        square[i] = (char*)malloc(n*sizeof(char));
    }
    return square; 
}

void free_square_mtx(char **m, int n) {
    for (int i = 0; i<n; i++) {
        free(m[i]);
    }
}

void pop_mtx_alpha(char **m, int n){
    srand(time(NULL));
    char pool[] ="abcdefghijklmnopqrstuvwxyz";
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            m[x][y] = pool[rand() % 26];
        }
    }
}


void display_mtx(char **m, int n){
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            printf("%c", m[x][y]);
        }
        printf("\n");
    }
}

void swap_rows(char **m, int n, int r1, int r2){
    if (r2 >= n || r2 < 0 || r1 >= n || r1 < 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        char temp;
        temp = m[r2][i];
        m[r2][i] = m[r1][i];
        m[r1][i] = temp;
    }
}

void swap_cols(char **m, int n, int c1, int c2){
    if (c2 >= n || c2 < 0 || c1 >= n || c1 < 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        char temp;
        temp = m[i][c2];
        m[i][c2] = m[i][c1];
        m[i][c1] = temp;
    }
}


void rotate_right(char **m, int n){
    int x = 0;
    int y = 0;
    int prev, curr;
    int endrow = n;
    int endcol = n;
    while (x < endrow && y < endcol) {
        prev = m[x+1][y];
        for (int i = y; i<endcol; i++) {
            curr = m[x][i];
            m[x][i] = prev;
            prev = curr;
        }
        x++;
        for (int i = x; i < endrow; i++) {
            curr = m[i][endcol-1];
            m[i][endcol-1] = prev;
            prev = curr;
        }
        endcol--;
        if (x < endrow) {
            for (int i = endcol-1; i>= y; i--) {
                curr = m[endrow-1][i];
                m[endrow-1][i] = prev;
                prev = curr;
            }
        } 
        endrow--;
        if (y < endcol) {
            for (int i = endrow-1; i>= x; i-- ) {
                curr = m[i][y];
                m[i][y] = prev;
                prev = curr;
            }
        }
        y++;
    }
}


void floating_boulders(char **m, int n, int nb){
    srand(time(NULL));
    int boulders = 0;
    int seed = 0;
    if (nb >= n*n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                m[i][j] = '#';
            }
        }
        return;
    }
    while(boulders<nb) {
        int x = rand() % n;
        int y = rand() % n;
        if (m[x][y] != '#') {
            m[x][y] = '#';
            boulders++;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (m[i][j] != '#') {
                m[i][j] = '.';
            }
        }
    }
}


void mountains(char **m, int n){
    srand(time(NULL));
    char asset[] = ".#";
    char mount[n];
    // this code section is for generating the base of mountains randomly
    // for (int i = 0; i<n; i++) {
    //     int choice = rand() % 2;
    //     m[n-1][i] = asset[choice];
    //     mount[i] = choice;
    // }
    // for (int i = n-2; i >= 0; i--) {
    //     for (int j = 0; j < n; j++) {
    //         if (mount[j] == 1) {
    //             int choice = rand() % 2;
    //             m[i][j] = asset[choice];
    //             mount[j] = choice;
    //         } else {
    //             m[i][j] = '.';
    //         }
    //     }
    // }


    // this code section is for generating the height of mountains randomly
    for (int i = 0; i < n; i++) {
        mount[i] = rand() % (n+1);
        //commented code snippet is for debugging to check for intended mountain height
        //printf("%i Mountain height: %i\n", i, mount[i]);
    }
    for (int i = n-1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (mount[j] >= n-i) {
                m[i][j] = '#';
            } else {
                m[i][j] = '.';
            }
        }
    }
}



void sink(char **m, int n){
    char prev[n];
    char temp;
    for (int i = 0; i < n; i++) {
        prev[i] = m[0][i];
        m[0][i] = '.';
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (prev[j] == '.' && m[i][j] != '.') {
                prev[j] = m[i][j];
                m[i][j] = '.';
            } else {
                temp = prev[j];
                prev[j] = m[i][j];
                m[i][j] = temp;
            }
        }
    }
}



void gravity(char **m, int n){
    char prev[n];
    char temp;
    char **t;
    int x = 0;
    int y = 0;
    t = alloc_square_mtx(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            t[i][j]='.';
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = n-1; j >= 0; j--) {
            if (m[j][i] != '.') {
                t[x][y] = m[j][i];
                x++;
            } 
        }
        x = 0;
        y++;
    }
    y=0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = t[n-x-1][j];
        }
        x++;
    }
    free_square_mtx(t, n);
}




/***********************************************
*                                             **
*   STRING FUNCTIONS                          **
*                                             **
***********************************************/


void str_trim(char *s) {
    char* start = s;
    int length = strlen(s)+1;
    char* end = s + strlen(s) - 1;
    while (isspace(*start)) {
        start++;
        length--;
        if (*start == '\0') {
            return;
        }
    }
    while (isspace(*end)) {
        end--;
        length--;
    }
    for (int i = 0; i < length-1; i++) {
        s[i] = start[i];
        end--;
    }
    s[length-1] = '\0';
}


int str_search(char *s, char *pattern) {
    char* search = s;
    int index = 0;
    int found = 0;
    while (*search != '\0') {
        if (*search == pattern[0]) {
            found = 1;
            for (int i = 0 ; i < strlen(pattern)-1; i++) {
                if (search[i] != pattern[i]) {
                    found = 0;
                    continue;
                }
            }
            if (found == 1) {
                return index; //return index here if for loop fully executes
            }
        }
        search++;
        index++;
    }
    return -1;  // just a placeholder to make gcc happy for now

}





#ifndef _LIB  // DO NOT REMOVE THIS LINE!!!
              // IT DOESN"T CHANGE HOW YOUR PROGRAM
              // WORKS, BUT IT GIVES US A WAY TO CALL
              // YOUR FUNCTIONS FROM OUR CODE FOR
              // TESTING

/**
* Write a test driver in main below to exercise and
*   your function implementations.
*
* Think carefully about your test cases!
*/
int main(){

    char **m;
    // char **a;
    // a = alloc_square_mtx(3);
    m = alloc_square_mtx(8);
    mountains(m, 8);
    printf("\n");
    display_mtx(m, 8);
    // sink(m, 8);
    // printf("\n");
    // display_mtx(m, 8);

    // a[0][0] = 'a';
    // a[0][1] = 'b';
    // a[0][2] = 'c';
    // a[1][0] = 'd';
    // a[1][1] = 'e';
    // a[1][2] = 'f';
    // a[2][0] = 'g';
    // a[2][1] = 'h';
    // a[2][2] = 'i';
    // sink(a, 3);
    // printf("\n");
    // display_mtx(a, 3);

    // m[0][0]='.'; m[0][1]='^'; m[0][2]='.'; m[0][3]='.'; m[0][4]='8'; m[0][5]='.'; 
    // m[1][0]='.'; m[1][1]='^'; m[1][2]='#'; m[1][3]='#'; m[1][4]='.'; m[1][5]='.'; 
    // m[2][0]='#'; m[2][1]='.'; m[2][2]='.'; m[2][3]='.'; m[2][4]='.'; m[2][5]='#'; 
    // m[3][0]='#'; m[3][1]='.'; m[3][2]='#'; m[3][3]='@'; m[3][4]='.'; m[3][5]='$'; 
    // m[4][0]='&'; m[4][1]='#'; m[4][2]='#'; m[4][3]='#'; m[4][4]='.'; m[4][5]='#'; 
    // m[5][0]='.'; m[5][1]='.'; m[5][2]='#'; m[5][3]='#'; m[5][4]='*'; m[5][5]='.'; 
    // display_mtx(m, 6);
    // printf("\n");
    // gravity(m, 6);
    // display_mtx(m, 6);

    // char test[] = "abcd";
    // //str_trim(test);
    // printf("\n");
    // //printf("%s", test);
    // printf("%i\n", str_search(test, "dab"));
}

#endif        // DO NOT REMOVE THIS LINE!!!