#ifndef ACTION_H
#define ACTION_H

#include "quicreator.h"
#include "ui_quicreator.h"
#include <QCloseEvent>//关闭事件
#include <QMessageBox>//消息盒子库
#include <QPushButton>//按钮库
#include <QFileDialog>//文件操作库
#include <QTextStream>//文本流库
#include <QDialog>//窗口库
#include <QLineEdit>//行编辑器库
#include <QLabel>//标签库
#include <QDebug>//Debug

class QLineEdit;
class QDialog;
class QLabel;

class action : public QObject//新定义action，继承QObject
{
    Q_OBJECT//Q_OBJECT宏，使用信号槽需添加

public://共用函数
    explicit action(QObject *parent = 0);//父控件引用,从父控件获取参数
    static action *instance();//单例模式

    void setIcon(QLabel *lab, QChar c, quint32 size = 9);//设置标签字体
    void setIcon(QAbstractButton *btn, QChar c, quint32 size = 9);//设置按钮字体
    void ceshi(Ui::QUICreator *ui);//传递ui控件指针

    QString binToDec(QString strBin);//二进制转十进制
    QString decTobin(QString strDec);//十进制转二进制
    QString decToHex(QString strDec, int width);//十进制转十六进制
    QString hexToDec(QString strHex);//十六进制转十进制
    QString btnTextColor();//字体颜色代码
    QString btnPanelColor();//背景颜色代码
    QString btnBorderColor();//边框颜色代码
    QString btnFont();//字体设置代码
    QString btnPage();//页面设置代码
    QString btnSSS();//按钮样式
    QString labSSS();//按钮样式
    QString scbSSS();//滚动条样式
    QString sldSSS();//滑动条样式
    QString cboxSSS();//下拉框样式
    QString spbSSS();//选值框样式
    QString leditSSS();//编辑框样式
    QString calSSS();//编辑框样式

private://私有对象定义
    QFont iconFont;


private slots://槽函数


protected:
//    void closeEvent(QCloseEvent *event);

};

#endif // ACTION_H
