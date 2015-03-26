#ifndef LABEL_REGIONS_H
#define LABEL_REGIONS_H

#include <stdio.h>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"


std::map<int, vector<Point>> label_regions(vector<vector<int>>  clusters, int rows, int cols) {
std::map<int, vector<Point>> region_map;
Point coor;
for (int i = 0; i < rows; i++)  {
       for (int j = 0; j < cols; j++)  {
			
			coor.x=i; coor.y=j;
			if (region_map.count(clusters[i][j])!=0)  
			{ //if the ent exist
				/*vector<Point> exist=region_map[clusters[i][j]];
				exist.push_back(coor);*/
				region_map[clusters[i][j]].push_back(coor); //exist;
				//exist.clear(); 
			}
			else 
			{
				vector<Point> exist;
			    exist.push_back(coor);
				region_map[clusters[i][j]]=exist;
				exist.clear();
			}
				//creating a hashkey with cluster center ID, push all the points there
	
			
	   }
	}
return region_map;
}


#endif