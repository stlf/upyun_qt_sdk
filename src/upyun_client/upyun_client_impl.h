#ifndef UPYUN_CLIENT_IMPL_H
#define UPYUN_CLIENT_IMPL_H

#include <QObject>

class upyun_client_impl : public QObject
{
    Q_OBJECT
public:
    explicit upyun_client_impl(const QString &usr, const QString &pass, QObject *parent = 0);

signals:

public slots:

};

#endif // UPYUN_CLIENT_IMPL_H
