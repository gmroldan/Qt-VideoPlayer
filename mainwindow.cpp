#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTime>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->init();
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

void MainWindow::positionChanged(qint64 position)
{
    this->currentContentSlider->setValue(position);
    this->updateDurationInfo();
}

void MainWindow::init()
{
    this->ui->setupUi(this);
    this->videoWidget = new QVideoWidget();
    this->mediaPlayer = new QMediaPlayer();
    this->currentContentSlider = new QSlider();
    this->currentContentDuration = new QLabel("00:00/00:00");

    this->mediaPlayer->setVideoOutput(this->videoWidget);
    this->currentContentSlider->setOrientation(Qt::Horizontal);

    this->initLayout();
    this->initSignalsAndSlots();
}

void MainWindow::initLayout()
{
    QBoxLayout* displayLayout = new QHBoxLayout;
    displayLayout->addWidget(videoWidget);

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addWidget(this->currentContentSlider);
    hLayout->addWidget(this->currentContentDuration);

    QBoxLayout* boxLayout = new QVBoxLayout();
    boxLayout->addLayout(displayLayout);
    boxLayout->addLayout(hLayout);

    this->ui->centralWidget->setLayout(boxLayout);
}

void MainWindow::initSignalsAndSlots()
{
    connect(this->mediaPlayer, &QMediaPlayer::durationChanged, this->currentContentSlider, &QSlider::setMaximum);
    connect(this->mediaPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);
    connect(this->currentContentSlider, &QSlider::sliderMoved, this->mediaPlayer, &QMediaPlayer::setPosition);
}

void MainWindow::updateDurationInfo()
{
    const qint64 currentInfo = this->mediaPlayer->position() / 1000;
    const qint64 duration = this->mediaPlayer->duration() / 1000;
    QString tStr;

    if (currentInfo)
    {
        QTime currentTime((currentInfo / 3600) %60,
                          (currentInfo / 60) % 60,
                          (currentInfo % 60),
                          (currentInfo * 1000) % 1000);
        QTime totalTime((duration / 3600) % 60,
                        (duration / 60) % 60,
                        (duration % 60),
                        (duration * 1000) % 1000);
        QString format = "mm:ss";

        if (duration > 3600)
            format = "hh:mm:ss";

        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }

    this->currentContentDuration->setText(tStr);
}
