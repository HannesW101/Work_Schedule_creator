#ifndef EMPLOYEEINPUTDIALOG_H
#define EMPLOYEEINPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialogButtonBox>

// createing custom class that will add checkboxes to the QDialog to indicate which days employees can work
class EmployeeInputDialog : public QDialog
{
    Q_OBJECT

public:
    EmployeeInputDialog(QWidget *parent = nullptr);

    QString getEmployeeName() const;
    QStringList getSelectedDays() const;

private:
    QLineEdit *nameLineEdit;
    QList<QCheckBox *> dayCheckboxes;
};

#endif // EMPLOYEEINPUTDIALOG_H
