#include"BitmapIOSample.h"


void BitmapManager::LoadBitmap24(std::string path, std::vector<unsigned char>& pixels)
{
    std::ifstream ifs(path, std::ios_base::in | std::ios::binary);
    if (ifs.fail()) {
        std::cerr << "File open error: " << path << "\n";
        std::quick_exit(0);
    }
    std::ifstream::pos_type currentPos = ifs.tellg();//�ǂݍ��݈ʒu

    //ifs.read((char*)&bitmapHeader, sizeof(BitmapHeader));//56
    ifs.read((char*)&bitmapHeader.bfType, sizeof(bitmapHeader.bfType));
    ifs.read((char*)&bitmapHeader.bfSize, sizeof(bitmapHeader.bfSize));
    ifs.read((char*)&bitmapHeader.bfReserved1, sizeof(bitmapHeader.bfReserved1));
    ifs.read((char*)&bitmapHeader.bfReserved2, sizeof(bitmapHeader.bfReserved2));
    ifs.read((char*)&bitmapHeader.bfOffBits, sizeof(bitmapHeader.bfOffBits));
    ifs.read((char*)&bitmapHeader.biSize, sizeof(bitmapHeader.biSize));
    ifs.read((char*)&bitmapHeader.biWidth, sizeof(bitmapHeader.biWidth));
    ifs.read((char*)&bitmapHeader.biHeight, sizeof(bitmapHeader.biHeight));
    ifs.read((char*)&bitmapHeader.biPlanes, sizeof(bitmapHeader.biPlanes));
    ifs.read((char*)&bitmapHeader.biBitCount, sizeof(bitmapHeader.biBitCount));
    ifs.read((char*)&bitmapHeader.biCompression, sizeof(bitmapHeader.biCompression));
    ifs.read((char*)&bitmapHeader.biSizeImage, sizeof(bitmapHeader.biSizeImage));
    ifs.read((char*)&bitmapHeader.biXPixPerMeter, sizeof(bitmapHeader.biXPixPerMeter));
    ifs.read((char*)&bitmapHeader.biYPixPerMeter, sizeof(bitmapHeader.biYPixPerMeter));
    ifs.read((char*)&bitmapHeader.biClrUsed, sizeof(bitmapHeader.biClrUsed));
    ifs.read((char*)&bitmapHeader.biClrImporant, sizeof(bitmapHeader.biClrImporant));

    //�ǂݍ��݈ʒu
    currentPos = ifs.tellg();

    {
        int w = bitmapHeader.biWidth;
        int h = bitmapHeader.biHeight;
        int step = ToBitmapStep(3 * w);

        std::vector<unsigned char> originalPixels(step * h);
        ifs.seekg(bitmapHeader.bfOffBits);//�ǂݍ��݈ʒu����
        ifs.read((char*)originalPixels.data(), originalPixels.size());
        //�����܂ł����A2839102�c(10�i)�œ����Ă�

        pixels.resize(3 * w * h);
        for (int i = 0; i < h; ++i)
            memcpy(pixels.data() + i * 3 * w, originalPixels.data() + i * step, 3 * w);
    }

    //�t�@�C�����鏈��
    ifs.close();
}

int BitmapManager::ToBitmapStep(int step)
{
    int paddings[] = { 0, 3, 2, 1 };
    return step + paddings[step % 4];
}

void BitmapManager::SaveBitmap24(std::string path, const unsigned char* pixels)
{
    std::ofstream ofs(path, std::ios::binary);
    if (ofs.fail()) {
        std::cerr << "File open error: " << path << "\n";
        std::quick_exit(0);
    }

    int step = ToBitmapStep(3 * bitmapHeader.biWidth);

    bitmapHeader.bfType = 0x4d42; // "BM"
    bitmapHeader.bfSize = step * bitmapHeader.biHeight + 54;//???????????
    bitmapHeader.bfReserved1 = 0;
    bitmapHeader.bfReserved2 = 0;
    bitmapHeader.bfOffBits = 54;
    bitmapHeader.biSize = 40;
    bitmapHeader.biWidth = bitmapHeader.biWidth;
    bitmapHeader.biHeight = bitmapHeader.biHeight;
    bitmapHeader.biPlanes = 1;
    bitmapHeader.biBitCount = 24;
    bitmapHeader.biCompression = 0;
    bitmapHeader.biSizeImage = 0;
    bitmapHeader.biXPixPerMeter = 0;
    bitmapHeader.biYPixPerMeter = 0;
    bitmapHeader.biClrUsed = 0;
    bitmapHeader.biClrImporant = 0;
    
    ofs.write((char*)&bitmapHeader.bfType, sizeof(bitmapHeader.bfType));
    ofs.write((char*)&bitmapHeader.bfSize, sizeof(bitmapHeader.bfSize));
    ofs.write((char*)&bitmapHeader.bfReserved1, sizeof(bitmapHeader.bfReserved1));
    ofs.write((char*)&bitmapHeader.bfReserved2, sizeof(bitmapHeader.bfReserved2));
    ofs.write((char*)&bitmapHeader.bfOffBits, sizeof(bitmapHeader.bfOffBits));
    ofs.write((char*)&bitmapHeader.biSize, sizeof(bitmapHeader.biSize));
    ofs.write((char*)&bitmapHeader.biWidth, sizeof(bitmapHeader.biWidth));
    ofs.write((char*)&bitmapHeader.biHeight, sizeof(bitmapHeader.biHeight));
    ofs.write((char*)&bitmapHeader.biPlanes, sizeof(bitmapHeader.biPlanes));
    ofs.write((char*)&bitmapHeader.biBitCount, sizeof(bitmapHeader.biBitCount));
    ofs.write((char*)&bitmapHeader.biCompression, sizeof(bitmapHeader.biCompression));
    ofs.write((char*)&bitmapHeader.biSizeImage, sizeof(bitmapHeader.biSizeImage));
    ofs.write((char*)&bitmapHeader.biXPixPerMeter, sizeof(bitmapHeader.biXPixPerMeter));
    ofs.write((char*)&bitmapHeader.biYPixPerMeter, sizeof(bitmapHeader.biYPixPerMeter));
    ofs.write((char*)&bitmapHeader.biClrUsed, sizeof(bitmapHeader.biClrUsed));
    ofs.write((char*)&bitmapHeader.biClrImporant, sizeof(bitmapHeader.biClrImporant));

    std::vector<unsigned char> bmpPixels(step * bitmapHeader.biHeight);
    for (int i = 0; i < bitmapHeader.biHeight; ++i)
        memcpy(bmpPixels.data() + i * step, pixels + i * 3 * bitmapHeader.biWidth, 3 * bitmapHeader.biWidth);
    ofs.write((char*)bmpPixels.data(), bmpPixels.size());

    //�t�@�C�����鏈��
    ofs.close();
}

void BitmapManager::InsertToHeader() {
    {
        char bfTyape_temp[2] = {};
    }
    for (int i = 0; i < 2; i++) {
        headerBinary[i];
    }
    
}

void BitmapManager::EditBitmap(std::vector<unsigned char> & pixels) {
    for (int i = 0; i < bitmapHeader.biWidth * bitmapHeader.biHeight; ++i) {
        //std::swap(pixels[3 * i], pixels[3 * i + 2]);
        //������std::vector<unsigned char>*�ɂ�����A�N�Z�X�ᔽ�B���[�v����łȂ��Ă�B
        //�Q�Ɠn���ł������
        unsigned char average = ((pixels[3 * i] + pixels[3 * i + 1] + pixels[3 * i + 2]) / 3);

        if (average > 240) {
            average = 255;
        }
        else if (average <= 230 && average > 210) {
            average = 150;
        }
        else if (average <= 210 && average > 170) {
            average = 50;
        }
        else if (average <= 180 && average > 90) {
            average = 0;
        }
        else if (average <= 90 && average > 50) {
            average = 0;
        }
        else {
            average = 0;
        }
        pixels[3 * i] = (unsigned char)average;
        pixels[3 * i + 1] = (unsigned char)average;
        pixels[3 * i + 2] = (unsigned char)average;
    }
        
}

void BitmapManager::EditBitmap(std::vector<unsigned char>& pixels, unsigned int averageColor1, unsigned int averageColor2, unsigned int averageColor3, unsigned int averageColor4, unsigned int averageColor5, unsigned int resultColor1, unsigned int resultColor2, unsigned int resultColor3, unsigned int resultColor4, unsigned int resultColor5, unsigned int resultColor6) {
    for (int i = 0; i < bitmapHeader.biWidth * bitmapHeader.biHeight; ++i) {
        //std::swap(pixels[3 * i], pixels[3 * i + 2]);
        //������std::vector<unsigned char>*�ɂ�����A�N�Z�X�ᔽ�B���[�v����łȂ��Ă�B
        //�Q�Ɠn���ł������
        unsigned char average = ((pixels[3 * i] + pixels[3 * i + 1] + pixels[3 * i + 2]) / 3);

        if (average > averageColor1) {
            average = resultColor1;
        }
        else if (average <= averageColor1 && average > averageColor2) {
            average = resultColor2;
        }
        else if (average <= averageColor2 && average > averageColor3) {
            average = resultColor3;
        }
        else if (average <= averageColor3 && average > averageColor4) {
            average = resultColor4;
        }
        else if (average <= averageColor4 && average > averageColor5) {
            average = resultColor5;
        }
        else {
            average = resultColor6;
        }
        pixels[3 * i] = (unsigned char)average;
        pixels[3 * i + 1] = (unsigned char)average;
        pixels[3 * i + 2] = (unsigned char)average;
    }

}
/*
*�ǂݍ��݈ʒu
currentPos = file.tellg();//0


//�\���̂̃T�C�Y�����������H��C��56�ɂȂ��Ă�
    std::cout << sizeof(BitmapHeader);
    //����56�ɂȂ��Ă�B�R���X�g���N�^�i�������֐��j�̕����H
    //54�o�C�g=4�̔{���ł͂Ȃ����߁A���ɂ���ẮA�����o�̈�O�ɋ󂫂�����遨�\���̂̃p�f�B���O
�p�f�B���O��������(�T�C�Y��54�̂͂���56)���ƂƁA�ǂݔ�΂���Ă���(���Ԃ�����Ă��āA03����n�܂��Ă���)���Ƃ�2�̌������d�Ȃ��Ă���
https://programming-place.net/ppp/contents/cpp2/main/binary_io.html#data_format



(0.BMP�t�@�C�������n�I�Ȍ`���ɕϊ�)
    -1.BMP�̓ǂݍ���
    -2.BMP�̏o�͐ݒ�
    --�h���Ă���s�N�Z���𔻕�
    ---�c����H
    ---12,1,1�݂����ȂƂ���3,3,3�Ƃ��ɂ����ƁH�H�ς��H�H�H
    ----(12+1+1)/3=4,1+2/3*4�Ƃ�
    --�h���Ă���s�N�Z���̔Z���ɂ���āA����̔Z���̃s�N�Z���ɂ���B���Ƃ���50,50,50�̃s�N�Z����70,70,70�̃s�N�Z�����������ꍇ�A������ǂ����60,60,60�Ƃ��ēh�蒼��
    --����̐ݒ肪�ł���悤�ɂ���B
    ---50~70��60�ɂ���̂��B50~70��65�ɂ���̂��B40~80��65�ɂ���̂��B�͈͂Ɨ�����l�B�i�����I�ɂ͂����ݒ�E�C���h�E�Łj
    -3.BMP�̏o��
    --�S��vector�ɓ˂����ނ̏d������A�ҏW�Əo�͓����ɂ�����ق����y���Ȃ�H�H�H�H�H�H
*/