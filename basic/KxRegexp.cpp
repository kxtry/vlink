#include <QDebug>
#include "KxRegexp.h"

KxRegexp::KxRegexp(QObject *parent)
    : QObject(parent)
{

}

QString KxRegexp::pattern() const
{
    return regex.pattern();
}

void KxRegexp::setPattern(const QString &pattern)
{
    regex.setPattern(pattern);
}

QStringList KxRegexp::capturedTexts(const QString &text)
{
    QStringList list;
    int pos = 0;
    while ((pos = regex.indexIn(text, pos)) != -1) {
          list << regex.cap(1);
          pos += regex.matchedLength();
    }
    return list;
}
