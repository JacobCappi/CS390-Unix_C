/* Program: lls.c -- Uses readdir to populate a dirent structure */

#define TRUE 1
#define FALSE 0

#include <dirent.h> /* used for directory struct and readdir */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -----
// Author : Jacob Cappi
// Date : 30 March 2021
// Program : myls.c 
// Tested on : catalina.cs.uah.edu w/ gcc
// ----- */
  
/* LS program, behaves like ls, but doesn't handle multiple
 * dir names */

int main(int argc, char **argv) {

    DIR *dir;
    struct dirent *direntry;

    int fileLocation = 1;
    int showHidden = FALSE;
    int setDir = FALSE;

    if(argc == 1){
        dir = opendir(".");
        setDir = TRUE;
    }
    else if(argc >= 2){
        if(strcmp(argv[1], "-a") == 0){
            showHidden = 1;
            fileLocation = 2;
            if(argc == 2){
                dir = opendir(".");
                setDir = TRUE;
            }
        }
        else if(argv[1][0] == '-'){
            printf("myls: Error: invalid option -- %s\nUsage myls [-a]\n", argv[1]);
            exit(0);
        }

    }
    /* Assuming that behavior 'ls [dir] [dir] ...' is not implemented*/
    if(argc >= 4){
        printf("myls: Error: Usage myls [-a] : Does not implement multiple dir files as per instruction\n");
        exit(0);
    }
    
    if(setDir == FALSE){
        if(argv[fileLocation][0] == '~'){
            char * path;
            argv[fileLocation]++;
            char *tmpChar = (char *)malloc(100);
            tmpChar = getenv("HOME"); 
            strcat(tmpChar, argv[fileLocation]);
            strcpy(argv[fileLocation], tmpChar);
        }
        if ((dir = opendir(argv[fileLocation])) == NULL){
            printf("myls: cannot open directory \'%s\': File does not Exist\n", argv[1]);
            exit(0);
        }
    }

    while ((direntry = readdir(dir)) != NULL){ /* Until entries are exhausted */
        if(direntry->d_name[0] != '.'){
            printf("%s\n", direntry->d_name);
        }
        else if (direntry->d_name[0] == '.' && showHidden == TRUE){
            printf("%s\n", direntry->d_name);
        }
    }

    closedir(dir);
    exit(0);
}
