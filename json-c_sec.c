/**
  * @file json-c_sec.c
  */

#include "json-c_sec.h"


/**
  * Call the @c json_object_from_file() function to turn the JSON file located at @p path into a pointer to a json_object
  */

json_object* readJSONFile(const char* path) {
	json_object *result = json_object_from_file(path);
	if (!result) {
	  printf("error, file %s not found\n", path);
	  return NULL;
	}
	return result;
}

/**
  *  Traverse @p *parentJSON through facts, us_gaap, netIncomeLoss,and units to find the USD array, through which we can iterate
  */ 

json_object* getIterationArray(json_object *parentJSON) {

	json_object *facts, *us_gaap, *netIncomeLoss, *units, *USD; 

	json_object_object_get_ex(parentJSON, key_facts, &facts);
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


/**
  * -# Attempt to obtain the JSON object represented by the key @c key_val within the JSON object @p period
  * -# Attempt to obtain an integer representation of that JSON object and return the result
  *
  * @note Need to implement better error handling
  */

int reportedValue(json_object *period) {

	json_object *value;

	json_object_object_get_ex(period, key_val, &value);
	if (!value) {
	  printf("Error, no JSON object found at key: %s in period: %s", key_val, json_object_to_json_string(period));
	  return 0;
	}

	int result = json_object_get_int(value);
	if (!result) {
	  printf("Error obtaining int value from JSON object: %s", json_object_to_json_string(value));
	  return 0;
	}

	return result;
}


/**
  * -# Obtain the JSON object at key @c key_start in @p period and convert it to a string
  * -# Convert that string to a <tt>struct tm</tt> and return it
  *
  * @note Need to see if there's a way to get a string representation of a @c json_object for printing to screen during error handling
  */

struct tm startDate(json_object *period) {
	json_object *start;
	struct tm tm_start = {0};

	json_object_object_get_ex(period, key_start, &start);
	if (!start) {
	  printf("Error: JSON object has no value at key %s\n", key_start);
	  return tm_start;
        }

	const char *buf_start = json_object_get_string(start);
	if (!buf_start) {
	  printf("Error converting JSON object to string");
	  return tm_start;
	}

	strptime(buf_start, "%Y-%m-%d", &tm_start);
	return tm_start;
}


/**
  * -# Obtain the JSON object at key @c key_end in @p period and convert it to a string
  * -# Convert that string to a <tt>struct tm</tt> and return it
  */

struct tm endDate(json_object *period) {
	json_object *end;
	struct tm tm_end = {0};

	json_object_object_get_ex(period, key_end, &end);
	if (!end) {
	  printf("Error: JSON object has no value at key %s\n", key_end);
	  return tm_end;
	}

	const char *buf_end = json_object_get_string(end);
	if (!buf_end) {
	  printf("Error converting JSON object to string");
	  return tm_end;
	}

	strptime(buf_end, "%Y-%m-%d", &tm_end);
	return tm_end;
}
