#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QPainter>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->coos,&QPushButton::clicked,this,&Widget::Openimg);
}

void Widget::Openimg()
{
    QString Imgfile;
    QString ImgfilePath;
    QImage Img;
    QImage guoqi;
    guoqi.load(":/image/guoqi.jpg");
    Imgfile = QFileDialog::getOpenFileName(this,"请选择图片","","image(*.jpg *.png *.bmp *.pgm *.pbm);");
    if(Imgfile != "")
    {

        if(Img.load(Imgfile))
        {
            QPixmap pixChina(":/image/guoqi.jpg");
            QImage newGuoqi = guoqi.scaled(Img.width(),Img.height());
            QImage imgOverlay = QImage(newGuoqi.size(), QImage::Format_ARGB32_Premultiplied);
            imgOverlay.fill(Qt::transparent);
            QPainter p1(&imgOverlay);
            p1.setCompositionMode(QPainter::CompositionMode_Source);
            p1.drawImage(0, 0, newGuoqi);
            p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            p1.fillRect(newGuoqi.rect(), QColor(0, 0, 0, 200));
            p1.end();

            //QString style1  = " background: qradialgradient(cx:0, cy:0, radius: 1,fx:0.5, fy:0.5, stop:0 white, stop:1 green);" ;
            //ui->labelImg->setPixmap(QPixmap::fromImage(Img));
            QImage ImgResult = ImgOverlay(Img,imgOverlay);//叠加函数
            ImgResult.save("./china.png");
            QString ChinaFile = "./china.png";
            QString style  = "QWidget#labelImg{border-image:url("+ChinaFile+");}";
            ui->labelImg->setStyleSheet(style);

        }
    }
    QFileInfo ImgInfo;
    ImgInfo = QFileInfo(Imgfile);
    ImgfilePath = ImgInfo.filePath();
    ui->lineEdit->setText(ImgfilePath);
}


Widget::~Widget()
{
    delete ui;
}

QImage Widget::ImgOverlay(const QImage &bottomImg, const QImage &topImg)
{
    QImage imgOverlay = QImage(bottomImg.size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&imgOverlay);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(imgOverlay.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, bottomImg);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, topImg);
    painter.end();

    return imgOverlay;
}

void Widget::on_close_clicked()
{
    this->close();
}
