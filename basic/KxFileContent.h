#ifndef _KX_FILE_CONTENT_H_
#define _KX_FILE_CONTENT_H_

#include <QObject>
#include <QFile>
#include <QTextStream>

class KxFileContent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString content READ getContent)
    Q_PROPERTY(QString filename READ getFileName WRITE setFileName)

public:
    explicit KxFileContent(QObject *parent = 0);
    ~KxFileContent();

public:
    Q_INVOKABLE QString getContent();
    Q_INVOKABLE QString getFileName();

public slots:
    void setFileName(const QString& filename);
    void clearContent();

private:
    QFile   *file;
    QString content;
    QString filename;
};

#endif
