#include "main.h"


int main(int argc, char **argv) {

	json_object *root = getRootJSON();
	if (!root)
	  return 1;

	json_object *iterationArray = getIterationArray(root);

	iterateThroughQuarters(iterationArray);

	//printf("the object from key %s is: %s\n", key_USD, json_object_get_string(USD));	

	json_object_put(root);

	return 0;
}

json_object* getRootJSON() {
	char relativePathName[] = "sec-data/companyfacts/CIK0000001750.json";
	json_object *root = json_object_from_file(relativePathName);
	if (!root) {
	  printf("error, file %s not found\n", relativePathName);
	  return NULL;
	}
	return root;
}

json_object* getIterationArray(json_object *root) {

	json_object *facts, *us_gaap, *netIncomeLoss, *units, *USD; 

	json_object_object_get_ex(root, key_facts, &facts);
	json_object_object_get_ex(facts, key_us_gaap, &us_gaap);
	json_object_object_get_ex(us_gaap, key_netIncomeLoss, &netIncomeLoss);
	json_object_object_get_ex(netIncomeLoss, key_units, &units);
	json_object_object_get_ex(units, key_USD, &USD);
	if (!USD) {
	  printf("error, could not find iteration array\n");
	  return NULL;
	}
	return USD;
}

void iterateThroughQuarters(json_object *obj) {


	json_object *it, *start, *end;

	const char key_start[] = "start";
	const char key_end[] = "end";
	
	int n = json_object_array_length(obj);

	struct tm tm_start;
	struct tm tm_end;
	char *buf_start;
	char *buf_end;
	
	for (int i=0; i<n; i++)
	{
	  it = json_object_array_get_idx(obj, i);
	  json_object_object_get_ex(it, key_start, &start);
	  buf_start = strdup(json_object_get_string(start));
          strptime(buf_start, "%Y-%m-%d", &tm_start);

	  json_object_object_get_ex(it, key_end, &end);
	  buf_end = strdup(json_object_get_string(end));
	  strptime(buf_end, "%Y-%m-%d", &tm_end);

	  printf("The period starts on %s and ends on %s\n", buf_start, buf_end);
	}
}
