#ifndef KXSYSTEMTRAY_H
#define KXSYSTEMTRAY_H

#include <QPointer>
#include <QSystemTrayIcon>

class QMenu;
class QAction;

class KxSystemTray : public QObject
{
    Q_OBJECT

public:
    explicit KxSystemTray(QObject *parent = nullptr);
    ~KxSystemTray();

protected:
    void activeTray(QSystemTrayIcon::ActivationReason reason);
    void exitApp();
    void showMenu();
private:
    QPointer<QSystemTrayIcon> tray;
    QPointer<QMenu> menu;
};

#endif // KXSYSTEMTRAY_H
