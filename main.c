#include <stdio.h>
#include <json-c/json.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
// #include <stdlib.h>

int main(int argc, char **argv) {
	FILE *fp;

	char buffer[4194304];

	char relativePathName[] = "sec-data/companyfacts/CIK0000001750.json";

	struct json_object *parsed_json;

	fp = fopen(relativePathName, "r");

	if (fp==NULL)
	{
	   printf("File could not be opened\n");
	   exit(0);
	}

	fread(buffer, 4194304, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);
	printf("here is the parsed json file:\n");
	
	puts(json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
	
	json_object_put(parsed_json);

	return 0;

}
