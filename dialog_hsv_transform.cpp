#include "dialog_hsv_transform.h"
#include "ui_dialog_hsv_transform.h"

DialogHsvTransform::DialogHsvTransform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHsvTransform)
{
    ui->setupUi(this);
}

DialogHsvTransform::~DialogHsvTransform()
{
    delete ui;
}

void DialogHsvTransform::on_buttonBox_accepted()

{
    double *h_f = new double[3];
    double *h_b=  new double[3];
    double *s_f = new double[3];
    double *s_b = new double[3];
    double *v_f = new double[3];
    double *v_b = new double[3];
    h_f[0]=ui->hf0DoubleSpinBox->value();
    h_f[1]=ui->hf1DoubleSpinBox->value();
    h_f[2]=ui->hf2DoubleSpinBox->value();
    h_b[0]=ui->hb0DoubleSpinBox->value();
    h_b[1]=ui->hb1DoubleSpinBox->value();
    h_b[2]=ui->hb2DoubleSpinBox->value();
    s_f[0]=ui->sf0DoubleSpinBox->value();
    s_f[1]=ui->sf1DoubleSpinBox->value();
    s_f[2]=ui->sf2DoubleSpinBox->value();
    s_b[0]=ui->sb0DoubleSpinBox->value();
    s_b[1]=ui->sb1DoubleSpinBox->value();
    s_b[2]=ui->sb2DoubleSpinBox->value();
    v_f[0]=ui->vf0DoubleSpinBox->value();
    v_f[1]=ui->vf1DoubleSpinBox->value();
    v_f[2]=ui->vf2DoubleSpinBox->value();
    v_b[0]=ui->vb0DoubleSpinBox->value();
    v_b[1]=ui->vb1DoubleSpinBox->value();
    v_b[2]=ui->vb2DoubleSpinBox->value();
    emit sendData(h_f, h_b, s_f, s_b, v_f, v_b);
}

