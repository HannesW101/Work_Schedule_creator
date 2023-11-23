#include "DailyShiftList.h"
#include <QDebug>

DailyShiftList::DailyShiftList(QStringList Employees_Working_Today){
    EmployeesWorkingToday = Employees_Working_Today;
}

// function to return EmployeesWorkingToday
QStringList DailyShiftList::getNames(){
    return EmployeesWorkingToday;
}
