/*
 * Copyright (c) 2011-2014 stlf@live.cn.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/system/InvokeManager>
#include <bb/system/InvokeTargetReply>
#include <QDateTime>
#include "upyun_client.h"

using namespace bb::cascades;

#include <QtSql/QtSql>
#include <QDebug>

#include <bb/data/SqlDataAccess>
#include <bb/data/DataAccessError>
#include <QtSql/QtSql>
#include <stdexcept>
#include <time.h>
#include <bb/system/SystemDialog>

using namespace bb::cascades;

using namespace bb::data;
using namespace bb::system;

class QDBI
{
public:
	const static int DB_LOCK_TIMEOUT = 1222;

    bool init(const QString &type, const QString &dbhost, const QString &dbn,
        const QString &user, const QString &pass)
    {

       // QCoreApplication::addLibraryPath("./");

       qDebug() << "Available drivers:";
       QStringList drivers = QSqlDatabase::drivers();
       foreach(QString driver, drivers)
           qDebug() << "\t" << driver;


       QString dbnn = dbn;
       dbnn += QString::number(clock());
       db = QSqlDatabase::addDatabase(type, dbnn/*, dbn*/);

       db.setHostName(dbhost);

//       QString dsn = QString::fromLocal8Bit(
//                   "DRIVER={SQL SERVER};SERVER=%1;DATABASE=%2").arg(dbhost).arg(dbn);

       db.setDatabaseName(dbn);


       db.setUserName(user);
       db.setPassword(pass);

       bool isopen = db.open();

       return isopen;

    }


    Q_INVOKABLE QVariant exesql(const QString &sql_str)
    {
        if (!db.isOpen())
        {
            db.open();
            if(!db.isOpen())
            {
            	throw std::logic_error(
            			QString(QString(Q_FUNC_INFO) + "if(!db.isOpen())").toStdString()
            			);
            }
        }

        QSqlQuery query(db);
        query.setForwardOnly(true);

        QString sql = sql_str;

        qDebug() << "***query.exec:" << sql;

        bool b = query.exec(sql);

        if(!b)
        {

            QSqlError lastError = query.lastError();

            QString err_text = "sql exe error:";
            err_text += lastError.databaseText() + " " + QString::number(lastError.number());

            err_text += " ";

            std::string rt = err_text.toStdString();

            if(err_text.count(QString::fromLocal8Bit("通讯链接失败")) >= 0)
                    db.close();

            if(DB_LOCK_TIMEOUT == lastError.number()) // 锁超时
            {
                db.close();
                return exesql(sql_str);

            }


            throw std::logic_error(rt);
        }

        QSqlRecord rec = query.record();
        int count = rec.count();

        QList<QVariant> sd;

        while (query.next()) {

        	QMap<QString, QVariant> sr;
            for (int i = 0; i != count; ++i)
            {
                 QString field_name = rec.field(i).name();
                 QString value = query.value(i).toString();

                 sr[field_name] = value;

            }

            sd.push_back(sr);

        }

        query.finish();

        return QVariant::fromValue(sd);
    }

    QSqlDatabase db;
};

void alert(const QString &message)
{
    SystemDialog *dialog; // SystemDialog uses the BB10 native dialog.
    dialog = new SystemDialog("OK", 0); // New dialog with on 'Ok' button, no 'Cancel' button
    dialog->setTitle("Alert"); // set a title for the message
    dialog->setBody(message); // set the message itself
    dialog->setDismissAutomatically(true); // Hides the dialog when a button is pressed.

    // Setup slot to mark the dialog for deletion in the next event loop after the dialog has been accepted.
    bool ok = QObject::connect(dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), dialog, SLOT(deleteLater()));
    Q_ASSERT(ok);
    dialog->show();
}

const QString DB_PATH = "./data/db.db";
ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
        QObject(app), _spdbi(new QDBI)
{

    if(!_spdbi->init("QSQLITE", "", DB_PATH, "", ""))
    {
    	alert(QString(Q_FUNC_INFO)+ ":if(!_spdbi->init");
    }
    else{

    	try{
    		QVariant sd =
    				_spdbi->exesql("SELECT name FROM sqlite_master WHERE type='table' AND name='login_info'");

			if(!sd.toList().size())
			{
				QString sql = "CREATE TABLE login_info "
										  "  (ID INTEGER PRIMARY KEY AUTOINCREMENT, "
										  "  user VARCHAR, "
										  "  pass VARCHAR);";
				sd = _spdbi->exesql(sql);

			}
    	}
    	catch(const std::exception &e)
    	{
    		alert(QString(e.what()));
    	}
    }



    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    // This is only available in Debug builds
    Q_ASSERT(res);
    // Since the variable is not used in the app, this is added to avoid a
    // compiler warning
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    qml->setContextProperty("_app", this);
    // Set created root object as the application scene
    app->setScene(root);



}

QVariant ApplicationUI::get_userinfo()
{
    QVariant v;

    return v;

}



bool ApplicationUI::signin()
{
    InvokeManager* invokeManager = new InvokeManager();
    InvokeRequest cardRequest;
    cardRequest.setTarget("sys.browser");
    cardRequest.setAction("bb.action.VIEW");
    cardRequest.setUri("https://www.upyun.com/cp/#/register/");
    InvokeTargetReply* reply = invokeManager->invoke(cardRequest);
    reply->setParent(this);
    return true;
}

bool ApplicationUI::login(const QString &bucket, const QString &user, const QString &pass)
{
    _upyun = QSharedPointer<UpyunUser>(new UpyunUser(user, pass, bucket));

    try{
        _upyun->getBucketUsage();
    }catch(const QString &e)
    {
        alert("Login failed!");
        return false;
    }
    return true;
}

QString ApplicationUI::pwd()
{
    return _upyun->pwd();
}

QString ApplicationUI::parentDir()
{
    return _upyun->parentDir();
}

QString ApplicationUI::gotoParentDir()
{
    return _upyun->gotoParentDir();
}

void ApplicationUI::cd(const QString &dir)
{
    try{
        _upyun->cd(dir);
    }
    catch(const QString &e)
    {
        alert(e);
    }
}

bool ApplicationUI::uploadFile(const QString &local_path)
{
    try{
        _upyun->uploadFile(local_path);
    }
    catch(const QString &e)
    {
        alert(e);
        return false;
    }

    return true;
}


const QString DOWN_LOAD_PATH = "shared/downloads";
bool ApplicationUI::downloadFile(const QString &file_name)
{
    try{
        const QByteArray &buf = _upyun->downloadFile(file_name);
        QFile f(DOWN_LOAD_PATH + "/" + file_name);
        if(!f.open(QIODevice::WriteOnly))
            throw QString("can not open ") + file_name;
        f.write(buf);

    }
    catch(const QString &e)
    {
        alert(e);
        return false;
    }

    return true;
}

bool ApplicationUI::removeFile(const QString &file_name)
{
    try{
        _upyun->removeFile(file_name);
    }
    catch(const QString &e)
    {
        alert(e);
        return false;
    }
    return true;
}

bool ApplicationUI::makeDir(const QString &dir_name)
{
    try{
        _upyun->makeDir(dir_name);
    }
    catch(const QString &e)
    {
        alert(e);
        return false;
    }

    return true;
}

bool ApplicationUI::removeDir(const QString &dir_name)
{
    try{
        _upyun->removeDir(dir_name);
    }
    catch(const QString &e)
    {
        alert(e);
        return false;
    }

    return true;
}

QVariant ApplicationUI::listDir()
{
    QVariant v = QVariant::fromValue(QVariantMap());
    try{
       const QList<upyun_file_info>&l = _upyun->listDir();

       QVariantList list;
       foreach (upyun_file_info i, l)
       {
            QVariantMap item;
            item.insert("name", i.name);
            item.insert("type", i.type);
            QString sf;
            if(i.size != "0"){
                sf = QString::number(i.size.toInt() / 1000.0f) + "KB";
            }else{
                sf = "";
            }
            item.insert("size", sf);
            item.insert("date", QDateTime::fromTime_t(i.date.toInt()).toString());
            list.append(item);
       }

       qDebug() << list;
       v = QVariant::fromValue(list);
    }
    catch(const QString &e)
    {
        alert(e);
    }
    return v;
}

QVariant ApplicationUI::getFileInfo(const QString &file_name)
{
    QVariant v;
    try{
       const upyun_file_info &l =  _upyun->getFileInfo(file_name);
    }
    catch(const QString &e)
    {
        alert(e);
    }
    return v;
}


void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("bb10_for_UPYUN_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}
