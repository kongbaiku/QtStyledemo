#include <QtCore>
#include <QtGui>
#include <QtNetwork>

#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))//QT版本号大于5，0，0
#include <QtWidgets>
#endif

#if _MSC_VER >= 1600//编译器版本号大于1600(Visual Studio 2010 version 10.0)
#pragma execution_character_set("utf-8")
#endif

#define TIMEMS qPrintable (QTime::currentTime().toString("HH:mm:ss zzz"))
#define TIME qPrintable (QTime::currentTime().toString("HH:mm:ss"))
#define QDATE qPrintable (QDate::currentDate().toString("yyyy-MM-dd"))
#define QTIME qPrintable (QTime::currentTime().toString("HH-mm-ss"))
#define DATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
#define STRDATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))
#define STRDATETIMEMS qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss-zzz"))

#define AppName "styledemo"
#define AppPath qApp->applicationDirPath()
#define AppDeskWidth qApp->desktop()->availableGeometry().width()
#define AppDeskHeight qApp->desktop()->availableGeometry().height()
