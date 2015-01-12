#pragma once

#include <QtSql\QtSql>

class DbManager {
public:

	DbManager();

	virtual ~DbManager();

	bool createConnection();

protected:
	 
	QSqlDatabase db;
};

