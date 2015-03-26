#ifndef CONVERTSTRING_H
#define CONVERTSTRING_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "opencv2/core/core.hpp"


string convertString(Vec3b  color) {
int col_coord[3] = {(int)color.val[0], (int)color.val[1], (int)color.val[2]}; //get the colour values
			int gt; 
			stringstream sw; //create string and put there the colour coordinates
			string CODEDstring;
			for (gt = 0; gt < 3; gt++)
			{
				sw << col_coord[gt]<<','; //so that each coordinate was separated by como
			}
			
			CODEDstring=sw.str();
return CODEDstring;
}			

#endif