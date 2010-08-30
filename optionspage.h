#ifndef OPTIONSPAGE_H
#define OPTIONSPAGE_H

#include <QtGui/QWidget>

namespace Ui {
    class OptionsPage;
}

class OptionsPage : public QWidget {
    Q_OBJECT
public:
    OptionsPage(QWidget *parent = 0);
	~OptionsPage();
	void updateSettings();

public slots:
	void numberOfPasswordsChanged(int i);
	void noSimular(bool i);
	void unique(bool i);

protected:
    void changeEvent(QEvent *e);

private:
	Ui::OptionsPage *ui;
};

#endif // OPTIONSPAGE_H
