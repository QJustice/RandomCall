#ifndef CWIDGET_H
#define CWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CWidget; }
QT_END_NAMESPACE

class CWidget : public QWidget
{
    Q_OBJECT

public:
    CWidget(QWidget *parent = nullptr);
    ~CWidget();

public slots:
    void handleTimeout();

private:
    Ui::CWidget *ui;

    void readList();    //读取人员名单函数
    QTimer *m_pTimer;   //计时器
    QStringList list;   //名单数据
    int code = 0;   //状态码：0读取名单文件成功 1没有找到名单文件，2名单文件读取失败
};
#endif // CWIDGET_H
