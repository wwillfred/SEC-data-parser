/**
  * @file main.c

  * @note This function currently does not reflect any real program logic; it simply calls functions to test some basic functionality of the json-c package
  */
#include "main.h"

/**
  *  -# Call getParentJSON() to obtain a pointer to the parent JSON object we will parse
  *  -# Pass the parent JSON object to getIterationArray() to obtain the array through which we will iterate
  *  -# Passes the iteration array to iterateThroughQuarters()
  *  -# Clean up
  *
  */

int main() {

	json_object *parentJSON= getParentJSON();
	if (!parentJSON)
	  return 1;

	json_object *iterationArray = getIterationArray(parentJSON);
	if (!iterationArray)
	  return 1;

	iterateThroughQuarters(iterationArray);

	//printf("the object from key %s is: %s\n", key_USD, json_object_get_string(USD));	

	json_object_put(parentJSON);

	return 0;
}

/**
  * Call the json_object_from_file() function to turn the JSON file located at JSONRelativePathName into a pointer to a json_object
  */

json_object* getParentJSON() {
	json_object *result = json_object_from_file(JSONRelativePathName);
	if (!result) {
	  printf("error, file %s not found\n", JSONRelativePathName);
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
  * -# For every element in @p JSONArray, call daysInPeriod() to find how many days are in the period represented by the element
  * -# If the number of days is greater than or equal to @c minDaysInQuarter and is less than or equal to @c maxDaysInQuarter then print a confirmation message
  *   -# Similarly check if the number of days matches the length of a year
  *   -# Otherwise, print that the period is neither a quarter nor a year
  */

void iterateThroughQuarters(json_object *JSONArray) {

	struct json_object *it;

	int arrayLength = (int)json_object_array_length(JSONArray);

	for (int i=0; i<arrayLength; i++)
	{
	  it = json_object_array_get_idx(JSONArray, (size_t) i);
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

/**
  * -# Copy the strings referenced by start and end in @p *period and convert them into @c tm structs
  * -# Calculate the number of seconds between the start and end @c tm structs and convert that to days and return the result
  */

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
