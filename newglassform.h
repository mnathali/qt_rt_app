#ifndef NEWGLASSFORM_H
#define NEWGLASSFORM_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class NewGlassForm;
}

class NewGlassForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewGlassForm(QWidget *parent = nullptr);
    ~NewGlassForm();

private slots:
    void on_AddGlassButton_clicked();

    void on_RefractionIndexGlass_textEdited(const QString &arg1);

    void on_GlassName_textEdited(const QString &arg1);

    void on_WaveLenghtGlass_textEdited(const QString &arg1);

    void on_WaveLinesBox_currentIndexChanged(int index);

private:
    Ui::NewGlassForm *ui;
    QSqlDatabase main_db;

};

#endif // NEWGLASSFORM_H
