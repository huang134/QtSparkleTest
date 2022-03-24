#include "widget.h"
#include "ui_widget.h"
#include <QDialog>

#define VERSION_1_0_0 "1.0.0"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->label_version->setText("MFSparkleTest current version is " + QString(VERSION_1_0_0));
    ui->btn_show_dialog->setText("Click to show nonmodal dialog");

    connect(ui->btn_show_dialog, &QAbstractButton::clicked, this, &Widget::onClickToShowDialog);
}

Widget::~Widget()
{
    delete ui;
}

// 点击显示对话框
void Widget::onClickToShowDialog()
{
    ptr_dlg_->setVisible(true);
}
