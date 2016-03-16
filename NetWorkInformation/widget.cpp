#include "widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    hostLabel = new QLabel(tr("主机name:"));               //控件定义
    LineEditLocalHostName = new QLineEdit;
    ipLabel = new QLabel(tr("IP地址"));
    LineEditAddress = new QLineEdit;
    detailBtn = new QPushButton(tr("详细"));
    mainLayout = new QGridLayout(this);

    mainLayout->addWidget(hostLabel,0,0);               //控件布局
    mainLayout->addWidget(LineEditLocalHostName,0,1);
    mainLayout->addWidget(ipLabel,1,0);
    mainLayout->addWidget(LineEditAddress,1,1);
    mainLayout->addWidget(detailBtn,2,0,1,2);


    setWindowTitle("getHostInfo");

    resize(300,300);

    getHostInformation();
    connect(detailBtn,SIGNAL(clicked()),this,SLOT(sloteDetail()));

}

Widget::~Widget()
{

}


void Widget::getHostInformation()
{
    QString localHostname = QHostInfo::localHostName();
    LineEditLocalHostName->setText(localHostname);

    QHostInfo hostInfo = QHostInfo::fromName(localHostname);

    /*//获取ip地址列表
    QList<QHostAddress> listAddress = hostInfo.addresses();

    qDebug() << listAddress.first().toString() << endl;

    if(!listAddress.isEmpty())
    {

        LineEditAddress->setText(listAddress.first().toString());

    }*/
    //以下这段网上解决获取主机ip地址并且转换为十进制的ip地址
    QList<QNetworkInterface> interfaceipList = QNetworkInterface ::allInterfaces();//返回所有找到的主机接口清单

    for(int i=0;i<interfaceipList.length();i++)
    {
        if(interfaceipList[i].isValid())//如果包含网络接口有效信息就返回真
            foreach (QNetworkAddressEntry addressE, interfaceipList[i].addressEntries())
            {
                if(addressE.ip().protocol() == QAbstractSocket::IPv4Protocol&&addressE.broadcast()!=QHostAddress::Null)
                {
                    LineEditAddress->setText(addressE.ip().toString());
                    qDebug()<<addressE.ip().toString();
                }
            }
    }

}

void Widget::sloteDetail()
{
    QString detail = "";

    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();

    for(int i = 0; i < list.count() ;i++)
    {
        QNetworkInterface interface = list.at(i);

        detail = detail + tr("设备:") + interface.name()+"\n";

        detail = detail + tr("硬件设备:") + interface.hardwareAddress() + "\n";

        QList<QNetworkAddressEntry> entryList = interface.addressEntries();

        for(int j = 0;j < entryList.count(); j++)
        {
            QNetworkAddressEntry entry = entryList.at(j);

            detail = detail + "\t" + tr("IP 地址:") + entry.ip().toString() + "\n";

            detail = detail + "\t" + tr("子网掩码:") + entry.netmask().toString() + "\n";

            detail = detail + "\t" + tr("广播地址")  + entry.broadcast().toString() + "\n";

        }
    }
    QMessageBox::information(this,tr("Detail"),detail);
}
