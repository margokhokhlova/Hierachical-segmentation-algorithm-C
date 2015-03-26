#ifndef GETINDEXOFLARGESTELEMENT_H
#define GETINDEXOFLARGESTELEMENT_H


#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"

int getIndexOfLargestElement(vector<int> arr, int size) {
    int largestIndex = 0;
    for (int index = largestIndex; index < size; index++) {
        if (arr[largestIndex] < arr[index]) {
            largestIndex = index;
        }
    }
    return largestIndex;
}
#endif