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
/*
struct Connection {
	File *file;
	struct DataBase *db;
};

int Database_create(struct connection *conn)
{
	int location = 0;
	check(conn, "Error with Connection.");
	check(conn->file, "Error with File.");
	
	rewind(conn->file);

	int rc = fwrite(MAX_DATA, sizeof(int), 1, conn->file);
	rc = fwrite(MAX_ROW, sizeof(int), 1, conn->file);
	return 1;
	error:
	return 0;
}
*/

FILE *Open_Database(char *Path, char *type)
{
	FILE *file = fopen(Path, type);
	check (file, "Failed to Open File: %s", Path);
	return file;
	error:
	return 0;
}

int Load_Database(struct DataBase *db, char *Path, char *type)
{
	db->file = fopen (Path, type);
	check(fread(&(db->MAX_DATA), sizeof(int),1,db->file), "Failed read");
	check(fread(&(db->MAX_ROW), sizeof(int),1,db->file), "Failed read");
	
	struct Address **Rows = malloc(sizeof(struct Address) * db->MAX_ROW);

	int count = 0;
	while(!feof(db->file) && count < db->MAX_ROW)
	{	
		char **newchararray = malloc(sizeof(char) * db->MAX_DATA);
		check(fread(newchararray, sizeof(char[db->MAX_DATA]),1,db->file), "Failed to Read name");
		Rows++;
	}

	return 1;
	error:
	return 0;
}	

int Save_Database(struct DataBase *db, FILE *file)
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
	FILE *file;
	//int *data;
	int count = 0;
	char *filename;
	struct DataBase *db = malloc(sizeof(struct DataBase));

	check (argc > 1, "Not Enough Args!");

	switch((char)argv[1][0])
	{
		case 'c':
			check(argc > 4, "Not Enough Args to create.");
			int set = 0;
			
			filename = argv[2];
			
			file = Open_Database(filename, "w");
			int Input_Data = atoi(argv[3]);
			int Input_Row = atoi(argv[4]);

			char *EmptyString = malloc(sizeof(char) * Input_Data);
			//EmptyString[0] = 'a';
			//EmptyString[1] = 'b';
			EmptyString[Input_Data -1] = '\0';
			//printf("EmptyString '%s'\n", EmptyString);

			//Write the max sizes to the file (did not check to make sure it was int)
			check(fwrite(&Input_Data, sizeof(int), 1, file), "Error write 1");
			check(fwrite(&Input_Row, sizeof(int), 1, file),"Error Write 2");
			
			printf("Input_Data: %d\n", Input_Data);
			printf("Input_Row: %d\n", Input_Row);
			printf("Sizeof(EmptyString): %ld = %ld\n", sizeof(EmptyString), sizeof(char) * Input_Data);

			//Write Blank Data base to file;
			
			for (count = 0; count < Input_Row; count++)
			{ 
				printf("Count %d\n", count);
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
			break;
		case 'r':
			//struct DataBase *db = malloc(sizeof(struct DataBase));

			filename = argv[2];
			db->file = fopen(filename, "r");

			check(fread(&(db->MAX_DATA), sizeof(int),1,db->file), "Failed read MAX_DATA");
			check(fread(&(db->MAX_ROW), sizeof(int),1,db->file), "Failed read MAX_ROW");
			
			printf("Data: %d\nRow: %d\n", db->MAX_DATA, db->MAX_ROW);			

			//struct Address **things 
            db->Rows = (struct Address **) malloc(sizeof(struct Address) * db->MAX_ROW);

			check(db->Rows, "Error creating Address Array.");
			//db->Rows = things;

			int sizeofstrings = sizeof(char) * db->MAX_DATA;
			//char *data = malloc(sizeofstrings);

			//Give Names and email points an location
			//count = 0;
		
			printf("Start of Name/email:\n");
			for(count = 0; count < db->MAX_ROW; count++)
			{	
				db->Rows[count] = malloc(sizeof(struct Address));
				check(db->Rows[count], "Failed to Create Rows %d", count);
				//printf("Name/Email %p\n", db->Rows[count]);
				db->Rows[count]->Name = malloc(sizeofstrings);
				check(db->Rows[count]->Name, "Failed to Create Name %d.", count);
				db->Rows[count]->Email = malloc(sizeofstrings);
				check(db->Rows[count]->Email, "Failed to Create Email %d.", count);
			}			
			
						
			printf("Start of Loop\n");
			count = 0;
			
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
			printf("End of Loop\n");
			fclose(db->file);

			free(db->Rows);
			break;
		case 'a':
			check(argc > 4, "Not Enough Args to Add.");

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
	if (file) {fclose(file);}
	if (db->file) {fclose(file);}
	if (db->Rows) {free(db->Rows);}
	printf("Base {a,c,r} {options}\n");
	printf("\t c {Path} {MAX_DATA} {MAX_ROW}\n");
	printf("\t r {Path}\n");
	printf("\t a {Path} {id} {Name} {Address}");
	return 0;
}
