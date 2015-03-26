#include <string>
#include "SLIC.h"
#include <iostream>
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "floodFillPostprocess.h"




FUCK IT!


//#include "label_regions.h"
#include "Getkeysh.h"
//#include "getIndexOfLargestElement.h"
//#include "getIndexOfLargestElementwithLeastContourPoints.h"
//#include "keyExist.h"
//#include "displaySegmentation.h"
#include "colorMapPix.h"
#include "GetMeanColour.h"
#include "ColorSegmentationMeanColor.h"
//#include "getContourswithCanny.h"
#include "mat_connected.h"
#include "ColorRegion.h"
#include "RollingGuidanceFilter.h"
#include "label_regions.h"
#include "GetLabeledGraph.h"
#include "MergeRegions.h"
#include "IntToStr.h"
#include "Get_regions.h"
#include "ReColorLAB.h"

// for directory checking
#define DIRECTORY_CHECKING
#ifdef DIRECTORY_CHECKING

#if defined(_WIN32) || defined(_MSC_VER)
#include <Windows.h>
#include <WinBase.h>
#include <WinNT.h>
#include <Shlobj.h>
#include <io.h>

#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#endif

#endif

#include "time.h"


using namespace cv; 
using namespace std;



typedef pair<std::string, vector<Point>> Hash_Pair;
int main(int argc, const char * argv[])
{
	string st = "119082.jpg"; //file name
	clock_t start,end;
	Mat img = imread(st, IMREAD_COLOR);
	int rows=img.rows;
	int cols=img.cols;
	if(img.empty())
	{
		cout<<"No such file.\n";
		getchar();
		exit(1);
	}
	Mat imglab;
	CreateDirectory(("result\\"+st).c_str(), NULL); //create a directory
	std::ofstream o(("result\\"+st+"\\savetxt").c_str()); //create file with parameters
	o<<"Parameters for the obtained hierarchy"<<endl;
	//Mat edge=getContourswithCanny(img1, st, 1000);
	
	cvtColor(img, imglab, CV_BGR2Lab);
	Mat img1 = imread(st, IMREAD_COLOR);
	Mat imgRGBA(img.rows, img.cols, CV_8UC4);
	cvtColor(img, img, CV_BGR2RGB);
	cvtColor(img, imgRGBA, CV_RGB2RGBA);
	Mat imgARGB(imgRGBA.rows, imgRGBA.cols, imgRGBA.type());
	int from_to[] = { 0,1, 1,2, 2,3, 3,0 };
	cv::mixChannels(&imgRGBA, 1, &imgARGB, 1, from_to, 4);
	int width = imgARGB.cols;
	int height = imgARGB.rows;
	int sz = width*height;
	//*imgARGB.channels();
	// unsigned int (32 bits) to hold a pixel in ARGB format as follows:
	// from left to right,
	// the first 8 bits are for the alpha channel (and are ignored)
	// the next 8 bits are for the red channel
	// the next 8 bits are for the green channel
	// the last 8 bits are for the blue channel
	unsigned int* pbuff = new UINT[sz];	
	uchar * p_data = imgARGB.data;
	for(int i = 0; i < sz; i++, p_data+=4)
		pbuff[i] = UINT(((*p_data)<<24) + ((*(p_data+1))<<16) + ((*(p_data+2))<<8) + *(p_data+3));
	//----------------------------------
	// Initialize parameters
	//----------------------------------	
	int* klabels = NULL;
	int numlabels(0);
	int k=700; //number of superpix;
	int m=20; //second parameter
	int num_iter=4;
	float sigma_s(8.0); float sigma_r(0.5); //for the RGF
	/*string filename = "result\\image.jpg";*/
	o<<"Method with weighted color dist. Black/1"<<endl;
	o<<"Superpixels defined "<<k<<endl;
	vector<Mat> SEG_level; //each segmented map
	size_t temp=0, temp2; //for the merging step
    vector<std::map<int, vector<Point>>> REG_hierach;//region maps
		vector<std::map<std::string, vector<Point>>> Hierach_seg; //store the maps
		//store the mean colour for region
		vector<Vec3b> mean_colour;
	//----------------------------------
	// Perform SLIC on the image buffer
	//----------------------------------
	SLIC segment;
	start = clock();
	segment.DoSuperpixelSegmentation_ForGivenNumberOfSuperpixels(pbuff, width, height, klabels, numlabels, k, m);
	end = clock();
//char* str="labels.jpg";
//char* filename3="result/35010.jpg";
//segment.SaveSuperpixelLabels(klabels, width, height, str,  filename3);	
	// Alternately one can also use the function DoSuperpixelSegmentation_ForGivenStepSize() for a desired superpixel size
	Mat labelMat(height, width, CV_8U); //Actual labels!
	p_data = labelMat.data;  
	for(int i = 0; i < sz; i++) 
	*p_data++ = (uchar)(klabels[i]);
	///take the labels?  

//
//
//string filename="result/"+st+"/ImageSuperPix.png";
//imwrite(filename, labelMat); //apply a colour map on it!
Mat rgbmat;
//cvtColor(labelMat,rgbmat,CV_GRAY2RGB);
Mat G=colorMapPix(labelMat);
Mat R=colorMapPix(labelMat);
std::vector<cv::Mat> array_to_merge;
array_to_merge.push_back(labelMat); array_to_merge.push_back(G); array_to_merge.push_back(R);
cv::merge(array_to_merge, rgbmat);
floodFillPostprocess(rgbmat, Scalar::all(1)); // display result coloured		
std::map<std::string, vector<Point>> hash_map0;
hash_map0=Get_regions(rgbmat,hash_map0); //to make hash map for the pixels 
cout<<"Number of regions "<<hash_map0.size()<<endl;
cout<<rows<<" rows"<<cols<<" cols"<<endl;
vector<vector<int>> Labels;
for (int i=0;i<rows; i++) {
	vector<int> temp_lab;
	for (int j=0; j<cols; j++) {
    temp_lab.push_back(0);
	}
	Labels.push_back(temp_lab);
	temp_lab.clear();
}
cout<<Labels.size()<<endl;


int label_temp=0;
cout<<label_temp;
vector<Point> onereg;
Point coord;

for (map<std::string, vector<Point>>::iterator it=hash_map0.begin(); it!=hash_map0.end(); it++){
	onereg=it->second;
	for (vector<Point>::iterator iter=onereg.begin(); iter!=onereg.end(); iter++) {
		coord=*iter;
		//cout<<coord<<endl;
		Labels[coord.y][coord.x]=label_temp;
	}
	label_temp++;
}

//cout<<rows<<" "<<cols<<endl;
//cout<<img.at<Vec3b>(23,382)<<endl;




//prepare an image for the segmentation

	//----------------------------------
	// Draw boundaries around segments
	//----------------------------------
	segment.DrawContoursAroundSegments(pbuff, klabels, width, height, 0xff0000);
	
	//----------------------------------
	// Save the image with segment boundaries.
	//----------------------------------	
	p_data = imgARGB.data;
	for(int i = 0; i < sz; i++)
	{
		*p_data++ = (uchar)(pbuff[i] >> 24) & 255;
		*p_data++ = (uchar)(pbuff[i] >> 16) & 255;
		*p_data++ = (uchar)(pbuff[i] >> 8) & 255;
		*p_data++ = (uchar)(pbuff[i]);
	}


	int from_to2[] = { 0,3, 1,0, 2,1, 3,2 };
	cv::mixChannels(&imgARGB, 1, &imgRGBA, 1, from_to2, 4);
	cv::cvtColor(imgRGBA, imgRGBA, CV_RGBA2BGRA);
	
	string filename1="result/"+st+"/ImageSuperPixCont.png";
	cv::imwrite(filename1, imgRGBA);




std::map<int, vector<Point>> Regions=label_regions(Labels, rows, cols); 
cout<<Regions.size();
REG_hierach.push_back(Regions);
o<<"Number of regions computed with the superpixels is:"<<Regions.size()<<endl;
	cout<<"Superpixels computed and saved. Total number of regions is: "<<Regions.size()<<endl;
cout<<"Build the neigbours graph for "<<Regions.size()<<" regions"<<endl;
size_t numreg=Regions.size(); int condat = static_cast<int>(numreg);
mean_colour=GetMeanColour(REG_hierach.back(), img1, 1); //maybe i+1
vector<vector<double>> Mat_connections=GetLabeledGraph(condat, Labels, rows, cols, mean_colour);
Mat img_colored=ColorSegmentationMeanColor(REG_hierach.back(), mean_colour, rows, cols, st, 1000);
Regions.clear(); mean_colour.clear();

cout<<"Super pixels extracted. Simplification of the image is started"<<endl;
double threshold=5.5; //(JND)
o<<"Threshoild value for merging is equal: "<<threshold<<endl;

// ******************************** Hierarchical aligment procedure *************************************** //
Mat res1, res;
bool NoMoreRegions;
 int i=0;
 while (num_iter<24) {
 NoMoreRegions=false;
threshold=threshold+0.55;
 cout<<"Mat_connections"<<Mat_connections.size()<<endl;
 cout << "Running the Rolling Guidance filtering" << std::endl;
res1 = RollingGuidanceFilter::filter(img1,sigma_s,sigma_r, num_iter); //to store result of filtering
string filename3="result/"+st+"/ImageFilteredaferSegm" + IntToStr(i) +".png";
imwrite(filename3, res1); 
sigma_s=sigma_s+2; sigma_r=sigma_r+0.15; //update for next iteration
o<<"Rolling Guidance Filter Parameters. sigma_s - "<<sigma_s<<", sigma_r - "<<sigma_r<<", number of iterations -"<<num_iter<<endl;
if (i>4) {num_iter++;}
res;
cvtColor(res1, res, CV_BGR2Lab);
string filename4="result/"+st+"/ImageFilteredaferSegmLAB" + IntToStr(i) +".png";
imwrite(filename4, res); 
mean_colour=GetMeanColour(REG_hierach.back(), res,1);
res.release(); res1.release();
Mat_connections=ReColorLAB(Mat_connections, mean_colour);

//while (NoMoreRegions==false) {
cout<<"scanning the regions"<<endl;
//temp2=temp;
//mean_colour=GetMeanColour(REG_hierach.back(), res); //maybe i+1
//cout<<mean_colour.size();
pair<map<int, vector<Point>>,vector<vector<double>>> result=MergeRegions(REG_hierach.back(), Mat_connections, threshold, mean_colour);
if (result.first.size()<10)
break;//Label_center=result.second;
REG_hierach.push_back(result.first); //save the hierachical level
Mat_connections=result.second; //update the matrix with regions
//temp=result.first.size();

//if (temp==temp2){
i++;
//NoMoreRegions=true;
	//	}
//	}
cout<<"When all regions Merged, the size is "<<REG_hierach.back().size()<<endl;
o<<"When all regions Merged, the size is "<<REG_hierach.back().size()<<endl;
mean_colour=GetMeanColour(REG_hierach.back(), img1, 1);
cout<<REG_hierach.back().size()<<"Number of regions"<<endl;
cout<<mean_colour.size()<<"size of color values"<<endl;
img_colored=ColorSegmentationMeanColor(REG_hierach.back(), mean_colour, rows, cols, st, i);
mean_colour.clear();
 }




	printf("\n\n******** PROGRAM EXITED NORMALLY : %f seconds ********\n\n",float(end-start)/CLOCKS_PER_SEC);
	waitKey(0);
	return 0; 
}

