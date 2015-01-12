#ifndef DROPSHADOWWINDOW_DEFINE_H
#define DROPSHADOWWINDOW_DEFINE_H

#define SHADOW_WIDTH 10
#define SHADOW_HEIGHT 10
#define PADDING 5

#include <QtWidgets>

enum eDirection{
    NONE = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 4,
    LEFT=8,
    LEFTTOP = UP+LEFT,
    LEFTBOTTOM = DOWN+LEFT,
    RIGHTBOTTOM = RIGHT+DOWN,
    RIGHTTOP = UP+RIGHT
};

enum eBKMode
{
	BKNONE =0,
    BKTILE, //使用css背景，排列（适合纯色背景）
    BKSTRETCH,//使用css背景，拉伸（适合自定义）
    BKNOTILESTRETCH,//使用css背景，不排列不拉伸
    CUSTOMSTRETCH,//在paintEvent绘制自定义拉伸图片
	CUSTOMTILE,//在paintEvent绘制自定义排列图片
	PURECOLOR
};

#define css_bk_stretch			"DropShadowWindow { border-image:url(%1) 0 0 0 0 stretch stretch; border-radius: 0px;  margin:10px;}"
#define css_bk_stretch_round    "DropShadowWindow { border-image:url(%1) 0 0 0 0 stretch stretch; border-radius: 0px;  margin:10px;})"
#define css_bk_tile				"DropShadowWindow { background:url(%1);  margin:5px;})"
#define css_bk_notilestretch    "DropShadowWindow { background:url(%1);background-repeat:no-repeat;})"
  
extern Q_DECL_IMPORT void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed = 0);

#endif // DROPSHADOWWINDOW_DEFINE_H
