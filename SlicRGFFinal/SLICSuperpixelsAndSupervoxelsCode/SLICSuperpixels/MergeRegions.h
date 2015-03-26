#ifndef MERGEREGIONS_H
#define MERGEREGIONS_H


#include <stdio.h>

#include <map> //to use Hash Table

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"


#include "updateRegions.h"

#include "updateColour.h"

double dist;
double Euclideandist(Vec3b color1, Vec3b color2)
{
dist=0.0;
dist=sqrt(pow(color1.val[0]-color2.val[0],2.0)/4+pow(color1.val[1]-color2.val[1],2.0)+pow(color1.val[2]-color2.val[2],2.0)); //Euclidean distance between regions= );
return dist;
}

// Function is comparing regions and merge the ones which similarity is lower than a threshold
// and distance between which is lower than Average distance between region centers * 2
// Output are updated Region map and vector with region-center coordinate corespondance
// Inputs are Region map, Label and center vector, threshold values
mat_connected Mat_connected;
pair<map<int, vector<Point>>,vector<vector<double>>> MergeRegions(map<int, vector<Point>> Regions, vector<vector<double>> conmatrix,  double threshold, vector<Vec3b> mean_colour) 
{
cout<<"Threshold value is "<<threshold<<endl;
pair<map<int, vector<Point>>,vector<vector<double>>> result;
result.first=Regions; result.second=conmatrix; 
int x, x1, y, y1;
int index, index2, tempind;


vector<int> neigh;
bool NothingToMerge=false;
while (NothingToMerge==false) {
int count=0;
double distance=1000.0, tempdistance, finaldistance;
//vector<vector<int>>temp;
while( count<result.first.size())
{	
	//for all regions
	//vector<int> neigh;
	//distance=1000.00; //to calculate anew the value
	 for (std::vector<double>::iterator it = conmatrix[count].begin() ; it != conmatrix[count].end(); ++it) {
	 
	 //matrix conmatrix is the connectivity matrix, where entry is one if the regions have common border and entry is 0 if they don't
	 // so browsing though the line with corresponding index, all non-zero components would be the direct neigbours.
	 //val=it*;
	 
		 if (*it>0) { //Here I am taking the indexes of all the corresponding regions
			 tempdistance=*it;
			  //tempindex = it - conmatrix[count].begin();
				
		 if (distance>tempdistance) {
				distance=tempdistance; //store the value		
				 index2=it - conmatrix[count].begin();
				 index=count;
			}
		}	

 }
count++;
}
//at this moment I have the most similar regions to merge and their indexes
finaldistance=distance;
 //cout<<finaldistance<<" Last val to compare"<<endl;

if (finaldistance<threshold)
{
	//cout<<index<<" "<<index2<<" and mean colour is"<<mean_colour.size()<<endl;
	for (std::vector<double>::iterator it = conmatrix[index2].begin() ; it != conmatrix[index2].end(); ++it) {
	 if (*it>0) {
	 tempind = it - conmatrix[index2].begin();
	 //cout<<tempind<<" ";
	 neigh.push_back(tempind);
		}
	}
result=updateRegions(result, index, index2); //update procedure
conmatrix=Mat_connected.DeleteRaw(conmatrix, neigh, index, index2, mean_colour);
mean_colour=updateColour(mean_colour, index, index2); //update the new mean color
neigh.clear();
index=0; index2=0;  //just reinit variables when regions are megrged
//	for (int i = 0; i < conmatrix.size(); i++)  {
//		cout<<endl;
//       for (int j = 0; j < conmatrix[i].size(); j++)  {  
//		     cout<<conmatrix[i][j]<<" ";
//	   }
//	}
//cout<<conmatrix.size()<<endl;

//neigh.clear();
//cout<<endl;
}
else NothingToMerge=true; 
}
result.second=conmatrix;
return result;
}



#endif







//Greedy merge

//#ifndef MERGEREGIONS_H
//#define MERGEREGIONS_H
//
//
//#include <stdio.h>
//
//#include <map> //to use Hash Table
//
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//
//
//#include "updateRegions.h"
//
//#include "updateColour.h"
//
//double dist;
//double Euclideandist(Vec3b color1, Vec3b color2)
//{
//dist=0.0;
//dist=sqrt(pow(color1.val[0]-color2.val[0],2.0)/4+pow(color1.val[1]-color2.val[1],2.0)+pow(color1.val[2]-color2.val[2],2.0)); //Euclidean distance between regions= );
//return dist;
//}
//
//// Function is comparing regions and merge the ones which similarity is lower than a threshold
//// and distance between which is lower than Average distance between region centers * 2
//// Output are updated Region map and vector with region-center coordinate corespondance
//// Inputs are Region map, Label and center vector, threshold values
//mat_connected Mat_connected;
//pair<map<int, vector<Point>>,vector<vector<int>>> MergeRegions(map<int, vector<Point>> Regions, vector<vector<int>> conmatrix,  double threshold, vector<Vec3b> mean_colour) 
//{
//cout<<"Threshold value is "<<threshold<<endl;
//pair<map<int, vector<Point>>,vector<vector<int>>>result;
//result.first=Regions; result.second=conmatrix; 
//int x, x1, y, y1;
//int index, tempindex, tempind;
//double distance=1000.0, tempdistance, finaldistance;
//int count=0;
//
////vector<vector<int>>temp;
//while( count<result.first.size())
//{	
//	//for all regions
//	vector<int> neigh;
//	distance=1000.00; //to calculate anew the value
//	 for (std::vector<int>::iterator it = conmatrix[count].begin() ; it != conmatrix[count].end(); ++it) {
//	 
//	 //matrix conmatrix is the connectivity matrix, where entry is one if the regions have common border and entry is 0 if they don't
//	 // so browsing though the line with corresponding index, all non-zero components would be the direct neigbours.
//	 //val=it*;
//	 
//		 if (*it>0) { //Here I am taking the indexes of all the corresponding regions
//				tempindex = it - conmatrix[count].begin();
//				//cout<<"Index of the neighbour "<<tempindex<<endl;
//				tempdistance=Euclideandist(mean_colour[count], mean_colour[tempindex]); //calculate the distance between the regions
//				//cout<<tempdistance<<" dist "<<endl; cout<<" distance "<<distance<<endl;
//		 if (distance>tempdistance) {
//				distance=tempdistance; //store the value		
//				 index=tempindex;
//			}
//		}	
//
// }
// finaldistance=distance;
// //cout<<finaldistance<<" Last val to compare"<<endl;
//if (finaldistance<threshold)
//{
//	result=updateRegions(result, count, index); //update procedure
//	mean_colour=updateColour(mean_colour, count, index); //update the new mean color
//	for (std::vector<int>::iterator it = conmatrix[index].begin() ; it != conmatrix[index].end(); ++it) {
//	 if (*it>0) {
//	 tempind = it - conmatrix[index].begin();
//	 //cout<<tempind<<" ";
//	 neigh.push_back(tempind);
//		}
//	}
//conmatrix=Mat_connected.DeleteRaw(conmatrix, neigh, count, index);
//neigh.clear();
//tempindex=0; index=0; tempdistance=0; //just reinit variables when regions are megrged
////	for (int i = 0; i < conmatrix.size(); i++)  {
////		cout<<endl;
////       for (int j = 0; j < conmatrix[i].size(); j++)  {  
////		     cout<<conmatrix[i][j]<<" ";
////	   }
////	}
////cout<<conmatrix.size()<<endl;
//}
////neigh.clear();
////cout<<endl;
//count++;	
//}
//result.second=conmatrix;
//return result;
//}
//
//
//
//#endif
//

