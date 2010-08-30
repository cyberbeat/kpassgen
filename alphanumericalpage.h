#ifndef ALPHANUMERICALPAGE_H
#define ALPHANUMERICALPAGE_H

#include <QtGui/QWidget>
#include <QCheckBox>
#include <KLocale>
#include <KLineEdit>
#include <QItemDelegate>
class QTableWidgetItem;
class Settings;

namespace Ui {
    class AlphanumericalPage;
}

class AlphaWidgetDelagate : public QItemDelegate
 {
     Q_OBJECT
 public:
     AlphaWidgetDelagate(QObject *parent = 0);

     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const;

     void updateEditorGeometry(QWidget *editor,
         const QStyleOptionViewItem &option, const QModelIndex &index) const;
 private:
	 int maxValue(const QModelIndex &index) const;
 };

class AlphanumericalPage : public QWidget {
    Q_OBJECT
public:
    AlphanumericalPage(QWidget *parent = 0);
	~AlphanumericalPage();

	bool isSimple()			const;
    void updateSettings();

private:
    int checkedCount() const;
    void enableAll(const bool b = true);


private slots:
	void setSimple(bool b);
	void disableLast();
	void simpleToggle(bool value);
	void simpleToleranceChanged(int value);
	void tableChanged(QTableWidgetItem* item);
	void column1Changed(QTableWidgetItem* item);
	void column2Changed(QTableWidgetItem* item);


protected:
    void changeEvent(QEvent *e);

private:
	Ui::AlphanumericalPage *m_ui;
};

#endif // ALPHANUMERICALPAGE_H
