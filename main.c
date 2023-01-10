#include<stdio.h>
#include<json-c/json.h>

int main(int argc, char **argv) {
	FILE *fp;
	char buffer[262144];

	struct json_object *parsed_json;

	printf("Attempting to read json file...\n");
	fp = fopen("large-file.json", "r");
	printf("successfully called fopen\n");

	fread(buffer, 262144, 1, fp);
	fclose(fp);
	printf("Just read the file\n");

	parsed_json = json_tokener_parse(buffer);
	printf("just parsed the json input\n");
	
	printf("The json file:\n\n%s\n", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
	
	json_object_put(parsed_json);

	return 0;

}
