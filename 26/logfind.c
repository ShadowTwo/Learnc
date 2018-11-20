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

int Findall(char* haystack, int ArrayMax, char *needle, int *resultindex, int resultmax, strsearch Search_Method)
{
	check(ArrayMax && resultmax, "Arrays must larger than 0.");
	check(haystack && resultindex, "Arrays not inialized.");
	
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
				resultindex[x++] = find - haystack;
				if(x >= resultmax) {break;}
				find = Search_Method(Newhaystack, needle);
			}
			else {find = NULL;}
		}
		
		return 1;
	}
	else {return 0;}//Not Found
	
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
	
	//int count = 1;
	
	/*for(; count < argc; count++)
	{
		debug("Starting Arg(%d):[%s]\n", count, argv[count]);
		char* find = thesearch(wholefile, argv[count]);
	
		debug("Find return(%p).", find);
		if(find) 
		{  //found a patten need to go to next pattern.
			debug("The string [%s] was found!", argv[count]);
		 	debug("Wholefile - file = %d", (int) (find - wholefile));
		 	int middleindex = (int)(find - wholefile);
		 	check(PrintArraySection(wholefile, size, middleindex - 30, middleindex + 30), "Error Printing Sub Section of Array");
		}
		else if(isAND) 
		{
			printf("String [%s] not Found!\n", argv[count]);
			goto error;
		}//Not found and we are not on or.
		else {debug("Did not find %s.", argv[count]);} 
	}*/
	
	for(; count < argc; count++)
	{
		int ResultIndexs[Max_Number] = {0};
		
		int rc = Findall(wholefile, size, argv[count], ResultIndexs, Max_Number, thesearch);
		if(rc)
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
		else {debug("Did not find %s.", argv[count]);} 
	}
	
	
	fclose(file);
	free(wholefile);
	return 1;
	error:
	if(file) {fclose(file);}
	if(wholefile) {free(wholefile);}
	return 0;
}//end of main
