#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QDialog;
class QTimer;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    // 点击显示对话框
    void onClickToShowDialog();
    // 点击显示检测更新
    void onCheckUpdate();

private:
    Ui::Widget *ui;

    QDialog* ptr_dlg_{ nullptr };
    QTimer* ptr_hide_timer_{ nullptr };
};
#endif // WIDGET_H
