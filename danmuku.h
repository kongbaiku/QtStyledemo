#ifndef DANMUKU_H
#define DANMUKU_H

#include "quicreator.h"
#include "ui_quicreator.h"
#include <QPushButton>//按钮库
#include <QDialog>//窗口库
#include <QDebug>//Debug
#include <QtWidgets>

class QLineEdit;
class QDialog;
class QLabel;

class danmuku : public QObject//新定义danmuku，继承QObject
{
    Q_OBJECT//Q_OBJECT宏，使用信号槽需添加

public://共用函数
    explicit danmuku(QObject *parent = 0);//父控件引用,从父控件获取参数
    static danmuku *instance();//单例模式
    void danmukuNO1(QLabel *lb, QPalette pal, QFont ft, int time, QString mode, QStringList strl);//弹幕1号机
    void setCyclePlayTimerInterval(int ms);//循环时间间隔
    void startupCyclePlay();//循环开始
    void cyclePlayInit();//循环播放
    void r2lDispText();//从右到左显示文本
    void l2rDispText();
    void lrDispText();
    void danmuText();
    void execCyclePlayPaint();//程序循环播放绘制
    void cyclePlayTimerCallback(void);
    void allempty();//全部清空

private://私有对象定义
    int labelWidht;//标签宽
    int labelHeight;//标签高
    int cyclePlayTimerInterval;//循环播放时间间隔
    int curPlayStrXPos;    //当前播放字符串在标签做标牌系x坐标
    int curPlayStrInd;     //当前播放字符串索引
    int curPlayStrPrevInd; //当前播放字符串索引前一个索引
    int randomnum;//随机数
    int rightSpace;//文字绘制区域距标签右边距距离

    QString dispModel;//默认模式
    QStringList cyclePlayStrList;  //循环滚动播放字符串
    QTimer *cyclePlayTimer;    //定时更新循环播放区域
    QString curPlayStr;        //当前播放字符串
    QPalette labelPatette;//标签绘制
    QFont labelFont;//标签字体
    QLabel *damula;

private slots://槽函数


protected:


};

#endif // DANMUKU_H
