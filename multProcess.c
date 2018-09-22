/********************************************************************************
|
|	Source code:  multProcess.c
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
|	*Include header file in directory*
|
*******************************************************************************/

#include "multipleProcesses.h"

/******************************childProcess*************************************
|
|	Function:	displayMemory(int, int*, int);
|
|	Purpose:	Gets the process's private index and shared memory to
|				square the value at the private index.
|
|	@author:	Kevin Gonzalez
|	@date:		April 19th, 2018
|
|	@param:		int privMem
|				Size of shm arrays
|
|	@param:		int* shm
|				Shared memory
|
|	@param:		int shmSize
|				Size of shared memory (used in
|							displayMemory(...))
|
*******************************************************************************/

void childProcess(const int privMem, int* shm, int shmSize)
{

	printf("\tChild ID: %d ", (privMem + 1));
	displayMemory(shmSize, shm);
	printf("\tChild ID: %d My Private Memory : {INDEX : %d; VALUE : %d}\n",
					(privMem + 1), privMem, shm[privMem]);
	printf("\tChild ID: %d Updates Shared Memory\n", (privMem + 1));
	shm[privMem] *= (privMem + 1);
	printf("\tChild ID: %d ", (privMem + 1));
	displayMemory(shmSize, shm);
	return;
}

/******************************displayMemory************************************
|
|	Function:	displayMemory(int, int*);
|
|	Purpose:	Gets a pointer to an array and displays its content.
|
|	@author:	Kevin Gonzalez
|	@date:		April 18th, 2018
|
|	@param:		int arrSize
|				Size of shm arrays
|
|	@param:		int* shm
|				An array of shared integer memory.
|
*******************************************************************************/

void displayMemory(int shmSize, int* shm)
{
	int shmIndex = -1;
	char buffer[BUFFER_SIZE] = {"Shared Memory  ["};
	for (shmIndex = 0; shmIndex < shmSize; shmIndex++)
	{
		if(shmIndex == (shmSize - 1))
		{
			sprintf(buffer, "%s%d%s", buffer, shm[shmIndex], "]");
		}
		else
		{
			sprintf(buffer, "%s%d%s", buffer, shm[shmIndex], ", ");
		}
	}

	printf("%s\n", buffer);

	return;
}

/*********************************fillMemory************************************
|
|	Function:	fillMemory(int, int*, char**);
|
|	Purpose:	Gets a pointer to an array and populates another array
|			with its content.
|
|	@author:	Kevin Gonzalez
|	@date:		April 18th, 2018
|
|	@param:		int shmSize
|				Size of smh arrays
|
|	@param:		int* shm
|				An array of shared integer memory.
|
|	@param:		char **argv
|				A character array containing the arguments
|				passed through the command line.
|
*******************************************************************************/

void fillMemory(int shmSize, int* shm, char** argv)
{
	int shmIndex = -1;
	for (shmIndex = 0; shmIndex < shmSize; shmIndex++)
	{
		shm[shmIndex] = atoi(argv[shmIndex + FIRST_ARG_INDEX]);
	}

	return;
}

/******************************forkChildren*************************************
|
|	Function:	forkChildren(int, int*);
|
|	Purpose:	Forks the amount of children specified and stores their
|			fid in the array.
|
|	@author:	Kevin Gonzalez
|	@date:		April 18th, 2018
|
|	@param:		int shmSize
|				Size of smh array
|
|	@param:		int* fidArr
|				An array storing the children's pid.
|
|	@param:		int* privMem
|				Assigns private memory in privMem.
|
*******************************************************************************/

void forkChildren(int shmSize, int* privMem)
{
	int child = -1;
	int fid = FAILED;
	for (child = 0; child < shmSize; child++)
	{
		if (fid != 0)
		{
			fid = fork();
			if (fid == 0)
			{
				printf("\tChild ID: %d I've come to life!\n",
								(child + 1));
				*privMem = child;
			}
		}

		if (fid != 0)
		{
			if (fid > FAILED)
			{
				printf("Parent : Forks Child %d\n", (child + 1));
			}
			else
			{
				printf("Fork %d failed, trying again...\n",
								(child + 1));
				child--;
				sleep(1); //1 second
			}

		} // End of parent call.

	} // End of for

	return;
}


/*******************************waitForChildren*********************************
|
|	Function:	waitForChildren(int);
|
|	Purpose:	Gets the number of children and waits for that amount.
|
|	@author:	Kevin Gonzalez
|	@date:		April 19th, 2018
|
|	@param:		int argc
|				Number of children waiting for.
|
*******************************************************************************/

void waitForChildren (int numChild)
{
	int childrenComp = FAILED;
	int completedPID = FAILED;
	int status = FAILED;

	for(childrenComp = 0; childrenComp < numChild; childrenComp++)
	{
		puts("Parent : Waits for Children");
		completedPID = wait(&status);
		printf("Parent : Detects Child %d Completion\n", completedPID);
		printf("Parent : Child %d's exit code is %d\n", completedPID,
									status);
	}

	puts("Parent : All Children Accounted For");
	return;
}

/***********************************validArgs***********************************
|
|	Function:	validArgs(int, char**);
|
|	Purpose:	Gets command line arguments and determines whether the
|			put is valid for this program. This function will
|			form users of possible errors.
|
|	@author:	Kevin Gonzalez
|	@date:		April 17th, 2018
|
|	@param:		int argc
|				Number of arguments passed through the command
|				line.
|
|	@param:		char **argv
|				A character array containing the arguments
|				passed through the command line.
|
|	@return:	Bool valid
|				Returns TRUE if there is valid input. Returns
|				put is invalid.
|
*******************************************************************************/

Bool validArgs (int argc, char**argv)
{
	Bool valid = TRUE;
	int argVal = 0;
	int argIndex = 0;
	Bool duplicate[MAX_ARG_VAL] = {0};

	if ((MIN_ARGS > (argc - 1)) || ((argc - 1) > MAX_ARGS))
	{
		valid = FALSE;
		printf(" Incorrect number of command line arguments. There "
			"must be a minimum of %d and a maximum of %d.\n"
			" Keep in mind argument values should be unique "
			"integers from %d to %d.\n\n", MIN_ARGS, MAX_ARGS,
			MIN_ARG_VAL, MAX_ARG_VAL);
	} // End of argc if Validation

	else
	{
		for (argIndex = FIRST_ARG_INDEX; argIndex <= (argc - 1);
								argIndex++)
		{
			argVal = atoi(argv[argIndex]);
			if ((argVal < MIN_ARG_VAL) || (argVal > MAX_ARG_VAL))
			{
				valid = FALSE;
				printf(" Incorrect argument value. Should be "
					"an integer in range [%d-%d]. Check "
					"argument %d.\n Keep in mind integers "
					"must be unique.\n\n", MIN_ARG_VAL,
					MAX_ARG_VAL, argIndex);
			}

			else if (duplicate[argVal] == TRUE)
			{
				valid = FALSE;
				printf(" Duplicate value found. Make "
					"argument %d unique.\n\n",
					argIndex);
			}
			else
			{
				duplicate[argVal] = 1;
			} // End of duplicate check

		} // End of for loop

	} // End of argc else
	return valid;
}

