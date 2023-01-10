#include "main.h"

int main() {

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
	char relativePathName[] = "CIK0000056873.json";
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


	struct json_object *it;

	int n = (int)json_object_array_length(obj);

	for (int i=0; i<n; i++)
	{
	  it = json_object_array_get_idx(obj, (size_t) i);
	  int daysInIt = daysInPeriod(it);
 
	  if ((minDaysInQuarter <= daysInIt) && (daysInIt <= maxDaysInQuarter)) {
	    printf("This period is a quarter.\n"); 
	  }
	  else if ((minDaysInYear <= daysInIt) && (daysInIt <= maxDaysInYear)) {
	    printf("This period is a year.\n");
	  }	
	  else {
	    printf("This period is neither a quarter nor a year.\n");
	  }
	}
}

int daysInPeriod(json_object *period) {

	json_object *start, *end;
	struct tm tm_start = {0};
	struct tm tm_end = {0};
	
	json_object_object_get_ex(period, key_start, &start);
       	char *buf_start = strdup(json_object_get_string(start));
        strptime(buf_start, "%Y-%m-%d", &tm_start);
	time_t start_date = mktime(&tm_start);

	json_object_object_get_ex(period, key_end, &end);
	char *buf_end = strdup(json_object_get_string(end));
	strptime(buf_end, "%Y-%m-%d", &tm_end);
	time_t end_date = mktime(&tm_end);

	double diff_seconds = difftime(end_date, start_date);
	
	int result = (int) (diff_seconds / (secondsInADay));
	//printf("The number of days in the period is %d\n", result);
	return result;
}
