#include <stdio.h>
#include <string.h>
#include "dbg.h"
#include "datastructs.h"


void Print_Menu(struct DataBase *db)
{
	if(db)
	{
		printf("Please select operation:\n");
		printf("\t1.) Add Record\n");
		printf("\t2.) Delete Record\n");
		printf("\t3.) Find Record\n");
		printf("\t4.) Get Record\n");
		printf("\t5.) List All Records\n");
		printf("\t6.) Quit Application\n");
	}
	else
	{
		printf("Please create or select a DataBase:\n");
		printf("\t1.) Create Database\n");
		printf("\t2.) Select Database\n");
		printf("\t3.) Quit Application\n");	
	}
	
	printf(">> ");
}

char *Read_String()
{
	return "Not Done";
}

int InteractiveLoop(struct DataBase *db)
{
	int running = 1;
	int UserInput = 0;
	int rc = 0;
	char *rs = NULL;
	
	printf("Welcome to Interactive Mode. Please entera selection:\n");
	
	while(running)
	{
		Print_Menu(db);
		rc = fscanf(stdin, "%d", &UserInput);
		check(rc, "Invaild Entry. Please enter the number for your selection.\n");
		
		if(db)
		{
			switch(UserInput)
			{
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					running = 0;
					break;
				default:
					sentinel("How did we get here"); //Need a real error message
			}
		}
		else
		{
			switch(UserInput)
			{
				case 1: //Create
					//Get Max Data
					printf("\nMax Length of text Fields>> ");
					int Max_Data;
					rc = fscanf(stdin, "%d", &Max_Data);
					check(rc, "Invaild Entry. Please enter the number for your selection.\n");

					//Get Max Row
					int Max_Row;
					printf("\nMax Number of Rows>> ");
					rc = fscanf(stdin, "%d", &Max_Row);
					check(rc, "Invaild Entry. Please enter the number for your selection.\n");

					//Get File Name

					fflush(stdin);

					printf("Enter File name of Database>> ");
					char *Path = malloc(Max_Data * sizeof(char));
					rs = fgets(Path, Max_Data -1, stdin);
					check(rs != NULL, "Failed to Read Path.");

					debug("Lets make a DB at %s! With %d Rows that are %d wide...", Path, Max_Row, Max_Data);

					// create Empty DB
					//check(Database_create(Path, Max_Data, Max_Row), "Error Creating DataBase file");		
					// Load DB
					break;
				case 2: //Select
					break;
				case 3: //Quit
					running = 0;
					break;
				default:
					sentinel("How did we get here"); //Need a real error message
			}
		}
		
		
		error:;
		
	} //end of while running loop
	
	printf("Exiting Application. Have a Great Day!\n");
	
	return 1;
}//end of InteractiveLoop
