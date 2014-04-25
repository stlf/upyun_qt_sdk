#ifndef UPYUN_CLIENT_IMPL_H
#define UPYUN_CLIENT_IMPL_H

#include <QObject>
#include <QNetworkAccessManager>

class QNetworkReply;
class upyun_client_impl : public QObject
{
    Q_OBJECT
public:
    explicit upyun_client_impl(const QString &usr, const QString &pass, const QString &bucket,
                               QObject *parent = 0);

signals:
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    void error(const QString &e);
    void finished();

public slots:
    QNetworkReply *uploadFile(const QString &local_path, const QString &remote_path);
    QNetworkReply *downloadFile(const QString &remote_path);

private:
    QString _usr;
    QString _pwd;
    QString _bucket;

    QNetworkAccessManager _qnam;
    QNetworkReply *_reply;

};

#endif // UPYUN_CLIENT_IMPL_H
