#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->videoWidget = new QVideoWidget();
    this->mediaPlayer = new QMediaPlayer();

    this->setCentralWidget(this->videoWidget);
    this->mediaPlayer->setVideoOutput(this->videoWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open a File", "", "Video File (*.avi, *.mpg, *.mp4)");

    this->mediaPlayer->stop();
    this->mediaPlayer->setMedia(QUrl::fromLocalFile(fileName));
    this->mediaPlayer->play();
}
