#include<stdio.h>
#include <unistd.h>
#include <limits.h>
#include <json-c/json.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	FILE *fp;

	char buffer[4194304];

	char completePathName[128];
	char cwd[PATH_MAX];
	char relativePathName[] = "/sec-data/companyfacts/CIK0000001750.json";
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
	   printf("Current working dir: %s\n", cwd);
	}
	   else {
	      perror("getcwd() error");
	      return 1;
	}
	
	if (sizeof(completePathName) < strlen(cwd) +1) { /* +1 is for null character */

	   fprintf(stderr, "Current working directory pathname '%s' is too long\n", cwd);
	   return 1;
	}
	strncpy(completePathName, cwd, sizeof(completePathName));

	if (sizeof(completePathName) < (strlen(completePathName) + strlen(relativePathName) + 1) ) {
	   fprintf(stderr, "Final size of complete pathname is too long!\n");
	   return 1;
	}
	strncat(completePathName, relativePathName, (sizeof(completePathName) - strlen(completePathName) -1) ); /* -1 is for null haracter */
	printf("Complete pathname is %s\n", completePathName);

	struct json_object *parsed_json;

	printf("Attempting to open file...\n");
	fp = fopen(completePathName, "r");


	if (fp==NULL)
	{
	   printf("File could not be opened\n");
	   exit(0);
	}

	printf("successfully opened file\n");

	fread(buffer, 4194304, 1, fp);
	fclose(fp);
	printf("Just read the file\n");

	parsed_json = json_tokener_parse(buffer);
	printf("just parsed the json input:\n");
	
	puts(json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
	
	json_object_put(parsed_json);

	return 0;

}
