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
		if (db->file) {free(db->file);}
	}
	return 1;
}

struct DataBase *Database_Init(char *filename)
{
	struct DataBase *db = malloc(sizeof(struct DataBase));
	db->file = fopen(filename, "r");

	check(fread(&(db->MAX_DATA), sizeof(int),1,db->file), "Failed read MAX_DATA");
	check(fread(&(db->MAX_ROW), sizeof(int),1,db->file), "Failed read MAX_ROW");		

	//struct Address **things 
    db->Rows = (struct Address **) malloc(sizeof(struct Address) * db->MAX_ROW);

	check(db->Rows, "Error creating Address Array.");

	int sizeofstrings = sizeof(char) * db->MAX_DATA;
	//char *data = malloc(sizeofstrings);

	//Give Names and email points an location
	int count = 0;

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
		printf("id: %d\n", db->Rows[count]->ID);
		check(fread(&(db->Rows[count]->set), sizeof(int),1,db->file), "Failed read Set");
		printf("Set: %d\n", db->Rows[count]->set);
		check(fread(db->Rows[count]->Name, sizeofstrings,1,db->file), "Failed read name");
		printf("Address->Name: '%s'\n", db->Rows[count]->Name);
		//db->Rows[count]->Name = data;
		check(fread(db->Rows[count]->Email, sizeofstrings,1,db->file), "Failed read email");
		printf("Address->Email: '%s'\n", db->Rows[count]->Email);
		//db->Rows[count]->Email = data;
		count++;
	}
	
	return 1;
	error:
	DataBase_Destory(db);
	return 0;
}

void Database_Print(struct DataBase *db)
{
	int count = 0;
			
	while(count < db->MAX_ROW)
	{
		printf("id: %d\n", db->Rows[count]->ID);
		printf("Set: %d\n", db->Rows[count]->set);
		printf("Address->Name: '%s'\n", db->Rows[count]->Name);
		printf("Address->Email: '%s'\n", db->Rows[count]->Email);
		count++;
	}
}	

int Save_Database(struct DataBase *db)
{
	check(1==1, "yup");
	return 1;
	error:
	return 0;
}

int Add_Record(struct DataBase *db, int ID, char *Name, char *Email)
{
	check(1==1, "yup")
	return 1;
	error:
	return 0;

}

int main(int argc, char *argv[])
{
	struct DataBase *db;
	//struct DataBase *db = malloc(sizeof(struct DataBase));

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

			db = Database_Init(argv[2]);
			check(db, "Failed to Create DB.");		
			check(Database_Load(db), "Failed to Load DB.");
			
			
			//int id = atoi(argv[3]);
			//check(Add_Record(argv[1], id, argv[4], argv[5]), "Failed to Add Record: %d:) %s - %s", id, argv[4], argv[5]);
			
			break;
		case 'd':
			break;
		default:
			printf("Options is not setup or misformated");
	}
	return 1;
	error:
	if (db) {DataBase_Destory(db);}
	printf("Base {a,c,l} {options}\n");
	printf("\t c {Path} {MAX_DATA} {MAX_ROW}\n");
	printf("\t l {Path}\n");
	printf("\t a {Path} {id} {Name} {Address}\n");
	return 0;
}
