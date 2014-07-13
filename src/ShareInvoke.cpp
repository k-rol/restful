/*
 * ShareInvoke.cpp
 *
 *  Created on: Jul 13, 2014
 *      Author: cauellet
 */

#include <ShareInvoke.h>
#include <bb/system/InvokeRequest>


using namespace bb::system;


ShareInvoke::ShareInvoke(QObject *parent) :
        QObject(parent), m_invokeManager(new InvokeManager(this))
{
    // TODO Auto-generated constructor stub

}



ShareInvoke::~ShareInvoke()
{
    // TODO Auto-generated destructor stub
}

