#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>
#include <QHostInfo>
#include <QNetworkInterface>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);

    void getHostInformation();       //获取主机名
    ~Widget();

private:                             //控件定义
    QLabel *hostLabel;
    QLineEdit *LineEditLocalHostName;
    QLabel *ipLabel;
    QLineEdit *LineEditAddress;
    QPushButton *detailBtn;
    QGridLayout *mainLayout;         //主布局

private slots:
    void sloteDetail();              //详细槽
};

#endif // WIDGET_H
