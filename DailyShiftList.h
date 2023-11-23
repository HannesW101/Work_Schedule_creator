#ifndef DAILYSHIFTLIST_H
#define DAILYSHIFTLIST_H

#include <QStringList>

class DailyShiftList{
public:
    DailyShiftList(QStringList Employees_Working_Today);
    QStringList getNames();
private:
    QStringList EmployeesWorkingToday;
};

#endif // DAILYSHIFTLIST_H
