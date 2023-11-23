#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pBaddEmployee_clicked();

    void on_lwEmployees_itemDoubleClicked(QListWidgetItem *item);

    void on_pBcalculateShiftsForMonth_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
