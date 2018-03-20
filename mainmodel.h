#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include "bcdevice.h"
#include <QDebug>

class MainModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value NOTIFY valueChanged)
public:
    explicit MainModel(QObject *parent = nullptr);
    QString value();
    Q_INVOKABLE void openDevices();
    Q_INVOKABLE void closeDevices();

signals:
    void valueChanged();

public slots:
    void getNewData(QString value);

private:
    QString m_value;
};

#endif // MAINMODEL_H
