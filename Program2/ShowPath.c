#include <stdio.h>
#include <stdlib.h> //getenv() is stored in stdlib.h
#include <string.h> // strtok() is store in string.h

// -----
// Jacob Cappi
// Assignment 1
// 08 Feb 2020
// Tested with gcc on catalina.cs.uah.edu 
// -----

int printStrings(const char* args[]);

// Copies PATH into envString and prints to screen
int main(){
    int argc;
    const char* argv[100];

// ----- manually added vars
    char *envString; // stores getenv's return
    char *delimiter;
    int i; // all purpose counter variable

// ----- end of vars

// ----- Code :
    
    // getenv by default returns nulll-terminated string
    envString = getenv("PATH"); // getenv(const char*) returns char*
    delimiter = ":"; // assuming this as delimiter given the PATH

    envString = strtok(envString, delimiter); //grab first token
    
    i = 0;
    while(envString != 0){
        argv[i++] = envString; // store and increment 
        envString = strtok(0, delimiter); // clipping the used part
    }
    argv[i] = 0; // attatch zero from directions and to prevent faults

    printStrings(argv);
// ----- Code END

    return 0;
}

// Most likely needs no explanation
int printStrings(const char* args[]){
    
    int i;
    i = 0;

    while(args[i] != 0){
        printf("%s \n", args[i++]);
    }
    return 0;
}

