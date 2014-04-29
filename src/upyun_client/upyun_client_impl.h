#ifndef UPYUN_CLIENT_IMPL_H
#define UPYUN_CLIENT_IMPL_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class UpyunClientPrivate : public QObject
{
    Q_OBJECT
public:
    explicit UpyunClientPrivate(const QString &usr, const QString &pass, const QString &bucket,
                               QObject *parent = 0);
signals:
    void error(const QString &info);

public slots:
    QNetworkReply *uploadFile(const QString &local_path, const QString &remote_path);
    QNetworkReply *downloadFile(const QString &remote_path);

    QNetworkReply *removeFile(const QString &remote_path);
    QNetworkReply *makeDir(const QString &remote_path);
    QNetworkReply *removeDir(const QString &remote_path);
    QNetworkReply *listDir(const QString &remote_path);

    QNetworkReply *getBucketInfo();
    QNetworkReply *getFileInfo(const QString &remote_path);

private:
    QString _usr;
    QString _pwd;
    QString _bucket;

    QNetworkAccessManager _qnam;

};


#endif // UPYUN_CLIENT_IMPL_H
