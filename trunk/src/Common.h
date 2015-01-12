/**
 *Webbox 4 Source file
 *Macro definition to make simplified class
 */

#pragma once
 
#define NS_WEBBOX namespace Webbox {

#define NS_CONFIG namespace Config {

#define NS_END }

#define SAFE_DELETE(l)\
    if((l)!=NULL)\
        delete l;
#define _delete(l)

#define SAFE_RELEASE(l)\
    if((l)!=NULL)\
        (l)->Relase();
#define _release(l)\
    SAFE_RELEASE(l)

#define SAFE_DELETE_ARRAY(l)\
    if((l)!=NULL)\
        delete [] l;
#define _delete_array(l)\
    SAFE_DELETE_ARRAY(l)

#define PRIVATE private
#define PROTECTED protected
#define PUBLIC public

//macro for setter and getter
#define SETTER(type,name)\
    void set##name(type _##name)\
    {m_##name=_##name;}

#define GETTER(type,name)\
    type get##name() const \
    {return m_##name;}
 
#define DECLARE_SETTER(type,name)\
    void set##name(type _##name);

#define DECLARE_GETTER(type,name)\
    type get##name() const;

#define PROPERTY(type,name,access)\
	PUBLIC:\
		SETTER(type,name)\
		GETTER(type,name)\
	access:\
        type m_##name;

#define READONLY(type,name,access)\
	PUBLIC:\
        GETTER(type,name)\
	access:\
        type m_##name;

#define WRITEONLY(type,name,access)\
	PUBLIC:\
        SETTER(type,name)\
	access:\
        type m_##name;

#define ATTRIBUTE(type,name,access)\
	access:\
        type m_##name;

#define DECLARE(type,name,access)\
    PUBLIC:\
        GETTER(type,name)\
        DECLARE_SETTER(type,name)\
    access:\
        type m_##name;

#define _declare(type,name)\
    DECLARE(type,name,PROTECTED)

#define _readonly(type,name,access)\
    READONLY(type,name,access)

#define _writeonly(type,name,access)\
    WRITEONLY(type,name,access)

//PROPERTY
#define _P(type,name)\
	PROPERTY(type,name,PROTECTED)

#define _own(type,name)\
    PROPERTY(type,name,PRIVATE)

#define _property(type,name)\
    PROPERTY(type,name,PROTECTED)

//ATTRIBUTE
#define _A(type,name)\
	ATTRIBUTE(type,name,PUBLIC)

#define _attr(type,name)\
	_A(type,name)

#define _private(type,name)\
	ATTRIBUTE(type,name,PRIVATE)

#define _protected(type,name)\
	ATTRIBUTE(type,name,PROTECTED)

#define _public(type,name)\
	ATTRIBUTE(type,name,PUBLIC)
