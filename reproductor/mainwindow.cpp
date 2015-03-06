#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    //Initialize widgets
    mediaPlayer_  = new QMediaPlayer(this);
    playerSlider_ = new QSlider(Qt::Horizontal, this);
    videoWidget_  = new QVideoWidget(this);
    volumeSlider_ = new QSlider(Qt::Horizontal, this);
    btnOpen_      = new QToolButton(this);
    btnPlay_      = new QToolButton(this);
    btnPause_     = new QToolButton(this);
    btnStop_      = new QToolButton(this);

    //Initialize menu

    qmenu_ = new QMenuBar(this);
    menuArchivo_ = new QMenu("Archivo", this);
    menuVer_ = new QMenu("Ver", this);
    menuAyuda_ = new QMenu("Ayuda", this);
    about_label1 = new QLabel("about1", this);
    about_label2 = new QLabel("about2", this);
    url_label1 = new QLabel("url",this);

    //Initialize Action
    ArchivoAbrir = new QAction("&Abrir", this);
    URLAbrir = new QAction("&Abrir URL", this);
    //RecientesAction = new QAction("&Recientes", this);
    MetadatosAction = new QAction("&Metadatos", this);
    SalirAction = new QAction("&Salir", this);
    AboutAction = new QAction("&Acerca de", this);
    FullScreenAction = new QAction("&Pantalla Completa", this);
    dialog_ = new QDialog(this);
    url_ = new QDialog(this);
    about_grid = new QGridLayout(this);
    url_grid = new QGridLayout(this);

    // Configure optional exercises

    qmenu_->addMenu(menuArchivo_);
    qmenu_->addMenu(menuVer_);
    qmenu_->addMenu(menuAyuda_);
    menuArchivo_->addAction(ArchivoAbrir);
    menuArchivo_->addAction(URLAbrir);
    //menuArchivo_->addAction(RecientesAction);
    menuArchivo_->addAction(MetadatosAction);
    menuArchivo_->addAction(SalirAction);
    menuAyuda_->addAction(AboutAction);
    menuVer_->addAction(FullScreenAction);
    dialog_->setLayout(about_grid);
    url_->setLayout(url_grid);
    about_grid->addWidget(about_label1, 1, 0, 1, 5);
    about_grid->addWidget(about_label2, 0, 0, 1, 5);
    url_grid->addWidget(url_label1,1,0,1,5);
    url_grid->addWidget(url_edit, 1, 0, 1, 5);

    //Setup widwgets
    videoWidget_->setMinimumSize(400, 400);
    mediaPlayer_->setVideoOutput(videoWidget_);
    mediaPlayer_->setVolume(100);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    volumeSlider_->setRange(0, 100);
    volumeSlider_->setSliderPosition(100);

    //Populate grid layout
    lytMain_->addWidget(videoWidget_,  0, 0, 1, 5);
    lytMain_->addWidget(playerSlider_, 1, 0, 1, 5);
    lytMain_->addWidget(btnOpen_,      2, 0, 1, 1);
    lytMain_->addWidget(btnPlay_,      2, 1, 1, 1);
    lytMain_->addWidget(btnPause_,     2, 2, 1, 1);
    lytMain_->addWidget(btnStop_,      2, 3, 1, 1);
    lytMain_->addWidget(volumeSlider_, 2, 4, 1, 1);

    //Buttons icons
    btnOpen_->setIcon(QIcon(QPixmap(":/icons/resources/eject.png")));
    btnPause_->setIcon(QIcon(QPixmap(":/icons/resources/pause.png")));
    btnPlay_->setIcon(QIcon(QPixmap(":/icons/resources/play.png")));
    btnStop_->setIcon(QIcon(QPixmap(":/icons/resources/stop.png")));

    //Connections
    connect(btnOpen_,      SIGNAL(pressed()),               this,         SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_, SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_, SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,         SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,         SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,         SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,         SLOT(onVolumeChanged(int)));
    connect(ArchivoAbrir, SIGNAL(triggered()),  this,       SLOT(onOpen()));
    connect(AboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(FullScreenAction, SIGNAL(triggered()), this, SLOT(fullscreen()));
    //connect(RecientesAction, SIGNAL(triggered()), this, SLOT(recientes_function()));
    connect(MetadatosAction, SIGNAL(triggered()), this, SLOT(show_metadata()));
    connect(URLAbrir, SIGNAL(triggered()), this, SLOT(openURL()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::onOpen()
{
    //Show file open dialog
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Abrir archivo"));
    if (fileName != "")
    {
        mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
    }
    recientes_function(fileName);
}

void MainWindow::onSeek()
{
    mediaPlayer_->setPosition(playerSlider_->sliderPosition());
}

void MainWindow::onDurationChanged(qint64 duration)
{
    playerSlider_->setRange(0, duration);
}

void MainWindow::onPositionChanged(qint64 position)
{
    playerSlider_->setSliderPosition(position);
}

void MainWindow::onVolumeChanged(int volume)
{
    mediaPlayer_->setVolume(volume);
}

void MainWindow::fullscreen()
{
    videoWidget_->setFullScreen(true);
}

void MainWindow::about()
{
    QString labelText = "<P><b><i><FONT COLOR='#ff0000' FONT SIZE = 10>";
    labelText.append("Sobre mi");
    labelText.append("</i></b></P></br>");

    dialog_->show();
    about_label1->setText(labelText);

    QPixmap pixmap(":/icons/resources/GATO.jpg");
    about_label2->setPixmap(pixmap);
}

void MainWindow::recientes_function(QString input)
{
    A.add(input);
}

void MainWindow::show_metadata()
{
    QMessageBox mensaje;
    mensaje.setWindowTitle("Metadatos");
    if(mediaPlayer_ ->isMetaDataAvailable() == true)
    {
        QString vname = "Name: "+mediaPlayer_->metaData(QMediaMetaData::Title).toString();
        QString vauthor = "Author: "+mediaPlayer_->metaData(QMediaMetaData::Author).toString();
        QString vcodec = "Videocodec: " + mediaPlayer_->metaData(QMediaMetaData::VideoCodec).toString();
        QString vbritate = "Bitrate: " + mediaPlayer_->metaData(QMediaMetaData::VideoBitRate).toString();
        QString acodec = "Audiocodec: " + mediaPlayer_->metaData(QMediaMetaData::AudioCodec).toString();
        QString abitrate = "AudioBitrate: " + mediaPlayer_->metaData(QMediaMetaData::AudioBitRate).toString();
        mensaje.setText(vname+"\n"+vauthor+"\n"+vcodec+"\n"+vbritate+"\n"+acodec+"\n"+abitrate);
    }
    mensaje.exec();
}

void MainWindow::openURL()
{
    QString labelText = "<P><b><i><FONT COLOR='#ff' FONT SIZE = 8>";
    labelText.append("Abrir desde URL");
    labelText.append("</i></b></P></br>");

    url_label1->setText(labelText);

    url_->show();
/**    QDialog url_dialog;
    QVBoxLayout *box = new QVBoxLayout(this);
    QLabel *labelurl = new QLabel(this);
    QLineEdit *url_line = new QLineEdit;

    labelurl->setText("hola");
    box->addWidget(labelurl);
    url_dialog.exec();
    //    mediaPlayer_->setMedia(QUrl("http://208.92.53.87:80/MAXIMAFM"));
*/}

