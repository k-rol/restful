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

QBookmarks::QBookmarks(QObject* parent)
 {

}

void QBookmarks::getBookmarks()
{
	qDebug() << "Will it start?";
	QList<QVariantMap> maplist;
	QSettings settings(this);
	int setSize = settings.beginReadArray("bookmarks");
	qDebug() << setSize;
	for (int i = 0; i < setSize; ++i) {
		settings.setArrayIndex(i);
		qDebug() << "getBookmarks: !!!";

		QVariantMap map;

	    map.insert("name", "mocky ");
		map.insert("link", "http://www.mocky.io/v2/537fb5da27a1c45703f807b6");
		//map["string"] = QVariant("bar");
		//map["bool"] = QVariant(true);

		//map = settings.value("bookmarks").toString();
	}
	settings.endArray();
}

void QBookmarks::saveBookmarks(const QList<QVariantMap>* maplist)
{
	QSettings settings(this);
	settings.beginWriteArray("bookmarks");
	for (int i = 0; i < maplist->size(); ++i) {
		qDebug() << "saveBookmarks:";
		settings.setArrayIndex(i);
		qDebug() << maplist->at(i);
		settings.setValue("bookmarks", maplist->at(i));
	}
	settings.endArray();
	settings.sync();

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
	// TODO Auto-generated destructor stub
}

