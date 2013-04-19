#ifndef _CHROMA_FEAT
#define _CHROMA_FEAT

#include "rsrfft.h"
#include <cmath>
#include <vector>

#define FS  			 4000
#define NUMBEROFCHROMES		12
#define STARTNOTE           48
#define ENDNOTE             83
#define NUMNOTES            36
#define _2ROOT12		1.059463094f
#define FREQREF		7.943049790954413f	// the frequency of (midi = -0.5), which is the left boundary for C0
#define ZERO_PADDING_RATE	1.0f



class ChromaFeat {
public:
	int Chroma(const float* buffer);
	//int Chroma2(const short* buffer);
	ChromaFeat(unsigned long lengthArg);
	~ChromaFeat();
	float *chroma;
    int chromadim = NUMBEROFCHROMES;
    double *gDataIn;
	
protected:
	SplitRadixFFT *fft;
	unsigned long length;
	float *hammingWin;
	float *powerOf2ROOT12;
	unsigned long FFT_Point;
	short FFT_Order; 
};

#endif
