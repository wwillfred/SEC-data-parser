/**
  * @file main.c
  */

#include "main.h"

/**
  *  -# Call @c readJSONFile() to obtain a pointer to the parent JSON object we will parse
  *  -# Pass the parent JSON object to @c getIterationArray() to obtain the array through which we will iterate
  *  -# Passes the iteration array to @c iterateThroughQuarters()
  *  -# Clean up
  *
  * @note This function currently does not reflect any real program logic; it simply calls functions to test some basic functionality of the json-c package
  */

int main() {

	json_object *parentJSON= readJSONFile(JSONRelativePathName);
	if (!parentJSON)
	  return 1;

	json_object *iterationArray = getIterationArray(parentJSON);
	if (!iterationArray)
	  return 1;

	open_database();

	//iterateThroughQuarters(iterationArray);

	//printf("the object from key %s is: %s\n", key_USD, json_object_get_string(USD));	

	json_object_put(parentJSON);

	add_net_income(2023, 1, 40000);

	print_quarter(2023, 1);

	close_database();

	return 0;
}


/**
  * -# For every element in @p JSONArray, call @c startDate() and @c endDate() to obtain <tt>struct tm</tt> representations of these dates
  * -# Call daysBetween() to find how many days are in between these two <tt>struct tm</tt> objects
  * -# Use @c strftime() to obtain string representations of the two <tt>struct tm</tt> objects
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

          struct tm period_start_tm = startDate(it);
          if (period_start_tm.tm_mday == 0)
            printf("Error obtaining start date from JSON object");
 
          struct tm period_end_tm = endDate(it);
          if (period_end_tm.tm_mday == 0)
            printf("Error obtaining start date from JSON object");

          int daysInIt = daysBetween(period_start_tm, period_end_tm);


          char period_start_str[9];
          strftime(period_start_str,9,"%x", &period_start_tm);

          char period_end_str[9];
          strftime(period_end_str,9, "%x", &period_end_tm);

          if ((minDaysInQuarter <= daysInIt) && (daysInIt <= maxDaysInQuarter)) {
            printf("This period has %i days and is a quarter\nIt starts on %s and ends on %s\nNet Income for this period is %d\n", daysInIt, period_start_str, period_end_str, reportedValue(it));
          }
          else if ((minDaysInYear <= daysInIt) && (daysInIt <= maxDaysInYear)) {
            printf("This period has %i days and is a year\nIt starts on %s and ends on %s\nNet Income for this period is %d\n", daysInIt, period_start_str, period_end_str, reportedValue(it));
          }
          else {
            printf("This period has %i days and is neither a quarter nor a year\nIt starts on %s and ends on %s\nNet Income for this period is %d\n", daysInIt, period_start_str, period_end_str, reportedValue(it));
          }
        printf("\n");
        }
}

/**
  * -# Use @c mktime() to obtain @c time_t representations of @p tm_start and @p tm_end
  * -# Use @c difftime() to find the number of seconds between @c end_date and @c start_date
  * -# Divide this by the number of seconds in a day and return the result
  */

int daysBetween(struct tm tm_start, struct tm tm_end) {

	time_t start_date = mktime(&tm_start);
	time_t end_date = mktime(&tm_end);

	double diff_seconds = difftime(end_date, start_date);
	
	int result = (int) (diff_seconds / (secondsInADay));
	//printf("The number of days in the period is %d\n", result);
	return result;
}
