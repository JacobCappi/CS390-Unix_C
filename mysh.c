/* Name: Jacob Cappi (just in case) */
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h> /* use of system calls */
#include <sys/types.h> /* directories */
#include <sys/stat.h> /* directories */
#include <string.h> /* string tokeniser */
#include <unistd.h> /* lots of system calls */

/* -----
// Author : Jacob Cappi
// Date : 21 Feb 2021
// Program : mysh.c
// Requires : sys/file.h
// Tested on : catalina.cs.uah.edu w/ gcc
// ----- */

/* -----
// Note: all on one file as directions only specified one file name
// Sorry: I still tried to organize as best I could
// ----- */

int main(){

/* ----- START List of Vars */
    char *command[50]; /* command line */
    char *commandString; /* General Use char * */

    const char *commandList[20]; /* List of Commands*/
    char *tmpToken; /* issues with assignment */
    
    char *delimiter;
    char *charDisplay; /* the PS1 */
    int flag; /* general purpose bool flag */
    int i;

    int fd; 
    int outputFile;
    char *buffer;
    struct stat sb; /* stat.h directory checker */
/* ----- END */

    delimiter = " ";
    charDisplay = (char*)malloc(40); /* Default PS1 = "$ "*/
    memset(charDisplay, ' ', 2);
    memset(charDisplay, '$', 1);
   
/* ----- START List of commands for easy conversion*/

/* this is dumb, but it was an easy fix to a wierd issue */
    char stringOfCommands[50] = "echo PS1 cat cp rm mkdir rmdir -n exit last" ; /* issues with assignment */
    tmpToken = strtok(stringOfCommands, delimiter);

    i=0;
    while(tmpToken != 0){
        commandList[i++] = tmpToken;
        tmpToken = strtok(0, delimiter);
    }
    commandList[i] = 0;
/* ----- END */

    while(1){
    /* ----- START fetching the command */
        printf("%s", charDisplay);
        commandString = (char*)malloc(100); /* Assuming command to not exceed 100; */
        fgets(commandString, 100, stdin);
    /* ----- END */


    /* ----- START parsing the command */
        commandString = strtok(commandString, delimiter);    

        i=0;
        while(commandString != 0){
            command[i++] = commandString;
            commandString = strtok(0, delimiter);
        }
        command[i] = 0;
    /* ----- END */

    /* ----- START Logic: */
        /* ----- START echo */
        if(strcmp(command[0], commandList[0]) == 0){
            i=1;
            flag = 0;

            if(strcmp(command[1], commandList[7]) == 0){
                i=2;
                flag = 1;
            }
            /* simple fix to weird issue, will check later */
            while(command[i] != 0){
                if(command[++i] == 0 && flag == 1){
                    command[--i][strlen(command[i])-1] = 0;
                    i++;
                }
                i--;
                /* dumb formatting */
                if(i == 1 || (flag == 1 && i == 2)){
                    printf("%s", command[i++]);
                }
                else{
                    printf(" %s", command[i++]);
                }
            }
        }
        /* ----- END */

        /* ----- START PS1 (don't ask, no spaces makes parsing impossible) */
        else if(command[0][0] == 'P' && command[0][1] == 'S' && command[0][2] == '1'&& command[0][3] == '='){
            i=4;
            flag = 0;
            memset(charDisplay, 0, 40);
            while(command[0][i] != 0){
                charDisplay[flag++] = command[0][i++];
            }
            charDisplay[--flag] = ' ';
        }
        /* ----- END */

        /* ----- START cat */
        /* assuming cat opens -> reads -> closes -> : */
        else if(strcmp(command[0], commandList[2]) == 0){
            i = 1;

            while(command[i] != 0){
                /* code from echo to remove enter */
                buffer = (char *)malloc(100);

                if(command[++i] == 0){
                    command[--i][strlen(command[i])-1] = 0;
                    i++;
                }
                --i;
                
                fd = open(command[i++], O_RDONLY);
                if(fd < 0){
                    printf("\nError: %s does not exist\n", command[--i]);
                    break;
                }
                else{
                    while(read(fd, buffer, 100) != 0){
                        printf("%s", buffer);
                    /* issue with overflow*/
                        memset(buffer, 0, 100);
                    }
                }
                free(buffer);
                close(fd);
            }
        }
        /* ----- END */

        /* ----- START cp */
        else if(strcmp(command[0], commandList[3]) == 0){
            fd = open(command[1], O_RDONLY, 0);
            if(fd < 0){
                printf("Error: Copy File does not exist\n");
            }
            else{
                buffer = (char *)malloc(100);
                command[2][strlen(command[2])-1] = 0;

                outputFile = creat(command[2], 0700);
                if(outputFile < 0){
                    printf("Error: could not create file\n");
                }
                else{
                    while(read(fd, buffer, 100) != 0){
                        write(outputFile, buffer, 100);
                        memset(buffer, 0, 100);
                    }
                }
            }
        }
        /* ----- END */

        /* ----- START rm */
        else if(strcmp(command[0], commandList[4]) == 0){
            i=1;
            while(command[i] != 0){
                if(command[++i] == 0){
                    command[--i][strlen(command[i])-1] = 0;
                    i++;
                }
                --i;

                fd = open(command[i], O_RDONLY);
                if(fd < 0){
                    printf("\nError: %s does not exist\n", command[1]); 
                    break;
                }
                else{
                    unlink(command[i++]);
                }
                close(fd);

            }
        }
        /* ----- END */

        /* ----- START mkdir */
        else if(strcmp(command[0], commandList[5]) == 0){
            i=1;
            while(command[i] != 0){
                if(command[++i] == 0){
                    command[--i][strlen(command[i])-1] = 0;
                    i++;
                }
                --i;

                if(stat(command[i], &sb) == 0 && S_ISDIR(sb.st_mode)){
                    printf("Error: folder %s already exists", command[i]);
                    break;
                }

                outputFile = mkdir(command[i++], 0700);
                if(outputFile == 1){
                    printf("\nError: %s not created", command[--i]); 
                    break;
                }

            }
        }
        /* ----- END */

        /* ----- START rmdir */
        else if(strcmp(command[0], commandList[6]) == 0){
            i=1;
            while(command[i] != 0){
                if(command[++i] == 0){
                    command[--i][strlen(command[i])-1] = 0;
                    i++;
                }
                --i;

                if(stat(command[i], &sb) == 0 && S_ISDIR(sb.st_mode)){
                    rmdir(command[i++]);
                }
                else{
                    printf("Error: file not deleted");
                    break;
                }

            }

        }
        /* ----- END */

        /* ----- START exit (issue with auto newlines and stuff); */
        else if(strcmp(command[0], "exit\n") == 0){
            break;
        }
        /* ----- END */

        /* ----- START Usage */
        else{
            printf("\nUsage:\nCommands: echo PS1= cat cp rm mkdir rmdir exit");
            printf("\necho: [-n] repeats whatever is after echo.\n\t-n removes newline");
            printf("\nPS1= : set PS1= to something (max 38 char no spaces) | ex) PS1=$ PS1=Hello");
            printf("\ncat: cats a file or multiple files | ex) cat file1 file2");
            printf("\ncp: copies one file to another (2 parameters) | ex) cp file1 file2");
            printf("\nrm: removes a file or multiple files | ex)rm file1 file2");
            printf("\nmkdir: makes one or more dirs | ex) mkdir dir1 dir2");
            printf("\nrmdir: deletes one or more dirs | ex) rmdir dir1 dir2");
            printf("\nexit: exits from shell | ex) exit\n\n");


        }
    /* ----- END */
        free(commandString);
    }

    return 0;
}
