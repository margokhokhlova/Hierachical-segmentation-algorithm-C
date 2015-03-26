#ifndef KEYEXIST_H
#define KEYEXIST_H

#include <stdio.h>
#include <map>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

bool keyExist(string key, std::map<std::string, vector<Point>> hashmap) {
if (hashmap.count(key)==0)
	{ //if the entry already exist

return 0;

	}
else return 1;
}



#endif