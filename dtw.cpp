//
//  dtw.cpp
//  chroma
//
//  Created by annie zhang on 3/3/13.
//  Copyright (c) 2013 annie zhang. All rights reserved.
//

#include "dtw.h"

int DTW::min( int x, int y, int z ) {
  if( ( x <= y ) && ( x <= z ) ) return x;
	if( ( y <= x ) && ( y <= z ) ) return y;
	if( ( z <= x ) && ( z <= y ) ) return z;
}

double DTW::min( double x, double y, double z ) {
	if( ( x <= y ) && ( x <= z ) ) return x;
	if( ( y <= x ) && ( y <= z ) ) return y;
	if( ( z <= x ) && ( z <= y ) ) return z;
}

double DTW::run( int* v, int vlength, int* w, int wlength) {
    
	double cost;
    double** mGamma;
    mGamma = new double*[vlength];
    for(int i=0; i<vlength; i++)
        mGamma[i] = new double[wlength];
    
	for( int i = 1; i < wlength; i++ ) {
		mGamma[0][i] = INF;
	}

	for( int i = 1; i < vlength; i++ ) {
		mGamma[i][0] = INF;
	}
	mGamma[0][0] = 0;
    
	for( int i = 1; i < vlength; i++ ) {
		for( int j = 1; j < wlength; j++ ) {
            cost = sqrt(abs( v[i] - w[j])*abs( v[i] - w[j]));
			mGamma[i][j] = cost + min( mGamma[i-1][j], mGamma[i][j-1], mGamma[i-1][j-1] );
		}
	}
    cost = mGamma[vlength-1][wlength-1];
    for(int i=0; i<vlength; i++)
        delete mGamma[i];
    delete mGamma;

	return cost;
}
