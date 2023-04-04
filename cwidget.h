#ifndef CWIDGET_H
#define CWIDGET_H

#include <QWidget>
#include <QStatusBar>
#include "form.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CWidget; }
QT_END_NAMESPACE

class CWidget : public QWidget
{
    Q_OBJECT

public:
    CWidget(QWidget *parent = nullptr);
    ~CWidget();

 signals:

public slots:
    void handleTimeout();

private slots:
    void on_otherOnebtn_clicked();


    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::CWidget *ui;
    QStatusBar *m_statusBar;
    void readList();    //读取人员名单函数
    QTimer *m_pTimer;   //计时器
    QTimer *myTimer;
    QStringList list;   //名单数据
    QStringList lukey_list; // 已经出厂名单
    int code = 0;   //状态码：0读取名单文件成功 1没有找到名单文件，2名单文件读取失败
    Form *lukeyWin = nullptr;
    int numAll;

};
#endif // CWIDGET_H
