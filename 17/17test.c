#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
	int id;
	int set;

	//[0] - name
	//[1] - email
	char *data[];
};

struct Database { 
	int MAX_DATA;
	int MAX_ROWS;
	struct Address rows[]; 
};

struct Connection {
	FILE *file;
	struct Database *db;
};

void die (const char *message)
{
	if (errno) {perror(message);}
	else { printf("Error: %s\n", message);}
	exit(1);
}

void createDB(struct Connection *conn, int Rows, int Data)
{
	struct Address addr;
	addr.data = malloc(sizeof(char[2][Data]));
	struct Database dbl = malloc(sizeof(addr)*Rows);
	dbl.MAX_DATA = Data;
	dbl.MAX_ROWS = Rows;
	
	conn->db = dbl;
	free(addr.data);
	free(dbl);
}

int main (int argc, char *argv[])
{
	int Rows = 100;
	int data = 100;

	if (argc < 2) {die("To few arg\n");}

	//char *file = argv[1];

	struct Connection *conn = malloc(sizeof(struct Connection));
	if (!conn) {die ("Conn Mem Error\n");}

	conn->file = fopen(argv[1], "w");
	createDB(conn, Rows, data);
	
	rewind (conn->file);

	int rc = fwrite(conn->db, sizeof(conn->db), 1, conn->file);
	if (rc !=1) {die("Failed to Write DB to File.\n");}

	rc = fflush(conn->file);
	if(rc == -1) {die("Failed to Flush file.\n");}

	return 0;
}
