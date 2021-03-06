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
    QString date;
};

class UpyunClientPrivate;
class QNetworkReply;

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

    QString getBucketUsage();
    upyun_file_info getFileInfo(const QString &remote_path);


signals:
    void notifyStop();
    void progress(qint64 bytesFinished, qint64 bytesTotal);

protected:
    Q_DECLARE_PRIVATE(UpyunClient)
    UpyunClientPrivate* d_ptr;


};

#include <QStringList>
#include <QDebug>
#include <QUrl>
class UpyunUser : public UpyunClient
{
    Q_OBJECT
public:
    UpyunUser(const QString &usr, const QString &pass, const QString &bucket):
        UpyunClient(usr, pass, bucket), _cur_dir("")
    {

    }

    QString pwd()
    {
        if(_cur_dir == "")
            return "/";
        return _cur_dir;
    }

    QString parentDir()
    {
        if("" == pwd())
            return "";
        QString dir = _cur_dir;
        dir.remove(_cur_dir.lastIndexOf("/"), _cur_dir.length() - _cur_dir.lastIndexOf("/"));

        return dir;
    }

    QString gotoParentDir()
    {
        _cur_dir = parentDir();
        return _cur_dir;
    }

    void cd(const QString& dir)
    {
        foreach(upyun_file_info fi, listDir())
        {
            if(fi.type == "F")
            {
                if(fi.name == dir)
                {
                    _cur_dir += "/" + dir;
                }
            }
        }
    }

    void uploadFile(const QString &local_path)
    {
        const QStringList &sl = local_path.split("/");
        if(sl.size())
        {
            QString fn = sl[sl.size() - 1];
            qDebug() << _cur_dir + "/" + fn;
            UpyunClient::uploadFile(local_path, QUrl::toPercentEncoding(_cur_dir + "/" + fn));
        }
        else
        {
            throw QString("local path is not available");
        }
    }

    QByteArray downloadFile(const QString &file_name)
    {
        return UpyunClient::downloadFile( QUrl::toPercentEncoding(_cur_dir +  "/" + file_name) );
    }

    void removeFile(const QString &file_name)
    {
        UpyunClient::removeFile( QUrl::toPercentEncoding(_cur_dir + "/" + file_name) );
    }

    void makeDir(const QString &dir_name)
    {
        UpyunClient::makeDir( QUrl::toPercentEncoding(_cur_dir + "/" + dir_name) );
    }

    void removeDir(const QString &dir_name)
    {
        UpyunClient::removeDir( QUrl(_cur_dir + "/" + dir_name).toEncoded() );
    }

    QList<upyun_file_info> listDir()
    {
        return UpyunClient::listDir( QUrl::toPercentEncoding(_cur_dir) );
    }

    upyun_file_info getFileInfo(const QString &file_name)
    {
        return UpyunClient::getFileInfo( QUrl::toPercentEncoding(_cur_dir + "/" + file_name) );
    }

private:
    QString _cur_dir;

};

#endif // UPYUN_CLIENT_H
