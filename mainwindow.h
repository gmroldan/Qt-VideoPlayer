#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSlider>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void positionChanged(qint64 position);

private:
    Ui::MainWindow *ui;
    QMediaPlayer* mediaPlayer;
    QVideoWidget* videoWidget;
    QSlider* currentContentSlider;
    QLabel* currentContentDuration;

    void init();
    void initLayout();
    void initSignalsAndSlots();
    void updateDurationInfo();

};

#endif // MAINWINDOW_H
