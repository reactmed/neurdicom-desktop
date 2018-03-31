//
// Created by Max Heartfield on 31.03.18.
//

#include "tumorsegmentation.h"
#include <algorithm>

using namespace std;

double mean(const IMG img, int size, ROI roi) {
    double sum = 0.0;
    int k = 0;
    for (int i = 0; i < size; i++)
        if (roi.isWithin(i)){
            ++k;
            sum += img[i * 4];
        }
    return sum / size;
}

double partialMean(const IMG img, const bool mask[], int size, ROI roi) {
    double sum = 0.0;
    int k = 0;
    for (int i = 0; i < size; i++)
        if (mask[i] && roi.isWithin(i)) {
            ++k;
            sum += img[i * 4];
        }
    return sum / k;
}


IMG TumorThresholdSegmentation::process(IMG image, int w, int h, ROI roi, ComputingMode mode) {
    int pixelsCount = w * h;
    int size = pixelsCount * 4;
    auto imageCopy = new IMG_PIXEL[size];
    copy(image, image + size, imageCopy);
    bool p1[pixelsCount];
    bool p2[pixelsCount];
    double t = mean(imageCopy, pixelsCount, roi);
    int k = 10;
    double eps = 0.001;
    if (mode == ComputingMode::CPU) {
        int it = -1;
        double mean1 = 0, mean2 = 0;
        do {
            for (int i = 0; i < pixelsCount; i++) {
                p1[i] = (p2[i] = !roi.isWithin(i));
                if (imageCopy[i * 4] < t) {
                    p1[i] = true;
                    p2[i] = false;
                } else {
                    p1[i] = false;
                    p2[i] = true;
                }
            }
            mean1 = partialMean(imageCopy, p1, pixelsCount, roi);
            mean2 = partialMean(imageCopy, p2, pixelsCount, roi);
            t = (mean1 + mean2) / 2.0;
        } while (++it > k || qAbs(mean1 - mean2) <= eps);
    }
    auto threshold = static_cast<IMG_PIXEL>((int) t);
    for (int i = 0; i < size; i++) {
        if (imageCopy[i] <= threshold && roi.isWithin(i))
            imageCopy[i] = (unsigned char) 0;
    }
    return imageCopy;
}
