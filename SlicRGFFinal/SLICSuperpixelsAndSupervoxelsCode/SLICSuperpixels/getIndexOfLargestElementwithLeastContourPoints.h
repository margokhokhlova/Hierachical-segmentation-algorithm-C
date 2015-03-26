

#ifndef GETINDEXOFLARGESTELEMENTWITHLEASTCONTOURPOINTS_H
#define GETINDEXOFLARGESTELEMENTWITHLEASTCONTOURPOINTS_H


#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"

int getIndexOfLargestElementwithLeastContourPoints(vector<int> arr, int size, vector<int> contour) {
    int largestIndex = 0;
    for (int index = largestIndex; index < size; index++) {
        if (double(arr[largestIndex]/contour[largestIndex]) < double(arr[index]/contour[index])) {
            largestIndex = index;
        }
    }
    return largestIndex;
}
#endif