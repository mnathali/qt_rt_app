#include "newglassform.h"
#include "ui_newglassform.h"
#include <QDoubleValidator>

NewGlassForm::NewGlassForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewGlassForm), main_db(QSqlDatabase::addDatabase("QSQLITE"))
{
    ui->setupUi(this);
    QDoubleValidator* validator = new QDoubleValidator();
    ui->RefractionIndexGlass->setValidator(validator);
    ui->WaveLenghtGlass->setValidator(validator);

    main_db.setDatabaseName(MAIN_DATABASE_PATH);

    QSqlQuery query;
    this->main_db.open();
    ui->WaveLinesBox->addItem("None");

    if (!main_db.open() || !query.exec("Select * from wavelines")) {
        qDebug() << "Error opening database:" << main_db.lastError().text();
        this->ui->AddGlassButton->setText("Database wasn't opened");
        ui->WaveLenghtGlass->setDisabled(true);
        ui->GlassName->setDisabled(true);
        ui->RefractionIndexGlass->setDisabled(true);
        ui->WaveLinesBox->setDisabled(true);

    }
    while (query.next()) {
        QString lineName = query.value(0).toString();
        ui->WaveLinesBox->addItem(lineName);
    }

}

NewGlassForm::~NewGlassForm()
{
    delete ui;
    main_db.close();
    main_db.removeDatabase(QSqlDatabase::defaultConnection);
}

void NewGlassForm::on_AddGlassButton_clicked()
{

    QString sql = "INSERT INTO glasses (model, wavelenght, r_index) VALUES (?, ?, ?)";
    QSqlQuery query;
    query.prepare(sql);

    // Bind values to the placeholders
    query.bindValue(0, this->ui->GlassName->text());
    query.bindValue(1, this->ui->WaveLenghtGlass->text().replace(",", ".").toDouble());
    query.bindValue(2, this->ui->RefractionIndexGlass->text().replace(",", ".").toDouble());

    // Execute the SQL statement
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text() << " Query: " << query.lastQuery();
        this->ui->AddGlassButton->setText("ERROR!");
        return ;
    }
    qDebug() << "Record inserted successfully";

    this->ui->WaveLenghtGlass->clear();
    this->ui->RefractionIndexGlass->clear();
    this->ui->AddGlassButton->setText("The Record was Added!");
}


void NewGlassForm::on_RefractionIndexGlass_textEdited(const QString &arg1)
{
    this->ui->AddGlassButton->setText("Add");
}


void NewGlassForm::on_GlassName_textEdited(const QString &arg1)
{
    this->ui->AddGlassButton->setText("Add");

}


void NewGlassForm::on_WaveLenghtGlass_textEdited(const QString &arg1)
{
    this->ui->AddGlassButton->setText("Add");

}


void NewGlassForm::on_WaveLinesBox_currentIndexChanged(int index)
{
    QSqlQuery query;

    if (!query.exec("Select wavelenght from wavelines where line = \"" + this->ui->WaveLinesBox->currentText() + "\"")) {
        this->ui->WaveLinesBox->setDisabled(true);
        return;
    }
    if (query.next()) {
        QString wavelenght = query.value(0).toString().replace(".", ",");
        this->ui->WaveLenghtGlass->setText(wavelenght);
    }
}

