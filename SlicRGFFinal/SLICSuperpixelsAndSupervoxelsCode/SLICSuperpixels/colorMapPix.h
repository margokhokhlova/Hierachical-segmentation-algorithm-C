#ifndef colorMapPix_H
#define colorMapPix_H

#include <stdio.h>
#include <map>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"



Mat colorMapPix(Mat image) {
	//cout<<"HU"<<endl;
	Mat G(image.rows, image.cols, CV_8U);
std::vector<int>::iterator index;
int rand_ind;
vector<int> label, G_val;
for (int i=0; i<image.rows; i++) {
	for (int j=0; j<image.cols; j++) {
		Scalar color=image.at<uchar>(i,j);
		//cout<<color<<endl;
		if (label.empty()) {
			label.push_back(color.val[0]);
		    rand_ind=rand() %255;
			G_val.push_back(rand_ind);	
		}
		if (find(label.begin(), label.end(), color.val[0])==label.end())
		{
			rand_ind=rand() %255;
			label.push_back(color.val[0]);
			G_val.push_back(rand_ind);
			G.at<uchar>(i,j)=rand_ind;
		}
		else
		{ 
        index=(find(label.begin(), label.end(), color.val[0]));
		
		G.at<uchar>(i,j)=G_val[index-label.begin()];
		}
		

            

	}
}

return G; 
}
#endif