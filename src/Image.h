//
// Created by Max Heartfield on 31.03.18.
//

#ifndef UNTITLED_IMAGE_H
#define UNTITLED_IMAGE_H

#include <iterator>
#include <algorithm>

using namespace std;

enum ColorSpace {
    RGBA = 0,
    GRAYSCALE_RGBA = 1
};

class ImageIterator {
public:

};

class Image {
public:
    Image(const unsigned char *rawData, int w, int h, ColorSpace colorSpace);

    Image(const Image &image);

    int getPixelsCount() const;

    int getArraySize() const;

    int getChannelsCount() const;

    int getWidth() const;

    int getHeight() const;

    ColorSpace getColorSpace() const;

    unsigned char* data() const;

private:
    unsigned char *_data;
    int _w, _h, _size;
    ColorSpace _colorSpace;
};


#endif //UNTITLED_IMAGE_H
