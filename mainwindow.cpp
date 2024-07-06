#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QHBoxLayout>
#include "newglassform.h"
#include "raytrace.h"
#include <QIntValidator>
#include <QDoubleValidator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto s1_cell = new QTableWidgetItem(ui->S1_value->text());
    s1_cell->setFlags(s1_cell->flags() & ~Qt::ItemIsEditable);
    ui->tableWidget->setItem(0, 1, s1_cell);

    connect(ui->comboBox_ND, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTableSTO(int)));

    ui->statusbar->addPermanentWidget(this->ui->label_FL);
    ui->statusbar->addPermanentWidget(this->ui->FLVal);
    ui->statusbar->addPermanentWidget(this->ui->label_Len);
    ui->statusbar->addPermanentWidget(this->ui->LinMagnification);
    ui->statusbar->addPermanentWidget(this->ui->label_Magn);
    ui->statusbar->addPermanentWidget(this->ui->TotalLenghtVal);

    QIntValidator *validator_i = new QIntValidator();
    ui->lineEdit_NP->setValidator(validator_i);
    QDoubleValidator *validator_d = new QDoubleValidator();
    ui->EPDiameter->setValidator(validator_d);
    ui->ObjNA->setValidator(validator_d);
    ui->FieldAngle->setValidator(validator_d);
    ui->FieldHeight->setValidator(validator_d);
    ui->S1_value->setValidator(validator_d);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_NP_editingFinished()
{
    // Convert the text to an integer
    bool ok;
    int numRows = this->ui->lineEdit_NP->text().toInt(&ok);

    if (ok && numRows < 3)
        numRows = 3;

    // Check if conversion was successful
    if (ok) {
        // Update the number of rows in the QTableWidget
        auto curr_n = this->ui->tableWidget->rowCount();
        auto curr_aper_pos = ui->comboBox_ND->currentIndex();
        ui->tableWidget->setRowCount(numRows);
        ui->tableWidget->setVerticalHeaderItem(0, new QTableWidgetItem("OBJ"));
        for (int row = curr_n - 1; row < ui->tableWidget->rowCount(); ++row) {
            if (ui->comboBox_ND->currentText().toInt() == row)
                continue;
            QTableWidgetItem *row_name = new QTableWidgetItem(QString::number(row));
            QTableWidgetItem *radius = new QTableWidgetItem("infinity");
            QTableWidgetItem *thickness = new QTableWidgetItem("0,0");
            this->ui->tableWidget->setVerticalHeaderItem(row, row_name);
            this->ui->tableWidget->setItem(row, 0, radius);
            this->ui->tableWidget->setItem(row, 1, thickness);
        }
        ui->tableWidget->setVerticalHeaderItem(numRows-1, new QTableWidgetItem("IMG"));
        if (numRows - 2 > curr_aper_pos)
            for (int index = ui->comboBox_ND->count() + 1; index < numRows - 1; ++index)
                ui->comboBox_ND->addItem(QString::number(index));
        else
            ui->comboBox_ND->setCurrentIndex(numRows-2);
        for (int row = curr_n - 3; row > numRows - 3; --row)
            this->ui->comboBox_ND->removeItem(row);

    }
}

void MainWindow::updateTableSTO(int index)
{
    ++index;
    if (index) {
        for (int row = 1; row < ui->tableWidget->rowCount() - 1; ++row) {
            QTableWidgetItem *Item = new QTableWidgetItem(QString::number(row));
            ui->tableWidget->setVerticalHeaderItem(row, Item);
        }
        ui->tableWidget->setVerticalHeaderItem(index, new QTableWidgetItem("APER"));
    }
}

void MainWindow::on_setInfinity_clicked()
{
    this->ui->S1_value->setText("-∞");
    this->ui->tableWidget->setItem(0, 1, new QTableWidgetItem(this->ui->S1_value->text()));
    this->ui->FieldAngle->setEnabled(true);
    this->ui->FieldAngle->setText("0");
    this->ui->EPDiameter->setEnabled(true);
    this->ui->EPDiameter->setText("0");
    this->ui->FieldHeight->setEnabled(false);
    this->ui->FieldHeight->setText("-");
    this->ui->ObjNA->setEnabled(false);
    this->ui->ObjNA->setText("-");

}


void MainWindow::on_S1_value_textChanged(const QString &arg1)
{
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(ui->S1_value->text()));
    this->ui->FieldAngle->setEnabled(false);
    this->ui->FieldAngle->setText("-");
    this->ui->EPDiameter->setEnabled(false);
    this->ui->EPDiameter->setText("-");
    this->ui->FieldHeight->setEnabled(true);
    this->ui->FieldHeight->setText("0");
    this->ui->ObjNA->setEnabled(true);
    this->ui->ObjNA->setText("0");

}


void MainWindow::on_FieldAngle_textEdited(const QString &arg1)
{
    this->ui->FieldHeight->setEnabled(false);
    this->ui->FieldHeight->setText("-");
    this->ui->ObjNA->setEnabled(false);
    this->ui->ObjNA->setText("-");
}


void MainWindow::on_FieldHeight_textEdited(const QString &arg1)
{
    this->ui->FieldAngle->setEnabled(false);
    this->ui->FieldAngle->setText("-");
    this->ui->EPDiameter->setEnabled(false);
    this->ui->EPDiameter->setText("-");
}


void MainWindow::on_EPDiameter_textEdited(const QString &arg1)
{
    this->ui->FieldHeight->setEnabled(false);
    this->ui->FieldHeight->setText("-");
    this->ui->ObjNA->setEnabled(false);
    this->ui->ObjNA->setText("-");
}


void MainWindow::on_ObjNA_textEdited(const QString &arg1)
{
    this->ui->FieldAngle->setEnabled(false);
    this->ui->FieldAngle->setText("-");
    this->ui->EPDiameter->setEnabled(false);
    this->ui->EPDiameter->setText("-");
}


void MainWindow::on_actionNew_triggered()
{
    this->ui->FieldHeight->setEnabled(true);
    this->ui->FieldHeight->setText("0");
    this->ui->ObjNA->setEnabled(true);
    this->ui->ObjNA->setText("0");
    this->ui->S1_value->setText("-∞");
    this->ui->FieldAngle->setEnabled(true);
    this->ui->FieldAngle->setText("0");
    this->ui->EPDiameter->setEnabled(true);
    this->ui->EPDiameter->setText("0");
    ui->tableWidget->clearContents();
    this->ui->lineEdit_NP->setText("0");
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(ui->S1_value->text()));

}

void MainWindow::on_actionAdd_New_Glass_triggered()
{
    NewGlassForm add_new_glass_form(this);
    add_new_glass_form.setModal(true);
    add_new_glass_form.exec();
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    auto cellValue = this->ui->tableWidget->item(row, column);
    bool isDouble = false;
    if (this->ui->tableWidget->horizontalHeaderItem(column)->text() == "Glass")
        return;
    qDebug() << row << column;
    if (cellValue) {
        auto d = cellValue->text().replace(",", ".").toDouble(&isDouble);
        if (isDouble == false && cellValue->text() != "-∞" && cellValue->text() != "infinity")
            this->ui->tableWidget->setItem(row, column, new QTableWidgetItem("0,0"));
        else if (cellValue->text() != "infinity"
                 && this->ui->tableWidget->horizontalHeaderItem(column)->text() == "Radius"
                 && d == 0)
            this->ui->tableWidget->setItem(row, column, new QTableWidgetItem("infinity"));

    }

}

void MainWindow::on_deleteWL_clicked()
{
    auto index = this->ui->listWidget_WLines->currentRow();
    if (index < 0)
        return;
    delete this->ui->listWidget_WLines->takeItem(index);
}


void MainWindow::on_addWL_clicked()
{
    auto selected_line = this->ui->comboBox_WLines->currentText();
    for (int i{}; i < this->ui->listWidget_WLines->count(); ++i)
        if (selected_line == this->ui->listWidget_WLines->item(i)->text())
            return;
    this->ui->listWidget_WLines->addItem(selected_line);

}


void MainWindow::on_actionSpot_Diagram_triggered()
{

}

std::vector<std::pair<double, double>> MainWindow::get_glass_specs(QString const &name)
{
    QSqlDatabase main_db = QSqlDatabase::addDatabase("QSQLITE");
    main_db.setDatabaseName(MAIN_DATABASE_PATH);
    QSqlQuery query;
    main_db.open();

    if (!main_db.open() || !query.exec("Select wavelenght, r_index from glasses where model = '" + name + "'")) {
        qDebug() << "Error opening database:" << main_db.lastError().text();
        QMessageBox::critical(this, "Error opening database", "Data base wasn't opened");
        return {};
    }
    std::vector<std::pair<double, double>> glass_data;
    while (query.next()) {
        glass_data.push_back({query.value(0).toDouble(), query.value(1).toDouble()});
    }
    qDebug() << glass_data.size() << name;
    main_db.close();
    main_db.removeDatabase(QSqlDatabase::defaultConnection);
    return glass_data;
}

opsll::OpticalSystem MainWindow::build_os()
{
    double field{}, s1{}, pupil_pos{}, pupil_size{};
    std::vector<opsll::Surface> surfs;
    std::vector<double> waves;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        auto radius = ui->tableWidget->item(row, 0)->text().replace(",", ".").toDouble();
        auto thickness = ui->tableWidget->item(row, 1)->text().replace(",", ".").toDouble();
        auto material_name = ui->tableWidget->item(row, 2) && ui->tableWidget->item(row, 2)->text().size()
                                 ? ui->tableWidget->item(row, 2)->text() : "real_air";
        auto glass_specs = get_glass_specs(material_name);
        opsll::Material material(glass_specs);
        opsll::Surface surface(radius, thickness, material);
        surfs.push_back(surface);
    }
    for (int index{}; index < this->ui->listWidget_WLines->count(); ++index) {
        QString line = this->ui->listWidget_WLines->item(index)->text();
        line = line.mid(line.lastIndexOf("- ") + 2).replace(",", ".");
        auto wavelenght = line.toDouble();
        qDebug() << wavelenght << "wavelenght" << line;
        waves.push_back(wavelenght);
    }
    pupil_pos = opsll::OpticalSystem::get_pupil_pos(surfs, 1, waves.front());
    if (this->ui->S1_value->text() == "-∞")
    {
        field = this->ui->FieldAngle->text().toDouble();
        s1 = std::numeric_limits<double>::infinity();
        pupil_size = this->ui->EPDiameter->text().toDouble();
    }
    else
    {
        field = this->ui->FieldHeight->text().toDouble();
        s1 = this->ui->S1_value->text().toDouble();
        pupil_size = 2 * std::abs(std::tan(std::asin(this->ui->ObjNA->text().toDouble())) * (s1 - pupil_pos));
    }
    opsll::OpticalSystem optical_system(s1, field, pupil_pos, pupil_size, surfs, waves);
    return optical_system;
}


void MainWindow::on_actionRay_Trace_triggered()
{
    auto optical_system = build_os();
    for (auto &surf : optical_system.get_surfaces())
        qDebug() << surf.get_curvature() << surf.get_radius() << surf.get_material().get_specs().size();
    RayTrace ray_trace(this, optical_system);
    ray_trace.setModal(true);
    ray_trace.exec();
}

