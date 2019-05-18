#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>

typedef int (*lib_function) (const char *data);

int main (int argc, char *argv[])
{
	int rc = 0;
	
	check (argc ==4, "Usage: ex29 libex29.so Function data");
	
	char *lib_file = argv[1];
	char *func_to_run = argv[2];
	char *data = argv[3];
	
	//Create a pointer to the DLL
	void *lib = dlopen(lib_file, RTLD_NOW);
	check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());
	
	//create a point to a function in a DLL
	lib_function func = dlsym(lib, func_to_run);
	check(func != NULL, "Did not find %s function in the Library %s: %s", func_to_run, lib_file, dlerror());
	
	rc = func(data);
	check(rc == 0, "Function %s returned %d for data: %s", func_to_run, rc, data);
	
	return 0;
	
	error:
	return 1;
	
}//end of Main
