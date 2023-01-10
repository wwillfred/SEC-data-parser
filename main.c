#include<stdio.h>
#include<json-c/json.h>

int main(int argc, char **argv) {
	FILE *fp;
	char buffer[32768];

	struct json_object *parsed_json;

	printf("Attempting to read json file...\n");
	fp = fopen("large-file.json", "r");
	printf("successfully called fopen\n");

	fread(buffer, 32768, 1, fp);
	fclose(fp);
	printf("Just read the file\n");

	parsed_json = json_tokener_parse(buffer);
	printf("just parsed the json input");
	
	return 0;

}
