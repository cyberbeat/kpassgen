#ifndef HEXPAGE_H
#define HEXPAGE_H

#include <QtGui/QWidget>

namespace Ui {
    class HexPage;
}

class HexPage : public QWidget {
    Q_OBJECT
public:
    HexPage(QWidget *parent = 0);
    ~HexPage();

    void updateSettings();

private slots:
    void lowerToggled(bool b);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::HexPage *m_ui;
};

#endif // HEXPAGE_H
