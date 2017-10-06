#include "mainwindow.h"
#include <QApplication>
#include <QMediaPlayer>
#include <QVideoWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    QVideoWidget* videoWidget = new QVideoWidget();
    videoWidget->setGeometry(100, 100, 300, 400);

    QMediaPlayer* mediaPlayer = new QMediaPlayer();
    mediaPlayer->setVideoOutput(videoWidget);
    mediaPlayer->setMedia(QUrl::fromLocalFile("/home/martin/Vídeos/test.mp4"));

    videoWidget->show();
    mediaPlayer->play();

    return a.exec();
}
