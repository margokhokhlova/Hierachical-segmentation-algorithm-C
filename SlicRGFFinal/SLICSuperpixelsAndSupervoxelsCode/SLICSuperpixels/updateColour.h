#ifndef UPDATECOLOUR_H
#define UPDATECOLOUR_H


#include <stdio.h>
#include <math.h>

double temp;
vector<Vec3b> updateColour(vector<Vec3b> mean_colour, int count, int index) {
Vec3b colour;
//cout<<"color to merge "<<mean_colour[count]<<" "<<mean_colour[index]<<endl;


temp=(mean_colour[count].val[0]+mean_colour[index].val[0])/2;
colour.val[0]=ceil(temp);
temp=(mean_colour[count].val[1]+mean_colour[index].val[1])/2;
colour.val[1]=ceil(temp);
temp=(mean_colour[count].val[2]+mean_colour[index].val[2])/2;
colour.val[2]=ceil(temp);
//cout<<colour<<" - updated value"<<endl;
mean_colour[count]=colour;

//cout<<index<<" index to be deleted"<<endl;
mean_colour.erase(mean_colour.begin()+index);


//cout<<mean_colour.size()<<" size"<<endl;
return mean_colour;
}


#endif