#include <stdio.h>
#include <json-c/json.h>
#include <string.h>

int main(int argc, char **argv) {

	char relativePathName[] = "sec-data/companyfacts/CIK0000001750.json";
	struct json_object *root = json_object_from_file(relativePathName);
	if (!root) {
	   printf("error, file %s not found\n", relativePathName);
	   return 1;
	}

	json_object *facts, *us_gaap, *netIncomeLoss, *units, *USD, *val, *fy, *fp, *it, *frame;
	const char key_facts[] = "facts";
	const char key_us_gaap[] = "us-gaap";
	const char key_netIncomeLoss[] = "NetIncomeLoss";
	const char key_units[] = "units";
	const char key_USD[] = "USD";
	const char key_val[] = "val";
	const char key_fy[] = "fy";
	const char key_fp[] = "fp";
	const char key_frame[] = "frame";

	json_object_object_get_ex(root, key_facts, &facts);
	json_object_object_get_ex(facts, key_us_gaap, &us_gaap);
	json_object_object_get_ex(us_gaap, key_netIncomeLoss, &netIncomeLoss);
	json_object_object_get_ex(netIncomeLoss, key_units, &units);
	json_object_object_get_ex(units, key_USD, &USD);

	const char *str;
	int n = json_object_array_length(USD);

	int quarterValues[4];

	for (int i=0; i<n; i++)
	{
	  it = json_object_array_get_idx(USD, i);
	  json_object_object_get_ex(it, key_frame, &frame);
	  if (!frame) continue;

	  const char *frameString = json_object_get_string(frame);
	  /* int tempYear = the four digits after the "CY" in frameString */

	  /* if frameString matches regex CY[0-9][0-9][0-9][0-9]Q[1-4]*/
	    /* int tempQuarter = the value after the "Q" in frameString */

	    /* if the tempQuarter-minus-one-th index in the qarterValues array is not null, then log a warning */
	    /* take tempQuarter and put it in the ith-minus-one index in the quarter array */
	    /* print a statement saying that the net income of tempQuarter quarter of tempYear year is quarterValues[tempQuarter minus 1]*/ 
	  /* else if frameString matches regex CY[0-9][0-9][0-9][0-9] */
	    /* tempYear = the four digits after "CY" in frameString */
	}

	//printf("the object from key %s is: %s\n", key_USD, json_object_get_string(USD));	

	json_object_put(root);

	return 0;

}
