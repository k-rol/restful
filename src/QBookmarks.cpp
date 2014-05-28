/*
 * QBookmarks.cpp
 *
 *  Created on: 2014-05-22
 *      Author: cauellet
 */

#include "QBookmarks.h"
#include <QSettings>
#include <QList>
#include <QDebug>
#include <QMap>

QBookmarks::QBookmarks(QObject* parent)
	: QObject(parent) {

	emit copyGetLink("test");
	qDebug() << "yup, the fuck should be here...";
}

void QBookmarks::callsignalGetLink(const QString &linke)
{
	qDebug() << "QBookmarks callsignalGetLink";
	qDebug() << linke;
	this->deleteLater();
	emit copyGetLink("hyg");
	qDebug() << "emit copyGetLink(hyg);";
}

QList<QVariantMap> QBookmarks::getBookmarks()
{
	QList<QVariantMap> maplist;// = new QList<QVariantMap>;
	QSettings settings(this);
	int setSize = settings.beginReadArray("bookmarks");

	for (int i = 0; i < setSize; ++i) {
		settings.setArrayIndex(i);
		qDebug() << "getBookmarks: !!!";

		QVariantMap map;

		QString link = settings.value("bookmarks").toMap().value("link").value<QString>();
		QString name = settings.value("bookmarks").toMap().value("name").value<QString>();

		qDebug() << name;
		qDebug() << link;

	    map.insert("name", name);
		map.insert("link", link);

		maplist << map;

		//qDebug() << settings.value("bookmarks");
		//maplist.append(settings.value("bookmarks"));
		//qDebug() << maplist.value<QVariantMap>().value("link");
	    //vmap.insert("name", settings.value("bookmarks"));
		//vmap.insert("link", settings.value("bookmarks"));
		//vmap["string"] = QVariant("bar");
		//vmap["bool"] = QVariant(true);

		//map.insert(settings.value("bookmarks"));
		//maplist << vmap;
		//qDebug() << maplist.at(i);
	}
	settings.endArray();
	//qDebug() << maplist.at(0);
	//qDebug() << maplist.at(1);
	deleteLater();
	return maplist;

}

void QBookmarks::saveBookmarks(const QList<QVariantMap>* maplist)
{
	QSettings settings(this);
	settings.remove("bookmark");
	settings.beginWriteArray("bookmarks");
	for (int i = 0; i < maplist->size(); ++i) {
		qDebug() << "saveBookmarks:";
		qDebug() << maplist->size();
		settings.setArrayIndex(i);
		qDebug() << maplist->at(i);
		settings.setValue("bookmarks", maplist->at(i));
	}
	//qDebug() << maplist->at(1);
	settings.endArray();
	//settings.sync();
	deleteLater();

}

QString QBookmarks::getSettings(const QString &objectName, const QString &defaultValue) {
        QSettings settings;

        // If no value has been saved, return the default value.
        if (settings.value(objectName).isNull()) {
                return defaultValue;
        }

        // Otherwise, return the value stored in the settings object.
        return settings.value(objectName).toString();
}

void QBookmarks::setSettings(const QString &objectName, const QString &inputValue) {
        // A new value is saved to the application settings object.
        QSettings settings;
        settings.setValue(objectName, QVariant(inputValue));
}

void QBookmarks::syncSettings()
{
	QSettings settings;
	settings.sync();
}

QBookmarks::~QBookmarks() {
	qDebug() << "QBookmark destroyed";
}

