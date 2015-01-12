#include "stdafx.h"
#include "DbManager.h"

DbManager::DbManager()
{

}

DbManager::~DbManager()
{

}

bool DbManager::createConnection()
{
	db = QSqlDatabase::addDatabase("");
	return true;
}