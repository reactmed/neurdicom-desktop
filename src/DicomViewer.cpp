//
// Created by Max Heartfield on 31.03.18.
//

#include "DicomViewer.h"

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

static const float QUAD[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};

DicomViewer::DicomViewer(QWidget *parent) : QOpenGLWidget(parent) {

}

DicomViewer::~DicomViewer() {
    makeCurrent();
    delete program;
    glDeleteBuffers(1, &quadVbo);
    glDeleteVertexArrays(1, &quadVao);
    doneCurrent();
}

void DicomViewer::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glGenVertexArrays(1, &quadVao);
    glBindVertexArray(quadVao);

    glGenBuffers(1, &quadVbo);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
    glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), QUAD, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    int w, h;
    auto image = DicomUtils::imgFromFile("data/brain.dcm", w, h);
    ROI roi;
    roi.x = 50;
    roi.y = 50;
    roi.w = 10;
    roi.h = 10;
    image = TumorThresholdSegmentation().process(image, w, h, roi, ComputingMode::CPU);
    texture = new QOpenGLTexture(QImage(reinterpret_cast<const unsigned char *>(image), w, h,
                                        QImage::Format_RGBA8888).mirrored());

    program = new QOpenGLShaderProgram(this);
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, "data/shaders/main.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, "data/shaders/main.frag");
    program->bindAttributeLocation("vert_Position", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("vert_TextureCoords", PROGRAM_TEXCOORD_ATTRIBUTE);
    program->link();
    program->bind();
    program->setUniformValue("texture", 0);
}

void DicomViewer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    program->bind();
    texture->bind();
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);

    glEnableVertexAttribArray(0);

    glDrawArrays(GL_QUADS, 0, 4);
}

void DicomViewer::resizeGL(int w, int h) {
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);
}
