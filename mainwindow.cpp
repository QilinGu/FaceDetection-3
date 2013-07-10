#include "mainwindow.h"
#include <QVideoWidget>
#include <QTime>
#include <QDebug>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *central=new QWidget(this);
    this->setCentralWidget(central);
    QVBoxLayout *layout=new QVBoxLayout(central);//*/


    cam=new QCamera(central);
    //video=new QCameraViewfinder(central);

    surface=new MyVideoSurface();
    cam->setViewfinder(surface);
    //cam->setCaptureMode(QCamera::CaptureStillImage);
    cam->setCaptureMode(QCamera::CaptureVideo);

    /*probe = new QVideoProbe(this);
    if (probe->setSource(cam)) {
        qDebug()<<"connected";
        // Probing succeeded, videoProbe->isValid() should be true.
        connect(probe, SIGNAL(videoFrameProbed(QVideoFrame)),
                this, SLOT(detectFace(QVideoFrame)));
    }
    qDebug()<<probe->isActive();*/
    cam->start();



    pix=new QLabel(central);
    saved=new QLabel(central);
    //QPushButton* render=new QPushButton("Render image",central);
    QPushButton* grab=new QPushButton("Grab image",central);


    layout->addWidget(pix);
    //layout->addWidget(render);
    layout->addWidget(grab);
    layout->addWidget(saved);


    connect(surface,SIGNAL(frameChanged(QImage*)),this,SLOT(render(QImage*)));
    //connect(render,SIGNAL(clicked()),this,SLOT(render()));
    connect(grab,SIGNAL(clicked()),this,SLOT(grab()));//*/


}

void MainWindow::render(QImage *render){

    pix->setPixmap(QPixmap::fromImage(*render));
    qDebug()<<"render "+QTime::currentTime().toString("hh:mm:ss:z");//*/


    //qDebug()<<video->grab().save("Saved");
}
void MainWindow::grab(){
    //pix->setPixmap(surfa);
    saved->setPixmap(QPixmap::fromImage(*surface->grabFrame()));
    qDebug()<<"grab";//*/
}
void MainWindow::detectFace(QVideoFrame frame){
    qDebug()<<"here";
    QImage::Format imgFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
    QImage lastImage(frame.bits(),frame.width(),frame.height(),frame.bytesPerLine(),imgFormat);

    pix->setPixmap(QPixmap::fromImage(lastImage));
}

MainWindow::~MainWindow()
{

}
