#ifndef __interactive_h__
#define __interactive_h__
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
#endif
