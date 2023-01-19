#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char **argv) {
	
	struct json_object_iterator it;
	struct json_object_iterator itEnd;

	char relativePathName[] = "sec-data/companyfacts/CIK0000001750.json";
	struct json_object *root = json_object_from_file(relativePathName);
	if (!root) {
	   printf("error, file %s not found\n", relativePathName);
	   return 1;
	}

	it = json_object_iter_init_default(); //not sure why this is necessary
	it = json_object_iter_begin(root);
	itEnd = json_object_iter_end(root);
	
	while (!json_object_iter_equal(&it, &itEnd))
	{
	   const char* key = json_object_iter_peek_name(&it);
	   json_object* val = json_object_iter_peek_value(&it);
	   printf("%s  -> %s\n", key, json_object_get_string(val));
	   json_object_iter_next(&it);
	}

	json_object_put(root);

	return 0;

}
