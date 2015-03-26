#ifndef GETLABELEDGRAPH_H
#define GETLABELEDGRAPH_H

#include <stdio.h>
#include <algorithm>


#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

//
//#include "Node.h"
#include "mat_connected.h"

// This function takes labels obtained from the superpixels computation 
// and make a graph representation, for each region nearest neighbours 
// are computed and saved. 

using namespace cv;
using namespace std;


/*vector<Node>*/
vector<vector<double>> GetLabeledGraph(int size, vector<vector<int>> superpix, int rows, int cols, vector<Vec3b> mean) {
//vector<Node> GraphNode;
//vector<Point>::iterator It;
vector<vector<double>> connections;
/*Point coordinate;*/ //to get each point coodinates
	cout<<"Create matrix"<<endl;
mat_connected Mat_connected;
Mat_connected.initMat(size);
//
cout<<"Locate neighbours"<<endl;
connections=Mat_connected.CheckConnectivity(superpix, rows, cols);
	//for (int j = 0; j < size; j++)  {
	//	cout<<endl;
 //      for (int i = 0; i < size; i++)  {  
	//	   cout<<connections[i][j]<<" ";
	//   }
	//}
cout<<"Apply Weight"<<endl;

vector<vector<double>> connectionsweighted=Mat_connected.AddWeightValues(mean);
cout<<"done"<<endl;

//
return connectionsweighted;
}


#endif

