 #include "alphanumericalpage.h"
#include "ui_alphanumericalpage.h"
#include "settings.h"

#include <QSpinBox>

AlphaWidgetDelagate::AlphaWidgetDelagate(QObject *parent)
{}

QWidget *AlphaWidgetDelagate::createEditor(QWidget *parent,
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const
{
/*
    QSpinBox *editor = new QSpinBox(parent);
    editor->setMinimum(0);
	editor->setMaximum(maxValue(index));

    return editor;
*/
 }

void AlphaWidgetDelagate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
/*
    int value = index.model()->data(index, Qt::DisplayRole).toInt();

    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
*/
}
void AlphaWidgetDelagate::setModelData(QWidget *editor, QAbstractItemModel *model,
                  const QModelIndex &index) const
{
/*
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->interpretText();
    int value = spinBox->value();

    model->setData(index, value, Qt::EditRole);
*/
}

void AlphaWidgetDelagate::updateEditorGeometry(QWidget *editor,
                      const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

int AlphaWidgetDelagate::maxValue(const QModelIndex &index) const
{
return 0;
//int max = Settings::numberOfCharacters();
//QList<int> minList(Settings::minimumList());
//for( int i = 0; i < minList.count(); ++i)
//	max -= minList[i];
//max += index.model()->data(index, Qt::DisplayRole).toInt();
//return max;
}

AlphanumericalPage::AlphanumericalPage(QWidget *parent) :
QWidget(parent),
m_ui(new Ui::AlphanumericalPage)
{
m_ui->setupUi(this);

//m_ui->alphaWidget->resizeColumnsToContents();
//m_ui->alphaWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
//m_ui->alphaWidget->horizontalHeader()->setResizeMode(1, QHeaderView::Interactive);

m_ui->alphaWidget->setItemDelegateForColumn(1, new AlphaWidgetDelagate);

//connect(m_ui->simple,		SIGNAL(toggled(bool)), this, SLOT(setSimple(bool)));
//connect(m_ui->alphaWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(tableChanged(QTableWidgetItem*)));

updateSettings();

}

AlphanumericalPage::~AlphanumericalPage()
{
delete m_ui;
}

bool AlphanumericalPage::isSimple()                     const { return m_ui->simple->isChecked(); }

void AlphanumericalPage::updateSettings()
{
/*
//QList<int> checkedList = Settings::checkedList();
//QStringList characterList = Settings::characterList();
//QList<int> minimumList = Settings::minimumList();

for( int i = 0; i < checkedList.count(); ++i )
{
        if(i < checkedList.count())
                m_ui->alphaWidget->item(i, 0)->setCheckState(static_cast<Qt::CheckState>(checkedList[i]));
        if(i < characterList.count())
                m_ui->alphaWidget->item(i, 0)->setText(characterList[i]);
        if(i < minimumList.count())
                m_ui->alphaWidget->item(i, 1)->setText(QString("%1").arg(minimumList[i]));
}
m_ui->simple->setChecked(Settings::simple());

disableLast();
*/
}

int AlphanumericalPage::checkedCount() const
{
/*
int count = 0;

QList<int> checkedList = Settings::checkedList();


for(int i = 0; i < checkedList.count(); ++i)
{
        if (checkedList[i] && !Settings::characterList()[i].isEmpty())
                ++count;
}
return count;
*/
return 0;
}

void AlphanumericalPage::enableAll(const bool b)
{
Qt::ItemFlags flags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
if (b)
    flags = flags | Qt::ItemIsUserCheckable;

m_ui->alphaWidget->item(0, 0)->setFlags(flags);
m_ui->alphaWidget->item(1, 0)->setFlags(flags);
m_ui->alphaWidget->item(2, 0)->setFlags(flags);
m_ui->alphaWidget->item(3, 0)->setFlags(flags);
m_ui->alphaWidget->item(4, 0)->setFlags(flags | Qt::ItemIsEditable);
m_ui->alphaWidget->item(5, 0)->setFlags(flags | Qt::ItemIsEditable);
}

void AlphanumericalPage::setSimple(bool b)
{
//Settings::setSimple(b);
if (b)
{
        enableAll(true);
        m_ui->alphaWidget->item(0, 0)->setCheckState(Qt::Checked);
        m_ui->alphaWidget->item(0, 0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}
else
        disableLast();
}

void AlphanumericalPage::disableLast()
{
if ( isSimple() )
        return;

if ( checkedCount() > 1 )
{
        enableAll();
    return;
}

if ( checkedCount() <= 0 )
{
        m_ui->alphaWidget->item(0, 0)->setCheckState(Qt::Checked);
    return;
}

for( int i = 0; i < m_ui->alphaWidget->rowCount(); ++i )
{
/*
        if( Settings::characterList()[i].isEmpty() ) m_ui->alphaWidget->item(i, 0)->setCheckState(Qt::Unchecked);
        if (m_ui->alphaWidget->item(i, 0)->checkState() == Qt::Checked)
        {
                if( i > 3 )
                        m_ui->alphaWidget->item(i, 0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
                else
                        m_ui->alphaWidget->item(i, 0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
        */
}

}

void AlphanumericalPage::simpleToggle(bool value)
{
if (value)
{
    m_ui->alphaWidget->item(0, 0)->setCheckState(Qt::Checked);
    m_ui->alphaWidget->item(0, 0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}
else
    disableLast();
}

void AlphanumericalPage::simpleToleranceChanged(int value)
{
//Settings::setSimpleTolerence(value);
}

void AlphanumericalPage::tableChanged(QTableWidgetItem* item)
{
switch (item->column())
{
        case 0:
                column1Changed(item);
                break;

        case 1:
                column2Changed(item);
                break;
}
}

void AlphanumericalPage::column1Changed(QTableWidgetItem* item)
{
if (item->column() != 0) return;

int row = item->row();

//QList<int> checkedList(Settings::checkedList());
//if (static_cast<int>(item->checkState()) != checkedList[row] )
//{
//        checkedList[row] = static_cast<int>(item->checkState());
//        Settings::setCheckedList(checkedList);
//        disableLast();
//}

//QStringList characterList(Settings::characterList());
//if (item->text() != characterList[row])
//{
//        characterList[row] = item->text();
//        Settings::setCharacterList(characterList);
//}
}

void AlphanumericalPage::column2Changed(QTableWidgetItem* item)
{
if (item->column() != 1) return;

int row = item->row();

//QList<int> minimumList(Settings::minimumList());
//minimumList[row] = item->text().toInt();
//Settings::setMinimumList(minimumList);
}

void AlphanumericalPage::changeEvent(QEvent *e)
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
