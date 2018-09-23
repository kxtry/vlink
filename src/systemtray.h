#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QPointer>
#include <QSystemTrayIcon>

class QSplashScreen;
class QMenu;
class QAction;

class SystemTray : public QObject
{
    Q_OBJECT

public:
    explicit SystemTray(QObject *parent = nullptr);
    ~SystemTray();

    void showSplash();
protected:
    void activeTray(QSystemTrayIcon::ActivationReason reason);
    void exitApp();//显示窗体
    void showMessage();//消息框
    void showMenu();//显示菜单

public slots:
    void splashTimeout();

private:
    QPointer<QSystemTrayIcon> tray;
    QPointer<QSplashScreen> splash;
    QPointer<QMenu> menu;
};

#endif // SYSTEMTRAY_H
