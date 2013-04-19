//
//  Querybh.cpp
//  chroma
//
//  Created by annie zhang on 3/9/13.
//  Copyright (c) 2013 annie zhang. All rights reserved.
//

#include "Querybh.h"

using namespace std;

Querybh::Querybh(){}
Querybh::~Querybh(){}

int Querybh::GetMaxIndex(float* x, int xsize)
{
    int index = 0;
    float max = x[0];
    for (int k=1; k< xsize; k++){
        if (x[k]>max){
            index = k;
            max = x[k];
        }
    }
    return index;
}

int* Querybh::GetMinIndex(vector<double> x)
{
    int* minindex = new int[3];
    int index;
    double min;
    for (int i=0; i<3; i++){
        index = 0;
        min = x[0];
        for (int k=1; k< x.size(); k++){
            if (x[k]<min){
                index = k;
                min = x[k];
            }
        }
        minindex[i] = index;
        x[index] = INFINITY;
    }
    return minindex;
}



double Querybh::MinVal(vector<double> x)
{
    int index = 0;
    double min = x[0];
    for (int k=1; k< x.size(); k++){
        if (x[k]<min){
            index = k;
            min = x[k];
        }
    }
    return min;
}

int Querybh::sinc(int p)
{
    if (p>0) return 1;
    else if (p<0) return -1;
    else return 0;
}

int Querybh::exist(vector<int> pp, int q)
{
    int out = -1;
    for(int j=0; j<pp.size(); j++)
        if(pp[j] == q)
            out = j;
    return out;
}

int Querybh::mid(int p[], int psize)
{
    vector<int> list;
    vector<int> ele;
    list.clear();
    ele.clear();
    int find;
    for(int i=0; i<psize; i++){
        find = exist(list, p[i]);
        if (find==-1){
            list.push_back(p[i]);
            ele.push_back(1);
        }
        else
            ele[find]++;
    }
    int maxele = ele[0];
    int maxindex = 0;
    for (int i=1; i<ele.size(); i++) {
        if (ele[i]>maxele){
            maxindex = i;
            maxele = ele[i];
        }
    }
    return list[maxindex];
}


int* Querybh::MatchChroma(int* target, int targetsize)
{
    int p0[] = {2,2,0,0,2,9,9,9,9,9,11,1,1,11,11,0,1,1,9,9,9,10,1,1,1,0,11,10,10,9,9,9,9,11,1,0,0,11,11,1,1,9,9,9};
    int p1[] = {8,8,8,8,7,7,7,8,8,8,8,8,5,5,5,5,5,5,5,11,6,6,6,9,9,9,4,4,9,9,9,8,8,8,8,8,8,8,9,9,6,6,6,6,6,6,6,9,9,9};
    int p2[] = {1,3,3,6,11,10,10,10,11,2,2,3,3,6,11,10,10,10,10,1,1,1,11,11,11,11,11,11,11,5,5,7,7,7,7,4,1,1,2,2,2};
    int p3[] = {10,10,7,7,7,7,7,7,7,7,7,10,0,5,5,5,5,5,5,4,4,4,7,7,8,8,8,10,10,3,1,1,2,2,9,10,0,0,9,7,7,7,8,0,11,11,1,1,1,0,0,0,4,3,3,3,3,0,10,10,10,10,4,4,4,6,7,7,11,10,10,10,10,11,9,9,7,8,3,3,3};
    
    int** p;
    p = new int*[4];
    p[0] = new int[sizeof(p0)/sizeof(int)];
    p[1] = new int[sizeof(p1)/sizeof(int)];
    p[2] = new int[sizeof(p2)/sizeof(int)];
    p[3] = new int[sizeof(p3)/sizeof(int)];
    
    
    p[0] = p0;
    p[1] = p1;
    p[2] = p2;
    p[3] = p3;

    
    songlist.push_back("here comes the sun.wav");
    songlist.push_back("someone like you.wav");
    songlist.push_back("goodbye.wav");
    songlist.push_back("hey jude.wav");
    
    lengthlist.push_back(sizeof(p0)/sizeof(int));
    lengthlist.push_back(sizeof(p1)/sizeof(int));
    lengthlist.push_back(sizeof(p2)/sizeof(int));
    lengthlist.push_back(sizeof(p3)/sizeof(int));


    int* midp = new int[lengthlist.size()];
    for(int i=0; i<lengthlist.size(); i++)
        midp[i] = mid(p[i], lengthlist[i]);

    int midpt = mid(target, targetsize);
    
    for (int i=0; i<lengthlist.size(); i++){
        for(int j=0; j<lengthlist[i]; j++){
            p[i][j] = (p[i][j]-midp[i]+midpt+12)%12;
          //  cout<<p[i][j]<<",";
        }
     //   cout<<endl<<endl;
    }

    for (int i=0; i<lengthlist.size(); i++)
        ps.push_back(p[i]);
    
    vector<double> dist;
    dist.clear();
//    vector<double> dtemp;
//    for (int k=0; k<songlist.size(); k++){
//        dtemp.clear();
//        int pp=0;
//        if((lengthlist[k]-targetsize)>4){
//            while (1) {
//                DTW *mDTW = NULL;
//                mDTW = new DTW(targetsize, targetsize+5);
//                dtemp.push_back(mDTW->run(target, targetsize, &ps[k][pp], targetsize+5));
//                pp++;
//                if(pp+targetsize+5>lengthlist[k])
//                    break;
//                delete mDTW;
//            }
//        }
//        else if ((targetsize-lengthlist[k])>4){
//            while (1) {
//                DTW *mDTW = NULL;
//                mDTW = new DTW(lengthlist[k]+5, lengthlist[k]);
//                dtemp.push_back(mDTW->run(&target[pp], lengthlist[k]+5, &ps[k][0], lengthlist[k]));
//                pp++;
//                if(pp+lengthlist[k]+5>targetsize)
//                    break;
//                delete mDTW;
//            }
//        }
//        
//        else{
//            DTW *mDTW = NULL;
//            mDTW = new DTW(targetsize, targetsize);
//            dtemp.push_back(mDTW->run(target, targetsize, &ps[k][0], targetsize));
//            delete mDTW;
//        }
//        dist.push_back(MinVal(dtemp));
    for (int k=0; k<lengthlist.size(); k++){
        DTW *mDTW = NULL;
        mDTW = new DTW(targetsize, lengthlist[k]);
        dist.push_back(mDTW->run(target, targetsize, &ps[k][0], lengthlist[k]));
        delete mDTW;
    }
    return GetMinIndex(dist);
}

int* Querybh::Smooth(int* c, long csize)
{
    for (int i=1; i<csize-1; i++){
        if(c[i-1] == c[i+1])
            c[i] = c[i-1];
    }
    return c;
}


int Querybh::GetChromaMatch(float* samples, long numSamples)
{
    long chunk = 4096;
    int movesize = 1024;
    int ksize = int((numSamples-chunk)/movesize);
    int* targetchroma = new int[ksize+1];
//    int* targetchromadiff = new int[ksize];
    
    for(int j=0; j<ksize; j++){
        ChromaFeat *cf = new ChromaFeat(chunk);
        cf->Chroma(&samples[j*movesize]);
        targetchroma[j]=GetMaxIndex(cf->chroma, cf->chromadim);
        delete cf;
    }
    ChromaFeat *cf = new ChromaFeat(numSamples-ksize*movesize);
    cf->Chroma(&samples[ksize*movesize]);
    targetchroma[ksize]=GetMaxIndex(cf->chroma, cf->chromadim);
    delete cf;

    int* smoothedchroma = Smooth(targetchroma, ksize+1);
    
    for(int i=0; i<ksize+1; i++)
        cout<<smoothedchroma[i]<<",";
    cout<<endl<<ksize+1<<endl<<endl;
//    for(int i=0; i<ksize; i++){
//        targetchromadiff[i] = smoothedchroma[i+1]-smoothedchroma[i];
//    }

    int* match = MatchChroma(smoothedchroma, ksize+1);
    cout<<"1. "<<songlist[match[0]]<<endl;
    cout<<"2. "<<songlist[match[1]]<<endl;
    cout<<"3. "<<songlist[match[2]]<<endl;
    return match[0];
}

double Querybh::sinc(double x)
{
    if(x == 0.0) return 1.0;
    x *= 3.141592653; // pi
    return std::sin(x) / x;
}

void Querybh::resample(float* input, float* output, unsigned in_rate, unsigned out_rate, long in_length)
{
    double ratio        = in_rate / (double)out_rate;
    unsigned out_length = std::ceil(in_length / ratio);
    const double support = 4.0;
    
    for(unsigned i=0; i<out_length; ++i)
    {
        double center = i * ratio;
        double min    = center-support;
        double max    = center+support;
        
        unsigned min_in = std::max(0,                  (int)(min + 0.5) );
        unsigned max_in = std::min( (int)in_length-1,  (int)(max + 0.5) );
        double sum    = 0.0;
        double result = 0.0;
        for(unsigned i=min_in; i<=max_in; ++i)
        {
            double factor = sinc(i-center);
            result += input[i] * factor;
            sum    += factor;
        }
        if(sum != 0.0) result /= sum;
        output[i] = result + 0.5;
    }
}

bool Querybh::convolve1D(short* in, float* out, long dataSize, float* kernel, int kernelSize)
{
    int i, j, k;
    
    // check validity of params
    if(!in || !out || !kernel) return false;
    if(dataSize <=0 || kernelSize <= 0) return false;
    
    // start convolution from out[kernelSize-1] to out[dataSize-1] (last)
    for(i = kernelSize-1; i < dataSize; ++i)
    {
        out[i] = 0;                             // init to 0 before accumulate
        
        for(j = i, k = 0; k < kernelSize; --j, ++k)
            out[i] += in[j] * kernel[k];
    }
    
    // convolution from out[0] to out[kernelSize-2]
    for(i = 0; i < kernelSize - 1; ++i)
    {
        out[i] = 0;                             // init to 0 before sum
        
        for(j = i, k = 0; j >= 0; --j, ++k)
            out[i] += in[j] * kernel[k];
    }
    return true;
}


bool convolve(short *in, long dataSize, float *kernel, int kernelSize, float *&out)
{
    int count=0;
    if(!in || !kernel) return false;
    if(dataSize <=0 || kernelSize <= 0) return false;
    
    long outSize = dataSize+kernelSize-1;
    out = new float[outSize];
    for(int i=0; i<outSize; i++)
        out[i] = 0.0;
    for(int k=0; k<dataSize; k++)
    {
        for(int m=0; m<kernelSize; m++)
        {
            if(k+m < outSize)
            {
                count++;
                out[k+m] += in[k] * kernel[m];
            }
        }
    }
    return true;
}



int Querybh::qbh(char* path)
{
    printf("haha...\n");

    FILE * pFile;
    pFile = fopen (path,"rb");
    if (pFile==NULL)
    {
        printf("can not open file\n");
        exit(-1);
    }
    
    long int maxInSamples;
    short* gWavDataIn;
    char* wBuffer;
    int wBufferLength;
    short int* pU;
    unsigned char* pC;
    
    size_t stat;
    WAV_HDR* pWavHeader = new WAV_HDR;
    CHUNK_HDR* pChunkHeader = new CHUNK_HDR;
    
    fseek (pFile , 0 , SEEK_END);
    long lSize=ftell(pFile);
    rewind (pFile);
   
    char* buffer = new char[lSize];
    stat = fread(buffer, lSize, 1, pFile);
    if( 1 != stat)
    {
        printf("I just can't read data. Sorry!\n");
        exit(-1);
    }
   
    int startp=0;
    for(int j=0; j<lSize-4; j++){
        if(buffer[j]=='d'&&buffer[j+1]=='a'&&buffer[j+2]=='t'&&buffer[j+3]=='a'){
            startp = j;
            break;
        }
    }
    rewind(pFile);

    // allocate memory to contain the whole file:
    stat = fread(pWavHeader, sizeof(WAV_HDR), 1, pFile);
    if( 1 != stat)
    {
        printf("I just can't read data. Sorry!\n");
        exit(-1);
    }
    
    if(startp-36>0){
        char* buffer1= new char[startp];
        stat = fread(buffer1, startp, 1, pFile);
        if( 1 != stat)
        {
            printf("I just can't read data. Sorry!\n");
            exit(-1);
        }
    }


//    pFile = fopen (path,"rb");
//    if (pFile==NULL)
//    {
//        printf("can not open file\n");
//        exit(-1);
//    }
    
//   int startp = 36;
//    char* buffer1;
//    buffer1 = (char*) malloc (sizeof(char)*startp);
//    cout<<startp<<endl;
//    stat = fread((void*)buffer1, sizeof(buffer1), (size_t)1, pFile);
//    
//    for(int i=0; i<36; i++)
//        cout<<buffer1[i]<<endl;

//    cout<<pFile->_offset<<endl;
    stat = fread((void*)pChunkHeader, sizeof(CHUNK_HDR), (size_t)1, pFile);
    if( 1 != stat)
    {
        printf("I just can't read data. Sorry!\n");
        exit(-1);
    }
    
    gWavDataIn = NULL;
    wBufferLength = pChunkHeader->dLen;
    maxInSamples = pChunkHeader->dLen;
    maxInSamples /= pWavHeader->numBitsPerSample/8;
    wBuffer = new char[wBufferLength];
    if( wBuffer == NULL){
        printf("Can't allocate\n");
        exit(-1);
    }
    
    gWavDataIn = new short[maxInSamples];
    
    if(gWavDataIn == NULL){
        printf("Can't allocate\n");
        exit(-1);
    }
    
    stat = fread((void*)wBuffer, wBufferLength, (size_t)1, pFile);
    if( 1 != stat)
    {
        printf("Can't read buffer\n");
        exit(-1);
    }
    
    if(pWavHeader->numBitsPerSample == 16)
    {
        pU = (short*) wBuffer;
        for( int i = 0; i < maxInSamples; i++)
        {
            gWavDataIn[i] = (short) (pU[i]);
        }
    }
    else
    {
        pC = (unsigned char*) wBuffer;
        for( int i = 0; i < maxInSamples; i++)
        {
            gWavDataIn[i] = (short) (pC[i]);
        }
    }
    
    fclose (pFile);
    
    int windowsize = 38;
    long convolvedsize = maxInSamples+windowsize-1;
    float window[windowsize];
    
    float a0 = 0.42659;
    float a1 = 0.49656;
    float a2 = 0.076849;
    float pi = 3.141592653;
    
    // blackman window
    for(int j=0; j<windowsize; j++)
        window[j] = a0 - a1*cos(2*pi*j/(windowsize-1)) + a2*cos(4*pi*j/(windowsize-1));
    
    float* convolvedData;
    int b = convolve(&gWavDataIn[0], maxInSamples, &window[0], windowsize, convolvedData);
    if(!b)
        cout<<"can't convolve"<<endl;
    
//    float* convolvedData = new float[convolvedsize];
//    convolve1D(&gWavDataIn[0], convolvedData, convolvedsize, &window[0], windowsize);
    
    int newdatasize = ceil(convolvedsize*4000/44100);
    float* newdata = new float[newdatasize];
    resample(convolvedData, newdata, 44100, 4000, convolvedsize);
    
    return GetChromaMatch(newdata, newdatasize);
    
}
