#include<vector>
#include<iostream>
#include<string>
#include<Windows.h>
#include"BitmapIOSample.h"

int main()
{
    std::string inputImageName;
    std::string outputImageName;

    unsigned int averageColor1 = 0x0;
    unsigned int averageColor2 = 0x0;
    unsigned int averageColor3 = 0x0;
    unsigned int averageColor4 = 0x0;
    unsigned int averageColor5 = 0x0;
    unsigned int resultColor1 = 0x0;
    unsigned int resultColor2 = 0x0;
    unsigned int resultColor3 = 0x0;
    unsigned int resultColor4 = 0x0;
    unsigned int resultColor5 = 0x0;
    unsigned int resultColor6 = 0x0;

    std::cin >> inputImageName;
    std::cin >> outputImageName;
    std::cin >> averageColor1;
    std::cin >> averageColor2;
    std::cin >> averageColor3;
    std::cin >> averageColor4;
    std::cin >> averageColor5;
    std::cin >> resultColor1;
    std::cin >> resultColor2;
    std::cin >> resultColor3;
    std::cin >> resultColor4;
    std::cin >> resultColor5;
    std::cin >> resultColor6;



    BitmapManager bitmapManager;
    std::vector<byte> pixels;

    bitmapManager.LoadBitmap24(inputImageName, pixels);
    bitmapManager.EditBitmap(pixels, averageColor1, averageColor2, averageColor3, averageColor4, averageColor5, resultColor1, resultColor2, resultColor3, resultColor4, resultColor5, resultColor6);
    bitmapManager.SaveBitmap24(outputImageName, pixels.data());

    return 0;
}

/*
unsigned char averageColor1 = 0x0;
    unsigned char averageColor2 = 0x0;
    unsigned char averageColor3 = 0x0;
    unsigned char averageColor4 = 0x0;
    unsigned char averageColor5 = 0x0;
    unsigned char resultColor1 = 0x0;
    unsigned char resultColor2 = 0x0;
    unsigned char resultColor3 = 0x0;
    unsigned char resultColor4 = 0x0;
    unsigned char resultColor5 = 0x0;
    unsigned char resultColor6 = 0x0;

    std::cin >> averageColor1;
    std::cin >> averageColor2;
    std::cin >> averageColor3;
    std::cin >> averageColor4;
    std::cin >> averageColor5;
    std::cin >> resultColor1;
    std::cin >> resultColor2;
    std::cin >> resultColor3;
    std::cin >> resultColor4;
    std::cin >> resultColor5;
    std::cin >> resultColor6;

    230
210
170
90
50
255
150
50
0
0
0
    にしたらaverageColor1に"2"、averageColor2に"3"、averageColor3に"0"。勝手に文字型にするのか…

./bmp/NoelleGuts.bmp
./bmp/NoelleGutsoutput.bmp
230
210
170
90
50
255
150
50
0
0
0
*/