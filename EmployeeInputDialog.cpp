#include "employeeinputdialog.h"
#include <QVBoxLayout>

// constructor to setup the layout and styling for this widget
EmployeeInputDialog::EmployeeInputDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Employee Information");

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add a line edit for entering the employee name
    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setPlaceholderText("Enter employee name...");
    layout->addWidget(nameLineEdit);

    // Create checkboxes for each day of the week
    QStringList daysOfWeek = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    for (const QString &day : daysOfWeek) {
        QCheckBox *checkbox = new QCheckBox(day, this);
        dayCheckboxes.append(checkbox);
        layout->addWidget(checkbox);
    }

    // Add OK and Cancel buttons
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttonBox);

    // Apply stylesheets to customize appearance
    setStyleSheet(
                  "QLineEdit { color: white; }"
                  "QCheckBox { color: white; }"
                  "QDialogButtonBox QPushButton { color: white; border: 1px solid white; padding: 5px; padding-left: 30px; padding-right: 30px; }"
                  "QDialogButtonBox QPushButton:hover { background-color: rgb(67, 85, 133); }"
        );
}

// returns name in line edit
QString EmployeeInputDialog::getEmployeeName() const
{
    return nameLineEdit->text();
}

// returns days employee can work as a QStringList
QStringList EmployeeInputDialog::getSelectedDays() const
{
    QStringList selectedDays;
    for (QCheckBox *checkbox : dayCheckboxes) {
        if (checkbox->isChecked()) {
            selectedDays.append(checkbox->text());
        }
    }
    return selectedDays;
}
