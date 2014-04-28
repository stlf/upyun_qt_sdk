#include <time.h>
#include <QUrlQuery>
#include <QCryptographicHash>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QFile>
#include <string>
#include "upyun_client_impl.h"

const static QString upyun_api_host = "https://v0.api.upyun.com";

std::string rfc1123_datetime( time_t time )
{
    struct tm * timeinfo;
    char buffer [80];

    timeinfo = gmtime ( &time );
    strftime (buffer,80,"%a, %d %b %Y %H:%M:%S GMT",timeinfo);

    return buffer;
}

QString get_sign(const QString &method, const QString &path_url, const QString &now_time,
                        const QString &content_len, const QString &pwd)
{
    QString linkstr = method + "&" + path_url + "&" +
            now_time + "&" + content_len;

    QString pwd_hash = QCryptographicHash::hash(pwd.toUtf8(), QCryptographicHash::Md5).toHex();

    linkstr += "&" + pwd_hash;

    return QCryptographicHash::hash(linkstr.toUtf8(), QCryptographicHash::Md5).toHex();
}

QString get_auth_string(const QString &usr, const QString &sign)
{
    QString auth =  "UpYun " + usr +":";
    auth.append(sign);
    return auth;
}

//QNetworkReplyHelper::QNetworkReplyHelper(QNetworkReply *parent):QObject(parent),_parent(parent)
//{
//    connect(_parent, SIGNAL(error), this, SLOT(_error));
//}


upyun_client_impl::upyun_client_impl(const QString &usr, const QString &pass, const QString &bucket,
                                     QObject *parent) :
    _usr(usr), _pwd(pass), _bucket(bucket), QObject(parent)
{

}

QNetworkReply* upyun_client_impl::uploadFile(const QString &local_path,
                                             const QString &remote_path)
{
    // read file
    QFile file(local_path);
    if (!file.open(QIODevice::ReadOnly))
    {
        error("can not open or read file:" + local_path);
    }

    const QByteArray &file_data = file.readAll();

    QString content_len = QString::number(file_data.length());
    QString path_url =  "/" + _bucket + "/" + remote_path;
    QString now_time =  rfc1123_datetime(time(NULL)).c_str();

    QString auth = get_auth_string(_usr,
                                   get_sign("PUT", path_url, now_time, content_len, _pwd));

    QUrl url = upyun_api_host + path_url;

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", auth.toLatin1());
    request.setRawHeader("Content-Length", content_len.toLatin1());
    request.setRawHeader("Date", now_time.toLatin1());
    request.setRawHeader("mkdir","true");

    QNetworkReply *reply = _qnam.put(request, file_data);


    // in vs2012, use lambda express can not compile function with nest type parameter, :(,
    // so walk around use QNetworkReplyHelper!
    //    connect(_reply, &QNetworkReply::error, [=]( QNetworkReply::NetworkError code ){
    //    });

//    QNetworkReplyHelper *pnh = new QNetworkReplyHelper(reply);
//    connect(pnh, &QNetworkReplyHelper::error, this, &upyun_client_impl::error);

//    connect(reply, &QNetworkReply::uploadProgress, this, &upyun_client_impl::uploadProgress);
//    connect(reply, &QNetworkReply::finished, this, &upyun_client_impl::finished);


    return reply;

}

QNetworkReply* upyun_client_impl::downloadFile(const QString &remote_path)
{
    QString path_url =  "/" + _bucket + "/" + remote_path;
    QString now_time =  rfc1123_datetime(time(NULL)).c_str();
    QString auth = get_auth_string(_usr,
                                   get_sign("GET", path_url, now_time, 0, _pwd));
    QUrl url = upyun_api_host + path_url;

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", auth.toLatin1());
    request.setRawHeader("Date", now_time.toLatin1());

    QNetworkReply *reply = _qnam.get(request);

//    QNetworkReplyHelper *pnh = new QNetworkReplyHelper(reply);
//    connect(pnh, &QNetworkReplyHelper::error, this, &upyun_client_impl::error);
//    connect(reply, &QNetworkReply::downloadProgress, this, &upyun_client_impl::downloadProgress);
//    connect(reply, &QNetworkReply::finished, this, &upyun_client_impl::finished);

    return reply;
}

QNetworkReply *upyun_client_impl::removeFile(const QString &remote_path)
{
    QString path_url =  "/" + _bucket + "/" + remote_path;
    QString now_time =  rfc1123_datetime(time(NULL)).c_str();
    QString auth = get_auth_string(_usr,
                                   get_sign("DELETE", path_url, now_time,
                                            0, _pwd));

    QUrl url = upyun_api_host + path_url;

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", auth.toLatin1());
    request.setRawHeader("Date", now_time.toLatin1());
    request.setRawHeader("mkdir","true");

    QNetworkReply *reply = _qnam.deleteResource(request);

    return reply;
}

QNetworkReply *upyun_client_impl::makeDir(const QString &remote_path)
{
    QString path_url =  "/" + _bucket + "/" + remote_path;
    QString now_time =  rfc1123_datetime(time(NULL)).c_str();
    QString auth = get_auth_string(_usr,
                                   get_sign("POST", path_url, now_time,
                                            0, _pwd));

    QUrl url = upyun_api_host + path_url;

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", auth.toLatin1());
    request.setRawHeader("Date", now_time.toLatin1());
    request.setRawHeader("Folder", "create");

    QNetworkReply *reply = _qnam.post(request,"");

    return reply;
}

QNetworkReply *upyun_client_impl::removeDir(const QString &remote_path)
{
    QString path_url =  "/" + _bucket + "/" + remote_path;
    QString now_time =  rfc1123_datetime(time(NULL)).c_str();
    QString auth = get_auth_string(_usr,
                                   get_sign("DELETE", path_url, now_time,
                                            0, _pwd));

    QUrl url = upyun_api_host + path_url;

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", auth.toLatin1());
    request.setRawHeader("Date", now_time.toLatin1());

    QNetworkReply *reply = _qnam.deleteResource(request);

    return reply;
}

QNetworkReply *upyun_client_impl::listDir(const QString &remote_path)
{
    QString path_url =  "/" + _bucket + "/" + remote_path;
    QString now_time =  rfc1123_datetime(time(NULL)).c_str();
    QString auth = get_auth_string(_usr,
                                   get_sign("GET", path_url, now_time,
                                            0, _pwd));

    QUrl url = upyun_api_host + path_url;

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", auth.toLatin1());
    request.setRawHeader("Date", now_time.toLatin1());

    QNetworkReply *reply = _qnam.get(request);

    return reply;
}

QNetworkReply *upyun_client_impl::getBucketInfo()
{
    QString path_url =  "/" + _bucket + "/?usage";
    QString now_time =  rfc1123_datetime(time(NULL)).c_str();
    QString auth = get_auth_string(_usr,
                                   get_sign("GET", path_url, now_time,
                                            0, _pwd));

    QUrl url = upyun_api_host + path_url;

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", auth.toLatin1());
    request.setRawHeader("Date", now_time.toLatin1());

    QNetworkReply *reply = _qnam.get(request);

    return reply;
}

QNetworkReply *upyun_client_impl::getFileInfo(const QString &remote_path)
{
    QString path_url =  "/" + _bucket + "/" + remote_path;
    QString now_time =  rfc1123_datetime(time(NULL)).c_str();
    QString auth = get_auth_string(_usr,
                                   get_sign("HEAD", path_url, now_time,
                                            0, _pwd));

    QUrl url = upyun_api_host + path_url;

    QNetworkRequest request(url);
    request.setRawHeader("Authorization", auth.toLatin1());
    request.setRawHeader("Date", now_time.toLatin1());

    QNetworkReply *reply = _qnam.head(request);

    return reply;
}

