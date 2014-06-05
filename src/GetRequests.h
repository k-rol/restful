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
	void getReceived(const QString &response, const QString &toSendRawHeader, const QString &toSendhttpStatusCode, const QString &toSendContentLength);

private:
    QNetworkAccessManager* m_networkAccessManager;
};

#endif /* GETREQUESTS_H_ */
