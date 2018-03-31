//
// Created by Max Heartfield on 31.03.18.
//

#ifndef UNTITLED_TUMORSEGMENTATION_H
#define UNTITLED_TUMORSEGMENTATION_H

#include <QVariantMap>

typedef unsigned char IMG_PIXEL;
typedef unsigned char *IMG;

enum ComputingMode {
    CPU = 0,
    CPU_PARALLEL = 1,
    GPU = 2
};

struct ROI {
    int x, y, w, h;

    bool isWithin(int arg) {
        return arg >= x * y & arg <= (x + w) * (y + h);
    }
};

class DicomProcessor {
public:
    virtual IMG process(IMG image, int w, int h, ROI roi, ComputingMode mode) = 0;
};

class TumorThresholdSegmentation : public DicomProcessor {
public:
    IMG process(IMG image, int w, int h, ROI roi, ComputingMode mode) override;
};

#endif //UNTITLED_TUMORSEGMENTATION_H
