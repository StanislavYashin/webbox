#pragma once

#include "GeneralSchema.hpp"

class SchemaHelper
{ 
public: 
	static GeneralSchema *getMainDbSchema()
	{
		GeneralSchema *__main_db_schema = new GeneralSchema();
		__main_db_schema->addSchema("id", 0, eGeneralFieldType::GFT_GUID);
		__main_db_schema->addSchema("name_cn", 1, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("name_en", 2, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("name_other", 3, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("language", 4, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("release_date", 5, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("category", 6, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("company", 7, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("platform", 8, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("version", 9, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("icon", 10, eGeneralFieldType::GFT_BYTE);
		__main_db_schema->addSchema("homepage", 11, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("url", 12, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("rank", 13, eGeneralFieldType::GFT_INTEGER);
		__main_db_schema->addSchema("torrent", 14, eGeneralFieldType::GFT_BYTE);
		__main_db_schema->addSchema("magnet", 15, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("baiduyun", 16, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("size", 17, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("star_marks", 18, eGeneralFieldType::GFT_INTEGER);
		__main_db_schema->addSchema("desc", 19, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("license", 20, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("update_time", 21, eGeneralFieldType::GFT_STRING);
		__main_db_schema->addSchema("snapshot_urls", 22, eGeneralFieldType::GFT_STRING);
		return __main_db_schema;
	}

};

