/**
  * @file main.h
  */
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include <time.h>
#include "json-c_sec.h"
#include "sqlite_financials.h"


static const char* const JSONRelativePathName = "CIK0000056873.json"; ///< JSON file of a single company's financial statements we're using to test and build the project

static const int secondsInADay = 86400;


/**
  * @brief The program's entrypoint
  */


int main();

/**
  * @brief Iterate through @p JSONArray and print whether each element references a period that is a fiscal quarter
  *
  * @param *JSONArray A pointer to the JSON object through which we will iterate
  */

void iterateThroughQuarters(json_object *JSONArray);


/**
  * @brief Calculates how many days are between the two dates represented by @p tm_start and @p tm_end
  *
  * @param tm_start The beginning date
  * @param tm_end The end date
  * @return The number of days between @p tm_start and @p tm_end
  */

int daysBetween(struct tm tm_start, struct tm tm_end);

#endif // _MAIN_H_
