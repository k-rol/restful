/*
 * QBookmarks.cpp
 *
 *  Created on: 2014-05-22
 *      Author: cauellet
 */

#include "QBookmarks.h"
#include <QSettings>
#include

QBookmarks::QBookmarks(QObject* parent)
: QObject(parent) {

}

void QBookmarks::getBookmarks()
{
	QSettings settings(this);
	//settings.setValue()
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

