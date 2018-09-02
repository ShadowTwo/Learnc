#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include "dbg.h"



struct Address 
{
	int ID;
	int set;
	char *Name;
	char *Email;
};

struct DataBase
{
	int MAX_DATA;
	int MAX_ROW;
	FILE *file;
	struct Address **Rows;
};


int Database_create(char *Path, int Input_Data, int Input_Row)
{
	int count =0;
	int set = 0;
	FILE *file = fopen(Path, "w");
	char *EmptyString = malloc(sizeof(char) * Input_Data);

	//End the string just in case)
	EmptyString[Input_Data -1] = '\0';
	//printf("EmptyString '%s'\n", EmptyString);

	//Write the max sizes to the file (did not check to make sure it was int)
	check(fwrite(&Input_Data, sizeof(int), 1, file), "Error write 1");
	check(fwrite(&Input_Row, sizeof(int), 1, file),"Error Write 2");
	
	//printf("Input_Data: %d\n", Input_Data);
	//printf("Input_Row: %d\n", Input_Row);
	//printf("Sizeof(EmptyString): %ld = %ld\n", sizeof(EmptyString), sizeof(char) * Input_Data);

	//Write Blank Data base to file;
	
	for (count = 0; count < Input_Row; count++)
	{ 
		//printf("Count %d\n", count);
		//Write ID (count)
		check(fwrite(&count, sizeof(int), 1, file), "Error write count");
		//Write Set Status
		check(fwrite(&set, sizeof(int), 1, file), "Error write Set");
		//Write Name
		check(fwrite(EmptyString, sizeof(char) * Input_Data, 1, file), "Error write name");
		//Write Email
		check(fwrite(EmptyString, sizeof(char) * Input_Data, 1, file), "Error write Email");
	}

	//Close the file;
	fclose(file);
	free(EmptyString);
	return 1;
	error:
	if(EmptyString) {free(EmptyString);}
	if(file) {fclose(file);}
	return 0;
}

int DataBase_Destory(struct DataBase *db)
{
	if (db)
	{
		if (db->Rows)
		{
			int count = 0;
			for(count = 0; count < db->MAX_ROW; count++)
			{	
				if(db->Rows[count]) 
				{
					if(db->Rows[count]->Name) {free(db->Rows[count]->Name);}
					if(db->Rows[count]->Email) {free(db->Rows[count]->Email);}
				}
			}
			free(db->Rows);
		}
		free(db);
		if (db->file) 
		{
			fclose(db->file); 
			free(db->file);
		}
	}
	return 1;
}

struct DataBase *Database_Init(char *filename)
{
	debug("Top of Init");
	struct DataBase *db = malloc(sizeof(struct DataBase));
	check(db, "Failed top create a db");
	db->file = fopen(filename, "r+");
	check(db->file, "Failed to open File.");
	debug("Reading Maxes");
	check(fread(&(db->MAX_DATA), sizeof(int),1,db->file), "Failed read MAX_DATA");
	check(fread(&(db->MAX_ROW), sizeof(int),1,db->file), "Failed read MAX_ROW");		

	//struct Address **things 
    db->Rows = (struct Address **) malloc(sizeof(struct Address *) * db->MAX_ROW);
	check(db->Rows, "Error creating Address Array.");

	int sizeofstrings = sizeof(char) * db->MAX_DATA;
	//char *data = malloc(sizeofstrings);

	//Give Names and email points an location
	int count = 0;
	debug("Start init loop:");
	for(count = 0; count < db->MAX_ROW; count++)
	{	
		//Do I need this line if i crated the large array above?
		db->Rows[count] = malloc(sizeof(struct Address));
		check(db->Rows[count], "Failed to Create Rows %d", count);
		db->Rows[count]->Name = malloc(sizeofstrings);
		check(db->Rows[count]->Name, "Failed to Create Name %d.", count);
		db->Rows[count]->Email = malloc(sizeofstrings);
		check(db->Rows[count]->Email, "Failed to Create Email %d.", count);
	}
	debug("End of init loop");

	return db;
	error:
	if(db) {DataBase_Destory(db);}
	return NULL;
}

int Database_Load(struct DataBase *db)
{
	int sizeofstrings = sizeof(char) * db->MAX_DATA;
	int count = 0;
			
	while((!feof(db->file)) && (count < db->MAX_ROW))
	{
		//printf("Prefirst Read\n");
		check(fread(&(db->Rows[count]->ID), sizeof(int),1,db->file), "Failed read ID");
		//debug("id: %d\n", db->Rows[count]->ID);
		check(fread(&(db->Rows[count]->set), sizeof(int),1,db->file), "Failed read Set");
		//debug("Set: %d\n", db->Rows[count]->set);
		check(fread(db->Rows[count]->Name, sizeofstrings,1,db->file), "Failed read name");
		//debug("Address->Name: '%s'\n", db->Rows[count]->Name);
		check(fread(db->Rows[count]->Email, sizeofstrings,1,db->file), "Failed read email");
		//debug("Address->Email: '%s'\n", db->Rows[count]->Email);

		count++;
	}
	
	return 1;
	error:
	DataBase_Destory(db);
	return 0;
}

void Database_PrintRecord(struct DataBase *db, int ID)
{
	check(db->Rows[ID], "Record does not exist.")
	printf("id: %d\n", db->Rows[ID]->ID);
	printf("Set: %d\n", db->Rows[ID]->set);
	printf("Address->Name: '%s'\n", db->Rows[ID]->Name);
	printf("Address->Email: '%s'\n", db->Rows[ID]->Email);
	error:;
}	

void Database_Print(struct DataBase *db)
{
	int count = 0;
			
	while(count < db->MAX_ROW)
	{
		
		Database_PrintRecord(db, count);
		count++;
	}
}	

int Save_Database(struct DataBase *db)
{
	//check(db->file, "File is not set.");
	//debug("End of File Status before rewind: %d.", feof(db->file));
	rewind(db->file);
	//debug("End of File Status After Rewind: %d.", feof(db->file));
	int count = 0;
	
	//Write the max sizes to the file (did not check to make sure it was int)
	check(fwrite(&(db->MAX_DATA),  sizeof(int), 1, db->file), "Error write 1");
	check(fwrite(&(db->MAX_ROW), sizeof(int), 1, db->file),"Error Write 2");

	//Write Data base to file;
	check(feof(db->file), "EOF File.");
	for (count = 0; count < db->MAX_ROW; count++)
	{ 
		//printf("Count %d\n", count);
		//Write ID (count)
		check(fwrite(&(db->Rows[count]->ID), sizeof(int), 1, db->file), "Error write count");
		//Write Set Status
		check(fwrite(&(db->Rows[count]->set), sizeof(int), 1, db->file), "Error write Set");
		//Write Name
		//check(fwrite(db->Rows[count]->Name, sizeof(char) * db->MAX_DATA, 1, db->file), "Error write name");
		int mycheck = fwrite(db->Rows[count]->Name, sizeof(char) * db->MAX_DATA, 1, db->file);
		debug("Saved Name: %s", db->Rows[count]->Name);
		debug("Sizeof(Name): %ld\n Sizeof(Data): %ld\nData Writen: %d", sizeof(db->Rows[count]->Name), sizeof(char) * db->MAX_DATA, mycheck);
		//Write Email
		check(fwrite(db->Rows[count]->Email, sizeof(char) * db->MAX_DATA, 1, db->file), "Error write Email");
	}

	//Close the file;
	return 1;
	error:
	return 0;
}

int Add_Record(struct DataBase *db, int ID, char *Name, char *Email)
{
	debug("Top of Add Record.");
	check(db->Rows[ID], "ID Does not Exist.");
	
	check(db->Rows[ID]->set == 0, "ID is already set. Delete First.");
	
	db->Rows[ID]->set = 1;
	
	check(strncpy(db->Rows[ID]->Name, Name, db->MAX_DATA), "Failed to Copy Name.");
	check(strncpy(db->Rows[ID]->Email, Email, db->MAX_DATA), "Failed to Copy Email.");
	
	debug("Name: %s - CPName: %s", Name, db->Rows[ID]->Name);
	
	return 1;
	error:
	DataBase_Destory(db);
	return 0;
}

int Remove_Record(struct DataBase *db, int ID)
{
	check(db->Rows[ID], "Record not Found.");
	db->Rows[ID]->set = 0;
	
	return 1;
	error:
	return 0;
}

int main(int argc, char *argv[])
{
	struct DataBase *db;

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
			
			DataBase_Destory(db);		
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
			DataBase_Destory(db);
			break;
		case 'd':
			check(argc > 3, "Not enough Args.");
			
			db = Database_Init(argv[2]);
			check(db, "Failed to Create DB.");		
			check(Database_Load(db), "Failed to Load DB.");
			
			//Remove_Record(struct DataBase *db, int ID)
			Remove_Record(db, atoi(argv[3])); // why return a value if not going to check it?
			DataBase_Destory(db);
			
			break;
		case 'g':
			check(argc > 3, "Not Enough Args.");
			
			db = Database_Init(argv[2]);
			check(db, "Failed to Create DB.");		
			check(Database_Load(db), "Failed to Load DB.");
			
			debug("Getting Record %d...", atoi(argv[3]));
			Database_PrintRecord(db, atoi(argv[3]));
			debug("Record Should be Printed");
			DataBase_Destory(db);	
			break;
		default:
			printf("Options is not setup or misformated");
	}
	return 1;
	error:
	if (db) {DataBase_Destory(db);}
	printf("Base {a,c,d,l} {options}\n");
	printf("\t c {Path} {MAX_DATA} {MAX_ROW}\n");
	printf("\t l {Path}\n");
	printf("\t a {Path} {id} {Name} {Email}\n");
	printf("\t d {Path} {id}\n");
	return 0;
}
