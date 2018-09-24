#include <QDebug>
#include "kxfilecontent.h"

KxFileContent::KxFileContent(QObject *parent) {

}

KxFileContent::~KxFileContent() {
    delete file;
}

QString KxFileContent::getFileName() {
    return this->filename;
}

void KxFileContent::setFileName(const QString &filename) {
    this->filename = filename;
    file = new QFile(filename);

}

QString KxFileContent::getContent() {
    if( content.length() == 0 ) {
        file->open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(file);
        content = in.readAll();
        if( content.length() == 0) {
            qDebug() << "[Warning] KxFileContent: file " << this->filename << "is empty" << endl;
        }
    }
    return content;
}

void KxFileContent::clearContent() {
    content.clear();
}
