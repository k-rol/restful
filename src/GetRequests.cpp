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
	QString toSendRawHeader;
	QString toSendContentLength;
	QString toSendhttpStatusCode;
	QString hexCode;
	QString hexText;
	if(reply) {
		if (reply->error() == QNetworkReply::NoError) {
			const int available = reply->bytesAvailable();
			if(available > 0) {
				const QByteArray buffer(reply->readAll());
				response = buffer;

				hexCode = hexSortCode(buffer.toHex());
				hexText = hexCodeToText(buffer.toHex());



				//reads rawheader
				QList<QByteArray> headerList = reply->rawHeaderList();
				foreach(QByteArray head, headerList) {
					//qDebug() << head << ":\t" << reply->rawHeader(head);
					QString stringHead(head);
					QString stringRawHead( reply->rawHeader(head));
					toSendRawHeader += QString("\n\r %1 : %2").arg(stringHead, stringRawHead);
				}
				qDebug() << toSendRawHeader;

				//reads knownheader
				//QNetworkRequest::KnownHeaders knownheader = QNetworkRequest::ContentLengthHeader;
				QVariant contentType = reply->header(QNetworkRequest::ContentTypeHeader);
				QVariant contentLength = reply->header(QNetworkRequest::ContentLengthHeader);
				QVariant httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

				qDebug() << "KNOWN HEADER";
				//qDebug() << contentType.value<QString>();
				//qDebug() << contentLength.value<QString>();
				//qDebug() << httpStatusCode.value<QString>();

				toSendContentLength = contentLength.value<QString>();
				toSendhttpStatusCode = httpStatusCode.value<QString>();

				qDebug() << toSendContentLength;
				qDebug() << toSendhttpStatusCode;

			}

		} else {
            response =  tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
            qDebug() << response;
        }

		reply->deleteLater();
	}

	//qDebug() << response;
    emit getReceived(response, toSendRawHeader, toSendhttpStatusCode, toSendContentLength, hexCode, hexText);
}


QString GetRequests::hexCodeToText(const QByteArray &hexCode)
{
	QByteArray hexArray = QByteArray::fromHex(hexCode);
	QString hexAscii;

/*	for (int i = 0; i < hexArray.count(); i+=2) {
		if(i % 16 == 0) {
			hexAscii += "\n";
		}
		QByteArray hexdouble = QString("0A").toAscii().toHex();

		if (1 == 2){
			qDebug() << "YES";
			if (hexArray.data()[i+1] == 'A') {
				hexAscii += ".";
			} else {
				hexAscii += hexArray.data()[i];
				hexAscii += hexArray.data()[i+1];
			}

		} else {
			hexAscii += hexArray.data()[i];
			hexAscii += hexArray.data()[i+1];
		}

	}
*/
	/*QString hexString;
	for (int i = 0; i < hexCode.count(); i+=2) {
		QString hexDouble;
		hexDouble = hexCode.data()[i] + hexCode.data()[i+1];
		if (hexDouble == "0A"){
			hexString += ".";//Hex = 2E
		}else {
			hexString += hexCode.data()[i];
			hexString += hexCode.data()[i+1];
		}

	}*/

	for (int i = 0; i < hexArray.count(); i++) {


	}

	qDebug() << "FROM HEX";
	qDebug() << hexString;
	return "";
}

QString GetRequests::hexSortCode(const QByteArray &hexCode)
{
	int hexNum;

	QString hexString;
	for (int i = 0; i < hexCode.count(); i+=2) {
		if(i % 32 == 0) {
			hexString += "\n";
		}

//		try {
//			qDebug() << "hexNUM:";
//			hexNum = hexCode.data()[i];
//			qDebug() << hexNum;
//		} catch (int e) {
//			qDebug() << "NOP!";
//		}

		hexString += hexCode.data()[i];
		hexString += hexCode.data()[i+1];
		hexString += " ";

	}
	qDebug() <<"hexString:";
	qDebug() << hexString;

	//QString hexAscii
	return hexString.toUpper();
}


GetRequests::~GetRequests() {
	// TODO Auto-generated destructor stub
}

