/**
  * @file main.h
  */
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

static const char JSONRelativePathName[] = "CIK0000056873.json"; ///< JSON file of a single company's financial statements we're using to test and build the project

/**
  * Strings that represent keys in JSON files to drill down into the actual values
  */
static const char key_facts[] = "facts";
static const char key_us_gaap[] = "us-gaap";
static const char key_netIncomeLoss[] = "NetIncomeLoss";
static const char key_units[] = "units";
static const char key_USD[] = "USD";

/**
  * Strings that represent keys in JSON files for start and end dates for financial periods
  */
static const char key_start[] = "start";
static const char key_end[] = "end";

/**
  * Ints that define the minimum and maximum number of days used to determine whether a period is a quarter or a year
  */
static const int minDaysInQuarter =  80;
static const int maxDaysInQuarter = 100;
static const int minDaysInYear    = 350;
static const int maxDaysInYear    = 370;

static const int secondsInADay = 86400;


/**
  * @brief The program's entrypoint
  */

int main();


/**
  * @brief Obtain a pointer to a json_object for further processing
  *
  * @return A pointer to a json_object that represents the JSON file we want to analyze
  */

json_object* getParentJSON();


/**
  * @brief Find a JSON array through which we can iterate
  *
  * @param *parentJSON A pointer to a JSON object we will traverse
  * @return A pointer to the JSON array through which we can iterate
  */
json_object* getIterationArray(json_object *parentJSON);


/**
  * @brief Iterate through @p JSONArray and print whether each element references a period that is a fiscal quarter
  *
  * @param *JSONArray A pointer to the JSON object through which we will iterate
  */

void iterateThroughQuarters(json_object *JSONArray);


/**
  * @brief Calculate how many days are in the period represented by @p *period
  *
  * @param *period A pointer to the JSON object that has a start and end date
  * @return The number of days between the start and end dates in @p *period
  */

int daysInPeriod(json_object *obj);

#endif // _MAIN_H_
