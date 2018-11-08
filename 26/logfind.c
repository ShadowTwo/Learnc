#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define MAX_DATA 1024
#define Max_Number 10
const char *LogLocation = "~/.logfile";
char *LogFiles[Max_Number];

char *FileReadLine(FILE *file)
{
	check(file, "Error bad file passed");
	int count = 0;	
	char *NewLine = calloc(sizeof(char), MAX_DATA);
	char NextChar = ' ';
	int rc = 0;
	
	check(NewLine, "Failed to Create NewLine");
	
	while(count < MAX_DATA)
	{
		
		rc = fread(&NextChar, sizeof(char), 1, file);
		check(rc == 0, "Failed to Read to newline.");
		debug("%c", NextChar);
		if(NextChar == '\n' || feof(file)) 
		{
			NewLine[count] = '\0'; 
			goto outloop;
		}
		else {NewLine[count] = NextChar;}
		count++;
	}
	
	outloop:
	return NewLine;
	
	error:	
	if(NewLine){free(NewLine);}
	return 0;	
}

int GetLogsFromFile()
{
	int count = 0;
	FILE *file = fopen(LogLocation, "r");
	
	check(file, "Failed to open file.");
	
	while(!feof(file) && count < Max_Number)
	{
		LogFiles[count] = FileReadLine(file);
		check(LogFiles[count], "Error Reading from File.");
		count++;
	}
	
	for(; count > 0; count--)
	{
		printf("%d) %s\n", count, LogFiles[count]);
	}
	
	fclose(file);
	return 1;
	error:
	if(file) {fclose(file);}
	return 0;
}

int main(int argc, char *argv[])
{
	check(argc > 2, "Usage: Logfind [-o] Search1 [Search2 Search3 ...]");
	
	//load files from `./logfind'
	check(GetLogsFromFile(), "Error Reading logs");
	
	//foreach log in list find argv'scd 
	
	return 1;
	error:
	return 0;
}//end of main
