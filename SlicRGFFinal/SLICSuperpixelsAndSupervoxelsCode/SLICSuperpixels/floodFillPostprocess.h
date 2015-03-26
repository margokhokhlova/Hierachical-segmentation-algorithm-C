#ifndef FLOODFILLPOSTPROCESS_H
#define FLOODFILLPOSTPROCESS_H

#include <stdio.h>
#include <iostream>


#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

//This code colors the segmentations

static void floodFillPostprocess( Mat& img, const Scalar& colorDiff=Scalar::all(0) ) {
        CV_Assert( !img.empty() );
        RNG rng = theRNG();
		Mat mask( img.rows+2, img.cols+2, CV_8UC1, Scalar::all(0) ); 
		for( int y = 0; y < img.rows; y++ ) {
            for( int x = 0; x < img.cols; x++ ) {
                if( mask.at<uchar>(y+1, x+1) == 0){
                    Scalar newVal( rng(256), rng(256), rng(256) );
                    floodFill( img, mask, Point(x,y), newVal, 0, colorDiff, colorDiff );
                }
            }
        }
    }
		
#endif
/*
Parameters fo segmenation function:	
src – The source 8-bit, 3-channel image.
dst – The destination image of the same format and the same size as the source.
sp – The spatial window radius.
sr – The color window radius.
maxLevel – Maximum level of the pyramid for the segmentation.
termcrit – Termination criteria: when to stop meanshift iterations.
*/