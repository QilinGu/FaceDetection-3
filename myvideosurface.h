#ifndef MYVIDEOSURFACE_H
#define MYVIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QElapsedTimer>

class MyVideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit MyVideoSurface(QObject *parent = 0);
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType) const;
    bool present(const QVideoFrame &frame);
    ~MyVideoSurface();
private:
    QElapsedTimer *timer;
    QImage *m_lastImage;
    int m_ms;
signals:
    void frameChanged(QImage*);
public slots:
    void setTimerUpdateInterval(int ms);
    int timerUpdateInterval();
    QImage *grabFrame();
    
};

#endif // MYVIDEOSURFACE_H
