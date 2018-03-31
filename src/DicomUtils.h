//
// Created by Max Heartfield on 31.03.18.
//

#ifndef UNTITLED_DICOMUTILS_H
#define UNTITLED_DICOMUTILS_H

#include <QImage>
#include <vector>
#include <tuple>
#include <imebra/imebra.h>
#include <QDebug>
#include <iostream>

using namespace std;
using namespace imebra;

#define SS2QS(STR) (QString::fromStdString(STR))

class DicomUtils {
public:

    static QImage qImageFromDicomFile(const QString &fileName);

    static unsigned char *imgFromFile(const QString &fileName, int &width, int &height);

    static vector<tuple<QString, QString>> getTags(const QString &fileName);
};

#endif //UNTITLED_DICOMUTILS_H
