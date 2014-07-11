/*
 * GetRequests.h
 *
 *  Created on: 2014-05-21
 *      Author: CaroL
 */

#ifndef GETREQUESTS_H_
#define GETREQUESTS_H_

#include <QObject>

class QNetworkAccessManager;

class GetRequests : public QObject {
	Q_OBJECT
public:
	GetRequests(QObject* parent = 0);
	virtual ~GetRequests();

public Q_SLOTS:
	void send(const QString &command);

private Q_SLOTS:
	void onGetReply();

Q_SIGNALS:
	void getReceived(const QString &response, const QString &toSendRawHeader, const QString &toSendhttpStatusCode, const QString &toSendContentLength, const QString &hexCode, const QString &hexText);

private:
    QNetworkAccessManager* m_networkAccessManager;
    QString hexCodeToText(const QByteArray &hexCode);
    QString hexSortCode(const QByteArray &hexCode);
    int hexToInt(char c);
    int hexToLetter(char c, char d);
    char hexToAscii(char first, char second);

};

#endif /* GETREQUESTS_H_ */
