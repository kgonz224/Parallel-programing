#	Makefile
#	Author:  Kevin Gonzalez
#	Student ID:  5702392
#	Assignment:  Program #6 - Run Children Run
#	Course:  COP 4338 (Programming III)
#	Section:  U01
#	Instructor:  William Feild
#	Due Date:  April 19th, 2018, class time
#
#	I hereby certify that this collective work is my own
#	and none of it is the work of any other person or entity.
#	______Kevin_Gonzalez_______________ [Signature]
#


PARENT = parentMain.c
PARENTOUT = parent.out
AUX = multProcess.c

build: $(PARENT)
	gcc $(PARENT) $(AUX) -o $(PARENTOUT)

test: $(PARENTOUT)
#! should produce errors
	make build
	! ./$(PARENTOUT)
	! ./$(PARENTOUT) 1 2 3 4 5 6 7 8
	! ./$(PARENTOUT) Ma boi Fred!
	! ./$(PARENTOUT) 0 1 2 3 4
	! ./$(PARENTOUT) 6 7 8 9 10
	! ./$(PARENTOUT) 1 2 1 4 5 4
	./$(PARENTOUT) 1
	./$(PARENTOUT) 1 2 3 4 5 6 7
	./$(PARENTOUT) 2 4 6 8


