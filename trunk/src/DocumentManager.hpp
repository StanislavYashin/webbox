#pragma once

#include "BoxDocument.hpp"
#include <qmap.h>
#include "PathUtil.h"
#include "SchemaHelper.h"
 
class DocumentManager
{
public:

	DocumentManager()
	{
	}

	static DocumentManager *m_pInstance;

	class GC   
	{
	public:
		~GC()
		{
			if (DocumentManager::m_pInstance)
				delete DocumentManager::m_pInstance;
		}
	};

	static GC Garbo;   

	static BoxDocument *getAppStoreDocument()
	{
		static BoxDocument *_appDoc = NULL; 
		if (_appDoc == NULL)
		{
			_appDoc = new BoxDocument(
				Webbox::Utility::PathUtil::GetCurrentExePath() + "/" + QString::fromWCharArray(MAIN_DB),
				QString("onestore_app"),
				SchemaHelper::getMainDbSchema());
		}

		return _appDoc;
	}

	static BoxDocument *getGameStoreDocument()
	{
		static BoxDocument *_gameDoc = NULL; 
		if (_gameDoc == NULL)
		{
			_gameDoc = new BoxDocument(
				Webbox::Utility::PathUtil::GetCurrentExePath() + "/" + QString::fromWCharArray(MAIN_DB),
				QString("onestore_game"),
				SchemaHelper::getMainDbSchema());
		}

		return _gameDoc;
	}

public:
	static DocumentManager * GetInstance()
	{
		if (m_pInstance == NULL) 
			m_pInstance = new DocumentManager();
		return m_pInstance;
	}
}; 


	
 