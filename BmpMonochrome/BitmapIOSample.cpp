#include"BitmapIOSample.h"


void BitmapManager::LoadBitmap24(std::string path, std::vector<unsigned char>& pixels)
{
    std::ifstream ifs(path, std::ios_base::in | std::ios::binary);
    if (ifs.fail()) {
        std::cerr << "File open error: " << path << "\n";
        std::quick_exit(0);
    }
    std::ifstream::pos_type currentPos = ifs.tellg();//読み込み位置

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

    //読み込み位置
    currentPos = ifs.tellg();

    {
        int w = bitmapHeader.biWidth;
        int h = bitmapHeader.biHeight;
        int step = ToBitmapStep(3 * w);

        std::vector<unsigned char> originalPixels(step * h);
        ifs.seekg(bitmapHeader.bfOffBits);//読み込み位置調整
        ifs.read((char*)originalPixels.data(), originalPixels.size());
        //ここまでおｋ、2839102…(10進)で入ってる

        pixels.resize(3 * w * h);
        for (int i = 0; i < h; ++i)
            memcpy(pixels.data() + i * 3 * w, originalPixels.data() + i * step, 3 * w);
    }

    //ファイル閉じる処理
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

    //ファイル閉じる処理
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
        //引数をstd::vector<unsigned char>*にしたらアクセス違反。ループ初回でなってる。
        //参照渡しでええやん
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
        //引数をstd::vector<unsigned char>*にしたらアクセス違反。ループ初回でなってる。
        //参照渡しでええやん
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
*読み込み位置
currentPos = file.tellg();//0


//構造体のサイズがおかしい？一気に56になってる
    std::cout << sizeof(BitmapHeader);
    //うん56になってる。コンストラクタ（初期化関数）の部分？
    //54バイト=4の倍数ではないため、環境によっては、メンバの一つ前に空きが作られる→構造体のパディング
パディングがあった(サイズが54のはずが56)ことと、読み飛ばされていた(順番がずれていて、03から始まっていた)ことの2つの原因が重なっていた
https://programming-place.net/ppp/contents/cpp2/main/binary_io.html#data_format



(0.BMPファイルを原始的な形式に変換)
    -1.BMPの読み込み
    -2.BMPの出力設定
    --塗られているピクセルを判別
    ---…いる？
    ---12,1,1みたいなとこを3,3,3とかにする作業？？均す？？？
    ----(12+1+1)/3=4,1+2/3*4とか
    --塗られているピクセルの濃さによって、特定の濃さのピクセルにする。たとえば50,50,50のピクセルと70,70,70のピクセルがあった場合、それをどちらも60,60,60として塗り直す
    --それの設定ができるようにする。
    ---50~70は60にするのか。50~70は65にするのか。40~80を65にするのか。範囲と落ちる値。（将来的にはこれを設定ウインドウで）
    -3.BMPの出力
    --全部vectorに突っ込むの重いから、編集と出力同時にやったほうが軽くなる？？？？？？
*/