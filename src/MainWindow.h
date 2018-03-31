//
// Created by Max Heartfield on 31.03.18.
//

#ifndef UNTITLED_MAINWINDOW_H
#define UNTITLED_MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QMenuBar>
#include "DicomViewer.h"

class MainWindow : public QMainWindow {

Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    void createMenu();

    void createDicomViewer();

private:
    DicomViewer *dicomViewer;
    QWidget *centralWidget;
    QMenu *fileMenu, *toolsMenu, *programMenu;
    QAction *openAction;
};


#endif //UNTITLED_MAINWINDOW_H
