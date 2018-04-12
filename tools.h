#ifndef TOOLS_H
#define TOOLS_H


#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QPainter>
#include <QtMath>


namespace Tools {
QImage RGB2HSV(const QImage &origin, double *h_f, double *h_b, double *s_f, double *s_b, double *v_f, double *v_b);
}




#endif // TOOLS_H
