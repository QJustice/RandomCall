#include "cwidget.h"
#include "./ui_cwidget.h"
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QCoreApplication>
#include <QTimer>
#include <QMessageBox>
#include <QDateTime>

CWidget::CWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CWidget)
{
    ui->setupUi(this);

    this->m_statusBar = new QStatusBar(this);
    this->m_statusBar->setGeometry(QRect(0, 270, 500, 30));
    this->m_statusBar->addPermanentWidget(ui->labelNum);
    this->m_statusBar->showMessage("Ready", 3000); // 显示临时信息，时间3秒钟.

    this->myTimer=new QTimer(this);
    this->myTimer->start(1000);
    connect(this->myTimer , QTimer::timeout, [=](){
        QDateTime Date_Time =QDateTime::currentDateTime();
        QString Time_system = Date_Time.toString("yyyy-MM-dd hh:mm:ss ddd");
        this->m_statusBar->showMessage(Time_system);
    });
    // 禁用最大化按钮和禁止调节窗口大小
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    // 计时器
    this->m_pTimer = new QTimer(this);
    connect(this->m_pTimer,SIGNAL(timeout()),this,SLOT(handleTimeout()));
    connect(ui->startbtn,&QPushButton::clicked,[=](){
        this->readList();
        if(this->code==0)
        {
            if(this->m_pTimer->isActive())
            {
                ui->startbtn->setText("开始");
                this->m_pTimer->stop();
                if (ui->checkBox->isChecked())
                {
                    this->list.removeOne(ui->label->text());
                    this->lukey_list.append(ui->label->text());
                }
                else if (-1 == this->lukey_list.indexOf(ui->label->text()))
                {
                    this->lukey_list.append(ui->label->text());
                }
                else
                    return;
                QString str = QString("%1/%2(已出场/全部)").arg(this->lukey_list.length()).arg(this->numAll);
                ui->labelNum->setText(str);
                // qDebug() << this->lukey_list;
            }
            else
            {
                ui->startbtn->setText("停止");
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
    if (this->lukeyWin)
        delete this->lukeyWin;
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
    // qDebug() << this->list << "all ";
    // 获取程序当前运行目录
    if (!this->list.empty())
        return;
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
        this->numAll = list.length();
        this->lukey_list.clear();
        // qDebug() << list << "read";
    }
}


void CWidget::on_otherOnebtn_clicked()
{
    if (this->list.empty() && this->lukey_list.empty())
        this->readList();
    if (!this->lukeyWin)
        this->lukeyWin = new Form;
    else
        this->lukeyWin->activateWindow();
    this->lukeyWin->setlist(this->list, this->lukey_list);
    this->lukeyWin->show();
}


void CWidget::on_checkBox_stateChanged(int arg1)
{
    if (2 == arg1)
        for (int i = 0; i < this->lukey_list.length(); i++)
           this->list.removeOne(lukey_list.at(i));
    if (0 == arg1)
        this->list.clear();
        this->readList();
}


void CWidget::on_pushButton_clicked()
{
    ui->label->setText("开始");
    ui->labelNum->setText("0/0(已出场/全部)");
    this->list.clear();
    this->lukey_list.clear();
}
