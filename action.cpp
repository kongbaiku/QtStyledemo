#include "action.h"

Q_GLOBAL_STATIC(action, actionCOM)//创建一个名为actionCOM，类为QGlobalStatic的全局静态指针

action *action::instance()//单例模式
{
    return actionCOM();
}

action::action(QObject *parent) : QObject(parent)
{
    //QFontDatabase类提供关于底层窗口系统中可用字体的信息,从文件名指定的文件中加载字体，使其对应用程序可用
    int fontId = QFontDatabase::addApplicationFont(":/image/fontawesome-webfont.ttf");
    //返回由ID标识给定应用字体的字体系列列表
    QStringList fontName = QFontDatabase::applicationFontFamilies(fontId);

    if (fontName.count() > 0)
    {iconFont = QFont(fontName.at(0));}
    else
    {qDebug() << "load fontawesome-webfont.ttf error";}
}

//action::action(QObject *) : QObject(qApp)
//{

//}

void action::setIcon(QLabel *lab, QChar c, quint32 size)//设置标签字体
{
    iconFont.setPointSize(size);//设置点大小，点大小必须大于零
    lab->setFont(iconFont);//设定字体
    lab->setText(c);//输出文字
}

void action::setIcon(QAbstractButton *btn, QChar c, quint32 size)//设置按钮字体
{
    iconFont.setPointSize(size);//设置点大小，点大小必须大于零
    btn->setFont(iconFont);//设定字体
    btn->setText(c);//输出文字
}

void action::ceshi(Ui::QUICreator *ui)//传递ui控件指针
{
//    ui->btnError->setDisabled(1);//禁用错误按钮
}

QString action::binToDec(QString strBin)//二进制转十进制（最大值是4294967295）
{
    QString decimal;
    int nDec = 0,nLen;
    int i,j,k;
    nLen = strBin.length();
    for(i=0;i<nLen;i++)
    {
        if(strBin[nLen-i-1]=="0")
        {
            continue;
        }
        else
        {
            k=1;
            for(j=0;j<i;j++)
            k=k*2;
            nDec+=k;
        }
    }
    decimal = QString::number(nDec);
    return decimal;
}

QString action::decTobin(QString strDec)//十进制转二进制
{
    int nDec = strDec.toInt();
    int nYushu, nShang;
    QString strBin, strTemp;
    bool bContinue = true;
    while(bContinue)
    {
        nYushu = nDec % 2;
        nShang = nDec / 2;
        strBin=QString::number(nYushu)+strBin;
        strTemp = strBin;
        nDec = nShang;
        if(nShang == 0)
        {
           bContinue = false;
        }
    }
    int nTemp = strBin.length() % 4;
    switch(nTemp)
    {
        case 1:
        strTemp = "000"+strBin;
        strBin = strTemp;
        break;

        case 2:
        strTemp = "00"+strBin;
        strBin = strTemp;
        break;

        case 3:
        strTemp = "0"+strBin;
        strBin = strTemp;
        break;

        default:
        break;
    }
    return strBin;
}

QString action::decToHex(QString strDec, int width)//十进制转十六进制（数据，长度）
{
    int hex = strDec.toInt();
    QString hex1 = QString("%1").arg(hex,width,16,QLatin1Char('0'));//十进制转十六进制，最大限位width，无则填充0
    return hex1;
}

int hex2(unsigned char ch)//十六进制转换工具
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    return 0;
}

QString action::hexToDec(QString strHex)//十六进制转十进制
{
    int i;
    int v = 0;
    for(i=0;i<strHex.length();i++)
    {
        v*=16;
        v+=hex2(strHex[i].toLatin1());
    }
    return QString::number(v);
}

QString action::btnTextColor()//字体颜色代码
{
    QString SCode;
    SCode = "const QColor&color=QColorDialog::getColor(Qt::white,this);//利用颜色对话框让用户选择颜色,并存储于color中\n"
            "if (color.isValid())//检测color是否有效（用户可能选择了对话框中的取消按钮）\n"
            "{\n"
                "\tQRgb mRgb = qRgb(color.toRgb().red(),color.toRgb().green(),color.toRgb().blue());\n"
                "\tQString mRgbStr = QString::number(mRgb,16);//mRgb转mRgbStr（#66ccff）\n"
                "\tQString CHTML = mRgbStr.mid(2,6).prepend(\"#\");//把ff替换为#\n"
                "\tQString CHTML0 = CHTML;//备份\n"
                "\tQString CHTML1 = action::instance()->decToHex(QString::number(action::instance()->hexToDec(CHTML.mid(3,2)).toInt()-50),2);//中间两位-50\n"
                "\tif (CHTML1.length() != 2){CHTML1 = \"4f\";}//防止超出界限\n"
                "\tQString CHTML2 = CHTML.replace(3, 2,CHTML1);//替换中间两位\n"
                "\tQString style (tr(\"color: %1;\").arg(CHTML0));//设置plainTextEdit样式表\n"
                "\tQString style2 (tr(\"QPushButton{\"\n"
                    "\t\t\"background-color: %1;\"\n"
                    "\t\t\"}\"\n"
                    "\t\t\"QPushButton:hover{\"\n"
                    "\t\t\"background-color: %2;\"\n"
                    "\t\t\"}\"\n"
                    "\t\t\"QPushButton:pressed{\"\n"
                    "\t\t\"background-color: %1;\"\n"
                    "\t\t\"}\").arg(CHTML0).arg(CHTML2));//设置按钮样式表，使按钮与文字同色，按钮悬停-30色\n"
                "\tQString styleSheet = ui->plainTextEdit->styleSheet();//读取文本框样式表\n"
                "\tstyleSheet.append(style);//把设定样式添加进原样式\n"
                "\tui->txtTextColor->setText(CHTML0);//显示颜色代码\n"
                "\tui->plainTextEdit->setStyleSheet(styleSheet);//设置文本框样式\n"
                "\tui->btnTextColor->setStyleSheet(style2);//设置按钮样式\n"
                "\tQString txt = ui->txtMain->toPlainText();//读取文本\n"
                "\ttxt.append(tr(\"color: %1;\").arg(CHTML0));//添加样式代码\n"
                "\tui->txtMain->setPlainText(txt);//在主文本框显示代码\n"
                "\tui->plainTextEdit->setPlainText(txt);//在副文本框显示代码\n"
            "}\n";
    return  SCode;
}

QString action::btnPanelColor()//背景颜色代码
{
    QString SCode;
    SCode = "const QColor&color=QColorDialog::getColor(Qt::white,this);//利用颜色对话框让用户选择颜色,并存储于color中\n"
            "if (color.isValid())//检测color是否有效（用户可能选择了对话框中的取消按钮）\n"
            "{\n"
                "\tQRgb mRgb = qRgb(color.toRgb().red(),color.toRgb().green(),color.toRgb().blue());\n"
                "\tQString mRgbStr = QString::number(mRgb,16);//mRgb转mRgbStr（#66ccff）\n"
                "\tQString CHTML = mRgbStr.mid(2,6).prepend(\"#\");//把ff替换为#\n"
                "\tQString CHTML0 = CHTML;//备份\n"
                "\tQString CHTML1 = action::instance()->decToHex(QString::number(action::instance()->hexToDec(CHTML.mid(3,2)).toInt()-50),2);//中间两位-50\n"
                "\tif (CHTML1.length() != 2){CHTML1 = \"4f\";}//防止超出界限\n"
                "\tQString CHTML2 = CHTML.replace(3, 2,CHTML1);//替换中间两位\n"
                "\tQString style (tr(\"background-color: %1;\").arg(CHTML0));//设置plainTextEdit样式表\n"
                "\tQString style2 (tr(\"QPushButton{\"\n"
                    "\t\t\"background-color: %1;\"\n"
                    "\t\t\"}\"\n"
                    "\t\t\"QPushButton:hover{\"\n"
                    "\t\t\"background-color: %2;\"\n"
                    "\t\t\"}\"\n"
                    "\t\t\"QPushButton:pressed{\"\n"
                    "\t\t\"background-color: %1;\"\n"
                    "\t\t\"}\").arg(CHTML0).arg(CHTML2));//设置按钮样式表，使按钮与文字同色，按钮悬停-30色\n"
                "\tQString styleSheet = ui->plainTextEdit->styleSheet();//读取文本框样式表\n"
                "\tstyleSheet.append(style);//把设定样式添加进原样式\n"
                "\tui->txtTextColor->setText(CHTML0);//显示颜色代码\n"
                "\tui->plainTextEdit->setStyleSheet(styleSheet);//设置文本框样式\n"
                "\tui->btnTextColor->setStyleSheet(style2);//设置按钮样式\n"
                "\tQString txt = ui->txtMain->toPlainText();//读取文本\n"
                "\ttxt.append(tr(\"background-color: %1;\").arg(CHTML0));//添加样式代码\n"
                "\tui->txtMain->setPlainText(txt);//在主文本框显示代码\n"
                "\tui->plainTextEdit->setPlainText(txt);//在副文本框显示代码\n"
            "}\n";
    return  SCode;
}

QString action::btnBorderColor()//边框颜色代码
{
    QString SCode;
    SCode = "const QColor&color=QColorDialog::getColor(Qt::white,this);//利用颜色对话框让用户选择颜色,并存储于color中\n"
            "if (color.isValid())//检测color是否有效（用户可能选择了对话框中的取消按钮）\n"
            "{\n"
                "\tQRgb mRgb = qRgb(color.toRgb().red(),color.toRgb().green(),color.toRgb().blue());\n"
                "\tQString mRgbStr = QString::number(mRgb,16);//mRgb转mRgbStr（#66ccff）\n"
                "\tQString CHTML = mRgbStr.mid(2,6).prepend(\"#\");//把ff替换为#\n"
                "\tQString CHTML0 = CHTML;//备份\n"
                "\tQString CHTML1 = action::instance()->decToHex(QString::number(action::instance()->hexToDec(CHTML.mid(3,2)).toInt()-50),2);//中间两位-50\n"
                "\tif (CHTML1.length() != 2){CHTML1 = \"4f\";}//防止超出界限\n"
                "\tQString CHTML2 = CHTML.replace(3, 2,CHTML1);//替换中间两位\n"
                "\tQString style (tr(\"border:3px solid %1;\").arg(CHTML0));//设置plainTextEdit样式表\n"
                "\tQString style2 (tr(\"QPushButton{\"\n"
                    "\t\t\"background-color: %1;\"\n"
                    "\t\t\"}\"\n"
                    "\t\t\"QPushButton:hover{\"\n"
                    "\t\t\"background-color: %2;\"\n"
                    "\t\t\"}\"\n"
                    "\t\t\"QPushButton:pressed{\"\n"
                    "\t\t\"background-color: %1;\"\n"
                    "\t\t\"}\").arg(CHTML0).arg(CHTML2));//设置按钮样式表，使按钮与文字同色，按钮悬停-30色\n"
                "\tQString styleSheet = ui->plainTextEdit->styleSheet();//读取文本框样式表\n"
                "\tstyleSheet.append(style);//把设定样式添加进原样式\n"
                "\tui->txtBorderColor->setText(CHTML0);//显示颜色代码\n"
                "\tui->plainTextEdit->setStyleSheet(styleSheet);//设置文本框样式\n"
                "\tui->btnBorderColor->setStyleSheet(style2);//设置按钮样式\n"
                "\tQString txt = ui->txtMain->toPlainText();//读取文本\n"
                "\ttxt.append(tr(\"background-color: %1;\").arg(CHTML0));//添加样式代码\n"
                "\tui->txtMain->setPlainText(txt);//在主文本框显示代码\n"
                "\tui->plainTextEdit->setPlainText(txt);//在副文本框显示代码\n"
            "}\n";
    return  SCode;
}

QString action::btnFont()//字体设置代码
{
    QString SCode;
    SCode = "bool ok;\n"
            "const QFont&font = QFontDialog::getFont(&ok,QFont(\"Microsoft YaHei\", 12),this);//利用字体对话框让用户选择字体,并存储于font中\n"
            "if (ok)//检测font是否有效（用户可能选择了对话框中的取消按钮）\n"
            "{\n"
                "\tQString style (tr(\"font:normal %1px %2;\").arg(font.pointSize()).arg(font.family()));//设置plainTextEdit样式表\n"
                "\tQString styleSheet = ui->plainTextEdit->styleSheet();//读取文本框样式表\n"
                "\tstyleSheet.append(style);//把设定样式添加进原样式\n"
                "\tui->plainTextEdit->setStyleSheet(styleSheet);//设置文本框样式\n"
                "\tui->btnFontSettings->setText(QString::number(font.pointSize()));//显示字体大小\n"
                "\tui->txtFontSettings->setText(font.family());//显示字体名称\n"
                "\tui->txtFontSettings->setCursorPosition(0);//设置光标在左侧\n"
                "\tQString txt = ui->txtMain->toPlainText();//读取文本\n"
                "\ttxt.append(tr(\"font:normal %1px %2;\").arg(font.pointSize()).arg(font.family()));//添加样式代码\n"
                "\tui->txtMain->setPlainText(txt);//在主文本框显示代码\n"
                "\tui->plainTextEdit->setPlainText(txt);\n"
            "}\n";
    return  SCode;
}

QString action::btnPage()//页面设置代码
{
    QString SCode;
    SCode = "QPrinter printer;\n"
            "QPageSetupDialog dlg(&printer, this);//创建页面对话框\n"
            "if (dlg.exec() == QDialog::Accepted)\n"
            "{\n"
                "\tui->btnPageSettings->setText(printer.pageLayout().pageSize().key());\n"
                "\tQString width = QString::number(printer.pageLayout().pageSize().rectPoints().size().width());\n"
                "\tQString height = QString::number(printer.pageLayout().pageSize().rectPoints().size().height());\n"
                "\tui->txtPageSettings->setText(tr(\"%1*%2\").arg(width).arg(height));\n"
            "}\n";
    return  SCode;
}

QString action::btnSSS()//按钮样式
{
    QString SCode;
    SCode = "ui->Button->setStyleSheet(\n"
                "\t\"QPushButton{\"//正常状态\n"
                "\t\"color:rgb(183,203,188);\"//按钮文字颜色\n"
                "\t\"border: 2px solid grey;\"//边框宽2实线颜色灰\n"
                "\t\"border-radius: 8px;\"//按钮四角弧度\n"
                "\t\"border-color:rgb(183,203,188);\"//边框颜色\n"
                "\t\"border-style: outset;\"//边框样式\n"
                "\t\"border-image:url(:/icon/close);\"//按钮底图\n"
                "\t\"padding:4px 4px 2px 4px;\"//四边填衬\n"
                "\t\"background:rgb(183,203,188);\"//按钮背景色\n"
                "\t\"}\"\n"
                "\t\"QPushButton:hover{}\"//鼠标悬停\n"
                "\t\"QPushButton:pressed{}\"//按钮按下\n"
                "\t\"QPushButton:disabled{}\"//按钮无效\n"
                "\t\"QPushButton:hover:pressed{}\"//悬停按下\n"
                "\t);\n";
    return  SCode;
}

QString action::labSSS()//标签样式
{
    QString SCode;
    SCode = "ui->Label->setStyleSheet(\n"
                "\t\"QLabel{\"\n"
                "\t\"color:rgb(183,203,188);\"//标签文字颜色\n"
                "\t\"border: 2px solid grey;\"//边框宽2实线颜色灰\n"
                "\t\"border-color:rgb(183,203,188);\"//边框颜色\n"
                "\t\"border-image:url(:/icon/close);\"//标签底图\n"
                "\t\"background-color:rgb(183,203,188);\"//标签背景色\n"
                "\t\"selection-color:rgb(183,203,188);\"//选中文字色\n"
                "\t\"selection-background-color:rgb(183,203,188);\"//选中背景色\n"
                "\t\"}\"\n"
                "\t);\n";
    return  SCode;
}

QString action::scbSSS()//滚动条样式
{
    QString SCode;
    SCode = "ui->listWidget->verticalScrollBar()->setStyleSheet(\n"
                "\t\"QScrollBar{\"\n"
                "\t\"border: 0px solid transparent;\"//边框宽、实心、透明\n"
                "\t\"background:transparent;\"//背景\n"
                "\t\"width:11px;\"//宽度\n"
                "\t\"padding-top:10px;\"//滚动条上箭头预留大小\n"
                "\t\"padding-bottom:10px;\"//滚动条下箭头预留大小\n"
                "\t\"border-radius:2px;\"//四角弧度\n"
                "\t\"}\"\n"
                "\t\"QScrollBar:handle{}\"//滚动条滑块\n"
                "\t\"QScrollBar:handle:hover{}\"//滑块悬停\n"
                "\t\"QScrollBar:sub-line{}\"//上按钮边线\n"
                "\t\"QScrollBar:add-line{}\"//下按钮边线\n"
                "\t\"QScrollBar:add-page{}\"//滑块下槽\n"
                "\t\"QScrollBar:sub-page{}\"//滑块上槽\n"
                "\t\"QScrollBar:add-line:vertical{}\"//上箭头样式\n"
                "\t\"QScrollBar:sub-line:vertical{\"//下箭头样式\n"
                "\t\"height:10px;\"\n"
                "\t\"width:11px;\"\n"
                "\t\"border-image:url(:/icon/up);\"\n"
                "\t\"subcontrol-position:top;\"\n"
                "\t\"}\"\n"
                "\t\"QScrollBar:add-line:vertical:hover{}\"//鼠标经过上箭头时\n"
                "\t\"QScrollBar:sub-line:vertical:hover{}\"//鼠标经过下箭头时\n"
                "\t\"height:10px;\"\n"
                "\t\"width:11px;\"\n"
                "\t\"border-image:url(:/icon/up_on);\"\n"
                "\t\"subcontrol-position:top;\"\n"
                "\t\"}\"\n"
                "\t\"QScrollBar:handle:vertical{\"//设置垂直滑块的最小高度值,否则列表很大时滑块会消失\n"
                "\t\"min-height:5px\"\n"
                "\t\"}\"\n"
                "\t);\n";
    return  SCode;
}

QString action::sldSSS()//滑动条样式
{
    QString SCode;
    SCode = "ui->QSlider->setStyleSheet(\n"
                "\t\"QSlider{\"\n"
                "\t\"border:none;\"//无边框\n"
                "\t\"background-color:transparent;\"//背景透明\n"
                "\t\"border-radius: 8px;\"//四角弧度\n"
                "\t\"}\"\n"
                "\t\"QSlider:groove:horizontal{\"//水平槽\n"
                "\t\"border: 1px solid #00688B;\"\n"
                "\t\"height:5px;\"\n"
                "\t\"border-radius: 3px;\"\n"
                "\t\"}\"\n"
                "\t\"QSlider:handle:horizontal{\"//滑动键\n"
                "\t\"background: qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,\"\n"
                "\t\"fx:0.5,fy:0.5,stop:0 #bcbcbc, stop:0.25 #bcbcbc, stop:0.5 #bcbcbc, stop:1 #bcbcbc);\"\n"
                "\t\"width:10px;\"\n"
                "\t\"margin-top:-3px;\"\n"
                "\t\"margin-bottom:-3px;\"\n"
                "\t\"border-radius:5px;\"\n"
                "\t\"}\"\n"
                "\t\"QSlider:handle:horizontal:hover{\"//滑动键悬停\n"
                "\t\"background: qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,\"\n"
                "\t\"fx:0.5,fy:0.5,stop:0 #439cf3, stop:0.25 #439cf3, stop:0.5 #439cf3, stop:1 #439cf3);\"\n"
                "\t\"width:10px;\"\n"
                "\t\"margin-top:-3px;\"\n"
                "\t\"margin-bottom:-3px;\"\n"
                "\t\"border-radius:5px;\"\n"
                "\t\"}\"\n"
                "\t\"QSlider::add-page:horizontal{}\"//未划过的地方\n"
                "\t\"QSlider:sub-page:horizontal{}\"//划过的地方\n"
                "\t\"border-radius:3px;\"\n"
                "\t\"background:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #009ACD, stop:1 #008B8B);\"\n"
                "\t\"margin: 2px 0;\"\n"
                "\t\"}\"\n"
                "\t);\n";
    return  SCode;
}

QString action::cboxSSS()//下拉框样式
{
    QString SCode;
    SCode = "ui->ComboBox->setStyleSheet(\n"
                "\t\"QComboBox{\"\n"
                "\t\"color:rgb(183,203,188);\"//标签文字颜色\n"
                "\t\"border: 2px solid grey;\"//边框宽2实线颜色灰\n"
                "\t\"border-radius: 3px;\"//下拉框四角弧度\n"
                "\t\"padding: 1px 2px 1px 2px;\"//四边填衬\n"
                "\t\"border-color:rgb(183,203,188);\"//边框颜色\n"
                "\t\"border-image:url(:/icon/close);\"//下拉栏及下拉框底图\n"
                "\t\"background-color:rgb(183,203,188);\"//下拉栏及下拉框底色\n"
                "\t\"selection-color:rgb(183,203,188);\"//选中文字色\n"
                "\t\"selection-background-color:rgb(183,203,188);\"//选中背景色\n"
                "\t\"min-width: 9em;\"//最小宽度\n"
                "\t\"min-height:9em;\"//最小高度\n"
                "\t\"}\"\n"
                "\t\"QComboBox:drop-down{\"//下拉按钮\n"
                "\t\"subcontrol-origin: padding;\"//子控件来源\n"
                "\t\"subcontrol-position: top left;\"//子控件位置\n"
                "\t\"width:11px;\"//宽度\n"
                "\t\"border-left-width: 1px;\"//左边框宽度\n"
                "\t\"border-left-color: darkgray;\"//左边框颜色\n"
                "\t\"border-left-style: solid;\"//只有一条线\n"
                "\t\"border-top-right-radius: 3px;\"//上右边框宽度\n"
                "\t\"border-bottom-right-radius: 3px;\"//下右边框宽度\n"
                "\t\"border-left-style: solid;\"//只有一条线\n"
                "\t\"}\"\n"
                "\t\"QComboBox:down-arrow{\"//下拉箭头\n"
                "\t\"image: url(:/icon/down);\"//替换箭头图片\n"
                "\t\"}\"\n"
                "\t);\n";
    return  SCode;
}

QString action::spbSSS()//选值框样式
{
    QString SCode;
    SCode = "ui->SpinBox->setStyleSheet(\n"
                "\t\"QSpinBox{\"\n"
                "\t\"color:rgb(183,203,188);\"//标签文字颜色\n"
                "\t\"border: 2px solid grey;\"//边框宽2实线颜色灰\n"
                "\t\"border-radius: 3px;\"//下拉框四角弧度\n"
                "\t\"padding: 1px 2px 1px 2px;\"//四边填衬\n"
                "\t\"border-color:rgb(183,203,188);\"//边框颜色\n"
                "\t\"border-image:url(:/icon/close);\"//下拉栏及下拉框底图\n"
                "\t\"background-color:rgb(183,203,188);\"//下拉栏及下拉框底色\n"
                "\t\"selection-color:rgb(183,203,188);\"//选中文字色\n"
                "\t\"selection-background-color:rgb(183,203,188);\"//选中背景色\n"
                "\t\"min-width: 9em;\"//最小宽度\n"
                "\t\"min-height:9em;\"//最小高度\n"
                "\t\"padding-right: 15px;\"//右移为箭头腾空间\n"
                "\t\"}\"\n"
                "\t\"QSpinBox:up-button{\"//向上按钮\n"
                "\t\"subcontrol-origin: border;\"//子控件来源\n"
                "\t\"subcontrol-position: right;\"//子控件位置\n"
                "\t\"width:11px;\"//宽度\n"
                "\t\"padding: 0px;\"//无填衬\n"
                "\t\"border-image: url(:/images/spinup.png);\"//设置按钮图片\n"
                "\t\"border-width: 1px;\"//边框宽度\n"
                "\t\"border-bottom-width: 0;\"//边框下宽\n"
                "\t\"}\"\n"
                "\t\"QSpinBox:up-button:hover{}\"//向上按钮悬停\n"
                "\t\"QSpinBox:up-button:pressed{}\"//向上按钮按下\n"
                "\t\"QSpinBox:up-arrow{\"//向上箭头\n"
                "\t\"image: url(:/images/up_arrow.png);\"//设置箭头图片\n"
                "\t\"width: 7px;\"//宽度\n"
                "\t\"height: 7px;\"//高度\n"
                "\t\"}\"\n"
                "\t\"QSpinBox:up-arrow:disabled, QSpinBox::up-arrow:off{\"//值max时为关闭状态\n"
                "\t\"image: url(:/images/up_arrow_disabled.png);\"//设置关闭状态图片\n"
                "\t\"}\"\n"
                "\t\"QSpinBox::down-button{}\"//向下按钮\n"
                "\t\"QSpinBox::down-button:hover{}\"//向下按钮悬停\n"
                "\t\"QSpinBox::down-button:hover{}\"//向下按钮悬停\n"
                "\t\"QSpinBox::down-button:pressed {}\"//向下按钮按下\n"
                "\t\"QSpinBox::down-arrow {}\"//向下箭头\n"
                "\t\"QSpinBox::down-arrow:disabled, QSpinBox::down-arrow:off{\"//值min时为关闭状态\n"
                "\t\"image: url(:/images/down_arrow_disabled.png);\"//设置关闭状态图片\n"
                "\t\"}\"\n";
    return  SCode;
}

QString action::leditSSS()//编辑框样式
{
    QString SCode;
    SCode = "ui->LineEdit->setStyleSheet(\n"
                "\t\"QLineEdit{\"\n"
                "\t\"color:rgb(183,203,188);\"//文字颜色\n"
                "\t\"border: 2px solid grey;\"//边框宽2实线颜色灰\n"
                "\t\"border-radius: 3px;\"//四角弧度\n"
                "\t\"padding: 1px 2px 1px 2px;\"//四边填衬\n"
                "\t\"border-color:rgb(183,203,188);\"//边框颜色\n"
                "\t\"border-image:url(:/icon/close);\"//底图\n"
                "\t\"background-color:rgb(183,203,188);\"//底色\n"
                "\t\"selection-color:rgb(183,203,188);\"//选中文字色\n"
                "\t\"selection-background-color:rgb(183,203,188);\"//选中背景色\n"
                "\t\"min-width: 9em;\"//最小宽度\n"
                "\t\"min-height:9em;\"//最小高度\n"
                "\t\"}\"\n"
                "\t\"QLineEdit:read-only{}\"//仅读\n"
                "\t);\n";
    return  SCode;
}

QString action::calSSS()//日期框样式
{
    QString SCode;
    SCode = "ui->CalendarWidget->setStyleSheet(\n"
                "\t\"QCalendarWidget QSpinBox{\"//年编辑栏\n"
                "\t\"color:rgb(183,203,188);\"//文字颜色\n"
                "\t\"border: 2px solid grey;\"//边框宽2实线颜色灰\n"
                "\t\"border-radius: 3px;\"//四角弧度\n"
                "\t\"padding: 1px 2px 1px 2px;\"//四边填衬\n"
                "\t\"border-color:rgb(183,203,188);\"//边框颜色\n"
                "\t\"border-image:url(:/icon/close);\"//底图\n"
                "\t\"background-color:rgb(183,203,188);\"//底色\n"
                "\t\"selection-color:rgb(183,203,188);\"//选中文字色\n"
                "\t\"selection-background-color:rgb(183,203,188);\"//选中背景色\n"
                "\t\"width: 9em;\"//宽度\n"
                "\t\"height:9em;\"//高度\n"
                "\t\"}\"\n"
                "\t\"QCalendarWidget QSpinBox:up-button{\"//年编辑栏按钮上\n"
                "\t\"subcontrol-position: right;\"//位与右边\n"
                "\t\"}\"\n"
                "\t\"QCalendarWidget QSpinBox:down-button{\"//年编辑栏按钮下\n"
                "\t\"subcontrol-position: left;\"//位与左边\n"
                "\t\"}\"\n"
                "\t\"QCalendarWidget QMenu{\"//月菜单\n"
                "\t\"width: 150px;\"//宽度\n"
                "\t\"left: 20px;\"//左位移\n"
                "\t\"color: red;\"//文字颜色\n"
                "\t\"font-size: 18px;\"//字体大小\n"
                "\t\"background-color: rgb(100, 100, 100);\"//背景颜色\n"
                "\t\"}\"\n"
                "\t\"QCalendarWidget QAbstractItemView:disabled{\"//其他月份的天数\n"
                "\t\"color: rgb(164, 164, 64); \"//文字颜色\n"
                "\t\"}\"\n"
                "\t\"QCalendarWidget QAbstractItemView:enabled{\"//当月日期\n"
                "\t\"font-size:24px; \"//字体大小\n"
                "\t\"color: rgb(180, 180, 180);\"//文字颜色\n"
                "\t\"background-color: black;\"//背景颜色\n"
                "\t\"selection-background-color: rgb(64, 64, 64);\"//选中背景颜色\n"
                "\t\"selection-color: rgb(0, 255, 0);\"//选中颜色\n"
                "\t\"}\"\n"
                "\t\"#qt_calendar_prevmonth{}\"//上一月\n"
                "\t\"#qt_calendar_monthbutton{}\"//月按钮\n"
                "\t\"#qt_calendar_navigationbar{}\"//导航栏\n"
                "\t\"#qt_calendar_yearbutton{}\"//年按钮\n"
                "\t\"#qt_calendar_monthbutton{}\"//月按钮\n"
                "\t\"#qt_calendar_nextmonth{}\"//下一月\n"
                "\t);\n";
    return  SCode;
}

