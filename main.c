#include "main.h"

int main(int argc, char **argv) {

	json_object *root = getRootJSON();
	if (!root)
	  return 1;

	json_object *iterationArray = getIterationArray(root);
	if (!iterationArray)
	  return 1;

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
	
	//TO-DO: need to check that USD is actually an array
	if (!USD) {
	  printf("error, could not find iteration array\n");
	  return NULL;
	}
	return USD;
}

void iterateThroughQuarters(json_object *obj) {


	json_object *it;

	int n = json_object_array_length(obj);

	for (int i=0; i<n; i++)
	{
	  it = json_object_array_get_idx(obj, i);
	  bool answer = isQuarter(it);	
	
	}
}

bool isQuarter(json_object *obj) {

	json_object *start, *end;

	struct tm tm_start, tm_end;
	
	json_object_object_get_ex(obj, key_start, &start);
       	char *buf_start = strdup(json_object_get_string(start));
        strptime(buf_start, "%Y-%m-%d", &tm_start);
	char test_buffer_start [80];
	strftime(test_buffer_start,80, "%x",&tm_start);

	json_object_object_get_ex(obj, key_end, &end);
	char *buf_end = strdup(json_object_get_string(end));
	strptime(buf_end, "%Y-%m-%d", &tm_end);
	char test_buffer_end [80];
	strftime(test_buffer_end, 80, "%x", &tm_end);

	printf("The period starts on %s and ends on %s\n", test_buffer_start, test_buffer_end);

	return true;
}
