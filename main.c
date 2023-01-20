#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char **argv) {

	char relativePathName[] = "sec-data/companyfacts/CIK0000001750.json";
	struct json_object *root = json_object_from_file(relativePathName);
	if (!root) {
	   printf("error, file %s not found\n", relativePathName);
	   return 1;
	}

	json_object *facts, *us_gaap, *netIncomeLoss, *units, *USD, *val, *fy, *fp;
	const char key_facts[] = "facts";
	const char key_us_gaap[] = "us-gaap";
	const char key_netIncomeLoss[] = "NetIncomeLoss";
	const char key_units[] = "units";
	const char key_USD[] = "USD";
	const char key_val[] = "val";
	const char key_fy[] = "fy";
	const char key_fp[] = "fp";

	json_object_object_get_ex(root, key_facts, &facts);
	json_object_object_get_ex(facts, key_us_gaap, &us_gaap);
	json_object_object_get_ex(us_gaap, key_netIncomeLoss, &netIncomeLoss);
	json_object_object_get_ex(netIncomeLoss, key_units, &units);
	json_object_object_get_ex(units, key_USD, &USD);

	const char *str;
	int n = json_object_array_length(USD);
	for (int i=0; i<n; i++)
	{
	   struct json_object *it = json_object_array_get_idx(USD, i);
	   json_object_object_get_ex(it, key_val, &val);
	   json_object_object_get_ex(it, key_fy, &fy);
	   json_object_object_get_ex(it, key_fp, &fp);
	   printf("Net income in %s of %s was %s\n", json_object_get_string(fp), json_object_get_string(fy), json_object_get_string(val));
	}

	//printf("the object from key %s is: %s\n", key_USD, json_object_get_string(USD));	

	json_object_put(root);

	return 0;

}
