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
    this->currentContentSlider = new QSlider();

    this->setCentralWidget(this->videoWidget);
    this->mediaPlayer->setVideoOutput(this->videoWidget);

    this->currentContentSlider->setOrientation(Qt::Horizontal);
    this->ui->secondToolBar->addWidget(this->currentContentSlider);

    connect(this->mediaPlayer, &QMediaPlayer::durationChanged, this->currentContentSlider, &QSlider::setMaximum);
    connect(this->mediaPlayer, &QMediaPlayer::positionChanged, this->currentContentSlider, &QSlider::setValue);
    connect(this->currentContentSlider, &QSlider::sliderMoved, this->mediaPlayer, &QMediaPlayer::setPosition);
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

void MainWindow::on_actionPlay_triggered()
{
    if (QMediaPlayer::PausedState == this->mediaPlayer->state())
    {
        this->mediaPlayer->play();
        this->ui->statusBar->showMessage("Playing");
    }
}

void MainWindow::on_actionPause_triggered()
{
    if (QMediaPlayer::PlayingState == this->mediaPlayer->state())
    {
        this->mediaPlayer->pause();
        this->ui->statusBar->showMessage("Paused");
    }
}
