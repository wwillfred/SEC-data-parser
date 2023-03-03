#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

const char key_facts[] = "facts";
const char key_us_gaap[] = "us-gaap";
const char key_netIncomeLoss[] = "NetIncomeLoss";
const char key_units[] = "units";
const char key_USD[] = "USD";

int main(int argc, char **argv);

json_object* getRootJSON();

json_object* getIterationArray(json_object *root);

void iterateThroughQuarters(json_object *obj);

bool isQuarter(json_object *obj);

#endif // _MAIN_H_
