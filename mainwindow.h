#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QLabel>
#include <QDebug>
#include <QStandardPaths>
#include <QTranslator>
#include "graphicsview.h"
#include "tools.h"
#include "dialog_hsv_transform.h"


#define WINDOW_TITLE    "HSV CONTROL"
#define WINDOW_CRITICAL "Error - HSV"
#define WINDOW_WARNING  "Notice - HSV"
#define WINDOW_ABOUT    "About - HSV"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateRightImage(QPixmap &pixmap);
    void cleanImage();

    void setActionStatus(bool);
    void createToolBar();
    void createAction();

private slots:

    // 从子对话框中接收数据
    void receiveHsvTransformParamter(double*, double*, double*, double*, double*, double*);

    // On action triggered
    void on_actionOpen_triggered();
    void on_actionClose_triggered();        // Clear both left and right Scene
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();      // Save as
    void on_actionExit_triggered();         // Exit the program


    void on_actionAdjust_triggered();       // Adjust to fit the window size

    void on_actionT_triggered();

    void on_actionRGB2HSV_triggered();


private:
    QAction *finalEx;

    Ui::MainWindow  *ui;
    QGraphicsScene  *leftScene;
    QGraphicsScene  *rightScene;
    QGraphicsPixmapItem* leftPixmapItem;
    QGraphicsPixmapItem* rightPixmapItem;

    QLabel          *size;

    QFileInfo *info;

    QString getUserName();
    QString getUserPath();
};

#endif // MAINWINDOW_H
