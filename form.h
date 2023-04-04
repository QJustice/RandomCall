#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    void setlist(QStringList strlis1, QStringList strlis2);

private:
    Ui::Form *ui;
};

#endif // FORM_H
