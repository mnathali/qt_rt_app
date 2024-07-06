#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileInfo>
#include "OpticalSystem.hpp"
#include "Surface.hpp"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    opsll::OpticalSystem build_os();
    std::vector<std::pair<double, double>> get_glass_specs(QString const &name);

private slots:
    void updateTableSTO(int);

    void on_setInfinity_clicked();

    void on_S1_value_textChanged(const QString &arg1);


    void on_FieldAngle_textEdited(const QString &arg1);

    void on_FieldHeight_textEdited(const QString &arg1);

    void on_EPDiameter_textEdited(const QString &arg1);

    void on_ObjNA_textEdited(const QString &arg1);

    void on_actionNew_triggered();

    void on_actionAdd_New_Glass_triggered();

    void on_tableWidget_cellChanged(int row, int column);

    void on_lineEdit_NP_editingFinished();

    void on_deleteWL_clicked();

    void on_addWL_clicked();

    void on_actionSpot_Diagram_triggered();

    void on_actionRay_Trace_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
