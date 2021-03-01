#include "danmuku.h"

Q_GLOBAL_STATIC(danmuku, danmukuCOM)//创建一个名为danmukuCOM，类为QGlobalStatic的全局静态指针

danmuku *danmuku::instance()//单例模式
{
    return danmukuCOM();
}

danmuku::danmuku(QObject *parent) : QObject(parent)
{
}

void danmuku::allempty()//全部清空
{
    cyclePlayTimer->stop();//关闭计时器
    cyclePlayStrList.clear();//列表清空
}

void danmuku::danmukuNO1(QLabel *lb, QPalette pal, QFont ft, int time, QString mode, QStringList strl)//弹幕1号机
{
    if(cyclePlayTimer == NULL)//如果循环播放时间不为空
    {
       cyclePlayTimer = new QTimer();//创建计时器
       qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//仅添加一次随机种子
    }
    else
    {
        allempty();//全部清空
    }

    rightSpace = 0;
    damula = lb;//传递标签指针
    labelPatette = pal;//绘制
    labelFont = ft;//字体
    cyclePlayTimerInterval = time;//循环播放时间间隔
    dispModel = mode;//默认播放模式，从右到左R2L_Model
    cyclePlayStrList = strl;//循环播放内容
    randomnum = qrand()%240;//生成240以内的随机数

    lb->setScaledContents(true);//图片适应标签

    cyclePlayInit();//循环播放
    startupCyclePlay();//循环开始
}

void danmuku::cyclePlayInit()//循环播放
{
    setCyclePlayTimerInterval(cyclePlayTimerInterval);//设置循环时间间隔(需要放在创建定时器之后)
    connect(cyclePlayTimer, &QTimer::timeout, this, &danmuku::cyclePlayTimerCallback, Qt::UniqueConnection);//每次时间结束更改文字位置

    curPlayStrInd = 0;//当前播放字符串索引
    curPlayStrPrevInd = -1;//当前播放字符串索引前一个索引
}

void danmuku::setCyclePlayTimerInterval(int ms)//循环时间间隔
{
    if(cyclePlayTimer != NULL)//如果循环播放时间不为空
    {
        cyclePlayTimer->setInterval(ms);//设置计时器超时时间
    }
}

void danmuku::startupCyclePlay()//循环开始
{
    cyclePlayTimer->start();//打开计时器
}

void danmuku::cyclePlayTimerCallback(void)//循环播放时间复查
{
    execCyclePlayPaint();//程序循环播放绘制
}

void danmuku::execCyclePlayPaint()//程序循环播放绘制
{
    int dmode;

    if(dispModel == "L2R_Model")
    {dmode = 1;}
    else if(dispModel == "R2L_Model")
    {dmode = 2;}
    else if(dispModel == "LR_Model")
    {dmode = 3;}
    else if(dispModel == "DANMU")
    {dmode = 4;}

    switch(dmode)
    {
        case 1://从左到右
            l2rDispText();
            break;

        case 2://从右到左
            r2lDispText();
            break;

        case 3://左右来回
            lrDispText();
            break;

        case 4://弹幕
            danmuText();
            break;

         default:
            return;
    }
}

void danmuku::r2lDispText()//从右到左显示文本
{
    int strListSize = cyclePlayStrList.size();//滚动列表大小

    if(strListSize > 0)//如果滚动列表大于0
    {
        if(curPlayStrInd < strListSize)//如果当前播放字符串索引小于总字符串数
        {
            if(curPlayStrInd != curPlayStrPrevInd)       //一个字符串显示完了再进行下一个字符串显示
            {
                curPlayStr.clear();//清空当前播放字符串
                if (cyclePlayStrList.at(curPlayStrInd).isEmpty()) //空字符特殊处理
                {

                    curPlayStr.append("该条消息没有内容。");
                }
                else
                {
                    curPlayStr.append(cyclePlayStrList[curPlayStrInd]);//把当前索引字符串添加入播放字符串
                }
                curPlayStr.insert(0, QString("(%1) ").arg(curPlayStrInd+1));//给字符串加上序号
                curPlayStrPrevInd = curPlayStrInd;//顺延序号
            }
        }
        else//播放完毕
        {
            curPlayStrInd = 0;//清0重来
        }
    }
    else
    {
        return;
    }

    QPixmap drawTextPixmap(damula->width(), damula->height());//确定画布宽高
    QPainter painter(&drawTextPixmap);//确定绘制区域（指针）

    int fontHeight, curStrWidth;  //字体高度 整个字符串宽度

    drawTextPixmap.fill(labelPatette.window().color());//填充标签背景颜色
    painter.setPen(labelPatette.windowText().color());//设置标签文字颜色
    painter.setFont(labelFont);//设置字体

    fontHeight = painter.fontMetrics().height();//读取字体高度
    curStrWidth = painter.fontMetrics().width(QChar('中')) * curPlayStr.size();//当前字符串宽度为：一个字的宽度*字符数
    curPlayStrXPos = damula->width() - rightSpace;//确定当前字符串在标签的坐标

    rightSpace++;//文字绘制区域距标签右边距距离+1
    painter.drawText(curPlayStrXPos, damula->height() - (damula->height() /2 - fontHeight/2), curPlayStr);//绘制字符串
    damula->setPixmap(drawTextPixmap);//设置绘制参数

    if (curPlayStrXPos < -curStrWidth)   //显示完一条消息，显示下一个消息
    {
        curPlayStrInd++;//当前播放字符串索引+1
        rightSpace = 0;//文字绘制区域距标签右边距距离清零
    }
}

void danmuku::l2rDispText()//从左到右显示文本
{
    int strListSize = cyclePlayStrList.size();//滚动列表大小

    if(strListSize > 0)//如果滚动列表大于0
    {
        if(curPlayStrInd < strListSize)//如果当前播放字符串索引小于总字符串数
        {
            if(curPlayStrInd != curPlayStrPrevInd)       //一个字符串显示完了再进行下一个字符串显示
            {
                curPlayStr.clear();//清空当前播放字符串
                if (cyclePlayStrList.at(curPlayStrInd).isEmpty()) //空字符特殊处理
                {

                    curPlayStr.append("该条消息没有内容。");
                }
                else
                {
                    curPlayStr.append(cyclePlayStrList[curPlayStrInd]);//把当前索引字符串添加入播放字符串
                }
                curPlayStr.insert(0, QString("(%1) ").arg(curPlayStrInd+1));//给字符串加上序号
                curPlayStrPrevInd = curPlayStrInd;//顺延序号
            }
        }
        else//播放完毕
        {
            curPlayStrInd = 0;//清0重来
        }
    }
    else
    {
        return;
    }

    QPixmap drawTextPixmap(damula->width(), damula->height());//确定画布宽高
    QPainter painter(&drawTextPixmap);//确定绘制区域（指针）

    int fontHeight, curStrWidth;  //字体高度 整个字符串宽度

    drawTextPixmap.fill(labelPatette.window().color());//填充标签背景颜色
    painter.setPen(labelPatette.windowText().color());//设置标签文字颜色
    painter.setFont(labelFont);//设置字体

    fontHeight = painter.fontMetrics().height();//读取字体高度
    curStrWidth = painter.fontMetrics().width(QChar('中')) * curPlayStr.size();//当前字符串宽度为：一个字的宽度*字符数
    curPlayStrXPos = rightSpace;//确定当前字符串在标签的坐标

    rightSpace++;//文字绘制区域距标签右边距距离+1
    painter.drawText(curPlayStrXPos-curStrWidth, damula->height() - (damula->height() /2 - fontHeight/2), curPlayStr);//绘制字符串
    damula->setPixmap(drawTextPixmap);//设置绘制参数

    if (-curPlayStrXPos+curStrWidth < -curStrWidth)   //显示完一条消息，显示下一个消息
    {
        curPlayStrInd++;//当前播放字符串索引+1
        rightSpace = 0;//文字绘制区域距标签右边距距离清零
    }
}

void danmuku::lrDispText()//左右同时显示文本
{
    randomnum = qrand()%2;//生成1以内的随机数
    if(randomnum == 1)
    {
        r2lDispText();
    }
    else
    {
        l2rDispText();
    }
}

void danmuku::danmuText()//弹幕模式
{
    curPlayStr.clear();//清空当前播放字符串
    if (cyclePlayStrList.at(curPlayStrInd).isEmpty()) //空字符特殊处理
    {

        curPlayStr.append("该条消息没有内容。");
    }
    else
    {
        curPlayStr.append(cyclePlayStrList[0]);//把当前索引字符串添加入播放字符串
    }

    QPixmap drawTextPixmap(damula->width(), damula->height());//确定画布宽高
    QPainter painter(&drawTextPixmap);//确定绘制区域（指针）

    int fontHeight, curStrWidth;  //字体高度 整个字符串宽度

    drawTextPixmap.fill(labelPatette.window().color());//填充标签背景颜色
    painter.setPen(labelPatette.windowText().color());//设置标签文字颜色
    painter.setFont(labelFont);//设置字体

    fontHeight = painter.fontMetrics().height();//读取字体高度
    curStrWidth = painter.fontMetrics().width(QChar('中')) * curPlayStr.size();//当前字符串宽度为：一个字的宽度*字符数
    curPlayStrXPos = damula->width() - rightSpace;//确定当前字符串在标签的坐标

    rightSpace++;//文字绘制区域距标签右边距距离+1
    painter.drawText(curPlayStrXPos, randomnum, curPlayStr);//绘制字符串
    damula->setPixmap(drawTextPixmap);//设置绘制参数

    if (curPlayStrXPos < -curStrWidth)   //显示完一条消息关闭计时器
    {
        cyclePlayTimer->stop();//关闭计时器
    }
}


//void danmuku::resizeEvent(QResizeEvent *event)//大小事件
//{
//    //execCyclePlayPaint();
//    //resize(width(), height());
//    QLabel::resizeEvent(event);
//}
