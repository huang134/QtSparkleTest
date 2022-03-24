#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QDialog;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    // 点击显示对话框
    void onClickToShowDialog();

private:
    Ui::Widget *ui;

    QDialog* ptr_dlg_{ nullptr };
};
#endif // WIDGET_H
