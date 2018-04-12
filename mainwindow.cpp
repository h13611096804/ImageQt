#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    leftScene = new QGraphicsScene;
    rightScene = new QGraphicsScene;


    size = new QLabel;

    info = NULL;

    leftScene->setBackgroundBrush(QColor::fromRgb(224,224,224));
    ui->leftGraphicsView->setScene(leftScene);
    rightScene->setBackgroundBrush(QColor::fromRgb(224,224,224));
    ui->rightGraphicsView->setScene(rightScene);

    ui->statusBar->addPermanentWidget(size);

    createToolBar();

    setActionStatus(false);
    setWindowTitle("ImageTransform");
}

void MainWindow::createToolBar()
{
    ui->toolBar->addAction(ui->actionOpen);
    ui->toolBar->addAction(ui->actionSave_As);
    ui->toolBar->addAction(ui->actionClose);

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionRGB2HSV);

    ui->toolBar->addSeparator();
}



MainWindow::~MainWindow()
{
    delete ui;

    if (leftScene)
    {
        delete leftScene;
        leftScene = NULL;
    }

    if (size)
    {
        delete size;
        size = NULL;
    }


    //add
    if (rightScene)
    {
        delete leftScene;
        leftScene = NULL;
    }

}

/******************************************************************************
 *                Update right image and repaint right scene
 *****************************************************************************/
void MainWindow::updateRightImage(QPixmap &pixmap)
{

    rightPixmapItem->setPixmap(pixmap);
    rightScene->setSceneRect(QRectF(pixmap.rect()));

       qDebug() << "repaintRightScene"  << rightScene->items().count();
}

/******************************************************************************
 *                      Clean image of both Scene
 *
 *****************************************************************************/
void MainWindow::cleanImage()
{
    leftScene->clear();
    ui->leftGraphicsView->resetTransform();

    rightScene->clear();
    ui->rightGraphicsView->resetTransform();


    if (size)
    {
        delete size;
        size = new QLabel;
        ui->statusBar->addPermanentWidget(size);
    }



    this->setWindowTitle(WINDOW_TITLE);
    setActionStatus(false);
}

void MainWindow::setActionStatus(bool status)
{
    ui->actionSave->setEnabled(status);
    ui->actionClose->setEnabled(status);
    ui->actionSave_As->setEnabled(status);
}


/******************************************************************************
 *                      Open a image file and show it
 ******************************************************************************
 * Args:
 *      QString imagePath: The abslute path of a image
 *****************************************************************************/
void MainWindow::on_actionOpen_triggered()
{
        // Automatically detects the current user's home directory
        // And then wait the user to select one image
        QString imagePath = QFileDialog::getOpenFileName(this, tr("Open image"), getUserPath() + "/Pictures",
                                                 tr("All Files (*);;"
                                                    "All Images (*.bpm *.gif *.jpg *.jpeg *.png *.ppm *.xbm *.xpm);;"
                                                    "Image BPM (*.bpm);;"
                                                    "Image GIF (*.gif);;"
                                                    "Image JPG (*.jpg);;"
                                                    "Image JPEG (*.jpeg);;"
                                                    "Image PNG (*.png);;"
                                                    "Image PPM (*.ppm);;"
                                                    "Image XBM (*.xbm);;"
                                                    "Image XPM (*.xpm);;"));

    if (!imagePath.isEmpty())
    {
        QFile file(imagePath);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr(WINDOW_CRITICAL),
                                  tr("Unable to open image."));
            return;
        }

        // delete previous image
        cleanImage();

        // upload image
        info = new QFileInfo(imagePath);





        QPixmap leftPixmap(imagePath);
        leftPixmapItem = leftScene->addPixmap(leftPixmap);
        leftScene->setSceneRect(QRectF(leftPixmap.rect()));

        QPixmap rightPixmap(imagePath);
        rightPixmapItem = rightScene->addPixmap(rightPixmap);
        rightScene->setSceneRect(QRectF(rightPixmap.rect()));

        qDebug()<<"depth:"<<rightPixmap.depth();
        qDebug()<<"hasAlpha:"<<rightPixmap.hasAlpha();







        // settings
        this->setWindowTitle(info->fileName() + " - ImageQt");

        setActionStatus(true);

        size->setText(QString::number(leftPixmapItem->pixmap().width())
                      + " x " + QString::number(leftPixmapItem->pixmap().height()));



    }
}

/******************************************************************************
 *                      Clean image of both Scene
 *
 *****************************************************************************/
void MainWindow::on_actionClose_triggered()
{
    cleanImage();
}

void MainWindow::on_actionSave_triggered()
{

}

/******************************************************************************
 *                          Action : Save as
 *****************************************************************************/
void MainWindow::on_actionSave_As_triggered()
{

    QString newPath = QFileDialog::getSaveFileName(this, tr("Save image"), QString(),
            tr("All files (*);;"
               "Image BPM (*.bpm);;"
               "Image GIF (*.gif);;"
               "Image JPG (*.jpg);;"
               "Image JPEG (*.jpeg);;"
               "Image PNG (*.png);;"
               "Image PPM (*.ppm);;"
               "Image XBM (*.xbm);;"
               "Image XPM (*.xpm);;"));

    if (!newPath.isEmpty()) {

        QFile file(newPath);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr(WINDOW_CRITICAL), tr("Unable to save image."));
            return;
        }

        //Save image to new path
        rightPixmapItem->pixmap().save(newPath);
//        rightImage->save(newPath);
    }
}

/******************************************************************************
 *                        Exit the program
 *
 *****************************************************************************/
void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}




/******************************************************************************
 *                  Adjust the image size to fit the window
 *
 *****************************************************************************/
void MainWindow::on_actionAdjust_triggered()
{
    // left
    int height = leftPixmapItem->pixmap().height();
    int width = leftPixmapItem->pixmap().width();
    int max_height = ui->leftGraphicsView->height();
    int max_width = ui->leftGraphicsView->width();
    int size,max_size,fact=0;
    double val=0;


    size = qMin(width,height);
    max_size = qMin(max_width,max_height);


    if (size < max_size) {
        while ((size*val) < max_size)
            val = pow(1.2,fact++);
        val = pow(1.2,fact-2);
        ui->leftGraphicsView->setFactor(fact-2);
    }

    else {
        val = 1;
        while ((size*val) > max_size)
            val = pow(1.2,fact--);
        val = pow(1.2,fact+1);
        ui->leftGraphicsView->setFactor(fact+1);
    }

    ui->leftGraphicsView->scale(val,val);


    // right
    height = leftPixmapItem->pixmap().height();
    width = leftPixmapItem->pixmap().width();
    max_height = ui->rightGraphicsView->height();
    max_width = ui->rightGraphicsView->width();
    size = max_size = fact = 0;
    val=0;


    size = qMin(width,height);
    max_size = qMin(max_width,max_height);


    if (size < max_size) {
        while ((size*val) < max_size)
            val = pow(1.2,fact++);
        val = pow(1.2,fact-2);
        ui->rightGraphicsView->setFactor(fact-2);
    }

    else {
        val = 1;
        while ((size*val) > max_size)
            val = pow(1.2,fact--);
        val = pow(1.2,fact+1);
        ui->rightGraphicsView->setFactor(fact+1);
    }

    ui->rightGraphicsView->scale(val,val);


}


/******************************************************************************
 *                           获得当前用户的用户名
 *****************************************************************************/
QString MainWindow::getUserName()
{
    QString userPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString userName = userPath.section("/", -1, -1);
    return userName;
}

/******************************************************************************
 *                              获得当前用户的家目录
 *****************************************************************************/
QString MainWindow::getUserPath()
{
    QString userPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return userPath;
}

void MainWindow::on_actionT_triggered()
{
    QLabel* l = new QLabel;
    if (!rightPixmapItem->pixmap().isNull()) {
        qDebug() << "hello";
        l->setPixmap(rightPixmapItem->pixmap());
        l->show();
    }
}


/*****************************************************************************
 *                                 图像细化
 * **************************************************************************/

void MainWindow::receiveHsvTransformParamter(double *h_f, double *h_b, double *s_f, double *s_b, double *v_f, double *v_b)
{
    //QPixmap rightImage = rightPixmapItem->pixmap();
    QPixmap rightImage = leftPixmapItem->pixmap();
    QImage newImage = Tools::RGB2HSV(rightImage.toImage(),h_f, h_b, s_f, s_b ,v_f ,v_b);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

void MainWindow::on_actionRGB2HSV_triggered()
{
    DialogHsvTransform dialog;
    connect(&dialog, SIGNAL(sendData(double*, double*, double*, double*, double*, double*)),
            this, SLOT(receiveHsvTransformParamter(double*, double*, double*, double*, double*, double*)));
    dialog.exec();
}



