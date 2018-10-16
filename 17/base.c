#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "datastructs.h"
#include "dbg.h"
#include "interactive.h"

int main(int argc, char *argv[])
{
	struct DataBase *db = NULL;

	check (argc > 1, "Not Enough Args!");

	switch((char)argv[1][0])
	{
		case 'c':
			check(argc > 4, "Not Enough Args to create.");
			
			//filename = argv[2];
			
			int Input_Data = atoi(argv[3]);
			int Input_Row = atoi(argv[4]);
			
			check(Database_create(argv[2], Input_Data, Input_Row), "Error Creating DataBase file");

			break;
		case 'l':
			//struct DataBase *db = malloc(sizeof(struct DataBase));

			check(argc > 2, "Not enough Args.");
			
			db = Database_Init(argv[2]);
			check(db, "Failed to Create DB.");		
			check(Database_Load(db), "Failed to Load DB.");
			
			Database_Print(db);
			
			//DataBase_Destory(db);		
			break;
		case 'a':
			check(argc > 4, "Not Enough Args to Add.");

			debug("Creating DB.");
			db = Database_Init(argv[2]);
			check(db, "Failed to Create DB.");
			debug("Loading DB");		
			check(Database_Load(db), "Failed to Load DB.");
			
			//Add_Record(struct DataBase *db, int ID, char *Name, char *Email)
			check(Add_Record(db, atoi(argv[3]), argv[4], argv[5]), "Failed to Add Record: %d:) %s - %s", atoi(argv[3]), argv[4], argv[5]);
			debug("Added Record. Saving DB.");
			check(Save_Database(db), "Failed to Save DB.");
			
			debug("Destorying DB");
			//DataBase_Destory(db);
			break;
		case 'd':
			check(argc > 3, "Not enough Args.");
			
			db = Database_Init(argv[2]);
			check(db, "Failed to Create DB.");		
			check(Database_Load(db), "Failed to Load DB.");
			
			//Remove_Record(struct DataBase *db, int ID)
			Remove_Record(db, atoi(argv[3])); // why return a value if not going to check it?
			//DataBase_Destory(db);
			
			break;
		case 'g':
			check(argc > 3, "Not Enough Args.");
			
			db = Database_Init(argv[2]);
			check(db, "Failed to Create DB.");		
			check(Database_Load(db), "Failed to Load DB.");
			
			//debug("Getting Record %d...", atoi(argv[3]));
			Database_PrintRecord(db, atoi(argv[3]));
			//debug("Record Should be Printed");
			//DataBase_Destory(db);	
			break;
		case 'f':
			check(argc > 4, "Not Enough Args.");
			
			db = Database_Init(argv[2]);
			check(db, "Failed to Create DB.");		
			check(Database_Load(db), "Failed to Load DB.");
			
			debug("Lets seach %s for %s!", argv[3], argv[4]);
			DataBase_Search(db, argv[3], argv[4]);
			
			//DataBase_Destory(db);	
			break;
		case 'i':
			check (argc > 1, "This test is a waste of time");
			
			if (argc > 2) 
			{
				db = Database_Init(argv[2]);
				check(db, "Failed to Create DB.");		
				check(Database_Load(db), "Failed to Load DB.");
			}
			
			check(InteractiveLoop(db), "Failed InteractiveLoop");
			
			break;
		default:
			printf("Options is not setup or misformated\n"); //why is this not the warning mico?
	}
	
	DataBase_Destory(db);
	return 1;
	error:
	if (db) {DataBase_Destory(db);}
	printf("Base {a,c,d,l} {options}\n");
	printf("\t a {Path} {id} {Name} {Email}\n");
	printf("\t c {Path} {MAX_DATA} {MAX_ROW}\n");
	printf("\t d {Path} {id}\n");
	printf("\t f {Path} {Field} {Matching String} -- Search for record\n");
	printf("\t g {Path} {id} -- Get Record\n");
	printf("\t i [Path] -- Start Interactive Mode\n");
	printf("\t l {Path}\n");
	return 0;
}
