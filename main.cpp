#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "./Headers/ImageProcess.h"

using namespace std;

int main() {
    int imgWidth, imgHeight, imgBitDepth;
    unsigned char imgHeader[BMP_HEADER_SIZE];
    unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
    unsigned char imgInBuffer[_512by512_IMG_SIZE];
    unsigned char imgOutBuffer[_512by512_IMG_SIZE];

    const char imgName[] ="../images/lena512.png";
    const char newImgName[] ="../images/lena512_bright4.png";

    ImageProcess *myImage  = new ImageProcess(imgName,
                                                    newImgName,
                                                    &imgHeight,
                                                    &imgWidth,
                                                    &imgBitDepth,
                                                    &imgHeader[0],
                                                    &imgColorTable[0],
                                                    &imgInBuffer[0],
                                                    &imgOutBuffer[0]
    );

    myImage->readImage();

    myImage->brigthnessUp(imgInBuffer,imgOutBuffer,_512by512_IMG_SIZE,150);
    myImage->writeImage();

    cout<<"Success !"<<endl;
    cout<<"Image Height : "<<imgHeight<<endl;
    cout<<"Image Width  : "  <<imgWidth<<endl;

    return 0;
}