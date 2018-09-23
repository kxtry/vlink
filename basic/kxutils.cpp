#include <QStandardPaths>
#include "KxUtils.h"

KxUtils::KxUtils(QObject *parent)
    : QObject(parent)
{

}

QString KxUtils::genericPath() const
{
    static QString dataPath;
    if ( dataPath.isEmpty() ) {
        dataPath = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).first();
    }
    return dataPath;
}
