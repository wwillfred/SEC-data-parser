#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char **argv) {
	
	const char key_cik[] = "cik";

	struct json_object *cik;

	char relativePathName[] = "sec-data/companyfacts/CIK0000001750.json";
	struct json_object *root = json_object_from_file(relativePathName);
	if (!root) {
	   printf("error, file %s not found\n", relativePathName);
	   return 1;
	}

	json_object_object_get_ex(root, key_cik, &cik);
	if (!cik) {
	   printf("error, key %s not found\n", key_cik);
	   return 1;
	}

	printf("Company CIK is: %s\n", json_object_get_string(cik));

	json_object_put(root);

	return 0;

}
