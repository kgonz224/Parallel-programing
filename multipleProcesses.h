/********************************************************************************
|
|	Source code:  multipleProcesses.h
|	Author:  Kevin Gonzalez
|	Student ID:  5702392
|	Assignment:  Program #6 - Run Children Run
|
|	Course:  COP 4338 (Programming III)
|	Section:  U01
|	Instructor:  William Feild
|	Due Date:  April 19th, 2018, class time
|
|	I hereby certify that this collective work is my own
|	and none of it is the work of any other person or entity.
|	______Kevin_Gonzalez_______________ [Signature]
|
|	Language:  C
|
*******************************************************************************/

#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MIN_ARGS 1
#define MAX_ARGS 7

#define MIN_ARG_VAL 1
#define MAX_ARG_VAL 9

#define FIRST_ARG_INDEX 1

#define BUFFER_SIZE 100

#define FAILED -1

typedef enum Boolean {FALSE, TRUE}  Bool;

void childProcess(const int, int*, int);
void displayMemory(int, int*);
void fillMemory(int, int*, char**);
void forkChildren(int, int*);
void waitForChildren(int);
Bool validArgs (int, char**);
