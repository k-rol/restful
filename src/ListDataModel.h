/*
 * ListDataModel.h
 *
 *  Created on: 2014-05-22
 *      Author: cauellet
 */

#ifndef LISTDATAMODEL_H_
#define LISTDATAMODEL_H_

#include <QObject>
#include <bb/cascades/GroupDataModel>
#include <bb/system/SystemPrompt>

using namespace bb::cascades;

class ListDataModel : public QObject {
	Q_OBJECT
	Q_PROPERTY( bb::cascades::DataModel* dataModel READ dataModel CONSTANT )

public:
	ListDataModel(QObject* parent = 0);

    Q_INVOKABLE void addObject(const QString &name, const QString &link);

    Q_INVOKABLE void deleteObject(const QVariantList &indexPath);

    Q_INVOKABLE void promptName(const QString &message, const QString &link);

    virtual ~ListDataModel();

private:
    void saveObject();

public slots:
    void onPromptFinished(bb::system::SystemUiResult::Type type);
    void loadDataFromQSettings();
    void useLink(const QVariantList &indexPath);

Q_SIGNALS:
	void copyGetLink(const QString &link);

private:
    bb::cascades::GroupDataModel* dataModel() const;
    GroupDataModel* m_dataModel;
};

#endif /* LISTDATAMODEL_H_ */
