#ifndef CONFIG_H
#define CONFIG_H

//临时设置文件

#include "Define.h"

#include <QString>
#include "GlowEffect.h"
#include "PathUtil.h"

class Profile { 
public:
	Profile()
	{
		g_bkmode = eBKMode::CUSTOMSTRETCH;
        //g_bkimageurl = Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/nebulae.png";
		//g_bkimageurl = Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/blur.png";
		//g_bkimageurl = Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/wallpaper.jpg";
		//g_bkimageurl = Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/iOS7_02.jpg";
		//g_bkimageurl = Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/mosha.png"; 
		//g_bkimageurl = Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/imgWebbox::Utility::PathUtil::GetCurrentExePath() + /Skin.png";
		g_bkimageurl =Webbox::Utility::PathUtil::GetCurrentExePath() + "/Skin/img/lenovo.jpg";
		//g_bkimageurl = Webbox::Utility::PathUtil::GetCurrentExePath() +"/Skin/img/material_design.png";
        //g_bkimageurl = ":/image/bk";

		WindowWidth = 860+20;
		WindowHeight = 690+20;

		AppFont = QFont("Microsoft Yahei");

		BlueGlowEffect = new GlowEffect();
		BlueGlowEffect->setRadius(5);
		BlueGlowEffect->setGlowColor(Qt::blue);
	}
 
	static GlowEffect *generateGlowEffect(QColor color,int radius)
	{
		GlowEffect* glowEffect = new GlowEffect();
		glowEffect->setRadius(radius);
		glowEffect->setGlowColor(color);
		return glowEffect;
	}

public:
	static Profile GetProfile()
	{
		static Profile cfg;
		return cfg;
	} 

	QFont AppFont;

	GlowEffect *BlueGlowEffect;

	int WindowWidth;
	int WindowHeight;

	QString g_bkimageurl;
	eBKMode g_bkmode;
}; 

static Profile ProfileInstance()
{
	return Profile::GetProfile();
}

#define CFG_APPSTORE_GUID 0x100
#define CFG_APPSTORE_SUBMENU_GUID 0x101
#define CFG_GAMESTORE_GUID 0x200
#define CFG_GAMESTORE_SUBMENU_GUID 0x201

#endif
 
