/*
 * PostRequests.cpp
 *
 *  Created on: 2014-05-21
 *      Author: CaroL
 */

#include "PostRequests.h"
#include <QDebug>

PostRequests::PostRequests(QObject* parent)
	: QObject(parent) {


}

void PostRequests::tryIt()
{
	emit signalToQml("Signal postrequests RECEIVED!");
	qDebug() << "Postrequests signaltoqml emitted";
}

PostRequests::~PostRequests() {
	// TODO Auto-generated destructor stub
}

