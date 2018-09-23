#include <QApplication>
#include <QSplashScreen>
#include <QMenu>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>

#include "KxSystemTray.h"

KxSystemTray::KxSystemTray(QObject *parent)
    : QObject(parent)
{
    tray = new QSystemTrayIcon(this);

    menu = new QMenu();
    {
        QAction *action = new QAction(menu);
        action->setText(tr("E&xit"));
        menu->addAction(action);
        connect(action, &QAction::triggered, this, &KxSystemTray::exitApp);
    }

    tray->setContextMenu(menu);
    tray->setIcon(QIcon(":/res/logo.png"));
    tray->setToolTip(tr("VLink's remote assistant helper."));
    tray->show();
    connect(tray, &QSystemTrayIcon::activated, this, &KxSystemTray::activeTray);
    tray->installEventFilter(this);
}

KxSystemTray::~KxSystemTray()
{
    delete menu;
    delete tray;
}

void KxSystemTray::activeTray(QSystemTrayIcon::ActivationReason reason)
{
    qDebug() << "reason:" << reason;
    switch (reason)
    {
    case QSystemTrayIcon::Context:
        showMenu();
        break;
    case QSystemTrayIcon::DoubleClick:
        break;
    case QSystemTrayIcon::Trigger:
        break;
    }
}

void KxSystemTray::showMenu()
{
    menu->show();
}

bool KxSystemTray::eventFilter(QObject *obj, QEvent *event)
{
    qDebug() << "obj" << obj;
    qDebug() << "event" << event->type();
}


void KxSystemTray::exitApp()
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

void KxSystemTray::showMessage()
{
    tray->showMessage("Information",//消息窗口标题
        "There is a new message!",//消息内容
        QSystemTrayIcon::MessageIcon::Information,//消息窗口图标
        5000);//消息窗口显示时长
}