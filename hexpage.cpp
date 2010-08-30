#include "hexpage.h"
#include "ui_hexpage.h"
#include "settings.h"

HexPage::HexPage(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::HexPage)
{
    m_ui->setupUi(this);

    connect(m_ui->hexLower, SIGNAL(toggled(bool)), this, SLOT(lowerToggled(bool)));
}

HexPage::~HexPage()
{
    delete m_ui;
}

void HexPage::updateSettings()
{
    m_ui->hexLower->setChecked(Settings::hexLower());
}

void HexPage::lowerToggled(bool b)
{
    Settings::setHexLower(b);
}

void HexPage::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
