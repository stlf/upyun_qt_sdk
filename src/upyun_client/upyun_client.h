#ifndef UPYUN_CLIENT_H
#define UPYUN_CLIENT_H

#include "upyun_client_global.h"
#include <QObject>
#include <QList>

class /*UPYUN_CLIENTSHARED_EXPORT*/ upyun_file_info
{
public:
    QString name;
    QString type;
    QString size;
    QString last_modify_date;
};

class UpyunClientPrivate;

class /*UPYUN_CLIENTSHARED_EXPORT*/ UpyunClient : public QObject
{
    Q_OBJECT
public:
    UpyunClient(const QString &usr, const QString &pass, const QString &bucket);

    void uploadFile(const QString &local_path, const QString &remote_path);
    QByteArray downloadFile(const QString &remote_path);
    void removeFile(const QString &remote_path);
    void makeDir(const QString &remote_path);
    void removeDir(const QString &remote_path);
    QList<upyun_file_info> listDir(const QString &remote_path);

    QString getBucketInfo();
    // upyun_file_info getFileInfo(const QString &remote_path);

protected:
    Q_DECLARE_PRIVATE(UpyunClient)
    UpyunClientPrivate* d_ptr;

};

#endif // UPYUN_CLIENT_H
