#include "widget.h"
#include "ui_widget.h"
#include <QDialog>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QTimer>

// #define VERSION_1_0_0 "1.0.0"
// #define VERSION_1_5_0 "1.5.0"
#define VERSION_2_0_0 "2.0.0"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QString versionInfo;

#if defined VERSION_2_0_0
    versionInfo = QString(VERSION_2_0_0);
#elif defined VERSION_1_5_0
    versionInfo = QString(VERSION_1_5_0);
#elif defined VERSION_1_0_0
    versionInfo = QString(VERSION_1_0_0);
#endif

    ui->label_version->setText("MFSparkleTest current version is " + versionInfo);
    ui->btn_show_dialog->setText("Click to show nonmodal dialog");

    ui->btn_check_update->setText("Check update");

#ifdef VERSION_1_0_0
    ui->btn_check_update->setVisible(false);
#endif

    connect(ui->btn_show_dialog, &QAbstractButton::clicked, this, &Widget::onClickToShowDialog);

    connect(ui->btn_check_update, &QAbstractButton::clicked, this, &Widget::onCheckUpdate);
}

Widget::~Widget()
{
    delete ui;
}

// 点击显示对话框
void Widget::onClickToShowDialog()
{
#ifndef VERSION_1_0_0
    auto funcClose = [this]
    {
        if (nullptr != ptr_dlg_)
        {
            QRect rect = QApplication::desktop()->availableGeometry();
            QPoint startPoint(rect.x() + rect.width() - ptr_dlg_->width() - 50, rect.y() + rect.height() - ptr_dlg_->height() - 50);
            QPoint finishPoint(startPoint.x(), rect.y() + rect.height());

            QPropertyAnimation* propertyAnimation = new QPropertyAnimation(ptr_dlg_, "pos");
            propertyAnimation->setDuration(1000);
            propertyAnimation->setStartValue(startPoint);
            propertyAnimation->setEndValue(finishPoint);
            propertyAnimation->setEasingCurve(QEasingCurve::InQuad);

            propertyAnimation->start(QAbstractAnimation::DeleteWhenStopped);

            connect(propertyAnimation, &QAbstractAnimation::finished, this, [this]
            {
                if (nullptr != ptr_dlg_)
                {
                    ptr_dlg_->setVisible(false);
                }
            });
        }
    };

    if (nullptr == ptr_dlg_)
    {
        ptr_dlg_ = new QDialog();
        ptr_dlg_->setFixedSize(460, 334);
    }

    if (nullptr == ptr_hide_timer_)
    {
        ptr_hide_timer_ = new QTimer(this);
        ptr_hide_timer_->setSingleShot(true);
        ptr_hide_timer_->setInterval(3 * 1000);

        connect(ptr_hide_timer_, &QTimer::timeout, funcClose);
    }

    QRect rect = QApplication::desktop()->availableGeometry();
    QPoint startPoint(rect.x() + rect.width() - ptr_dlg_->width() - 50, rect.y() + rect.height());
    QPoint finishPoint(startPoint.x(), rect.y() + rect.height() - ptr_dlg_->height() - 50);

    QPropertyAnimation* propertyAnimation = new QPropertyAnimation(ptr_dlg_, "pos");
    propertyAnimation->setDuration(1000);
    propertyAnimation->setStartValue(startPoint);
    propertyAnimation->setEndValue(finishPoint);
    propertyAnimation->setEasingCurve(QEasingCurve::OutQuad);

    propertyAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    ptr_dlg_->move(startPoint);
#endif

#if defined (VERSION_2_0_0) || defined (VERSION_1_0_0)
    ptr_dlg_->setVisible(true);

    ptr_hide_timer_->start();
#endif
}

// 点击显示检测更新
void Widget::onCheckUpdate()
{

}
