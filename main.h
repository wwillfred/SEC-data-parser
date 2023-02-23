#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv);

void getIterationArray();

void iterateThroughQuarters(json_object *obj);

#endif // _MAIN_H_
