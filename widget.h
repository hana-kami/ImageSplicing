#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void Openimg();
    ~Widget();
QImage ImgOverlay(const QImage& baseImage, const QImage& overlayImage);
private slots:
void on_close_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
