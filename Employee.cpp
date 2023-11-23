#include "Employee.h"

// simple constructor and get methods
Employee::Employee(const QString employee_name, const QStringList passed_days) {
    EmployeeName = employee_name;

    // List of all days of the week
    QStringList allDays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    // Initialize AvailableDays with "0" for all days
    AvailableDays = QStringList(allDays.size(), "0");

    // Replace the corresponding days with the passed days
    for (const QString &day : passed_days) {
        int index = allDays.indexOf(day);
        if (index != -1) {
            AvailableDays.replace(index, day);
            numOfDaysCanWork++;
        }
    }
}

// get the name of the employee
QString Employee::getEmployeeName(){
    return EmployeeName;
}

// get the list of days employee is available to work
QStringList Employee::getAvailableDays(){
    return AvailableDays;
}

// increment the current number of shifts for an employee
void Employee::incNumShifts(){
    currNumShifts++;
}

// get the number of days employee can work
int Employee::getnumOfDaysCanWork(){
    return numOfDaysCanWork;
}

// get the currNumShifts
int Employee::getcurrNumShifts(){
    return currNumShifts;
}

// set current number of shifts for employee
void Employee::ResetCurrNumShifts(){
    currNumShifts = 0;
}
