#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employeeinputdialog.h"
#include "Employee.h"
#include "DailyShiftList.h"
// added packages
#include <QInputDialog>
#include <QDebug>
#include <QCheckBox>
#include <iostream>
#include <QDate>
using namespace std;
#include <vector>
#include <algorithm>
#include <set>
#include <QTableWidget>

// global variables
vector<Employee> EmployeeVector;
vector<DailyShiftList> ShiftsForMonthVector;
vector<QDate> DatesForShiftLists;

// function to implement algorithm
QStringList algForShiftList(int sBvalue,QString dayOfWeekStr){

    // this vector will be added to when employees fit criteria for day available
    vector<Employee> RefinedEmployeeVector;
    // this vector will be added to when employees fit criteria for min number of working days
    vector<Employee> PerfectFitEmployeeVector;
    // this is what needs to be returned
    QStringList ChosenEmployees;
    // this vector holds the number of shifts for each PerfectFitEmployeeVector item
    vector<int> NumShiftsPerfectFitEmployeeVector;

    // loop through all employees and add to RefinedEmployeeVector when criteria is met
    for (auto it = EmployeeVector.begin(); it != EmployeeVector.end(); it++){
        // loop through each day of available days for employee
        for (int i = 0; i < 7; i++){
            // check if the current avaiableday for the employee = dayOfWeekStr
            if(it->getAvailableDays()[i] == dayOfWeekStr){
                // add to RefinedEmployeeVector
                RefinedEmployeeVector.push_back(*it);
            }
        }
    }

    // loop through RefinedEmployeeVector and add to PerfectFitEmployeeVector
    for (int minValue = 0; PerfectFitEmployeeVector.size() < sBvalue; minValue++){
        for (auto it = RefinedEmployeeVector.begin(); it != RefinedEmployeeVector.end(); it++){
            // if the number of days that the employee can work is equal to minValue then add to PerfectFitEmployeeVector
            if (it->getnumOfDaysCanWork() == minValue){
                PerfectFitEmployeeVector.push_back(*it);
                // add to NumShiftsPerfectFitEmployeeVector
                NumShiftsPerfectFitEmployeeVector.push_back(it->getcurrNumShifts());
            }
        }
    }

    // sort NumShiftsPerfectFitEmployeeVector into ascending order
    sort(NumShiftsPerfectFitEmployeeVector.begin(), NumShiftsPerfectFitEmployeeVector.end());

    // use a set to keep track of unique employee names
    std::set<QString> uniqueEmployeeNames;

    // loop until ChosenEmployees is full
    for (int j = 0; j < sBvalue && j < NumShiftsPerfectFitEmployeeVector.size(); j++) {

        for (int i = 0; i < PerfectFitEmployeeVector.size(); i++) {

            if (NumShiftsPerfectFitEmployeeVector[j] == PerfectFitEmployeeVector[i].getcurrNumShifts()) {
                // add chosen employee to the list if not already added
                if (uniqueEmployeeNames.insert(PerfectFitEmployeeVector[i].getEmployeeName()).second) {
                    ChosenEmployees.append(PerfectFitEmployeeVector[i].getEmployeeName());

                    // increment current number of shifts for the specific employee
                    auto it = std::find_if(EmployeeVector.begin(), EmployeeVector.end(),
                                           [name = PerfectFitEmployeeVector[i].getEmployeeName()](Employee& e) {
                                               return e.getEmployeeName() == name;
                                           });

                    if (it != EmployeeVector.end()) {
                        it->incNumShifts();
                        qDebug() << "Num of shifts for " + it->getEmployeeName() + " is " + QString::number(it->getcurrNumShifts());
                    }
                    break;
                }
            }
        }
    }

    // debug to console
    for (int i = 0; i < ChosenEmployees.size(); i++) {
        qDebug() << ChosenEmployees[i];
    }

    return ChosenEmployees;
}


// function to calculate shift list for the next sBnumDays->value() days
void calculateShiftsForTheMonth(Ui::MainWindow *ui){
    // get the current date
    QDate currentDate = QDate::currentDate();

    // loop through current date + 1 to current date + sBnumDays->value() (all sBnumDays->value() days for shift list)
    for (int i=1 ; i<= ui->sBnumDays->value() ; i++){
        qDebug() << "Day " + QString::number(i);

        // add i days to the current day to represent days 1-30
        QDate currentDatePlusiDay = currentDate.addDays(i);
        // add the date the the DatesForShiftLists vector which will be used to display the dates on the tableView
        DatesForShiftLists.push_back(currentDatePlusiDay);
        // Get the day of the week as an integer (1 to 7)
        int dayOfWeekInt = currentDatePlusiDay.dayOfWeek();
        int sBvalue=0; // this stores the value of the spinBox relating to the current day (for the number of people allowed to work that day)
        QString dayOfWeekStr; // this is the current day of the week for the date we looping through
        // Map the integer to the corresponding day name and also set the value for sBmonday
        switch (dayOfWeekInt) {
        case 1:
            dayOfWeekStr = "Monday";
            sBvalue = ui->sBmonday->value();
            break;
        case 2:
            dayOfWeekStr = "Tuesday";
            sBvalue = ui->sBtuesday->value();
            break;
        case 3:
            dayOfWeekStr = "Wednesday";
            sBvalue = ui->sBwednesday->value();
            break;
        case 4:
            dayOfWeekStr = "Thursday";
            sBvalue = ui->sBthursday->value();
            break;
        case 5:
            dayOfWeekStr = "Friday";
            sBvalue = ui->sBfriday->value();
            break;
        case 6:
            dayOfWeekStr = "Saturday";
            sBvalue = ui->sBsaturday->value();
            break;
        case 7:
            dayOfWeekStr = "Sunday";
            sBvalue = ui->sBsunday->value();
            break;
        default: dayOfWeekStr = "Invalid Day"; break;
        }

        // call the algorithm to calculate the people working for the day
        QStringList Employees_Working_Today = algForShiftList(sBvalue,dayOfWeekStr);

        // create new dailyshiftlist object
        DailyShiftList dailyshiftlist(Employees_Working_Today);

        ShiftsForMonthVector.push_back(dailyshiftlist);
    }
}

// function to populate the tableview tVshiftLists
void populateTableView(QTableWidget *tableWidget, vector<DailyShiftList> &shiftsForMonthVector, vector<QDate> &datesForShiftLists) {
    // Set the number of rows in the table (number of employees)
    int numRows = EmployeeVector.size();
    tableWidget->setRowCount(numRows);

    // Set the number of columns in the table (number of days + 1 for the new column)
    int numCols = static_cast<int>(shiftsForMonthVector.size()) + 1;
    tableWidget->setColumnCount(numCols);

    // Set column headers with corresponding dates
    for (int col = 0; col < numCols - 1; ++col) {
        QTableWidgetItem *headerItem = new QTableWidgetItem(datesForShiftLists[col].toString("yyyy-MM-dd"));
        tableWidget->setHorizontalHeaderItem(col, headerItem);
    }

    // Set header for the new column
    QTableWidgetItem *newHeaderItem = new QTableWidgetItem("Employee (number of shifts)");
    tableWidget->setHorizontalHeaderItem(numCols - 1, newHeaderItem);

    // Populate the table with data
    for (int col = 0; col < numCols - 1; ++col) {
        const QStringList &names = shiftsForMonthVector[col].getNames();
        for (int row = 0; row < names.size(); ++row) {
            QTableWidgetItem *item = new QTableWidgetItem(names[row]);
            tableWidget->setItem(row, col, item);
        }
    }

    // Populate the new column with all employees and their number of shifts
    for (int row = 0; row < EmployeeVector.size(); ++row) {
        QString employeeName = EmployeeVector[row].getEmployeeName();
        QString shiftsInfo = QString::number(EmployeeVector[row].getcurrNumShifts());
        QTableWidgetItem *item = new QTableWidgetItem(employeeName + " (" + shiftsInfo + ")");
        tableWidget->setItem(row, numCols - 1, item);
    }

    // Resize the last column to fit its contents
    tableWidget->resizeColumnToContents(numCols - 1);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // clear vectors (just for my own peace of mind)
    EmployeeVector.clear();
    ShiftsForMonthVector.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// add employees to lwEmployees and update lblNumEmployees
void MainWindow::on_pBaddEmployee_clicked()
{
    // Create an instance of the custom dialog
    EmployeeInputDialog inputDialog(this);

    // Show the custom dialog
    if (inputDialog.exec() == QDialog::Accepted) {
        // Retrieve the entered information
        QString employeeName = inputDialog.getEmployeeName();
        QStringList selectedDays = inputDialog.getSelectedDays();

        // add as Employee object and add to global EmployeeVector
        Employee employee(employeeName,selectedDays);
        EmployeeVector.push_back(employee);

        // Add the employee name to the list widget
        ui->lwEmployees->addItem(employeeName);
    }
    // update lblNumEmployees
    ui->lblNumEmployees->setText(QString::number(EmployeeVector.size()));
}

// delete item in lwEmployees after being double clicked and also remove from EmployeeVector and update lblNumEmployees
void MainWindow::on_lwEmployees_itemDoubleClicked(QListWidgetItem *item)
{
    // remove item in EmployeeVector
    QString valueToRemove = item->text();
    for (auto it = EmployeeVector.begin(); it != EmployeeVector.end();) {
        if (it->getEmployeeName() == valueToRemove) {
            // Erase the element and update the iterator
            it = EmployeeVector.erase(it);
        } else {
            // Move to the next element
            ++it;
        }
    }

    // update lblNumEmployees
    ui->lblNumEmployees->setText(QString::number(EmployeeVector.size()));

    // remove item in lwEmployees
    delete item;
}

// call function to calculate shift list for the next 30 days
void MainWindow::on_pBcalculateShiftsForMonth_clicked()
{
    // clear items
    ui->tWshiftLists->clear();
    ShiftsForMonthVector.clear();
    DatesForShiftLists.clear();
    for (auto it=EmployeeVector.begin(); it != EmployeeVector.end(); it++){
        it->ResetCurrNumShifts();
    }

    calculateShiftsForTheMonth(ui);
    populateTableView(ui->tWshiftLists,ShiftsForMonthVector,DatesForShiftLists);
}

