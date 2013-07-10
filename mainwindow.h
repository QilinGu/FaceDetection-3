#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCameraViewfinder>
#include <QVideoProbe>
#include <QCamera>
#include <QLabel>
#include "myvideosurface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void render(QImage *render);
    void grab();
    void detectFace(QVideoFrame frame);
    
private:
    QCameraViewfinder *video;
    QLabel *pix,*saved;
    QCamera *cam;
    QVideoProbe *probe;
    MyVideoSurface *surface;
};

#endif // MAINWINDOW_H
