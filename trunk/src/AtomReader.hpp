#pragma once

#include <QtSql\qsql>
#include <QtSql\qsqldatabase.h>
#include <qstringlist.h>
#include <qmessagebox.h>
#include <QtSql\qsqlquery.h>
#include <qvariant.h>
#include "GeneralInstance.hpp"
#include <qdebug.h>

class AtomReader
{
public:

	AtomReader()
	{
	}

	virtual ~AtomReader()
	{
		close(); 
	}
 
	QList<GeneralInstance *> readFromDb(QString dbName, QString tableName , GeneralSchema *schema)
	{  
		bool isConnected = connect(dbName);
		
		QString cmdText = QString("select * from %1").arg(tableName);

		QSqlQuery query(__db);

		QList<GeneralInstance *> instanceList;

		if (query.exec(cmdText))
		{
			for (;query.next();)
			{
				GeneralInstance *instance = new GeneralInstance();
				QMap<int, QString>::iterator it;
				QVariant var;
				for (int idx = 0; idx < schema->count(); ++idx)
				{  
					GeneralField *field = schema->getFieldByIndex(idx); 
					instance->setValue(field->name, field->index, field->type, query.value(idx));
				}
				instanceList.append(instance);
			}
		}

		return instanceList;
	}

	static void test()
	{
		//QStringList drivers = QSqlDatabase::drivers();//静态成员函数，是类的成员函数，不是对象的.返回所有可用的数据库驱动程序的清单
	  
		//QString str = "";
		//foreach(QString driver, drivers)
		//	str += driver; 
		//const QString title = ""; 
	}

	bool connect(QString dbName)
	{
		__db = QSqlDatabase::addDatabase("QSQLITE");
		__db.setDatabaseName(dbName);

		qDebug() << QSqlDatabase::drivers();

		if (__db.open() == false)
		{
			QMessageBox::critical(NULL, "Sqlite connetion error", dbName, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			return false;
		}

		return true;
	}

	void close()
	{
		__db.close();
	}

private:

	QSqlDatabase __db; 
};

