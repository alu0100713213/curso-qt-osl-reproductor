#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMediaMetaData>
#include <QMessageBox>
#include <QDebug>
#include "recientes.h"
#include <QLayout>
#include <QGridLayout>
#include <QDialog>
#include <QLabel>
#include <QAction>
#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDir>
#include <QSlider>
#include <QFileDialog>
#include <QToolButton>
#include <QMenuBar>
#include <QMenu>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    QGridLayout*        lytMain_;
    QWidget*            wgtMain_;
    QMediaPlayer*       mediaPlayer_;
    QSlider*            playerSlider_;
    QVideoWidget*       videoWidget_;
    QSlider*            volumeSlider_;
    QToolButton*        btnOpen_;
    QToolButton*        btnPlay_;
    QToolButton*        btnPause_;
    QToolButton*        btnStop_;
//Initialize menu
    QMenuBar*           qmenu_;
    QMenu*              menuArchivo_;
    QMenu*              menuVer_;
    QMenu*              menuAyuda_;
    QMenu*              menuRecientes_;
//Initialize action
    QAction*            SalirAction;
    QAction*            MetadatosAction;
    QAction*            AboutAction;
    QAction*            FullScreenAction;
    QAction*            ArchivoAbrir;
    QAction*            URLAbrir;
//Initialize label
    QLabel*             about_label1;
    QLabel*             about_label2;
//Initialize dialog
    QDialog*            dialog_;
    //Initialize gridlayout
    QGridLayout*        about_grid;
//Initialize list of the recent views
    recientes A;
//Initialize open url streaming
    QDialog*            url_;
    QGridLayout*        url_grid;
    QLineEdit*          url_edit;
    QLabel*             url_label1;

private slots:
    void fullscreen();
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
// Add extra function for practise
    void about();
    void recientes_function(QString input);
    void show_metadata();
    void openURL();
};

#endif // MAINWINDOW_H
