#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<fstream>

struct BitmapHeader
{
    unsigned short bfType;//54�o�C�g=4�̔{���ł͂Ȃ����߁A���ɂ���ẮA�����o�̈�O�ɋ󂫂�����遨�\���̂̃p�f�B���O�H����Ƃ��A�ǂݔ�΂��Ă���ۂ��B4byte�ǂ��2byte�i�[���Ď̂ĂĂ�
    unsigned long bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned long bfOffBits;
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPixPerMeter;
    int biYPixPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImporant;
};

class BitmapManager {
public:
    void LoadBitmap24(std::string path, std::vector<unsigned char>& pixels);
    void EditBitmap(std::vector<unsigned char>& pixels);
    void SaveBitmap24(std::string path, const unsigned char* pixels);
    void EditBitmap(std::vector<unsigned char>& pixels, unsigned int averageColor1, unsigned int averageColor2, unsigned int averageColor3, unsigned int averageColor4, unsigned int averageColor5, unsigned int resultColor1, unsigned int resultColor2, unsigned int resultColor3, unsigned int resultColor4, unsigned int resultColor5, unsigned int resultColor6);

private:
    const char* headerBinary;
    BitmapHeader bitmapHeader;
    void InsertToHeader();
    int ToBitmapStep(int step);
};



/*
https://any-programming.hatenablog.com/entry/2017/04/27/110723
*/