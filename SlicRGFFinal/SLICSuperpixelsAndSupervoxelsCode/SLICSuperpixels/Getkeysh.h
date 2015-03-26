#ifndef GETKEYSH_H
#define GETKEYSH_H

#include <stdio.h>
#include <map>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

// FUNCTION O GET KEYS FROM A HASHMAP

static vector<int> Getkeysh(map<int, vector<Point>> HASHMAP) {
vector<int>hash_keys;
for(map<int, vector<Point>>::const_iterator it = HASHMAP.begin(); it !=  HASHMAP.end(); ++it) { //for all the hash keys
hash_keys.push_back(it->first); // get regions colour values as the names of hash table
} 
return hash_keys;
}








#endif