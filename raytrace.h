#ifndef RAYTRACE_H
#define RAYTRACE_H

#include <QDialog>
#include <QDebug>
#include "mainwindow.h"

namespace Ui {
class RayTrace;
}

class RayTrace : public QDialog
{
    Q_OBJECT

public:
    explicit RayTrace(QWidget *parent , opsll::OpticalSystem &);
    ~RayTrace();

private:
    Ui::RayTrace *ui;
    opsll::OpticalSystem &optical_system;
};

#endif // RAYTRACE_H
