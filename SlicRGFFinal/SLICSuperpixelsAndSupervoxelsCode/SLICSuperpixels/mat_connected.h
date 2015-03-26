#ifndef MAT_CONNECTED_H
#define MAT_CONNECTED_H


#include <stdio.h>
#include <math.h>


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/highgui.h>

using namespace std;
using namespace cv;


/*
This class builds the correspondance matrix for the the regions connections
*/

class mat_connected {

private:
vector<vector<double>> matrix;
double Euclideandist(Vec3b color1, Vec3b color2) {return sqrt(pow(color1.val[0]-color2.val[0],2.0)/1+pow(color1.val[1]-color2.val[1],2.0)+pow(color1.val[2]-color2.val[2],2.0));}





public:
	void mat_connected::initMat(int numReg) {
	vector<double> temp;
	int i=0;
	while (i<numReg)
	{
		temp.push_back(0.0);
		i++;
	}
	int j=0;
	while (j<numReg)
	{
		matrix.push_back(temp);
		j++;
	}

	cout<<matrix.size()<<"x"<<matrix[0].size()<<" matrix is created and initialized with zeros"<<endl;
	}
	
	vector<vector<double>> mat_connected::CheckConnectivity(vector<vector<int>> labels, int rows, int cols) {
	int RegionLab; //so the fist one is just any value
	int neighbour;
	Point coor;
		
	for (int i = 1; i < rows-1; i++)  {    
       for (int j = 1; j < cols-1; j++)  {  
		   //loop avoids all the border pixels
			
		   	// Here all the 4 direct neighbours are to be checked
	//               neighb1
	//       neighb2  pixel neighb3
	//               neighb4

			coor.x=i; coor.y=j;
			RegionLab=labels[i][j]; //label
			neighbour=labels[i-1][j];
			if (neighbour!=RegionLab) 
			matrix[RegionLab][neighbour]=1; //assigne the value 1 for the connected regions;
			neighbour=labels[i+1][j];
			if (neighbour!=RegionLab) 
			matrix[RegionLab][neighbour]=1;
			neighbour=labels[i][j-1];
			if (neighbour!=RegionLab) 
			matrix[RegionLab][neighbour]=1;
			neighbour=labels[i][j+1];
			if (neighbour!=RegionLab) 
			matrix[RegionLab][neighbour]=1;

	   }
	
	}

return matrix;	
}

vector<vector<double>> mat_connected::DeleteRaw(vector<vector<double>> matrix, vector<int> neighb, int index1, int index2, vector<Vec3b> mean){
	
	//cout<<index1<<" main ind, "<<index2<<" second to be merged"<<endl;
//cout<<neighb.size()<<"size of neigb"<<endl;
	for (int j=0; j<neighb.size(); j++) {
		//cout<<neighb[j]<<endl;
		if (neighb[j]!=index1) {
			matrix[neighb[j]][index1]=Euclideandist(mean[neighb[j]], mean[index1]); //change the neighb values
	matrix[index1][neighb[j]]=Euclideandist(mean[index1], mean[neighb[j]]);
		}
    //matrix[neighb[j]][index2]=-1;
	//matrix[index2][neighb[j]]=-2;
	}
	

//cout<<"with the value adjasted"<<endl;
//
//
//		for (int j = 0; j < matrix.size(); j++)  {
//		cout<<endl;
//       for (int i = 0; i < matrix[0].size(); i++)  {  
//		   cout<<matrix[j][i]<<" ";
//	   }
//	}
//
//cout<<endl;


	for (int i=0; i<matrix.size(); i++){
   	matrix[i].erase (matrix[i].begin()+index2); //deleting the column
	}
	matrix.erase(matrix.begin()+index2);//deleteing the row
return matrix;	
}

vector<vector<double>> mat_connected::AddWeightValues(vector<Vec3b> Mean_colour) {
//Function to fill in the matrix with the colour distance between connected regions
	
	size_t numreg=matrix.size();
double dist;
size_t count=0;
int count1;
//cout<<count<<" "<<numreg<<endl;
while (count<numreg) {
	count1=0;
	for (std::vector<double>::iterator it = matrix[count].begin() ; it != matrix[count].end(); ++it) {
		 //scan hrough the matrix
		//cout<<*it<<endl;
		 if (*it>0) {

//cout<<"Mean Colour:"<<Mean_colour[count]<<" "<<Mean_colour[count1]<<endl;
dist=Euclideandist(Mean_colour[count], Mean_colour[count1]);
//cout<<dist;
matrix[count][count1]=dist;		
matrix[count1][count]=dist;
		 }
	count1++;
	}
count++;
}
return matrix;



}


};



#endif
