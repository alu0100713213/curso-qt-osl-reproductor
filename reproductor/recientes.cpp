#include "recientes.h"

recientes::recientes()
{
//    QFile file("recientes.txt");
//    file.open(QIODevice::WriteOnly | QIODevice::Text);
    nombre_fichero = "recientes.txt";
}

recientes::~recientes()
{
}

void recientes::add(QString nom_add)
{
    QByteArray utf8;
    utf8.append(nom_add);

    QFile f(nombre_fichero);
    if(f.open(QFile::WriteOnly | QFile::Append))
    {
        f.seek(0);
        f.write("\n");
        f.write(utf8);
        f.close();
    }

}
