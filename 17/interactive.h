#include <stdio.h>
#include <string.h>
#include "dbg.h"
#include "datastructs.h"
#include "UserInput.h"

int Remove_NewLine(char *theString, int MaxLength, int StartingPlace)
{
	int x = StartingPlace;
	if (x < 0) {x=0;}
	for(; x < MaxLength; x++)
	{
		if (theString[x] == '\n') 
		{
			theString[x] = 0;
			return x; //Index of Newline that was removed lets hope it was not at 0....
		}
	}
	return 0; //no newline Found or the new line was at index 0.... 
}


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
	char *Path;
	struct Address record;
	
	printf("Welcome to Interactive Mode. Please entera selection:\n");
	
	while(running)
	{
		Print_Menu(db);
		rc = Read_Int(&UserInput);
		check(rc, "Invaild Entry. Please enter the number for your selection.\n");
		
		if(db)
		{
			switch(UserInput)
			{
				case 1:  //Add Record
				
					//Read a INT for Record Number
					
					//Read a String[Max_Data] for Name
					
					//Read a String[Max_Data] for Email
				
					// Add the Record
					//Add_Record(struct DataBase *db, int ID, char *Name, char *Email)
					//Save the Changes
					//Database_Save?
					debug("Add Record Complete.");
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
					rc = Read_Int(&Max_Data);
					check(rc, "Invaild Entry. Please enter the number for your selection.\n");

					//Get Max Row
					int Max_Row;
					printf("\nMax Number of Rows>> ");
					rc = Read_Int(&Max_Row);
					check(rc, "Invaild Entry. Please enter the number for your selection.\n");

					//Get File Name

					fflush(stdin);

					printf("Enter File name of Database>> ");
					Path = malloc(255 * sizeof(char));
					rs = fgets(Path, 255, stdin);
					check(rs != NULL, "Failed to Read Path.");
					
					//remove New Line;
					Remove_NewLine(Path, 255, 0);
					
					debug("Lets make a DB at %s! With %d Rows that are %d wide...", Path, Max_Row, Max_Data);
					
					// create Empty DB
					check(Database_create(Path, Max_Data, Max_Row), "Error Creating DataBase file");
					
					debug("That is done lets load this up and get started!");		
					// create DB Object
					db = Database_Init(Path);
					check(db, "Error Loading DB!");
					// Load DB into Memory
					check(Database_Load(db), "Error Loading the Database...");
					debug("Loaded lets roll!");
					free(Path);
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
		
		
		error:
		if(Path) {free(Path);}
		
	} //end of while running loop
	
	printf("Exiting Application. Have a Great Day!\n");
	
	return 1;
}//end of InteractiveLoop
