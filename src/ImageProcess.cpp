//
// Created by brAiN on 12/5/2021.
//

#include "../Headers/ImageProcess.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

ImageProcess::ImageProcess(
        const char *_inImgName,
        const char *_outImgName,
        int * _height,
        int * _width,
        int * _bitDepth,
        unsigned char * _header,
        unsigned char * _colorTable,
        unsigned char * _inBuf,
        unsigned char * _outBuf
        )
{
    inImgName  = _inImgName;
    outImgName = _outImgName;
    height     = _height;
    width      = _width;
    bitDepth   = _bitDepth;
    header     = _header;
    colorTable = _colorTable;
    inBuf      = _inBuf;
    outBuf     = _outBuf;
}

void ImageProcess::readImage()
{

    int i;
    FILE *streamIn;
    streamIn = fopen(inImgName,"rb");
    if(streamIn ==(FILE *)0)
    {
        cout<<"Unable to open file. Maybe file does not exist"<<endl;
        exit(0);
    }
    for(i=0;i<BMP_HEADER_SIZE;i++)
    {
        header[i] =  getc(streamIn);
    }
    *width = *(int *)&header[18];           //read the width from the image header
    *height = *(int *)&header[22];
    *bitDepth = *(int *)&header[28];

    if(*bitDepth <=8)
    {

        fread(colorTable,sizeof(unsigned char),BMP_COLOR_TABLE_SIZE,streamIn);
    }

    fread(inBuf,sizeof(unsigned char),_512by512_IMG_SIZE,streamIn );

    fclose(streamIn);
}

void ImageProcess::writeImage(){

    FILE  *fo = fopen(outImgName,"wb");
    fwrite(header,sizeof(unsigned char),BMP_HEADER_SIZE,fo);
    if(*bitDepth <=8)
    {
        fwrite(colorTable,sizeof(unsigned char),BMP_COLOR_TABLE_SIZE,fo);
    }

    fwrite(outBuf, sizeof(unsigned char),_512by512_IMG_SIZE,fo);
    fclose(fo);
}

void ImageProcess::copyImgData(unsigned char *_srcBuf, unsigned char *_destBuf, int bufSize)
{
    for(int i =0;i<bufSize;i++)
    {
        _destBuf[i] = _srcBuf[i];
    }
}

void ImageProcess::binarizeImage(unsigned char *_inImgData, unsigned char *_outImgData, int imgSize, int threshold)
{
    for(int i=0;i<imgSize;i++)
    {
        _outImgData[i] =  (_inImgData[i] > threshold) ? WHITE :BLACK;
    }
}

void ImageProcess::brigthnessUp(unsigned char *_inputImgData, unsigned char *_outImgData, int imgSize, int brightness)
{

    for (int i = 0; i < imgSize; i++) {
        int temp = _inputImgData[i] + brightness;
        _outImgData[i] = (temp > MAX_COLOR) ? MAX_COLOR : temp;
    }

}

ImageProcess::~ImageProcess()
{

}