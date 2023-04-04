#include "form.h"
#include "ui_form.h"
#include <QDebug>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::setlist(QStringList strlis1, QStringList strlis2)
{
    QString temp1;
    QString temp2;
    for(int i = 0; i < strlis1.length(); i++)
    {
        if (-1 == strlis2.indexOf(strlis1.at(i)))
            temp1.append(strlis1.at(i)+"\n");
    }
    for(int i = 0; i < strlis2.length(); i++)
    {
        temp2.append(strlis2.at(i)+"\n");
    }

    ui->textEdit1->setText(temp1);
    ui->textEdit2->setText(temp2);
}
