#include "mainmodel.h"

MainModel::MainModel(QObject *parent) : QObject(parent)
{

}

QString MainModel::value()
{
    return m_value;
}

void MainModel::openDevices()
{
    BcDevice::Instance()->openFromSerialNum("497713873933", 115200);
}

void MainModel::closeDevices()
{
    BcDevice::Instance()->close();
}

void MainModel::getNewData(QString value)
{
    m_value = value;
    emit valueChanged();
}


