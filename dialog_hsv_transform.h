#ifndef DIALOG_HSV_TRANSFORM_H
#define DIALOG_HSV_TRANSFORM_H

#include <QDialog>

namespace Ui {
class DialogHsvTransform;
}

class DialogHsvTransform : public QDialog
{
    Q_OBJECT

public:
    explicit DialogHsvTransform(QWidget *parent = 0);
    ~DialogHsvTransform();

private:
    Ui::DialogHsvTransform *ui;

signals:
    void sendData(double*, double*, double*, double*, double*, double*);

private slots:
    void on_buttonBox_accepted();
};

#endif // DIALOG_HSV_TRANSFORM_H

