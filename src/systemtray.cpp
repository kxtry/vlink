#include "systemtray.h"

#include <QApplication>
#include <QSplashScreen>
#include <QMenu>
#include <QTimer>
#include <QMessageBox>

SystemTray::SystemTray(QObject *parent)
    : QObject(parent)
{
    tray = new QSystemTrayIcon(this);

    menu = new QMenu();
    {
        QAction *action = new QAction(menu);
        action->setText(tr("E&xit"));
        menu->addAction(action);
        connect(action, &QAction::triggered, this, &SystemTray::exitApp);
    }

    tray->setContextMenu(menu);
    tray->setIcon(QIcon(":/res/logo.png"));
    tray->setToolTip(tr("WayPal在线教育专家"));
    tray->show();
    connect(tray, &QSystemTrayIcon::activated, this, &SystemTray::activeTray);//点击托盘，执行相应的动作

    QPixmap pixmap(":/res/splash.png");
    splash = new QSplashScreen(pixmap);
}

SystemTray::~SystemTray()
{
    delete menu;
    delete tray;
}

void SystemTray::showSplash()
{
    splash->show();
    QTimer::singleShot(1000*3, this, &SystemTray::splashTimeout);
}

void SystemTray::activeTray(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Context:
        showMenu();
        break;
    case QSystemTrayIcon::DoubleClick:
        showSplash();
        break;
    case QSystemTrayIcon::Trigger:
        break;
    }
}

void SystemTray::showMenu()
{
    menu->show();
}


void SystemTray::splashTimeout()
{
    splash->hide();
}

void SystemTray::exitApp()
{
    QMessageBox msgBox;
    msgBox.setText(tr("The program will exit."));
    msgBox.setInformativeText(tr("如果退出可能会影响上课质量，建议不要退出。"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Cancel){
        return;
    }
    QApplication::exit(0);
}

void SystemTray::showMessage()
{
    tray->showMessage("Information",//消息窗口标题
        "There is a new message!",//消息内容
        QSystemTrayIcon::MessageIcon::Information,//消息窗口图标
        5000);//消息窗口显示时长
}
