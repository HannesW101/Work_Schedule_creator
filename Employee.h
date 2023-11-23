#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QStringList>

class Employee
{
public:
    Employee(const QString employee_name,const QStringList available_days);
    QString getEmployeeName();
    QStringList getAvailableDays();
    int getnumOfDaysCanWork();
    void incNumShifts();
    int getcurrNumShifts();
    void ResetCurrNumShifts();
private:
    QString EmployeeName;
    QStringList AvailableDays;
    int currNumShifts=0;
    int numOfDaysCanWork=0;
};

#endif // EMPLOYEE_H
