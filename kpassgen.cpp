#include "kpassgen.h"
#include "ui_kpassgen.h"

KPassGen::KPassGen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KPassGen)
{
    ui->setupUi(this);
    ui->optionspane->setVisible(false);
}

KPassGen::~KPassGen()
{
    delete ui;
}

void KPassGen::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
