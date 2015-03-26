#ifndef GET_REGIONS_H
#define GET_REGIONS_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <map> //to use Hash Table
#include "convertString.h"
#include <algorithm>    // std::sort

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
//
//struct myclass {
//bool operator() (cv::Point pt1, cv::Point pt2) { return (pt1.y < pt2.y);}
//} myobject; //this one to sort the region with vector points

static std::map<std::string, vector<Point>> Get_regions(Mat & res_seg, std::map<std::string, vector<Point>>  hash_map) {
int rows = res_seg.rows;
int cols = res_seg.cols; //take the dimensions
typedef pair<string, Point> Hash_Pair;
cout << "Calculating the regions" << std::endl;
//std::map<std::string, vector<Point>> hash_map; //create an empty hashmap
// each key value would be the the unique colour value from segmented regions
			 for (int a = 0; a < cols; a++) {// loop for all the pixels
			 	 for (int b = 0; b < rows; b++) {
					 Vec3b  color = res_seg.at<Vec3b>(Point(a, b)); // take the colour coordinate from the pixel
					 // std::string s = std::to_string("%d%d%d",color_val(0), color_val(1),color_val(2));
					string returnstring=convertString(color);
						 if (hash_map.find(returnstring) != hash_map.end()) {//check if such entry exist in my hash  table
					 	 //case exist
						 hash_map[returnstring].push_back(Point(a, b)); //adding the point to he existing entry
						}
					 else {
						 //  if not exist
						 vector < Point> data; //create new vector
						 data.push_back(Point(a, b)); //get point coord and push it into the created vector
						 
						 hash_map[returnstring] = data; // create a new entry with String name and push string there
						 data.clear(); //clean vector after use
						}
				  }

			}

	////sort the values of the hashmap obtained
	//vector<string> hash_keys=Getkeysh(hash_map);
	//for (r=0; r<hash_map.size; r++) 
	//{
	//	sort(hash_map[hash_keys[r]].begin(), hash_map[hash_keys[r]].end(), myobject); // sort all he point by the increasing orde of y.
	//}
			 cout<<"Number of regions"<<hash_map.size()<<endl;
			 return hash_map;

}

#endif