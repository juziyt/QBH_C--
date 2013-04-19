//
//  WavDef.h
//  chroma
//
//  Created by annie zhang on 3/2/13.
//  Copyright (c) 2013 annie zhang. All rights reserved.
//

#ifndef chroma_WavDef_h
#define chroma_WavDef_h


typedef struct{
    char rID[4];      // 'RIFF'
    int rLen;
    char wID[4];      // 'WAVE'
    char fId[4];      // 'fmt'
    int pcmHeaderLength;
    short wFormatTag;
    short numChannels;
    int sampleRate;
    int byteRate;
    short numBlockAlingn;
    short numBitsPerSample;
} WAV_HDR;

/* header of wave file */
typedef struct
{
    char dId[4];  // 'data' or 'fact'
    int dLen;
} CHUNK_HDR;


#endif
