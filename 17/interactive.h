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

char *SelectField(int MaxLength)
{
	if(MaxLength = 0) {MaxLength = 255;}
	
	char *field = malloc(sizeof(char) * MaxLength);
	int selection = 0;
	
	check(field, "Error Allocating Memory for Field.");
	
	tryagain:
	
	printf("What Field do you wish to search?\n");
	printf("\t1. Name\n");
	printf("\t2. Email\n");
	printf("\t3. Exit\n");
	
	check(Read_Int(&selection), "Failed to read field.");
	
	switch(selection)
	{
		case 1:
			strncpy(field, "Name", MaxLength);
			break;
		case 2:
			strncpy(field, "Email", MaxLength);
			break;
		case 3:
			goto error;
			break;
		default:
			printf("Invalid Selection");
			goto tryagain;
			break;
	}
	
	return field;
	error:
	if (field) {free(field);}
	return 0;
}//end of SelectField

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
int InteractiveLoop(struct DataBase *db)
{
	int running = 1;
	int UserInput = 0;
	int rc = 0;
	char *rs = NULL;
	char *Path = NULL;
	struct Address record;
	record.set =0;
	record.Name = NULL;
	record.Email = NULL;
	
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
				    debug("Start of Add Record.");
					//Read a INT for Record Number
					printf("Which record do you wish to add>>");
					check(Read_Int(&record.ID), "Failed to read ID.");
					
					//Read a String[Max_Data] for Name
					printf("What is Contacts Name>>");
					record.Name = malloc(db->MAX_DATA * sizeof(char));
					rs = fgets(record.Name, db->MAX_DATA, stdin);
					check(rs != NULL, "Failed to Read Name.");
					
					Remove_NewLine(record.Name, 255, 0);
					
					//Read a String[Max_Data] for Email
					printf("What is Contacts Email>>");
					record.Email = malloc(db->MAX_DATA * sizeof(char));
					rs = fgets(record.Email, db->MAX_DATA, stdin);
					check(rs != NULL, "Failed to Read Email.");
					
					Remove_NewLine(record.Email, 255, 0);
					
					Print_Address(&record);
					
					// Add the Record
					check(Add_Record_Whole(db, &record), "Failed to Add Record.");
					
					//Save the Changes
					check(Save_Database(db), "Failed to Save Database.");
					
					debug("Add Record Complete.");
					break;
				case 2: // Delete Record
					printf("Which record do you wish to Delete>>");
					check(Read_Int(&record.ID), "Failed to read ID.");
					Remove_Record(db, record.ID);
					check(Save_Database(db), "Failed to Save Database.");
					break;
				case 3: // Find Record

					// Read dbfield
					record.Name = SelectField(255);
					
					check(record.Name, "");
					// Read Searchstr
					printf("Search for >>");
					rc = fscanf(record.Email, db->MAX_DATA, stdin);
					check(rc, "Failed to read search string");

					DataBase_Search(db, record.Name, record.Email);
					break;
				case 4: // Get Record
					printf("Which record do you wish to Get>>");
					check(Read_Int(&record.ID), "Failed to read ID.");
					Database_PrintRecord(db, record.ID);
					break;
				case 5: // List All
					Database_Print(db);
					break;
				case 6: // Quit
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

					//fflush(stdin);

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

		if(record.Name){free(record.Name);}
		if(record.Email){free(record.Email);}

		
	} //end of while running loop
	
	printf("Exiting Application. Have a Great Day!\n");
	
	return 1;
}//end of InteractiveLoop
