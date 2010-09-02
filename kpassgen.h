#ifndef KPASSGEN_H
#define KPASSGEN_H

#include <QWidget>

namespace Ui {
    class KPassGen;
}

class KPassGen : public QWidget
{
    Q_OBJECT

public:
    explicit KPassGen(QWidget *parent = 0);
    ~KPassGen();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::KPassGen *ui;
};

#endif // KPASSGEN_H
