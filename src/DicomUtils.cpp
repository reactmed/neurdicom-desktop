//
// Created by Max Heartfield on 31.03.18.
//

#include "DicomUtils.h"

QImage DicomUtils::qImageFromDicomFile(const QString &fileName) {
    int w, h;
    auto image = imgFromFile(fileName, w, h);
    return QImage(reinterpret_cast<const unsigned char *>(image), w, h,
                  QImage::Format_RGBA8888);
}

vector<tuple<QString, QString>> DicomUtils::getTags(const QString &fileName) {
    unique_ptr<DataSet> ds(CodecFactory::load(fileName.toStdString()));
    vector<tuple<QString, QString>> vec;
    for (auto &tagId : ds->getTags()) {
        try {
            tuple<QString, QString> keyValuePair(SS2QS(DicomDictionary::getTagName(tagId)),
                                                 SS2QS(ds->getString(tagId, 0, "")));
            vec.push_back(keyValuePair);
        }
        catch (DictionaryUnknownTagError &) {
            continue;
        }
    }
    return vec;
}

unsigned char *DicomUtils::imgFromFile(const QString &fileName, int &width, int &height) {
    unique_ptr<DataSet> ds(CodecFactory::load(fileName.toStdString()));
    unique_ptr<Image> image(ds->getImageApplyModalityTransform(0));
    unique_ptr<ReadingDataHandlerNumeric> dataHandler(image->getReadingDataHandler());
    TransformsChain chain;
    uint32_t _width = image->getWidth();
    uint32_t _height = image->getHeight();

    if (ColorTransformsFactory::isMonochrome(image->getColorSpace())) {
        VOILUT voilutTransform;
        vois_t vois = ds->getVOIs();
        vector<shared_ptr<LUT>> luts;
        for (size_t scanLUTs(0);; ++scanLUTs) {
            try {
                auto lut = shared_ptr<LUT>(ds->getLUT(TagId(tagId_t::VOILUTSequence_0028_3010), scanLUTs));
                luts.push_back(move(lut));
            }
            catch (const MissingDataElementError &) {
                break;
            }
        }

        if (!vois.empty()) {
            voilutTransform.setCenterWidth(vois[0].center, vois[0].width);
        } else if (!luts.empty()) {
            voilutTransform.setLUT(*(luts.front().get()));
        } else {
            voilutTransform.applyOptimalVOI(*image, 0, 0, _width, _height);
        }

        chain.addTransform((voilutTransform));
    }
    DrawBitmap bitmap(chain);
    auto size = bitmap.getBitmap(*image, drawBitmapType_t::drawBitmapRGBA, 2, nullptr, 0);
    qDebug() << "Image size" << size << endl;
    std::string buffer(size, char(0));
    bitmap.getBitmap(*image, imebra::drawBitmapType_t::drawBitmapRGBA, 2, &(buffer.at(0)), size);
    width = _width;
    height = _height;
    return (unsigned char *) buffer.c_str();
}
