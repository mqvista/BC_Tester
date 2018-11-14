#include "bcdevice.h"

BcDevice::BcDevice(QObject *parent) : QObject(parent)
{
    connect(&m_QSerialPort, &QSerialPort::readyRead, this, &BcDevice::rawSerialReceiveSlot);
}

BcDevice *BcDevice::Instance()
{
    static QMutex mutex;
    static QScopedPointer<BcDevice> instance;
    if (Q_UNLIKELY(!instance)) {
        mutex.lock();
        if (!instance) {
            instance.reset(new BcDevice);
        }
        mutex.unlock();
    }
    return instance.data();
}

void BcDevice::printSerialInfo()
{
    foreach (const QSerialPortInfo &serialPortInfo,  QSerialPortInfo::availablePorts())
    {
        qDebug() << "******";
        qDebug() << serialPortInfo.portName();
        qDebug() << serialPortInfo.manufacturer();
        qDebug() << serialPortInfo.serialNumber();
        qDebug() << "******";
    }

}

void BcDevice::open(QString port, quint32 baud)
{
    m_QSerialPort.setPortName(port);
    if (m_QSerialPort.open(QIODevice::ReadWrite))         //打开端口
    {
        qDebug() << "serial is opened " << endl;
        m_QSerialPort.setBaudRate(baud);
        m_QSerialPort.setDataBits(QSerialPort::Data8);
        m_QSerialPort.setParity(QSerialPort::NoParity);
        m_QSerialPort.setStopBits(QSerialPort::OneStop);
        m_QSerialPort.setFlowControl(QSerialPort::NoFlowControl);
        m_QSerialPort.clearError();
        m_QSerialPort.clear();
    }
    else
    {
        qDebug() << "Open Failed" << m_QSerialPort.errorString();
    }
}

bool BcDevice::openFromSerialNum(QString serialNum, quint32 baud)
{

    foreach (const QSerialPortInfo &serialPortInfo,  QSerialPortInfo::availablePorts())
    {
        qDebug() << "******";
        qDebug() << serialPortInfo.portName();
        qDebug() << serialPortInfo.manufacturer();
        qDebug() << serialPortInfo.serialNumber();
        qDebug() << "******";
        if (serialPortInfo.serialNumber() == serialNum)
        {
            open(serialPortInfo.portName(), baud);
            qDebug() << "GET Serial AND opened";
            return true;
        }
    }
    return false;
}

bool BcDevice::openFromSerialName(QString serialNum, quint32 baud)
{
    foreach (const QSerialPortInfo &serialPortInfo,  QSerialPortInfo::availablePorts())
    {
        qDebug() << "******";
        qDebug() << serialPortInfo.portName();
        qDebug() << serialPortInfo.manufacturer();
        qDebug() << serialPortInfo.serialNumber();
        qDebug() << "******";
        if (serialPortInfo.manufacturer() == serialNum)
        {
            open(serialPortInfo.portName(), baud);
            qDebug() << "GET Serial AND opened";
            return true;
        }
    }
    return false;
}

void BcDevice::close()
{
    if (m_QSerialPort.isOpen())
    {
        m_QSerialPort.close();
        qDebug()<< "Closed";
    }
}

void BcDevice::rawSerialReceiveSlot()
{
    quint16 startLocal;
    QByteArray readAllData = m_QSerialPort.readAll();     //读取收到的数据one Byte

    //static QString receivedata;                         //生成 static QString变量
    m_receivePartData.clear();
    m_receivePartData.append(readAllData.data());             //将QByteArray转为QString，并保存
    for (quint16 i=0; i<m_receivePartData.length(); i++)
    {
        if ((m_receivePartData.at(i) == '\r') && (m_receivePartData.at(i+1) == '\n'))
        {
            startLocal = i + 3;
            break;
        }
    }
    m_receiveData = m_receivePartData.mid(startLocal, m_receivePartData.length()-startLocal-2);
    qDebug() << m_receiveData;
    emit sendNewData(m_receiveData);
}
