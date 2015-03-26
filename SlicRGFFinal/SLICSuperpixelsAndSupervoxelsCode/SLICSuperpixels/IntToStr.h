#ifndef INTTOSTR_H
#define INTTOSTR_H


#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>


string IntToStr(int n) 
{
    stringstream result;
    result << n;
    return result.str();
}
#endif