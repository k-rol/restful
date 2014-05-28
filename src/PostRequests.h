/*
 * PostRequests.h
 *
 *  Created on: 2014-05-21
 *      Author: CaroL
 */

#ifndef POSTREQUESTS_H_
#define POSTREQUESTS_H_

#include <QObject>

class PostRequests: public QObject {
	Q_OBJECT
public:
	PostRequests(QObject* parent = 0);

	virtual ~PostRequests();

public Q_SLOTS:
	void tryIt();


Q_SIGNALS:
	void signalToQml(const QString &somestring);
};

#endif /* POSTREQUESTS_H_ */
