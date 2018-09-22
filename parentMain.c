/********************************************************************************
|
|	Source code:  parentMain.c
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
|	Compile/Run:
| 		gcc parentMain.c multProcess.c -o parent.out
|			or
|		make
|
|		./parent.out a b c d e f g
|			// Where a-g is a unique number from [1-9]
|			// Not all arguments are required. Required minimum 1
|				arg, maximum 7
|
|	*Include header in Directory*
|
|	************************************************************************
|
|	Description: 	This program take command line arguments and launches
|			the same number of programs as command line arguments.
|			Each launched program changes a specific index in a
|			shared memory location and changes the value. The
|			original program will wait until the launched programs
|			are done and terminates. Each step is printed.
|
|	Input:		A series of unique integers from [1-9]. Minimum number of
|			of integers: 1; Maximum number of integers: 7.
|
|	Output:		Printed the main steps of the program.
|
|	Process:	The program's steps are as follows:
|
|			1.  Prints "Parent Starts"
|			2.  Prints "Validate Command Line Arguments"
|			3.  Validates Command Line Args
|			4.  Request shared memory (print)
|			5.  If successful prints "Recieved Shared Memory"
|			6.  Create pointer to shared memory (print)
|			7.  Populate shared memory (print)
|			8.  Print memory
|			9.  Fork children (print)
|			10. Parent waits for Children to finish (prints status)
|				and displays exit codes
|			11. Parent prints memory
|			12. Parent closes and removes shared memory (prints)
|			13. Parent finishes
|
|	Child:		1.  Starts (prints)
|			2.  Displays shared memory
|			3.  Displays private memory
|			4.  Updates memory (prints)
|			5.  Displays shared memory
|			6.  Exists and displays code
|
|	Required
|	Features Not
|	Included:	None
|
|	Known Bugs:  None; the program operates correctly.
|
*******************************************************************************/

#include "multipleProcesses.h"

int main (int argc, char *argv[])
{
	puts("Parent : Starts");
	puts("Parent : Validate Command Line Arguments");
	if(!validArgs(argc, argv))
	{
		return EXIT_FAILURE;
	}

	int status = 0;
	const int shmSize = argc - FIRST_ARG_INDEX;
	int shmID = FAILED;
	int *shmPtr = NULL;
	int privMem = FAILED;
	int *privMemPtr = &privMem;
	int pid = FAILED;

	puts("Parent : Request Shared Memory");
	shmID = shmget(IPC_PRIVATE, (shmSize * sizeof(int)), IPC_CREAT | 0666);
	if (shmID == FAILED)
	{
		puts("Request Failed. Try Again Another Time.");
		return EXIT_FAILURE;
	}

	puts("Parent : Recieves Shared Memory");

	shmPtr = (int*) shmat(shmID, NULL, 0);
	if(((int) shmPtr) != FAILED)
	{
		puts("Parent : Attaches Shared Memory");
	}

	puts("Parent : Fills Shared Memory");
	fillMemory(shmSize, shmPtr, argv);
	printf("Parent : ");
	displayMemory(shmSize, shmPtr);
	forkChildren(shmSize, privMemPtr);
	pid = getpid();
	if (privMem > FAILED)
	{
		childProcess(privMem, shmPtr, shmSize);
		printf("\tChild ID: %d Exiting with %d\n", (privMem + 1), EXIT_SUCCESS);
	}
	else
	{
		waitForChildren(shmSize);
		printf("Parent : ");
		displayMemory(shmSize, shmPtr);
		puts("Parent : Detaches Shared Memory");
		shmdt(shmPtr);
		puts("Parent : Removes Shared Memory");
		shmctl(shmID, IPC_RMID, NULL);
		puts("Parent : Completed\n");
	}
	return EXIT_SUCCESS;
}

