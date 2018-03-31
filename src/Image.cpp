//
// Created by Max Heartfield on 31.03.18.
//

#include "Image.h"

Image::Image(const unsigned char *rawData, int w, int h, ColorSpace colorSpace) {
    this->_w = w;
    this->_h = h;
    this->_colorSpace = colorSpace;
    this->_size = this->_w * this->_h * 4;
    this->_data = new unsigned char[_size];
    copy(rawData, rawData + _size, _data);
}

Image::Image(const Image &image) {
    this->_w = image._w;
    this->_h = image._h;
    this->_colorSpace = image._colorSpace;
    this->_size = image._size;
    copy(image._data, image._data + image._size, _data);
}

int Image::getPixelsCount() const {
    return _w * _h;
}

int Image::getArraySize() const {
    return _size;
}

int Image::getChannelsCount() const {
    return 4;
}

int Image::getWidth() const {
    return _w;
}

int Image::getHeight() const {
    return _h;
}

ColorSpace Image::getColorSpace() const {
    return _colorSpace;
}

unsigned char *Image::data() const {
    return _data;
}