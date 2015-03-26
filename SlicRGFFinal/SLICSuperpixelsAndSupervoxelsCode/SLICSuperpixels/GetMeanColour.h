#ifndef GETMEANCOLOUR_H
#define GETMEANCOLOUR_H


#include <map>
#include <stdio.h>      
#include <math.h>       /* nearbyint */
#include <iostream>
#include <cmath>
#include <climits>

vector<Point> data;

vector<Vec3b> vectorcolour;
int counter;
Point coord;
vector<Vec3b> GetMeanColour(map<int, vector<Point>> Regions, Mat image, int mode){
vectorcolour.clear();
	if (mode==1) {
	cout<<"Mean colour mode on"<<endl;
for(map<int, vector<Point>>::const_iterator it = Regions.begin(); it !=  Regions.end(); ++it) { //for all the hash keys
	data.clear();
	Vec3d colour;
	data=it->second;
	//cout<<data.size()<<"size";
	colour.val[0]=0; colour.val[1]=0; colour.val[2]=0;
	//cout<<colour;
	counter=0;
	for (std::vector<Point>::iterator it1 = data.begin() ; it1 != data.end(); ++it1) {
		coord=*it1;
		//cout<<coord<<"coordinate which breakes"<<endl;
	    colour.val[0]=colour.val[0]+image.at<Vec3b>(coord.x, coord.y).val[0];
		colour.val[1]=colour.val[1]+image.at<Vec3b>(coord.x, coord.y).val[1];
		colour.val[2]=colour.val[2]+image.at<Vec3b>(coord.x, coord.y).val[2];
		//cout<<*it1<<endl;
		//cout<<image.at<Vec3b>(*it1)<<" Color from an image" <<endl;
		counter++;
		} 
	
	colour.val[0]=ceil(colour.val[0]/counter);
	colour.val[1]=ceil(colour.val[1]/counter);
	colour.val[2]=ceil(colour.val[2]/counter);
	
	//cout<<vectorcolour.size()<<" ";
vectorcolour.push_back(colour);


}
}

	else {
    int temp_index;
	cout<<"medium"<<endl;
    vector<int> R, G, B;
	for(map<int, vector<Point>>::const_iterator it = Regions.begin(); it !=  Regions.end(); ++it) { //for all the hash keys
	data.clear();
	Vec3d colour;
	data=it->second;
	//cout<<data.size()<<"size";
	colour.val[0]=0; colour.val[1]=0; colour.val[2]=0;
	//cout<<colour;
	
	for (std::vector<Point>::iterator it1 = data.begin() ; it1 != data.end(); ++it1) {
		coord=*it1;
		colour=image.at<Vec3b>(coord.x, coord.y);
	R.push_back(colour.val[0]); G.push_back(colour.val[1]); B.push_back(colour.val[2]);
	}

sort(R.begin(), R.end()); 
sort(G.begin(), G.end()); 
sort(B.begin(), B.end()); 
size_t n=R.size();
int medium;
 if(n%2==0) medium = (R[(n-1)/2]+R[((n-1)/2)+1])/2; // median finding
 else medium=R[n/2];
 colour.val[0]=medium;
 if(n%2==0) medium = (G[(n-1)/2]+G[((n-1)/2)+1])/2; // median finding
 else medium=G[n/2];
 colour.val[1]=medium;
 if(n%2==0) medium = (B[(n-1)/2]+B[((n-1)/2)+1])/2; // median finding
 else medium=B[n/2];
 colour.val[2]=medium;
// cout<<colour<<endl;
	//cout<<vectorcolour.size()<<" ";
vectorcolour.push_back(colour);


}
	
	
	}




return vectorcolour;

}






#endif