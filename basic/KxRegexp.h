#ifndef _KXREGEXP_H_
#define _KXREGEXP_H_

#include<QObject>
#include<QRegExp>

class  KxRegexp: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString pattern READ pattern WRITE setPattern)
public:
    explicit KxRegexp(QObject *parent = NULL);


    QString pattern() const;
    void setPattern(const QString& pattern);

    Q_INVOKABLE QStringList capturedTexts(const QString& text);

private:
    QRegExp regex;
};

#endif
