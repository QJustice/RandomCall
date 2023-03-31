#include "cwidget.h"
#include "./ui_cwidget.h"
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QCoreApplication>
#include <QTimer>
#include <QMessageBox>

CWidget::CWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CWidget)
{
    ui->setupUi(this);

    // 禁用最大化按钮和禁止调节窗口大小
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    // 计时器
    this->m_pTimer = new QTimer(this);
    connect(this->m_pTimer,SIGNAL(timeout()),this,SLOT(handleTimeout()));
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        this->readList();
        if(this->code==0)
        {
            if(this->m_pTimer->isActive())
            {
                ui->pushButton->setText("开始");
                this->m_pTimer->stop();
            }
            else
            {
                ui->pushButton->setText("停止");
                this->m_pTimer->start(50);
            }
        }
        else if(this->code==1)
            QMessageBox::critical(this,"出错了","请将data.txt人员名单放到程序同级目录下\n文件格式：一行一个姓名，多个姓名用换行符分割");
        else if(this->code==2)
            QMessageBox::critical(this,"出错了","读取文件出错！");
    });
}

CWidget::~CWidget()
{
    delete ui;
}

void CWidget::handleTimeout()
{
    QTime time = QTime::currentTime();
    srand(time.msec()+time.second()*1000);
    int num = rand() % this->list.size();
    QString str = this->list.at(num);
    ui->label->setText(str);
}

void CWidget::readList()
{
    // 获取程序当前运行目录
    QString filePath = QCoreApplication::applicationDirPath();
    QFile file(filePath + "/data.txt");
    if(!file.exists())
        this->code = 1;
    else if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        this->code = 2;
    else
    {
        this->code = 0;
        QByteArray bytes = file.readAll();
        QString content = bytes;
        QStringList distin;
        this->list = content.split("\n");
        this->list.removeAll(QString("")); // Returns the number of entries removed
        for(int i = 0; i < this->list.length(); i++)
        {
           if(!distin.contains(this->list[i]))
              distin.append(this->list[i]);
        }
        this->list = distin;
    }
}

