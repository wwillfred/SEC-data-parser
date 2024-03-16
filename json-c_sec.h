/**
  * @file json-c_sec.h
  */

#ifndef _JSON_C_SEC_H_
#define _JSON_C_SEC_H_


#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include <time.h>

/**
  * Strings that represent keys in JSON files to drill down into the actual values
  */
static const char key_facts[] = "facts";
static const char key_us_gaap[] = "us-gaap";
static const char key_netIncomeLoss[] = "NetIncomeLoss";
static const char key_units[] = "units";
static const char key_USD[] = "USD";

/**
  * Strings that represent keys in JSON files for data in financial periods
  */
static const char key_start[] = "start";
static const char key_end[] = "end";
static const char key_val[] = "val";


/**
  * Ints that define the minimum and maximum number of days used to determine whether a period is a quarter or a year
  */
static const int minDaysInQuarter =  80;
static const int maxDaysInQuarter = 120;
static const int minDaysInYear    = 350;
static const int maxDaysInYear    = 370;


/**
  * @brief Create a @c json_object from the JSON file at @p path
  *
  * @param path The relative path to the JSON file
  * @return The @c json_object created from the JSON file at @p path
  */

json_object* readJSONFile(const char* path);


/**
  * @brief Find a JSON array through which we can iterate
  *
  * @param *parentJSON A pointer to a JSON object within which we will look for the iteration array
  * @return A pointer to the JSON array through which we can iterate
  */

json_object* getIterationArray(json_object *parentJSON);


/**
  * @brief Obtains the line item's reported value for the fiscal period represented by @p period
  *
  * @param *period A pointer to a JSON object representing a fiscal period
  * @return The value reported for this fiscal period
  *
  * @note A JSON object @p *period belongs to a JSON object representing all periods of a particular line item (e.g. NetIncomeLoss), so for a given JSON object @p *period, the line item is implied
  */

int reportedValue(json_object *period);


/**
  * @brief Obtains the start date of the fiscal period represented by @p period
  *
  * @param *period A pointer to a JSON object representing a fiscal period
  * @return A <tt>struct tm</tt> representing the period's beginning date
  */

struct tm startDate(json_object *period);


/**
  * @brief Obtains the end date of the fiscal period represented by @p period
  *
  * @param *period A pointer to a JSON object representing a fiscal period
  * @return A <tt>struct tm</tt> representing the period's ending date
  */

struct tm endDate(json_object *period);


#endif // _JSON_C_SEC_H_
