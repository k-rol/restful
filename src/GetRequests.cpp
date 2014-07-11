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
//#include <stdio.h>
#include <iostream>
//#include <string.h>



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
	//QByteArray hexArray = QByteArray::fromHex(hexCode);
	QString hexAscii;

	const char* hexChar = hexCode.toUpper();
	int length = strlen(hexChar);
	char buf = 0;

	int AsciiLength = length / 2;
	int charsCounter = 0;
	char wholeChars[AsciiLength];

	for(int i = 0; i < length; i++) {
		if(i % 2 != 0) {
		    //int digitChar = hexToLetter(buf,hexChar[i]);
		    int digitChar = hexToAscii(buf,hexChar[i]);


		    if (digitChar <= 10) {
		        wholeChars[charsCounter] = '.';
		    }
		    else {
		        wholeChars[charsCounter] = hexToAscii(buf,hexChar[i]);
            }

            charsCounter++;

		} else {
			buf = hexChar[i];
		}
	}


    for (int i = 0; i < AsciiLength; ++i) {
        hexAscii += wholeChars[i];
    }

	qDebug() << "FROM HEX";
	qDebug() << hexAscii;
	return "";
}

char GetRequests::hexToAscii(char first, char second)
{
char hex[5], *stop;
hex[0] = '0';
hex[1] = 'x';
hex[2] = first;
hex[3] = second;
hex[4] = 0;
return strtol(hex, &stop, 16);
}

int GetRequests::hexToInt(char c)
{
	int first = c / 16 - 3;
	int second = c % 16;
	int result = first*10 + second;
	if (result > 9) result--;
	return result;
}

int GetRequests::hexToLetter(char c, char d)
{
	int high = hexToInt(c) * 16;
	int low = hexToInt(d);
	return high+low;
}

QString GetRequests::hexSortCode(const QByteArray &hexCode)
{


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

