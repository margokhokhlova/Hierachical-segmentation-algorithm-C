#ifndef GETCONTOURSWITHCANNY_H
#define GETCONTOURSWITHCANNY_H



// to obtain the canny edges on an image

Mat edge, gray, final;
Mat getContourswithCanny(Mat image, string name, int level) {
cvtColor(image, gray, CV_BGR2GRAY);
Canny( gray, edge, 50, 150, 5);
edge.convertTo(final, CV_8U);
string filename="result/"+name+"/Canny"+ IntToStr(level) +".png";
imwrite(filename, final);


return final;
}
















#endif
