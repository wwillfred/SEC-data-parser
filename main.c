#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char **argv) {

	char relativePathName[] = "sec-data/companyfacts/CIK0000001750.json";

	struct json_object *root = json_object_from_file(relativePathName);

	printf("here is the parsed json file:\n");
	
	puts(json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));
	
	json_object_put(root);

	return 0;

}
