#ifndef DISPLAYSEGMENTATION_H
#define DISPLAYSEGMENTATION_H


#include <stdio.h>
#include <map>
#include "Getkeysh.h"
#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"



using namespace cv;
using namespace std;

string IntToStr(int n) 
{
    stringstream result;
    result << n;
    return result.str();
}


void displaySegmentation(std::map<std::string, vector<Point>> map, string name, bool f, int rows, int cols, int level) {
Mat SegImage(rows, cols,  CV_8UC3 , Scalar(0,0,255)); //create an image filled with one colo 
vector<string> hash_keys = Getkeysh(map);

for (int i=0; i<map.size(); i++) 


{
		//generate random color for each region
		unsigned char r = 255 * (rand()/(1.0 + RAND_MAX));
        unsigned char g = 255 * (rand()/(1.0 + RAND_MAX));
        unsigned char b = 255 * (rand()/(1.0 + RAND_MAX));
				
			for (int j=0; j<map[hash_keys[i]].size(); j++) 
			{
				Point coordinate=Point(map[hash_keys[i]].at(j));
					SegImage.at<Vec3b>(coordinate)[0]=b;
					SegImage.at<Vec3b>(coordinate)[1]=g;
					SegImage.at<Vec3b>(coordinate)[2]=r;
			//SegImage.at<Vec3b>(coord) = (color.val[0], color.val[1], color.val[2]);
		  
			}
	

	}

//Mat false_color;
//applyColorMap(SegImage, false_color, COLORMAP_HSV);
if (f) {
string filename="result/"+name+"/ImageFin" + IntToStr(level) +".png";
imwrite(filename, SegImage);

}
else
{
string filename="result/"+name+"/ImageSeg" + IntToStr(level) +".png";
 imwrite(filename, SegImage);
}
cout<<"Result saved"<<endl;
}  





#endif







//
//
//
//
//
//
//
//
//
//#ifndef DISPLAYSEGMENTATION_H
//#define DISPLAYSEGMENTATION_H
//
//
//#include <stdio.h>
//#include <map>
//#include "Getkeysh.h"
//#include "opencv2/features2d/features2d.hpp"
////#include "opencv2/contrib/contrib.hpp"
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/objdetect/objdetect.hpp"
//
//
//
//using namespace cv;
//using namespace std;
//
//string IntToStr(int n) 
//{
//    stringstream result;
//    result << n;
//    return result.str();
//}
//
//
//void/*map<string, Vec3d> */displaySegmentation(std::map<std::string, vector<Point>> map, string name, bool f, int rows, int cols, int level/*, std::map<string, Vec3d> color_label*/) {
//Mat SegImage(rows, cols,  CV_8UC3 , Scalar(0,0,255)); //create an image filled with one colo 
//vector<string> hash_keys = Getkeysh(map);
////Vec3b color;
//Point coordinate;
////if (color_label.empty())
////{ // to create the random colorization for the first time.
//for (int i=0; i<map.size(); i++) 
//
//
//{
//		//generate random color for each region
//		unsigned char r = 255 * (rand()/(1.0 + RAND_MAX));
//        unsigned char g = 255 * (rand()/(1.0 + RAND_MAX));
//        unsigned char b = 255 * (rand()/(1.0 + RAND_MAX));
//			/*color_label[hash_keys[i]].val[0]=r;
//				color_label[hash_keys[i]].val[1]=g;
//					color_label[hash_keys[i]].val[2]=b;
//					cout<<color_label[hash_keys[i]]<<" pushed values"<<endl;*/
//			for (int j=0; j<map[hash_keys[i]].size(); j++) 
//			{
//					coordinate=Point(map[hash_keys[i]].at(j));
//					SegImage.at<Vec3b>(coordinate)[0]=b;
//					SegImage.at<Vec3b>(coordinate)[1]=g;
//					SegImage.at<Vec3b>(coordinate)[2]=r;
//			//SegImage.at<Vec3b>(coord) = (color.val[0], color.val[1], color.val[2]);
//		  
//			}
//	
//
//	}
////cout<<"Color lab size"<<color_label.size();
////}
//
////else	// the case when the color label list is already created and just have to be used...
////{  
////	for (int i=0; i<map.size(); i++) {
////		color.val[0]=color_label[hash_keys[i]].val[0];
////		color.val[1]=color_label[hash_keys[i]].val[1];
////		color.val[2]=color_label[hash_keys[i]].val[2];
////		cout<<"scalar values"<<color_label[hash_keys[i]]<<endl;
////		cout<<color.val[0]<<" "<<color.val[1]<<" "<<color.val[2]<<endl;
////		for (int j=0; j<map[hash_keys[i]].size(); j++) 
////		{
////				coordinate=Point(map[hash_keys[i]].at(j));
////				SegImage.at<Vec3b>(coordinate)[0]=color.val[0];
////				SegImage.at<Vec3b>(coordinate)[1]=color.val[1];
////				SegImage.at<Vec3b>(coordinate)[2]=color.val[2];
////		}
////	}
////}
////Mat false_color;
////applyColorMap(SegImage, false_color, COLORMAP_HSV);
//if (f) {
//string filename="result/"+name+"/ImageFin" + IntToStr(level) +".png";
//imwrite(filename, SegImage);
//
//}
//else
//{
//string filename="result/"+name+"/ImageSeg" + IntToStr(level) +".png";
// imwrite(filename, SegImage);
//}
//cout<<"Result saved"<<endl;
////return color_label;
//}  
//
//
//
//
//
//#endif