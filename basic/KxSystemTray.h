#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

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
    void exitApp();//显示窗体
    void showMessage();//消息框
    void showMenu();//显示菜单

public slots:

private:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    QPointer<QSystemTrayIcon> tray;
    QPointer<QMenu> menu;
};

#endif // SYSTEMTRAY_H
