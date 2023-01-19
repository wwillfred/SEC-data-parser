#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char **argv) {

	char relativePathName[] = "sec-data/companyfacts/CIK0000001750.json";
	struct json_object *root = json_object_from_file(relativePathName);
	if (!root) {
	   printf("error, file %s not found\n", relativePathName);
	   return 1;
	}

	json_object *facts, *us_gaap, *netIncomeLoss;
	const char key_facts[] = "facts";
	const char key_us_gaap[] = "us-gaap";
	const char key_netIncomeLoss[] = "NetIncomeLoss";

	json_object_object_get_ex(root, key_facts, &facts);
	json_object_object_get_ex(facts, key_us_gaap, &us_gaap);
	json_object_object_get_ex(us_gaap, key_netIncomeLoss, &netIncomeLoss);

	printf("the object from key %s is: %s\n", key_netIncomeLoss, json_object_get_string(netIncomeLoss));	

	json_object_put(root);

	return 0;

}
