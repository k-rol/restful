/*
 * QBookmarks.h
 *
 *  Created on: 2014-05-22
 *      Author: cauellet
 */

#ifndef QBOOKMARKS_H_
#define QBOOKMARKS_H_

#include <QObject>




class QBookmarks:public QObject {
        Q_OBJECT

public:
        QBookmarks(QObject* parent = 0);
        virtual ~QBookmarks();

        QList<QVariantMap> getBookmarks();
        void saveBookmarks(const QList<QVariantMap>* maplist);

        void callsignalGetLink(const QString &linke);

        Q_INVOKABLE
        QString getSettings(const QString &objectName, const QString &defaultValue);

        Q_INVOKABLE
        void setSettings(const QString &objectName, const QString &inputValue);

        Q_INVOKABLE
        void syncSettings();

Q_SIGNALS:
	void copyGetLink(const QString &linke);

};

#endif
