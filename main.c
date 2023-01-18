#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char **argv) {

	struct json_object *cik;

	char relativePathName[] = "sec-data/companyfacts/CIK0000001750.json";
	struct json_object *root = json_object_from_file(relativePathName);
	if (!root)
	   return 1;

	json_object_object_get_ex(root, "cik", &cik);
	printf("Company CIK is: %s\n", json_object_get_string(cik));

	json_object_put(root);

	return 0;

}
