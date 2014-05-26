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

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>

#include <bb/system/SystemDialog>
#include <bb/system/SystemPrompt>

#include <QDebug>

//alert
using namespace bb::system;

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
        QObject(app)
{
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


    qml->setContextProperty("_app", this);

    addSavedObject();
    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    app->setScene(root);
}

GroupDataModel* ApplicationUI::dataModel() const
{
    return m_dataModel;
}

void ApplicationUI::addSavedObject()
{
    m_dataModel = new GroupDataModel(this);
    m_dataModel->setSortingKeys(QStringList() << "customerID");
    m_dataModel->setGrouping(ItemGrouping::None);
	m_dataModel->setParent(this);
	m_dataModel->clear();

	//get stuff from QSettings...

	//then
    QVariantMap map;
    map.insert("name", "mocky ");
	map.insert("link", "http://www.mocky.io/v2/537fb5da27a1c45703f807b6");

	m_dataModel->insert(map);

    map.insert("name", "mocky2");
	map.insert("link", "http://www.mocky.io/v2/537fb5da27a1c45703f807b6");

    m_dataModel->insert(map);
}

void ApplicationUI::addObject(const QString &name, const QString &link)
{

    QVariantMap map;
    map.insert("name", name);
	map.insert("link", link);

	m_dataModel->insert(map);

}

void ApplicationUI::deleteObject(const QVariantList &indexPath)
{
    bool deleted = false;
//    bool saved = false;
//
//    if (!validateID(customerID))
//        return false;
//
//    // Create a person object with the required id.
//    // The name can be left out because find() will use the == operator
//    // defined in the Person class. See Person.cpp
//    Person *person = new Person(customerID, QString(), QString());
//
	qDebug() << "indexpath:";
	qDebug() << indexPath;
	deleted = m_dataModel->removeAt(indexPath);

	if (deleted)
	{
		alert(tr("deleted!"));
	}

//    const QVariantList deleteIndexPath = m_dataModel->find(map);

//    if (deleteIndexPath.isEmpty()) {
//        alert(tr("Object ID not found."));
//    } else {
//        deleted = m_dataModel->removeAt(deleteIndexPath);
//    }

}

//void ApplicationUI::refreshObjects()
//{
//    const int objectsReadCount = load();
//
//    if (objectsReadCount == 0) {
//        alert(tr("The customer list is empty."));
//    } else {
//        alert(tr("%1 objects loaded.").arg(objectsReadCount));
//    }
//}

void ApplicationUI::alert(const QString &message)
{
    qDebug() << "alert: " << message;
    SystemDialog *dialog; // SystemDialog uses the BB10 native dialog.
    dialog = new SystemDialog(tr("OK"), 0); // New dialog with on 'Ok' button, no 'Cancel' button
    dialog->setTitle(tr("Alert")); // set a title for the message
    dialog->setBody(message); // set the message itself
    dialog->setDismissAutomatically(true); // Hides the dialog when a button is pressed.

    // Setup slot to mark the dialog for deletion in the next event loop after the dialog has been accepted.
    bool ok = connect(dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), dialog, SLOT(deleteLater()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    dialog->show();
}

void ApplicationUI::promptName(const QString &message, const QString &link)
{
	SystemPrompt *prompt = new SystemPrompt();
	prompt->setTitle(message);
	prompt->setDismissAutomatically(true);
	prompt->inputField()->setEmptyText("Enter a name for your bookmark");
	prompt->setBody(link);

/*
	QLineEdit *lineedit = new QLineEdit(link);
	lineedit->setText(link);
	QSignalMapper *signalMapper = new QSignalMapper(this);
	connect(prompt,SIGNAL(finished(bb::system::SystemUiResult::Type)),signalMapper,SLOT(map()));
	signalMapper->setMapping(lineedit,link);
	connect(signalMapper,SIGNAL(mapped(const QString &)),this, SIGNAL(onPromptFinished(const QString &,bb::system::SystemUiResult::Type)));
*/

	bool success = QObject::connect(prompt,
	         SIGNAL(finished(bb::system::SystemUiResult::Type)),
	         this,
	         SLOT(onPromptFinished(bb::system::SystemUiResult::Type)));

	if (success) {
		prompt->show();
	} else {
        prompt->deleteLater();
    }


}

void ApplicationUI::onPromptFinished(bb::system::SystemUiResult::Type type)
{
	if (type == SystemUiResult::ConfirmButtonSelection) {

		SystemPrompt* prompt = qobject_cast<SystemPrompt*>(sender());
		const QString name = prompt->inputFieldTextEntry();
		const QString link = prompt->body();
		addObject(name, link);

	} else {
		qDebug() << "Saving Cancelled";
	}
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("DoItRestful_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}
