#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {

	char relativePathName[] = "sec-data/companyfacts/CIK0000001750.json";
	struct json_object *root = json_object_from_file(relativePathName);
	if (!root) {
	   printf("error, file %s not found\n", relativePathName);
	   return 1;
	}

	json_object *facts, *us_gaap, *netIncomeLoss, *units, *USD, *val, *fy, *fp, *it, *start, *end;
	const char key_facts[] = "facts";
	const char key_us_gaap[] = "us-gaap";
	const char key_netIncomeLoss[] = "NetIncomeLoss";
	const char key_units[] = "units";
	const char key_USD[] = "USD";
	const char key_val[] = "val";
	const char key_fy[] = "fy";
	const char key_fp[] = "fp";
	const char key_start[] = "start";
	const char key_end[] = "end";

	json_object_object_get_ex(root, key_facts, &facts);
	json_object_object_get_ex(facts, key_us_gaap, &us_gaap);
	json_object_object_get_ex(us_gaap, key_netIncomeLoss, &netIncomeLoss);
	json_object_object_get_ex(netIncomeLoss, key_units, &units);
	json_object_object_get_ex(units, key_USD, &USD);

	const char *str;
	int n = json_object_array_length(USD);

	int quarterValues[4];
	
	struct tm tm_start;
	struct tm tm_end;
	char *buf_start;
	char *buf_end;
	
	for (int i=0; i<n; i++)
	{
	  it = json_object_array_get_idx(USD, i);
	  json_object_object_get_ex(it, key_start, &start);
	  buf_start = strdup(json_object_get_string(start));
          strptime(buf_start, "%Y-%m-%d", &tm_start);

	  json_object_object_get_ex(it, key_end, &end);
	  buf_end = strdup(json_object_get_string(end));
	  strptime(buf_end, "%Y-%m-%d", &tm_end);

	  printf("The period starts on %s and ends on %s\n", buf_start, buf_end);
	}

	//printf("the object from key %s is: %s\n", key_USD, json_object_get_string(USD));	

	json_object_put(root);

	return 0;

}
