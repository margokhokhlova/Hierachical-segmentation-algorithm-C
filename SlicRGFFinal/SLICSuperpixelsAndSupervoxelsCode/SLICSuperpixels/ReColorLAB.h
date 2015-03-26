#ifndef RECOLORLAB_H
#define RECOLORLAB_H





#include <vector>
#include <string>
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include <algorithm>

using namespace std;


vector<vector<double>> ReColorLAB(vector<vector<double>> matrix, vector<Vec3b> Mean_colour) {
size_t numreg=matrix.size();
double dist;
Vec3b color1, color2;
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
			color1=Mean_colour[count];
			color2=Mean_colour[count1];
dist=sqrt(pow(color1.val[0]-color2.val[0],2.0)/5+pow(color1.val[1]-color2.val[1],2.0)+pow(color1.val[2]-color2.val[2],2.0));
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

#endif