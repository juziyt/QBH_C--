//
//  WavFile.cpp
//  chroma
//
//  Created by annie zhang on 3/2/13.
//  Copyright (c) 2013 annie zhang. All rights reserved.
//

#include "WavFile.h"
#include "WavDef.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

WavFile::WavFile(){}      

WavFile::~WavFile(){}

long int WavFile::getNumSamples()
{
    return maxInSamples;
}

int WavFile::getNumChannels()
{
    return nChannel;
}

int WavFile::getBitsPerSample()
{
    return bitsPerSample;
}

double WavFile::getSampleRateHz()
{
    return fs_hz;
}

int WavFile::ifMoreDataAvailable()
{
    if(numInSamples >= maxInSamples)
        return 0;
    return 1;
}

double WavFile::readCurrentInput()
{
    if( (gWavDataIn == NULL) || (maxInSamples <=0) || (numInSamples < 0) )
        printf("\nInput file not ready (or not loaded) !!!\n");
    
    if( numInSamples >= maxInSamples)
        printf("What you reading. Nothing is left to read, you crazy book-worm!!");

    return gWavDataIn[numInSamples++];
}

void WavFile::openWavFile(FILE * pFile)
{
    int i;
    size_t stat;
    char outBuffer[80];
    WAV_HDR* pWavHeader;
    CHUNK_HDR* pChunkHeader;
    short int* pU;
    unsigned char* pC;
    int sFlag;
    long int rMore;
    char* wBuffer;
    int wBufferLength;
   
    gWavDataIn = NULL;
    numInSamples = 0;
    maxInSamples = 0;
    
    pWavHeader = new WAV_HDR;
    pChunkHeader = new CHUNK_HDR;
    
    if( NULL == pWavHeader )
    {
        printf("can't new headers\n");
        exit(-1);
    }
    if( NULL == pChunkHeader )
    {
        printf("can't new headers\n");
        exit(-1);
    }

    stat = fread((void*)pWavHeader, sizeof(WAV_HDR), (size_t)1, pFile);
    if(stat != 1)
    {
        printf("Header missing. Maybe format is not OK!\n"); 
        exit(-1);
    }

    for(i = 0; i < 4; i++)
        outBuffer[i] = pWavHeader->rID[i];
    
    outBuffer[4] = 0;

    if(strcmp(outBuffer, "RIFF") != 0) 
    {
        printf("Bad RIFF format. I am not cool enough to support everything\n");
        exit(-1);
    }

    cout<<pWavHeader->rID<<endl;
    for(i = 0; i < 4; i++)
        outBuffer[i] = pWavHeader->wID[i];

    outBuffer[4] = 0;
   
    if(strcmp(outBuffer, "WAVE") != 0) 
    {
        printf("Bad WAVE format. I am not cool enough to support everything\n");
        exit(-1);
    }
    
    for(i = 0; i < 4; i++)
    {
        outBuffer[i] = pWavHeader->fId[i];
    }
    outBuffer[4] = 0;
  
    if(strcmp(outBuffer, "fmt ") != 0) // not with "fmt" since 4th pos is blank
    {
        printf("\nBad fmt format");
        exit(-1);
    }
    if(pWavHeader->wFormatTag != 1)
    {
        printf("\n Bad wav wFormatTag");
        exit(-1);
    }

    if( (pWavHeader->numBitsPerSample != 16) && (pWavHeader->numBitsPerSample != 8))
    {
        printf("\nBad wav bits per sample");
    }

    rMore = pWavHeader->pcmHeaderLength - (sizeof(WAV_HDR) - 20);
    if( 0 != fseek(pFile, rMore, SEEK_CUR))
        printf("Can't seek.");

    sFlag = 1;
  
    while(sFlag != 0)
    {
        if(sFlag > 10) { printf("\nToo manu chunks"); exit(-1);}
        stat = fread((void*)pChunkHeader, sizeof(CHUNK_HDR), (size_t)1, pFile);

        if( 1 != stat)
        {
            printf("\n I just can't read data. Sorry! haha");
            exit(-1);
        }
      
        for(i =0; i < 4; i++)
        {
            outBuffer[i] = pChunkHeader->dId[i];
        }
       
        outBuffer[4] = 0;
       
        if(strcmp(outBuffer, "data") == 0) { break;}
               sFlag++;

        stat = fseek(pFile, pChunkHeader->dLen, SEEK_CUR);
   
        if(stat != 0)
        {
            printf("Can't seek.");
            exit(-1);
        }
    }

    wBufferLength = pChunkHeader->dLen;
   
    maxInSamples = pChunkHeader->dLen;
    maxInSamples /= pWavHeader->numBitsPerSample/8;
    wBuffer = new char[wBufferLength];

    if( wBuffer == NULL)
        printf("\nCan't allocate."); exit(-1);

    gWavDataIn = new double[maxInSamples];

    if(gWavDataIn == NULL)
        printf("Can't allocate\n"); exit(-1);
   
    stat = fread((void*)wBuffer, wBufferLength, (size_t)1, pFile);

    if( 1 != stat)
    {
        printf("\nCan't read buffer.");
        exit(-1);
    }
  
    if(pWavHeader->numBitsPerSample == 16)
    {
        pU = (short*) wBuffer;
        for( i = 0; i < maxInSamples; i++)
        {
            gWavDataIn[i] = (double) (pU[i]);
        }
    }
    else
    {
        pC = (unsigned char*) wBuffer;
        for( i = 0; i < maxInSamples; i++)
        {
            gWavDataIn[i] = (double) (pC[i]);
        }
    }
    
#ifdef  DEBUG11
   
    for( i = 0; i < maxInSamples; i++)
    {
        printf("%d:%f\t",i, gWavDataIn[i]);
    }

#endif     /* -----  not DEBUG  ----- */
    fs_hz = (double) (pWavHeader->sampleRate);
    
    bitsPerSample = pWavHeader->numBitsPerSample;
    
    nChannel = pWavHeader->numChannels;
    
    /* reset and delete */
   
    numInSamples = 0;
   
    if(wBuffer != NULL) delete wBuffer;

    if(pWavHeader != NULL) delete pWavHeader;

    if(pChunkHeader != NULL) delete pChunkHeader;
  
    fclose(pFile);
}

int WavFile::displayInformation(char* fName)
{
#if 1
    printf("\n-----------------------------------------------------");
    printf("\nLoaded wav file : %s", fName);

    printf("\nSample rate: %1.01f (Hz)", fs_hz);

    printf("\nNumber of samples = %ld", maxInSamples);

    printf("\nBits per sample = %d", bitsPerSample);

    printf("\nNumber of channels = %d", nChannel);

    printf("\n----------------------------------------------------\n");
  
#endif
    
    return EXIT_SUCCESS;

}

int WavFile::writeDataToFile()
{
    FILE* pFile;
    pFile = fopen("speechData.txt", "w");
    for( int i = 0; i < maxInSamples; i++)
    {
        char data[30];
        int n;
        n = sprintf(data,"%d\t%1.01f\n",i,gWavDataIn[i]);
        fprintf(pFile, data);
    }

    fclose(pFile);
    return EXIT_SUCCESS;

}
