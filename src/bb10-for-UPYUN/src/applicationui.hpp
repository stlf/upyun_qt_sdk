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

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
 #include <QSharedPointer>

namespace bb
{
    namespace cascades
    {
        class Application;
        class LocaleHandler;
    }
}

class QTranslator;

/*!
 * @brief Application object
 *
 *
 */
class UpyunUser;
class QDBI;
class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    QVariant get_userinfo();

    Q_INVOKABLE bool signin();
    Q_INVOKABLE bool login(const QString &bucket, const QString &user, const QString &pass);

    Q_INVOKABLE QString pwd();

    Q_INVOKABLE QString parentDir();

    Q_INVOKABLE QString gotoParentDir();

    Q_INVOKABLE void cd(const QString& dir);

    Q_INVOKABLE bool uploadFile(const QString &local_path);

    Q_INVOKABLE bool downloadFile(const QString &file_name);

    Q_INVOKABLE bool  removeFile(const QString &file_name);

    Q_INVOKABLE bool  makeDir(const QString &dir_name);

    Q_INVOKABLE bool  removeDir(const QString &dir_name);

    Q_INVOKABLE QVariant listDir();

    Q_INVOKABLE QVariant getFileInfo(const QString &file_name);


    virtual ~ApplicationUI() { }
private slots:
    void onSystemLanguageChanged();
    // Q_INVOKABLE login

private:
    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;

    QSharedPointer<UpyunUser> _upyun;
    QSharedPointer<QDBI> _spdbi;
};

#endif /* ApplicationUI_HPP_ */
