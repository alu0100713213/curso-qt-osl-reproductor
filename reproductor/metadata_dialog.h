#ifndef METADATA_DIALOG_H
#define METADATA_DIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QListWidget>

namespace Ui{
class metadata_dialog;
}

class metadata_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit metadata_dialog(QMediaPlayer *player, QWidget *parent = 0);

private:
    Ui::metadata_dialog *ui;
    QMediaPlayer *player_;
    QStringList metadatosDisponibles_;
};

#endif // METADATA_DIALOG_H
