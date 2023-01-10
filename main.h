#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

static const char key_facts[] = "facts";
static const char key_us_gaap[] = "us-gaap";
static const char key_netIncomeLoss[] = "NetIncomeLoss";
static const char key_units[] = "units";
static const char key_USD[] = "USD";

static const char key_start[] = "start";
static const char key_end[] = "end";
	
static const int minDaysInQuarter =  80;
static const int maxDaysInQuarter = 100;
static const int minDaysInYear    = 350;
static const int maxDaysInYear    = 370;

static const int secondsInADay = 86400;
int main(int argc, char **argv);

json_object* getRootJSON();

json_object* getIterationArray(json_object *root);

void iterateThroughQuarters(json_object *obj);

int daysInPeriod(json_object *obj);

#endif // _MAIN_H_
