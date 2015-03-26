#ifndef COLORREGION_H
#define COLORREGION_H

Mat ColorRegion(Mat image, std::map<std::string, vector<Point>> map, string key, vector<Point> pixels)   {
	Point coordinate; //int x, y;
	vector<Point>::iterator It;
	if (map[key].size()>pixels.size()) {
		coordinate=map[key].at(0);
		//x=coordinate.x; y=coordinate.y;
		Vec3b colour=image.at<Vec3b>(coordinate);
		for (It=pixels.begin(); It!=pixels.end(); It++) {
			 coordinate=*It;    
			 image.at<Vec3b>(coordinate)=colour;
		}
	
	}
	else {
		coordinate=pixels[0];
		Vec3b colour=image.at<Vec3b>(coordinate);
			for (It=map[key].begin(); It!=map[key].end(); It++) {
		     coordinate=*It;    
			 image.at<Vec3b>(coordinate)=colour;

	}

	}

return image;
}




#endif