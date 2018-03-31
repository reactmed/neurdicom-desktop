//
// Created by Max Heartfield on 31.03.18.
//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) {
    setMinimumSize(512, 512);
    createMenu();
    createDicomViewer();
    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(dicomViewer);
    centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::createMenu() {
    //File menu
    menuBar()->setNativeMenuBar(false);
    fileMenu = new QMenu("File");
    openAction = new QAction("Open");
    fileMenu->addAction(openAction);
    menuBar()->addMenu(fileMenu);

    //Tools menu
    toolsMenu = new QMenu("Tools");
    menuBar()->addMenu(toolsMenu);

    //Program menu
    programMenu = new QMenu("Program");
    menuBar()->addMenu(programMenu);
}

void MainWindow::createDicomViewer() {
    dicomViewer = new DicomViewer;
}

MainWindow::~MainWindow() = default;
