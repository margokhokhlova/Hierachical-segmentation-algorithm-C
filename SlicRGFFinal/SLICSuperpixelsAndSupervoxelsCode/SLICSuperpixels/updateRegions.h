#ifndef UPDATEREGIONS_H
#define UPDATEREGIONS_H

#include <stdio.h>
#include <map> //to use Hash Table
#include "Getkeysh.h"
int Label1, Label2;
//map<int, vector<Point>>::const_iterator it2, it1;
pair<map<int, vector<Point>>,vector<vector<double>>> updateRegions(pair<map<int, vector<Point>>,vector<vector<double>>> result, int index1, int index2) {
//cout<<"Regions to be merged "<<index1<<" "<<index2<<endl;
//cout<<"Initial size of the Regions "<<Regions.size()<<" and of the centers "<<Label_center.size()<<"."<<endl;
vector<Point> temp, data; 
vector<int> hash_keys=Getkeysh(result.first);

data=result.first[hash_keys[index1]]; //the region which would remain itself after merging
temp=result.first[hash_keys[index2]]; //get all the points from region to be merged
//cout<<data<<"data"<<endl;
//data=it1->second;
for (auto iter=temp.begin(); iter!=temp.end(); iter++) {
	Point coor;
	coor.x=iter->x; coor.y=iter->y;
	data.push_back(coor);
}
result.first[hash_keys[index1]]=data; //push merged data into regions
result.first.erase(hash_keys[index2]); //delete one region

cout<<result.first.size()<<" size of the regions"<<endl;

return result;
}




#endif
