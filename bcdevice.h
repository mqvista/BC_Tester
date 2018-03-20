#ifndef BCDEVICE_H
#define BCDEVICE_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMutex>

class BcDevice : public QObject
{
    Q_OBJECT
public:
    static BcDevice *Instance();
    void printSerialInfo();
    void open(QString port, quint32 baud);
    Q_INVOKABLE bool openFromSerialNum(QString serialNum, quint32 baud);
    void close(void);

signals:
    void sendNewData(QString data);

public slots:
    void rawSerialReceiveSlot();

private:
    explicit BcDevice(QObject *parent = nullptr);
    QSerialPort m_QSerialPort;
    QSerialPortInfo m_QSerialPortInfo;
    QString m_receivePartData;
    QString m_receiveData;

};

#endif // BCDEVICE_H
