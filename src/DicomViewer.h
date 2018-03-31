//
// Created by Max Heartfield on 31.03.18.
//

#ifndef UNTITLED_DICOMVIEWER_H
#define UNTITLED_DICOMVIEWER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QImage>
#include "DicomUtils.h"
#include "tumorsegmentation.h"

class DicomViewer : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT
public:
    explicit DicomViewer(QWidget *parent = nullptr);

    ~DicomViewer() override;

public:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int, int) override;

private:
    QOpenGLShaderProgram *program;
    QOpenGLBuffer vbo;
    QOpenGLTexture *texture;
    GLuint quadVao, quadVbo;
};


#endif //UNTITLED_DICOMVIEWER_H
