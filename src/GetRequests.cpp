/*
 * GetRequests.cpp
 *
 *  Created on: 2014-05-21
 *      Author: CaroL
 */

#include "GetRequests.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QTimer>
#include <bb/data/JsonDataAccess>
#include <QNetworkCookie>

GetRequests::GetRequests(QObject* parent)
	: QObject(parent)
	, m_networkAccessManager(new QNetworkAccessManager(this))
{
}

void GetRequests::send(const QString &command)
{
	QNetworkRequest request(command);
	QNetworkReply* response = m_networkAccessManager->get(request);

	bool ok = connect(response, SIGNAL(finished()), this,SLOT(onGetReply()));
	Q_ASSERT(ok);
	Q_UNUSED(ok);
}

void GetRequests::onGetReply()
{
	QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
	QString response;

	if(reply) {
		if (reply->error() == QNetworkReply::NoError) {
			const int available = reply->bytesAvailable();
			if(available > 0) {
				const QByteArray buffer(reply->readAll());
				response = buffer;
//				QVariant header = reply->header(QNetworkRequest::CookieHeader);
//				if (header.isValid()) {
//					QList<QNetworkCookie> cookies = header.value<QList<QNetworkCookie> >();
//					foreach (QNetworkCookie cookie, cookies) {
//					qDebug() << "Header:";
//					qDebug() << cookie;
//						}
//				    QList<QNetworkCookie> cookies = header.value<QList<QNetworkCookie> >();
//				    foreach (QNetworkCookie cookie, cookies) {
//				    	qDebug() << "Header:";
//				    	qDebug() << cookie;
//				    }
//				}
				//QByteArray headerraw = reply->rawHeader(QNetworkRequest::);


			}

		} else {
            response =  tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
            qDebug() << response;
        }

		reply->deleteLater();
	}


    emit getReceived(response);
}



GetRequests::~GetRequests() {
	// TODO Auto-generated destructor stub
}

