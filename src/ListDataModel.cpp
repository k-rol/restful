/*
 * ListDataModel.cpp
 *
 *  Created on: 2014-05-22
 *      Author: cauellet
 */

#include "ListDataModel.h"
#include <bb/system/SystemPrompt>
#include <QDebug>
#include <QBookmarks.h>
#include <PostRequests.h>

using namespace bb::system;
using namespace bb::cascades;

ListDataModel::ListDataModel(QObject* parent)
	: QObject(parent) {

}

GroupDataModel* ListDataModel::dataModel() const
{
    return m_dataModel;
}

void ListDataModel::saveObject()
{
	QVariantList variantList;

	QList<QVariantMap> variantMapList = m_dataModel->toListOfMaps();
	QBookmarks *bookmarks = new QBookmarks();
	bookmarks->saveBookmarks(&variantMapList);


	/*  To see inside the list of maps
	for (int i = 0; i < variantMapList.size(); ++i) {
		QMap<QString, QVariant> myMap = variantMapList[i];
		QMapIterator<QString, QVariant> j(myMap);
		while (j.hasNext()) {
			j.next();
			qDebug() << "myIndex: " << i << " Key: " << j.key()
		<< " Value: " << j.value();
		}
	}*/


}

void ListDataModel::loadDataFromQSettings()
{
    m_dataModel = new GroupDataModel(this);
    m_dataModel->setSortingKeys(QStringList() << "customerID");
    m_dataModel->setGrouping(ItemGrouping::None);
	m_dataModel->setParent(this);
	m_dataModel->clear();

	QBookmarks *bookmarks = new QBookmarks();



	//maplist = new QList<QVariantMap>(bookmarks->getBookmarks());
	m_dataModel->insertList(bookmarks->getBookmarks());

	bookmarks->deleteLater();

/*
    QVariantMap map;
    map.insert("name", "mocky ");
	map.insert("link", "http://www.mocky.io/v2/537fb5da27a1c45703f807b6");

	m_dataModel->insert(map);

    map.insert("name", "mocky2");
	map.insert("link", "http://www.mocky.io/v2/537fb5da27a1c45703f807b6");

    m_dataModel->insert(map);
*/

}

void ListDataModel::addObject(const QString &name, const QString &link)
{

    QVariantMap map;
    map.insert("name", name);
	map.insert("link", link);

	m_dataModel->insert(map);

	//Save current list to QSettings in QBookmarks
	saveObject();

}

void ListDataModel::deleteObject(const QVariantList &indexPath)
{
    bool deleted = false;

	qDebug() << "indexpath:";
	qDebug() << indexPath;
	deleted = m_dataModel->removeAt(indexPath);

	if (deleted)
	{
		saveObject();
	}

//    const QVariantList deleteIndexPath = m_dataModel->find(map);

//    if (deleteIndexPath.isEmpty()) {
//        alert(tr("Object ID not found."));
//    } else {
//        deleted = m_dataModel->removeAt(deleteIndexPath);
//    }

}

//Decomissioned and not useful for now
void ListDataModel::useLink(const QVariantList &indexPath)
{

	qDebug() << "Trying useLink";
	loadDataFromQSettings();
	QString linke = m_dataModel->data(indexPath).toMap().value("link").value<QString>();
	qDebug() << linke;
	emit copyGetLink(linke);

}

void ListDataModel::promptName(const QString &message, const QString &link)
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

void ListDataModel::onPromptFinished(bb::system::SystemUiResult::Type type)
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


ListDataModel::~ListDataModel() {
	qDebug() << "!!!! ListDataModel was destroyed !!!!!";
}

