//
//  wav-file.h
//  chroma
//
//  Created by annie zhang on 3/2/13.
//  Copyright (c) 2013 annie zhang. All rights reserved.
//

#ifndef chroma_wav_file_h
#define chroma_wav_file_h


#include <iostream>
#include <iomanip>
#include <cmath>

#ifndef  CONST84
#define CONST84     
#endif


class WavFile{
    
    private:
        bool isExist;
        bool isOpen;
        bool isClose;
        char* fileName;
    
    public:
        WavFile (); 
        ~WavFile (); 
        long int getNumSamples();
        int getNumChannels();
        int getBitsPerSample();
        double getSampleRateHz();
        int displayInformation(char* fileName);
        double readCurrentInput();
        int ifMoreDataAvailable();
    
    public:
        double fs_hz;
        int bitsPerSample;
        int nChannel;
        int numInSamples;
        long int maxInSamples;
        double* gWavDataIn;

    public:
        void openWavFile(FILE * pFile);
        int writeDataToFile();
        int closeWavFile(FILE * pFile);

};

#endif
