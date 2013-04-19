//
//  Querybh.h
//  chroma
//
//  Created by annie zhang on 3/9/13.
//  Copyright (c) 2013 annie zhang. All rights reserved.
//

#ifndef __chroma__Querybh__
#define __chroma__Querybh__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include "ChromaFeat.h"
#include "WavDef.h"
#include "dtw.h"

class Querybh{
    
public:
    Querybh();
    ~Querybh();
  int GetMaxIndex(float* x, int xsize);
    int* GetMinIndex(vector<double> x);
    double MinVal(vector<double> x);
    int sinc(int p);
    double sinc(double x);
    int mid(int p[], int psize);
    int exist(vector<int> pp, int q);
    int* MatchChroma(int* target, int targetsize);
    int* Smooth(int* c, long csize);
    int GetChromaMatch(float* samples, long numSamples);
    void resample(float* input, float* output, unsigned in_rate, unsigned out_rate, long in_length);
    bool convolve1D(short* in, float* out, long dataSize, float* kernel, int kernelSize);
    int qbh(char* path);
    
protected:
	vector<std::string> songlist;
    vector<std::string> distinctlist;
    vector<int*> ps;
    vector<int> lengthlist;
    
};

#endif /* defined(__chroma__Querybh__) */
