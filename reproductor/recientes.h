#ifndef RECIENTES_H
#define RECIENTES_H

#include <QTextStream>
#include <QFile>
#include <QString>

class recientes
{
private:
    QFile* f;
    QString nombre_fichero;
public:
    recientes();
    ~recientes();
    void add(QString nom_add);
};

#endif // RECIENTES_H
