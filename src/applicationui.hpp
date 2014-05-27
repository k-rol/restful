/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
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
#include <bb/cascades/GroupDataModel>
#include <bb/system/SystemPrompt>

using namespace bb::cascades;

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

class ApplicationUI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bb::cascades::DataModel* dataModel READ dataModel CONSTANT)

public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI() { }

    Q_INVOKABLE void addObject(const QString &name, const QString &link);

    Q_INVOKABLE void deleteObject(const QVariantList &indexPath);

    Q_INVOKABLE void alert(const QString &message);

    Q_INVOKABLE void promptName(const QString &message, const QString &link);

private:
    void saveObject();

public slots:
    void onPromptFinished(bb::system::SystemUiResult::Type type);

private slots:
    void onSystemLanguageChanged();


private:
    void loadDataFromQSettings();

    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;

    bb::cascades::GroupDataModel* dataModel() const;
    GroupDataModel* m_dataModel;
};

#endif /* ApplicationUI_HPP_ */
