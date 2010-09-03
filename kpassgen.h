#ifndef KPASSGEN_H
#define KPASSGEN_H

#include <QWidget>
#include "ui_kpassgen.h"

//namespace Ui {
//    class KPassGen;
//}

class KPassGen : public QWidget
{
    Q_OBJECT

public:
    explicit KPassGen(QWidget *parent = 0);
    ~KPassGen();

    bool writeSettings();
    bool readSettings();

private slots:
    void genPass();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::KPassGen *ui;
};

#endif // KPASSGEN_H
