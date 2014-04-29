#include <QNetworkReply>
#include <QEventLoop>
#include <QFile>

#include "upyun_client.h"
#include "upyun_client_impl.h"

#define HTTP_OK 200
UpyunClient::UpyunClient(const QString &usr, const QString &pass, const QString &bucket):
    d_ptr(new UpyunClientPrivate(usr, pass, bucket, this))
{

}


int waiting_reply(QNetworkReply *reply)
{
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
}

void UpyunClient::uploadFile(const QString &local_path, const QString &remote_path)
{
    QFile file(local_path);
    if (!file.open(QIODevice::ReadOnly))
    {
        throw QString("can not open or read file:" + local_path);
    }

    Q_D(UpyunClient);
    QNetworkReply* reply = d->uploadFile(file.readAll(), remote_path);
    if(HTTP_OK != waiting_reply(reply))
         throw QString(reply->errorString());
}

QByteArray UpyunClient::downloadFile(const QString &remote_path)
{
    Q_D(UpyunClient);
    QNetworkReply* reply = d->downloadFile(remote_path);
    if(HTTP_OK != waiting_reply(reply))
         throw QString(reply->errorString());

    return reply->readAll();

}

void UpyunClient::removeFile(const QString &remote_path)
{
    Q_D(UpyunClient);
    QNetworkReply* reply = d->removeFile(remote_path);
    if(HTTP_OK != waiting_reply(reply))
        throw QString(reply->errorString());
}

void UpyunClient::makeDir(const QString &remote_path)
{
    Q_D(UpyunClient);
    QNetworkReply* reply = d->makeDir(remote_path);
    if(HTTP_OK != waiting_reply(reply))
        throw QString(reply->errorString());
}

void UpyunClient::removeDir(const QString &remote_path)
{
    Q_D(UpyunClient);
    QNetworkReply* reply = d->removeDir(remote_path);
    if(HTTP_OK != waiting_reply(reply))
        throw QString(reply->errorString());
}

QList<upyun_file_info> UpyunClient::listDir(const QString &remote_path)
{
    Q_D(UpyunClient);
    QNetworkReply* reply = d->listDir(remote_path);
    if(HTTP_OK != waiting_reply(reply))
         throw QString(reply->errorString());

    const QString &info = QString::fromUtf8(reply->readAll());

    const QStringList &file_items = info.split("\n");

    QList<upyun_file_info> file_infos;

    foreach(QString file_item, file_items)
    {
        upyun_file_info fi;

        const QStringList &cols = file_item.split("\t");

        if(cols.size() !=  4)
            throw QString("remote dir info can not be parsed!");
        fi.name = cols[0];
        fi.type = cols[1];
        fi.size = cols[2];
        fi.last_modify_date = cols[3];

        file_infos.push_back(fi);
    }

    return file_infos;
}

QString UpyunClient::getBucketInfo()
{
    Q_D(UpyunClient);
    QNetworkReply* reply = d->getBucketInfo();
    if(HTTP_OK != waiting_reply(reply))
         throw QString(reply->errorString());

    return QString::fromUtf8(reply->readAll());
}

//upyun_file_info UpyunClient::getFileInfo(const QString &remote_path)
//{
//    Q_D(UpyunClient);
//    QNetworkReply* reply = d->getFileInfo(remote_path);
//    if(HTTP_OK != waiting_reply(reply))
//        throw QString(reply->errorString());

//    reply->header(QNetworkRequest::ServerHeader);

//}




