#include "myvideosurface.h"

MyVideoSurface::MyVideoSurface(QObject *parent)
{
    setTimerUpdateInterval(50); // default timer interval
    m_lastImage=new QImage(QSize(0,0), QImage::Format_ARGB32_Premultiplied);
    m_lastImage->fill(Qt::transparent);
    timer=new QElapsedTimer();
    timer->start();

}

QList<QVideoFrame::PixelFormat> MyVideoSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const
{
    Q_UNUSED(handleType);

    // Return the formats you will support
    return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB565;
}

bool MyVideoSurface::present(const QVideoFrame &frame)
{
    if (timer->elapsed()>timerUpdateInterval()){
        timer->restart();
        QVideoFrame lastFrame=frame;
        // Handle the frame and do your processing
        if (lastFrame.map(QAbstractVideoBuffer::ReadOnly)) {
            QImage::Format imgFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
            delete m_lastImage;
            m_lastImage=new QImage(frame.bits(),frame.width(),frame.height(),frame.bytesPerLine(),imgFormat);
            lastFrame.unmap();
            emit frameChanged(m_lastImage);

        }
    }
    return true;
}
void MyVideoSurface::setTimerUpdateInterval(int ms){
    m_ms=ms;
}
int MyVideoSurface::timerUpdateInterval(){
    return m_ms;
}
QImage* MyVideoSurface::grabFrame(){
    return m_lastImage;
}

MyVideoSurface::~MyVideoSurface(){
    delete timer;
    delete m_lastImage;
}
