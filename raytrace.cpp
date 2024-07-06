#include "raytrace.h"
#include "ui_raytrace.h"
#include <cmath>

RayTrace::RayTrace(QWidget *parent, opsll::OpticalSystem &optical_system)
    : QDialog(parent)
    , ui(new Ui::RayTrace), optical_system(optical_system)
{
    ui->setupUi(this);

    auto *main_window = dynamic_cast<MainWindow*>(parent);

    auto waves = optical_system.get_waves();
    for (auto &wave: waves)
        this->ui->comboBox_waves->addItem(QString::number(wave));
    auto ray = opsll::Ray(opsll::Ray::values_tuple{0,0.1,0,0,0,0,1},
                          this->ui->comboBox_waves->itemText(0).toDouble());

    auto ray_coords = optical_system.ray_trace(ray);

    for (auto & ray : ray_coords)
    {
        auto specs = ray.get_coordinates();
        auto n_rows = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(++n_rows);
        ui->tableWidget->setItem(n_rows - 1, 0, new QTableWidgetItem(QString::number(std::acos(specs->X) / M_PI * 180)));
        ui->tableWidget->setItem(n_rows - 1, 1, new QTableWidgetItem(QString::number(std::acos(specs->Y) / M_PI * 180)));
        ui->tableWidget->setItem(n_rows - 1, 2, new QTableWidgetItem(QString::number(std::acos(specs->Z) / M_PI * 180)));
        ui->tableWidget->setItem(n_rows - 1, 3, new QTableWidgetItem(QString::number(specs->x)));
        ui->tableWidget->setItem(n_rows - 1, 4, new QTableWidgetItem(QString::number(specs->y)));
        ui->tableWidget->setItem(n_rows - 1, 5, new QTableWidgetItem(QString::number(specs->z)));
    }
    optical_system.get_focal_lengh();
}

RayTrace::~RayTrace()
{
    delete ui;
}
