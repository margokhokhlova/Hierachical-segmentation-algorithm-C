#ifndef COLORSEGMENTATIONMEANCOLOR_H
#define COLORSEGMENTATIONMEANCOLOR_H


#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "IntToStr.h"

Mat ColorSegmentationMeanColor(map<int, vector<Point>> regions, vector<Vec3b> color, int rows, int cols, string name, int level) {
vector<Point>::iterator It;
Mat SegImage(rows, cols,  CV_8UC3 , Scalar(0,0,255)); //create an image filled with one color
vector<int>hash_keys=Getkeysh(regions);
for (int d=0; d<regions.size(); d++) {
	for (It=regions[hash_keys[d]].begin(); It!=regions[hash_keys[d]].end(); It++) {
		Point2i coordinate=*It; //get a point coordinate	
		SegImage.at<Vec3b>(coordinate.x, coordinate.y)=color[d];
		//cout<<color[d]<<endl;
	}
}
//Mat SegImFilt;
//adaptiveBilateralFilter(SegImage, SegImFilt, Size(3,3), 5.0, 10.0, Point(-1, -1), BORDER_DEFAULT ); //Bilaerial filtering
string filename="result/"+name+"/ImageColoredMean" + IntToStr(level) +".png";
imwrite(filename, SegImage);
//Mat SegImageLab;
//cvtColor(SegImage, SegImageLab, CV_BGR2Lab);
return SegImage;
}
#endif