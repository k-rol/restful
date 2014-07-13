/*
 * ShareInvoke.h
 *
 *  Created on: Jul 13, 2014
 *      Author: cauellet
 */

#ifndef SHAREINVOKE_H_
#define SHAREINVOKE_H_

#include <QObject>
#include <bb/system/InvokeManager>

namespace bb {
namespace system {
class InvokeManager;
}
}

class ShareInvoke : public QObject
{
    Q_OBJECT
public:
    ShareInvoke(QObject *parent = 0);
    virtual ~ShareInvoke();

private:
    // The central object to manage invocations
    bb::system::InvokeManager* m_invokeManager;
};

#endif /* SHAREINVOKE_H_ */
