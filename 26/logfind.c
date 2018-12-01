//needed for the strcasestr function from the string.h library --linux only
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dbg.h"

#define MAX_DATA 1024
#define Max_Number 10
const char *LogLocation = ".logfile";
char *LogFiles[Max_Number];

typedef struct ReturnIndex
{
	int count;
	char *needle;
	int *Indexes;
} ReturnIndex;



//typedef for function for searching with or without case
typedef char *(*strsearch)(const char *haystack, const char *needle);

long unsigned int ReadtoEnd(FILE *file)
{
	char hold[100];
	long unsigned int size = 0;
	check(file, "Passed bad Value to ReadtoEnd");
	
	while(!feof(file))
	{
		size += fread(hold, sizeof(char), sizeof(hold), file);
	}
	
	return size;
	
	error:
	return 0;
}

char *FileReadLine(FILE *file)
{
	check(file, "Error bad file passed");
	int count = 0;	
	char *NewLine = calloc(sizeof(char), MAX_DATA);
	char NextChar = ' ';
	int rc = 0;
	
	check(NewLine, "Failed to Create NewLine");
	//check(!feof(file), "End of File");
	
	while(count < MAX_DATA)
	{
		
		rc = fread(&NextChar, sizeof(char), 1, file);
		//debug("%d) %c - %d", count, NextChar, (int) NextChar);
		
		if (NextChar == ' ' && (!count) ) {goto error;}
		else if(NextChar == '\n' || feof(file)) 
		{
			NewLine[count] = '\0'; 
			goto outloop; //break;?
		}
		else {NewLine[count] = NextChar;}
		count++;
	}
	
	outloop:
	return NewLine;
	
	error:	
	if(NewLine){free(NewLine);}
	return NULL;	
}

int GetLogsFromFile()
{
	int count = 0;
	debug("Opening: %s", LogLocation);
	FILE *file = fopen(LogLocation, "r");
	
	check(file, "Failed to open file.");
	
	do
	{
		LogFiles[count] = FileReadLine(file);
		//check(LogFiles[count], "Error Reading from File.");
		
		debug("%d) Log Found: %s EOF: %d", count, LogFiles[count], feof(file));
		count++;
	} while(LogFiles[count-1] && count < Max_Number && (!feof(file)));
	
	//for(count--; count >= 0; count--)
	//{
		//printf("%d) %s\n", count, LogFiles[count]);
	//}
	
	fclose(file);
	return 1;
	error:
	if(file) {fclose(file);}
	return 0;
}

int holdSearch(int argc, char *argv[], FILE *file)
{
	debug("%d args entered!", argc);
	check(argc > 1, "Usage: Logfind [-o] Search1 [Search2 Search3 ...]");
	
	//load files from `./logfind'
	check(GetLogsFromFile(), "Error Reading logs");
	
	//foreach log in list find argv'scd 
	//FILE *file = fopen(LogFiles[0], "r");
	
	check(file, "Failed to open the log");
	
	char *ReadLine = NULL;
	while(!feof(file))
	{
		ReadLine = FileReadLine(file);
		//printf("%s\n", ReadLine);
		//check(ReadLine, "Readline is NUll");
		if(ReadLine)
		{
			char *StrLoc = strstr(ReadLine, argv[argc -1]);
			//debug("strstr found: %d", StrLoc);
			if (StrLoc)
			{
				//debug("In Found");
				printf("Found string at: %p\n", StrLoc);
				printf("%s\n", ReadLine);
			}
			free(ReadLine);
		}
	}
	
	//From string - strstr(haystack, needle);
	fclose(file);
	return 1;
	error:
	return 0;
}

//Function to load array with index found for the needle
//return success or fail


//Function to print out each index found and there count


//Function to order the array indexes



int PrintArraySection(char *theArray, int ArrayMax, int StartIndex, int EndIndex)
{
	check(theArray, "Bad Array.");
	if(EndIndex > ArrayMax) {EndIndex = ArrayMax; debug("Endindex set to end of array.");}
	check(StartIndex < ArrayMax, "Cannot start past end of Array.");
	if(StartIndex < 0){ StartIndex = 0; debug("Start index changed to 0.");}
	check(EndIndex > StartIndex, "End Index must be larger then Start Index.");
	
	int x = StartIndex;
	
	debug("Starting at %d, and ending at %d", x, EndIndex);
	for(; x < EndIndex; x++)
	{
		printf("%c", theArray[x]);
	}
	
	return 1;
	error:
	return 0;
}


//Return < 0 on error, 0 for nothing found, or the total number of indexes found
int Findall(char* haystack, int ArrayMax, char *needle, ReturnIndex *resultindex, int resultmax, strsearch Search_Method)
{
	check(ArrayMax && resultmax, "Arrays must larger than 0.");
	check(haystack && resultindex, "Arrays not inialized.");
	check(resultindex || resultindex->Indexes, "Result Location can not be NULL.");
	
	//do i need to check that the string is termed in \0?
	char* Endhaystack = (haystack + ArrayMax);
	
	char *find = Search_Method(haystack, needle);
	int x = 0;
	if(find)
	{
		int needlelength = strlen(needle);
		while(find)
		{
			char *Newhaystack = haystack + ((find - haystack) + needlelength);
			if(Newhaystack < Endhaystack)
			{
				resultindex->Indexes[x++] = find - haystack;
				if(x >= resultmax) {break;}
				find = Search_Method(Newhaystack, needle);
			}
			else {find = NULL;}
		}
		resultindex->count = x;
		return x;
	}
	else {return 0;}//Not Found
	
	error:
	return -1; 
}

//Create Index Arrays
int CreateRecordIndexArrayes(ReturnIndex *returnindex, int size, char *needle)
{
	check(returnindex, "Null ReturnIndex.");
	check(size > 0, "Size must greater than 0.");
	
	returnindex->count = size;
	returnindex->needle = needle;
	returnindex->Indexes = calloc(1, sizeof(int) * size);
	
	check(returnindex->Indexes, "Failed to create indexes array.");
	
	return 1;
	
	error:
	return -1;
}

//Goes through each arg and find the closes indexes and return a Point to int array with each index. 
//Max length of the array is total number of arguments
int *FindCloseIndexes(ReturnIndex *returnindex, int Needle, int Index, int MaxDistance)
{

	return 1;
	error:
	return 0;
}

int main(int argc, char *argv[])
{	
	debug("%d args entered!", argc);
	
	int count = 1;
	int isAND = 1;
	char *wholefile = NULL;
	FILE *file = NULL;
	ReturnIndex *ReturnIndex_Array = NULL;
	
	check(argc > 1, "Usage: Logfind [-o] Search1 [Search2 Search3 ...]");
	
	//default to search without case
	strsearch thesearch = strcasestr;

	debug("Start of Options loop. Argc(%d).", argc);
	int x = 1;
	for(;(x<3) && (x < argc);x++)
	{
		debug("Start of Loop %d.", x);
		if(strcmp(argv[x], "-o") == 0)
		{
			debug("Setting up for OR!");
			count++;
			isAND = 0;
		}
		else if(strcmp(argv[x], "-c") == 0)
		{
			debug("Setting up case search");
			count++;
			thesearch = strstr;
		}
		debug("End of Option loop %d.", x);
	}
	debug("End of Option loop");
	
	debug("Argc(%d) and Count(%d)", argc, count);
	check((count != argc), "No search arguments entered.");
	
	//load files from `./logfind'
	check(GetLogsFromFile(), "Error Reading logs");
	
	//foreach log in list find argv'scd 
	file = fopen(LogFiles[0], "r");
	
	check(file, "Failed to open the log");
	
	long unsigned int size = ReadtoEnd(file);
	debug("The files is %ld bytes", size);
	
	wholefile = calloc(1, size);
	
	check(wholefile, "Failed to create memory.");
	//check(!feof(file), "Found end of file.");
	
	rewind(file);
	
	int rc = fread(wholefile, 1, size, file);
	
	check(rc, "Failed to read %s", LogFiles[0]);
	
	
	// find each each with out error
	
	
	int totalargs = argc - count;
	
	ReturnIndex_Array = calloc(1, sizeof(ReturnIndex)*totalargs);
	
	int currentarg = 0;
	
	for(; count < argc; count++, currentarg++)
	{
		ReturnIndex *ResultIndex_ptr = &(ReturnIndex_Array[currentarg]);
		
		rc = CreateRecordIndexArrayes(ResultIndex_ptr, Max_Number, argv[count]);
		
		check(rc > 0, "Failed to create index Arrayes.");
		
		
		int rc = Findall(wholefile, size, argv[count], ResultIndex_ptr, Max_Number, thesearch);
		/*if((!rc) && isAND) // make quick out for AND check (Not rc and isAND)
		{
			int x = 0;
			while(ResultIndexs[x] && x < Max_Number)
			{
				debug("Result[%d] = %d", x, ResultIndexs[x]);
				PrintArraySection(wholefile, size, ResultIndexs[x]-30, ResultIndexs[x]+30);
				printf("\n");
				x++;
			}
		}
		else if(isAND)
		{
			printf("String [%s] not Found!\n", argv[count]);
			goto error;
		}//Not found and we are not on or.
		else {debug("Did not find %s.", argv[count]);} */
	}
	
	//search through each arg to see if all are found to check for and condition
	
	if(isAND)
	{
		int x = 0;
		while (x<currentarg)
		{
			if(!(ReturnIndex_Array[x++].Indexes[0]))
			{
				printf("Failed to Find a Result for '%s'.", ReturnIndex_Array[--x].needle);
				return 0; //this needs to goto end of current log loop
			}
		}
	}
	
	//Sort Restults
	debug("Total Search Args: %d, ", totalargs);
	int y;
	
	for(y = 0; y < totalargs; y++)
	{
		int z;
		debug("There %d entrys for '%s': ", ReturnIndex_Array->count, ReturnIndex_Array->needle);
		for(z=0; z < ReturnIndex_Array[y].count; z++)
		{
			debug("\t%d", ReturnIndex_Array[y].Indexes[z]);
		}
	} 
	
	// find close results
	
	//repeat for each log file
	//need to clean all int points for resultindex
	if(ReturnIndex_Array)
	{
		int x = 0;
		for(x = 0; x < totalargs; x++) {free(ReturnIndex_Array[x].Indexes);}
		free(ReturnIndex_Array);
	}
	fclose(file);
	free(wholefile);
	return 1;
	error:
	if(file) {fclose(file);}
	if(wholefile) {free(wholefile);}
	if(ReturnIndex_Array)
	{
		int x = 0;
		for(x = 0; x < totalargs; x++) {free(ReturnIndex_Array[x].Indexes);}
		free(ReturnIndex_Array);
	}
	return -1;
}//end of main
