#-------------------------------------------------
#
# Project created by QtCreator 2017-02-19T12:55:42
#
#-------------------------------------------------

#项目使用模块
#core模块包含了Qt的核心功能，其他所有模块都依赖于这个模块
#gui模块提供了窗口系统集成、事件处理、OpenGL和OpenGL ES集成、2D图形、基本图像、字体和文本等功能
#network模块提供的类允许编写 TCP/IP clients 和 servers
#printsupport模块为打印提供支持
QT       += core gui network printsupport

#widgets模块提供了经典的桌面用户界面的UI元素集合，简单来说，所有C++程序用户界面部件都在该模块中
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#应用程序名称
TARGET          = styledemo
#定义了工程的编译模式，默认使用app模板，表明这是个应用程序
TEMPLATE        = app
#将含Q_OBJECT的头文件转换为标准的头文件存放的目录
MOC_DIR         = temp/moc
#将qrc文件转化为头文件所存放的目录
RCC_DIR         = temp/rcc
#ui转化为头文件所存放的目录
UI_DIR          = temp/ui
#生成的目标文件存放的目录
OBJECTS_DIR     = temp/obj
#生成目标的路径
DESTDIR         = bin
#程序中所用到的图片等资源文件
win32:RC_FILE   = other/main.rc
#预编译头文件（head.h包含需要预先编译的头文件信息）
PRECOMPILED_HEADER  = head.h
#指定工程要用到的头文件路径
INCLUDEPATH     += $$PWD
#告诉qmake应用程序的配置信息
CONFIG          += qt warn_off

#工程中包含的源文件
SOURCES += main.cpp\
    quicreator.cpp \       
    action.cpp \
    highlighter.cpp \
    danmuku.cpp \
    btnstyler.cpp

#头文件
HEADERS  += head.h\    
    quicreator.h \        
    action.h \
    highlighter.h \
    danmuku.h \
    btnstyler.h

#界面文件
FORMS    += \
    quicreator.ui \
    btnstyler.ui

#资源文件
RESOURCES += \
    other/qss.qrc \
    other/main.qrc
