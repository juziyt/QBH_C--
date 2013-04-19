//
//  dtw.h
//  chroma
//
//  Created by annie zhang on 3/3/13.
//  Copyright (c) 2013 annie zhang. All rights reserved.
//

#ifndef chroma_dtw_h
#define chroma_dtw_h

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

class DTW {
public:
  //vector< vector<double> > mGamma;
	enum {
		INF = 100000000
	};
	int min( int x, int y, int z );
	double min( double x, double y, double z );
    
	//DTW( int n, int m ): mGamma( n, vector<double>( m, INF ) ) {};
    DTW(int n, int m){};
	~DTW() {};
    
	double run( int* v, int vlength, int* w, int wlength );
};


#endif
