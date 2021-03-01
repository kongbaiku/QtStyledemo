#include "action.h"
#include "danmuku.h"
#include "highlighter.h"
#include "quicreator.h"
#include "ui_quicreator.h"
#include "btnstyler.h"
#include "ui_btnstyler.h"

//Q_GLOBAL_STATIC(QUICreator, QUICreatorCOM)//创建一个名为actionCOM，类为QGlobalStatic的全局静态指针

QString OBName;

QUICreator::QUICreator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QUICreator)//创建Ui::HelloDialog对象,变量名为ui
{
    ui->setupUi(this);//设置setupUi()函数的参数为this
    this->initForm();//执行初始化界面
}

QUICreator::~QUICreator()//析构函数
{
    delete ui;//删除ui
}

//QUICreator *QUICreator::instance()//单例模式
//{
//    return QUICreatorCOM();
//}

void QUICreator::initForm()//初始化界面
{
    this->initTableWidget();//表格控件初始化
    this->initTreeWidget();//树状控件初始化
    this->initListWidget();//列表控件初始化
    this->initOther();//其他项初始化
    this->initStyle();//样式初始化
    this->initTranslator();//翻译初始化
    this->iniSignalSlot();//信号槽初始化
    this->iniSignalMapper();//信号映射初始化

    ui->tabWidget->setCurrentIndex(0);//下方标签表控件跳转至索引0
    ui->txtMain->setEnabled(false);//主文本框不可用
//    ui->txtMain->setFocusPolicy(Qt::NoFocus);//主文本框无法获得焦点
    ui->btnTextColor->setContextMenuPolicy(Qt::CustomContextMenu);//设置右键菜单触发方式
    ui->btnPanelColor->setContextMenuPolicy(Qt::CustomContextMenu);//设置右键菜单触发方式
    ui->btnBorderColor->setContextMenuPolicy(Qt::CustomContextMenu);//设置右键菜单触发方式
    ui->btnFontSettings->setContextMenuPolicy(Qt::CustomContextMenu);//设置右键菜单触发方式
    ui->btnPageSettings->setContextMenuPolicy(Qt::CustomContextMenu);//设置右键菜单触发方式
    ui->tbtn1->setContextMenuPolicy(Qt::CustomContextMenu);//设置右键菜单触发方式
    Highlighter *h = new Highlighter(ui->txtMain->document());//新建高亮 
}

void QUICreator::initTableWidget()//表格控件初始化
{
    int width = qApp->desktop()->availableGeometry().width() - 120;//获取屏幕可视区宽度（1600） - 120
    ui->tableWidget->setColumnCount(5);//设置表格列数
    ui->tableWidget->setColumnWidth(0, width * 0.06);//设置列宽度，0列，宽*0.06
    ui->tableWidget->setColumnWidth(1, width * 0.10);
    ui->tableWidget->setColumnWidth(2, width * 0.06);
    ui->tableWidget->setColumnWidth(3, width * 0.10);
    ui->tableWidget->setColumnWidth(4, width * 0.15);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);//列标题头默认大小

    QStringList headText;//标题头文本
    headText << "设备编号" << "设备名称" << "设备地址" << "告警内容" << "告警时间";
    ui->tableWidget->setHorizontalHeaderLabels(headText);//设置水平标题头标签
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为不可编辑
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//设置表格为单项选中
    ui->tableWidget->setAlternatingRowColors(true);//是否隔行交替换色
    ui->tableWidget->verticalHeader()->setVisible(false);//是否隐藏表格标题头
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//设置表格是否充满，即行位不留空
    ui->tableWidget->setRowCount(101);//设置表格行数

    for(int i=0; i<100; i++)//批量填充表格
    {
        ui->tableWidget->setRowHeight(i, 24);//设置表格行高

        QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(i + 1));//设置设备编号
        QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString("测试设备%1").arg(i + 1));//设置设备名称
        QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(i + 1));//设置设备地址
        QTableWidgetItem *itemContent = new QTableWidgetItem("防区告警");//设置告警内容
        QTableWidgetItem *itemTime = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));//设置告警时间

        ui->tableWidget->setItem(i, 0, itemDeviceID);//把信息填充入表格
        ui->tableWidget->setItem(i, 1, itemDeviceName);
        ui->tableWidget->setItem(i, 2, itemDeviceAddr);
        ui->tableWidget->setItem(i, 3, itemContent);
        ui->tableWidget->setItem(i, 4, itemTime);
    }

    ui->tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    QScroller::grabGesture(ui->tableWidget,QScroller::LeftMouseButtonGesture);
    QScrollerProperties properties2 = QScroller::scroller(ui->tableWidget)->scrollerProperties();
    QVariant overshootPolicy2 = QVariant::fromValue<QScrollerProperties::OvershootPolicy>(QScrollerProperties::OvershootAlwaysOff);
    properties2.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, overshootPolicy2);
    QScroller::scroller(ui->tableWidget)->setScrollerProperties(properties2);
}

void QUICreator::initTreeWidget()//树状控件初始化
{
    ui->treeWidget->clear();//清除树状控件所有项目
    ui->treeWidget->setHeaderLabel(" 树状列表控件");//设置标题头标签

    QTreeWidgetItem *group1 = new QTreeWidgetItem(ui->treeWidget);//创建新组
    group1->setText(0, "父元素1");
    //设置组可以可以由用户勾选（否，则本元素不可以勾选）
    //设置组启用用户互交（否，则本组都不可改变）
    //设置组可以被选中（否，则本元素不可选中）
    group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group1->setCheckState(0, Qt::Unchecked);//设置本组有部分勾选

    QTreeWidgetItem *subItem11 = new QTreeWidgetItem(group1);//创建新元素于组下
    subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem11->setText(0, "子元素1");
    subItem11->setCheckState(0, Qt::Unchecked);//设置本元素勾选

    QTreeWidgetItem *subItem12 = new QTreeWidgetItem(group1);
    subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem12->setText(0, "子元素2");
    subItem12->setCheckState(0, Qt::Unchecked);//设置本元素未勾选

    QTreeWidgetItem *subItem13 = new QTreeWidgetItem(group1);
    subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem13->setText(0, "子元素3");
    subItem13->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *group2 = new QTreeWidgetItem(ui->treeWidget);
    group2->setText(0, "父元素2");
    group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group2->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *subItem21 = new QTreeWidgetItem(group2);
    subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem21->setText(0, "子元素1");
    subItem21->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *subItem211 = new QTreeWidgetItem(subItem21);
    subItem211->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem211->setText(0, "子子元素1");
    subItem211->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *subItem212 = new QTreeWidgetItem(subItem21);
    subItem212->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem212->setText(0, "子子元素2");
    subItem212->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *subItem31 = new QTreeWidgetItem(group2);
    subItem31->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem31->setText(0, "子元素2");
    subItem31->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *subItem311 = new QTreeWidgetItem(subItem31);
    subItem311->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem311->setText(0, "子子元素1");
    subItem311->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *subItem312 = new QTreeWidgetItem(subItem31);
    subItem312->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem312->setText(0, "子子元素2");
    subItem312->setCheckState(0, Qt::Unchecked);

    ui->treeWidget->expandAll();//扩展所有可扩展项目（否，则项目都为折叠状态）
}

void QUICreator::initListWidget()//列表控件初始化
{
    ui->cbox1->clear();
    ui->cbox2->clear();
    ui->CBColor->clear();

    QStringList MbDlg;//设置QString表
    MbDlg << "询问信息框" << "提示信息框" << "警告信息框" << "错误信息框" << "自定信息框" << "关于Qt";
    ui->cbox1->addItems(MbDlg);//把信息填充入下拉框1

    QStringList colorNameList = QColor::colorNames();//返回Qt已知的颜色名
    QString colorName;
    foreach(colorName,colorNameList)//遍历
    {
        QPixmap pix_color(70,15);//设置图框大小
        pix_color.fill(QColor(colorName));//重载列表
        ui->cbox2->addItem(QIcon(pix_color),NULL);//添加图标，无字
        ui->cbox2->setIconSize(QSize(70,15));//设置图标大小
        ui->cbox2->setSizeAdjustPolicy(QComboBox::AdjustToContents);//设置下拉列表的尺寸符合内容的大小
        QPixmap pix_color2(160,20);//设置图框大小
        pix_color2.fill(QColor(colorName));//重载列表
        ui->CBColor->addItem(QIcon(pix_color2),NULL);//添加图标，无字
        ui->CBColor->setIconSize(QSize(160,20));//设置图标大小
        ui->CBColor->setSizeAdjustPolicy(QComboBox::AdjustToContents);//设置下拉列表的尺寸符合内容的大小
    }
}

void QUICreator::initOther()//其他项初始化
{
    ui->btn1->click();//点亮btn1
    ui->rbtn1->setChecked(true);//设置单选按钮1被选中
    ui->ck1->setChecked(true);//设置复选按钮1被选中
    ui->ck2->setChecked(true);//设置复选按钮2被选中
    ui->ck3->setCheckState(Qt::PartiallyChecked);//设置复选按钮3被部分选中
    ui->btnInput->setDisabled(1);//禁用输入框按钮
    ui->horizontalSlider->setValue(88);//添加水平滑块，设置值为88
    ui->progressBar->setValue(88);//添加进度条，设置值为88

    ui->tab9->setStyleSheet("QPushButton{font:20pt;}");//设置UI界面内所有按钮字体大小为20
    ui->widgetVideo->setStyleSheet("QLabel{font:20pt;}");//设置视频监控内所有标签字体大小为20

    ui->widgetLeft->setProperty("nav", "left");//为对象的名称属性值设置值
    ui->widgetBottom->setProperty("form", "bottom");
    ui->widgetTop->setProperty("nav", "top");
    ui->widgetVideo->setProperty("video", true);

    ui->calendarWidget2->setStyleSheet("QCalendarWidget QSpinBox{"
                                       "width: 50px"
                                       "}"
                                       "QCalendarWidget QSpinBox:up-button{"//年编辑栏按钮上
                                       "subcontrol-position: right;"//位与右边
                                       "height: 25px;"
                                       "padding: 0px;"
                                       "}"
                                       "QCalendarWidget QSpinBox:down-button{"//年编辑栏按钮下
                                       "subcontrol-position: left;"//位与左边
                                       "height: 25px;"
                                       "padding: 0px;"
                                       "}");

    ui->spinBox->setStyleSheet("QSpinBox{"
                               "padding-right: 15px;"//右移为箭头腾空间
                               "}"
                               "QSpinBox:up-button{"//向上按钮
                               "subcontrol-origin: padding;"//子控件来源
                               "subcontrol-position: right;"//位与右边
                               "image: url(:/qss/psblack/add_right.png);"//设置按钮图片
                               "width: 10px;"//宽度
                               "height: 25px;"//高度
                               "padding: 0px;"
                               "}"
                               "QSpinBox:down-button{"//向下按钮
                               "subcontrol-origin: padding;"//子控件来源
                               "subcontrol-position: left;"//位与左边
                               "image: url(:/qss/psblack/add_left.png);"//设置按钮图片
                               "width: 10px;"//宽度
                               "height: 25px;"//高度
                               "padding: 0px;"
                               "}");

    QList<QLabel *> labChs = ui->widgetVideo->findChildren<QLabel *>();//返回具有给定名称的全部子集指针，添加入表
    foreach (QLabel *lab, labChs) //历遍所有标签
    {
        lab->setFocusPolicy(Qt::StrongFocus);//标签可通过Tab键接收焦点
    }
    if(ui->ck1->isChecked() == true)
    {
        ui->lineEdit->setPlaceholderText(tr("请输入自定信息框文本"));
    }

    //当前时间
    QTimer *CurrentTime = new QTimer(this);//新建定时器
    CurrentTime->start(500);//0s即timeout
    connect(CurrentTime,&QTimer::timeout,[=](){QDateTime current_time = QDateTime::currentDateTime();
    QString StrCurrentTime = current_time.toString("当前时间:yyyy-MM-dd hh:mm:ss");
    ui->lab4->setText(StrCurrentTime);});//每当timeout，调用系统时间更新标签

    //运行时间
    QTimer *Time1 = new QTimer(this);//新建定时器
    Time1->start(1000);//1s即timeout
    Time1->setTimerType(Qt::PreciseTimer);//提高定时器精度到毫秒级
    connect(Time1,&QTimer::timeout,[=](){
    sec1++;
    if(sec1>59){sec1=0;min1++;}
    if(min1>59){min1=0;hour1++;}
    if(hour1>23){hour1=0;day1++;}
    ui->lab3->setText(tr("已运行:%1天%2时%3分%4秒").arg(day1).arg(hour1).arg(min1).arg(sec1));
    });//每当timeout，更新标签

    action::instance()->ceshi(ui);//传递ui指针
}

void QUICreator::initStyle()//样式初始化
{
    QFile file(":/qss/psblack.css");//加载样式表
    if (file.open(QFile::ReadOnly))//如果文件以只读打开
    {
        QString qss = QLatin1String(file.readAll());//读取全部数据
        QString paletteColor = qss.mid(20, 7);//截取数据
        qApp->setPalette(QPalette(QColor(paletteColor)));//设置颜色
        qApp->setStyleSheet(qss);//设置样式表
        file.close();//文件关闭
    }
}

void QUICreator::initTranslator()//翻译初始化
{
    //加载鼠标右键菜单翻译文件
    QTranslator *translator1 = new QTranslator(qApp);
    translator1->load(":/image/qt_zh_CN.qm");
    qApp->installTranslator(translator1);//安装翻译

    //加载富文本框鼠标右键菜单翻译文件
    QTranslator *translator2 = new QTranslator(qApp);
    translator2->load(":/image/widgets.qm");
    qApp->installTranslator(translator2);//安装翻译
}

void QUICreator::iniSignalSlot()//信号槽初始化
{
    connect(ui->btnNew, &QPushButton::clicked, this, &QUICreator::newFile);
    connect(ui->btnOpen, &QPushButton::clicked, this, &QUICreator::openFile);
    connect(ui->btnSave, &QPushButton::clicked, this, &QUICreator::save);
    connect(ui->btnSaveOther, &QPushButton::clicked, this, &QUICreator::saveAs);
    connect(ui->btnTextColor, &QPushButton::clicked, this, &QUICreator::colorDialog1);
    connect(ui->btnPanelColor, &QPushButton::clicked, this, &QUICreator::colorDialog2);
    connect(ui->btnBorderColor, &QPushButton::clicked, this, &QUICreator::colorDialog3);
    connect(ui->btnFontSettings, &QPushButton::clicked, this, &QUICreator::fontDialog);
    connect(ui->btnPageSettings, &QPushButton::clicked, this, &QUICreator::pageDialog);
    connect(ui->btnPrintSettings, &QPushButton::clicked, this, &QUICreator::printDialog);
    connect(ui->btnInfo, &QPushButton::clicked, this, &QUICreator::messageBoxDialog);
    connect(ui->btnQuestion, &QPushButton::clicked, this, &QUICreator::wizardDialog);
    connect(ui->btnError, &QPushButton::clicked, this, &QUICreator::errorDialog);
    connect(ui->btnInput, &QPushButton::clicked, this, &QUICreator::inputDialog);
    connect(ui->btnProgress, &QPushButton::clicked, this, &QUICreator::progressDialog);
    connect(ui->btnInputPwd, &QPushButton::clicked, this, &QUICreator::passwordDialog);
    connect(ui->btndanmu, &QPushButton::clicked, this, &QUICreator::danmuku);
    connect(ui->btnstart, &QPushButton::clicked, this, &QUICreator::mainSBtn);


    connect(ui->treeWidget,&QTreeWidget::itemChanged,this,&QUICreator::TWUpdateChild); 
//    connect(ui->treeWidget,&QTreeWidget::itemChanged,this,&QUICreator::TWSetParentPartiallyChecked);
    connect(ui->treeWidget,&QTreeWidget::itemChanged,this,&QUICreator::TWUpdateParent);

    connect(ui->btnDialog, &QPushButton::clicked, [=](){customDialog("快乐提示框" ,"九龙闪大小兵(￣▽￣)／");});
    connect(ui->timebtn,&QPushButton::clicked, [=](){ui->timeEdit->setDateTime(TimeSelector(
            ui->timeEdit->time().toString("HH:mm").mid(0, 2),ui->timeEdit->time().toString("HH:mm").mid(3, 2)));});
    connect(ui->tbtn1, &QToolButton::clicked, [=](){btnRight = "tbtn1";styleSheet();});
    connect(ui->tbtn2, &QToolButton::clicked, [=](){btnRight = "tbtn2";styleSheet();});
    connect(ui->btn1, &QPushButton::clicked, [=](){btnRightNum = 1;});
    connect(ui->btn2, &QPushButton::clicked, [=](){btnRightNum = 2;});
    connect(ui->btn3, &QPushButton::clicked, [=](){btnRightNum = 3;});
    connect(ui->btn4, &QPushButton::clicked, [=](){btnRightNum = 4;}); 
    connect(ui->btn5, &QPushButton::clicked, [=](){btnRightNum = 5;});
    connect(ui->btn6, &QPushButton::clicked, [=](){btnRightNum = 6;});
    connect(ui->btn7, &QPushButton::clicked, [=](){btnRightNum = 7;});
    connect(ui->btn8, &QPushButton::clicked, [=](){btnRightNum = 8;});

    connect(ui->ck1, SIGNAL(stateChanged(int)), this, SLOT(singleStateChanged(int)));
    connect(ui->ck2, SIGNAL(stateChanged(int)), this, SLOT(singleStateChanged2(int)));
    connect(actionCode,SIGNAL(triggered(bool)),this,SLOT(sourceCode()));
    connect(ui->cbox1, SIGNAL(currentIndexChanged(int)), this, SLOT(cbox1Changed()));
    connect(ui->cbox2, SIGNAL(currentIndexChanged(int)), this, SLOT(cbox2Changed(int)));
    connect(ui->CBColor, SIGNAL(currentIndexChanged(int)), this, SLOT(CBColorChanged(int)));
    connect(ui->plainTextEdit, SIGNAL(textChanged()), this, SLOT(TEditHighlight()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(hSliderValue(int)));
}

void QUICreator::iniSignalMapper()//信号映射初始化
{
    btnMapper = new QSignalMapper();//新建映射

    connect(ui->btnTextColor,SIGNAL(customContextMenuRequested(const QPoint &)), btnMapper, SLOT(map()));//连接信号映射
    connect(ui->btnPanelColor,SIGNAL(customContextMenuRequested(const QPoint &)), btnMapper, SLOT(map()));
    connect(ui->btnBorderColor,SIGNAL(customContextMenuRequested(const QPoint &)), btnMapper, SLOT(map()));
    connect(ui->btnFontSettings,SIGNAL(customContextMenuRequested(const QPoint &)), btnMapper, SLOT(map()));
    connect(ui->btnPageSettings,SIGNAL(customContextMenuRequested(const QPoint &)), btnMapper, SLOT(map()));
    connect(ui->tbtn1,SIGNAL(customContextMenuRequested(const QPoint &)), btnMapper, SLOT(map()));

    btnMapper->setMapping(ui->btnTextColor, "btnTextColor");//设置映射信号所带参数
    btnMapper->setMapping(ui->btnPanelColor, "btnPanelColor");
    btnMapper->setMapping(ui->btnBorderColor, "btnBorderColor");
    btnMapper->setMapping(ui->btnFontSettings, "btnFontSettings");
    btnMapper->setMapping(ui->btnPageSettings, "btnPageSettings");
    btnMapper->setMapping(ui->tbtn1, "tbtn1");

    connect(btnMapper, SIGNAL(mapped(QString)), this, SLOT(btnContextMenu(QString)));//映射信号返回
}

void QUICreator::colorDialog1()//颜色对话框（文字颜色）
{
//    QPalette palette = ui->txtMain->palette(); //创建一个调色板对象,该对象与txtMain现有配色方案一致(因为程序只改变 Base 的颜色,而其它颜色不变）
//    palette.setColor(QPalette::Text,color);//设置调试板中的颜色为用户所选颜色
//    ui->txtMain->setPalette(palette);//设置txtMain的颜色为palette（与样式表冲突，弃用，仅做参考）

    const QColor&color = QColorDialog::getColor(Qt::white,this);//利用颜色对话框让用户选择颜色,并存储于color中
    if (color.isValid())//检测color是否有效（用户可能选择了对话框中的取消按钮）
    {
        QRgb mRgb = qRgb(color.toRgb().red(),color.toRgb().green(),color.toRgb().blue());
        QString mRgbStr = QString::number(mRgb,16);//mRgb转mRgbStr（#66ccff）
//        QColor mColor = QColor(mRgb);//mRgb转mColor
//        QColor color2(mRgbStr.toUInt(NULL,16));//mRgbStr转color
        QString CHTML = mRgbStr.mid(2,6).prepend("#");//把ff替换为#
        QString CHTML0 = CHTML.toUpper();//备份
        QString CHTML1 = action::instance()->decToHex(QString::number(action::instance()->hexToDec(CHTML.mid(3,2)).toInt()-50),2);//中间两位-50
        if(CHTML1.length() != 2){CHTML1 = "4f";}//防止超出界限
        QString CHTML2 = CHTML.replace(3, 2,CHTML1);//替换中间两位
        QString style = tr("color: %1;").arg(CHTML0);//设置plainTextEdit样式表
        QString style2 = tr("QPushButton{"
                            "background-color: %1;"
                            "}"
                            "QPushButton:hover{"
                            "background-color: %2;"
                            "}"
                            "QPushButton:pressed{"
                            "background-color: %1;"
                            "}").arg(CHTML0).arg(CHTML2);//设置按钮样式表，使按钮与文字同色，按钮悬停-30色
        QString styleSheet = ui->plainTextEdit->styleSheet();//读取文本框样式表
        styleSheet.append(style);//把设定样式添加进原样式
        ui->txtTextColor->setText(CHTML0);//显示颜色代码
        ui->plainTextEdit->setStyleSheet(styleSheet);//设置文本框样式
        ui->btnTextColor->setStyleSheet(style2);//设置按钮样式
        QString txt = ui->txtMain->toPlainText();//读取文本
        txt.append(tr("color: %1;\n").arg(CHTML0));//添加样式代码
        ui->txtMain->setPlainText(txt);//在主文本框显示代码
        ui->plainTextEdit->setPlainText(txt);
    }
}

void QUICreator::colorDialog2()//颜色对话框（背景颜色）
{
    const QColor&color = QColorDialog::getColor(Qt::white,this);//利用颜色对话框让用户选择颜色,并存储于color中
    if (color.isValid())//检测color是否有效（用户可能选择了对话框中的取消按钮）
    {
//        QRgb mRgb = qRgb(color.toRgb().red(),color.toRgb().green(),color.toRgb().blue());
//        QString mRgbStr = QString::number(mRgb,16);
//        QString CHTML = mRgbStr.mid(2,6).prepend("#");
        QString CHTML = color.name();//这一句简化上面三句
        QString CHTML0 = CHTML.toUpper();//备份
        QString CHTML1 = action::instance()->decToHex(QString::number(action::instance()->hexToDec(CHTML.mid(3,2)).toInt()-50),2);//中间两位-50
        if(CHTML1.length() != 2){CHTML1 = "4f";}//防止超出界限
        QString CHTML2 = CHTML.replace(3, 2,CHTML1);//替换中间两位
        QString style = tr("background-color: %1;").arg(CHTML0);//设置plainTextEdit样式表
        QString style2 = tr("QPushButton{"
                            "background-color: %1;"
                            "}"
                            "QPushButton:hover{"
                            "background-color: %2;"
                            "}"
                            "QPushButton:pressed{"
                            "background-color: %1;"
                            "}").arg(CHTML0).arg(CHTML2);//设置样式表，使按钮与文字同色，按钮悬停-30色
        QString styleSheet = ui->plainTextEdit->styleSheet();//读取文本框样式表
        styleSheet.append(style);//把设定样式添加进原样式
        ui->txtPanelColor->setText(CHTML0);;//显示颜色代码
        ui->plainTextEdit->setStyleSheet(styleSheet);//设置文本框样式
        ui->btnPanelColor->setStyleSheet(style2);//设置按钮样式
        QString txt = ui->txtMain->toPlainText();//读取文本
        txt.append(tr("background-color: %1;\n").arg(CHTML0));//添加样式代码
        ui->txtMain->setPlainText(txt);//在主文本框显示代码
        ui->plainTextEdit->setPlainText(txt);
    }
}

void QUICreator::colorDialog3()//颜色对话框（边框颜色）
{
    const QColor&color = QColorDialog::getColor(Qt::white,this);//利用颜色对话框让用户选择颜色,并存储于color中
    if (color.isValid())//检测color是否有效（用户可能选择了对话框中的取消按钮）
    {
        QRgb mRgb = qRgb(color.toRgb().red(),color.toRgb().green(),color.toRgb().blue());
        QString mRgbStr = QString::number(mRgb,16);
        QString CHTML = mRgbStr.mid(2,6).prepend("#");
        QString CHTML0 = CHTML.toUpper();//备份
        QString CHTML1 = action::instance()->decToHex(QString::number(action::instance()->hexToDec(CHTML.mid(3,2)).toInt()-50),2);//中间两位-50
        if(CHTML1.length() != 2){CHTML1 = "4f";}//防止超出界限
        QString CHTML2 = CHTML.replace(3, 2,CHTML1);//替换中间两位
        QString style = tr("border:3px solid %1;").arg(CHTML0);//设置plainTextEdit样式表
        QString style2 = tr("QPushButton{"
                            "background-color: %1;"
                            "}"
                            "QPushButton:hover{"
                            "background-color: %2;"
                            "}"
                            "QPushButton:pressed{"
                            "background-color: %1;"
                            "}").arg(CHTML0).arg(CHTML2);//设置样式表，使按钮与文字同色，按钮悬停-30色
        QString styleSheet = ui->plainTextEdit->styleSheet();//读取文本框样式表
        styleSheet.append(style);//把设定样式添加进原样式
        ui->txtBorderColor->setText(CHTML0);;//显示颜色代码
        ui->plainTextEdit->setStyleSheet(styleSheet);//设置文本框样式
        ui->btnBorderColor->setStyleSheet(style2);//设置按钮样式
        QString txt = ui->txtMain->toPlainText();//读取文本
        txt.append(tr("border:3px solid %1;\n").arg(CHTML0));//添加样式代码
        ui->txtMain->setPlainText(txt);//在主文本框显示代码
        ui->plainTextEdit->setPlainText(txt);
    }
}

void QUICreator::fontDialog()//字体对话框
{
    bool ok;
    const QFont&font = QFontDialog::getFont(&ok,QFont("Microsoft YaHei", 12),this);//利用字体对话框让用户选择字体,并存储于font中
    if (ok)//检测font是否有效（用户可能选择了对话框中的取消按钮）
    {
//        ui->plainTextEdit->setFont(font);//设置字体（通常情况下使用，在这里与样式表冲突）
        QString style (tr("font:normal %1px %2;").arg(font.pointSize()).arg(font.family()));//设置plainTextEdit样式表
        QString styleSheet = ui->plainTextEdit->styleSheet();//读取文本框样式表
        styleSheet.append(style);//把设定样式添加进原样式
        ui->plainTextEdit->setStyleSheet(styleSheet);//设置文本框样式
        ui->btnFontSettings->setText(QString::number(font.pointSize()));//显示字体大小
        ui->txtFontSettings->setText(font.family());//显示字体名称
        ui->txtFontSettings->setCursorPosition(0);//设置光标在左侧
        QString txt = ui->txtMain->toPlainText();//读取文本
        txt.append(tr("font:normal %1px %2;\n").arg(font.pointSize()).arg(font.family()));//添加样式代码
        ui->txtMain->setPlainText(txt);//在主文本框显示代码
        ui->plainTextEdit->setPlainText(txt);
    }
}

void QUICreator::pageDialog()//页面对话框
{
    QPrinter printer;
    QPageSetupDialog dlg(&printer, this);//创建页面对话框
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->btnPageSettings->setText(printer.pageLayout().pageSize().key());
        QString width = QString::number(printer.pageLayout().pageSize().rectPoints().size().width());
        QString height = QString::number(printer.pageLayout().pageSize().rectPoints().size().height());
        ui->txtPageSettings->setText(tr("%1*%2").arg(width).arg(height));
    }
}

void QUICreator::printDialog()//打印对话框
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);//创建打印对话框
    if (ui->txtMain->textCursor().hasSelection())//如果编辑器中有选中区域，则打印选中区域
    {
       dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    }
    if (dlg.exec() == QDialog::Accepted)
    {
        ui->txtMain->print(&printer);
//  printFile("D:/myRSM.doc");//或者指定文件打印
    }
}

void QUICreator::messageBoxDialog()//信息对话框
{
    if(ui->cbox1->currentText() != "关于Qt")
    {
        QMessageBox box;//信息盒结构体
        if(ui->cbox1->currentText() == "询问信息框")
        {
            box.setWindowTitle(tr("询问信息框"));//窗口标题
            box.setIcon(QMessageBox::Question);//窗口图标
            box.setText(tr("想明白生命的意义吗？想真正的......活着吗？"));//信息内容
            QPushButton *yesBtn = box.addButton(tr("YES(&Y)"),QMessageBox::YesRole);//“是”的类按钮
            QPushButton *noBtn = box.addButton(tr("NO(&N)"),QMessageBox::NoRole);//“否”的类按钮
        }
        else if(ui->cbox1->currentText() == "提示信息框")
        {
            box.setWindowTitle(tr("提示信息框"));
            box.setIcon(QMessageBox::Information);
            box.setText(tr("阿姆斯特朗加速回旋阿姆斯特朗炮发射准备！"));
            QPushButton *okBtn = box.addButton(tr("OK(&O)"),QMessageBox::YesRole);
        }
        else if(ui->cbox1->currentText() == "警告信息框")
        {
            box.setWindowTitle(tr("警告信息框"));
            box.setIcon(QMessageBox::Warning);
            box.setText(tr("<font size='4' color='red'>======樹 海 化 警 報======<br>===FORESTIZE  WARNING===</font>"));
            QPushButton *yesBtn = box.addButton(tr("WARNING(&W)"),QMessageBox::ActionRole);
        }
        else if(ui->cbox1->currentText() == "错误信息框")
        {
            box.setWindowTitle(tr("错误信息框"));
            box.setIcon(QMessageBox::Critical);
            box.setText(tr("<font color='red'>ERROR_</font><font color='cyan'>ZREO</font>"));
            QPushButton *yesBtn = box.addButton(tr("_(:3」∠)_"),QMessageBox::ActionRole);
        }
        else if(ui->cbox1->currentText() == "自定信息框")
        {
            box.setWindowTitle(tr("自定信息框"));
            box.setIconPixmap(QPixmap(":/MbDlg2.ico").scaled(QSize(50,50)));
            QPushButton *miaoBtn = box.addButton(tr("喵！"),QMessageBox::ActionRole);
            QPushButton *wangBtn = box.addButton(tr("汪？"),QMessageBox::ActionRole);
            QPushButton *mieBtn = box.addButton(tr("咩~"),QMessageBox::ActionRole);
            box.setText(tr("开启动物对话程序\n（并不能（笑\n%1").arg(ui->lineEdit->text()));
        }
        box.setStyleSheet(
                    "QMessageBox{"
                    "border-style:outset;"
                    "background-color:#484848;"
                    "}"
                    "QPushButton{"
                    " min-width:60px;"
                    " min-height:4px;"
                    "border-style:outset;"
                    "}");
        box.exec();//box结构执行
    }
    else if(ui->cbox1->currentText() == "关于Qt")
    {
        QMessageBox::aboutQt(this, tr("关于Qt"));
    }
}

void QUICreator::wizardDialog()//向导对话框
{
    QWizard wizard;
    wizard.addPage(createFirstPage());//添加向导页面
    wizard.addPage(createSecondPage());
    wizard.addPage(createThirdPage());
    wizard.setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);//去掉帮助按钮
    wizard.setWizardStyle(QWizard::ModernStyle);//设置向导样式
    wizard.setOption(QWizard::NoBackButtonOnStartPage);//开始页没有后退键
//    wizard.setOption(QWizard::NoBackButtonOnLastPage);//下一页没有后退键
//    wizard.setOption(QWizard::NoCancelButton);//没有取消键
    wizard.setTitleFormat(Qt::RichText);//设置页面主标题的显示格式
    wizard.setSubTitleFormat(Qt::RichText);//设置子标题显示格式
    wizard.setButtonText(QWizard::NextButton, "下一步");//设置按钮文本
    wizard.setButtonText(QWizard::BackButton, "上一步");
    wizard.setButtonText(QWizard::FinishButton, "执行");
    wizard.setMinimumHeight(480);//设置最小高
    wizard.setMinimumWidth(800);//设置最小宽
    wizard.setStyleSheet("QWizard{"
                         "background-color: #444444;"
                         "}"
                         "QPushButton{"
                         " min-width:60px;"
                         " min-height:4px;"
                         "background-color: blue;"
                         "}"
                         "QPushButton:hover{"
                         "background-color: red;"
                         "}"
                         "QPushButton:pressed{"
                         "background-color: white;"
                         "}");

    wizard.setWindowTitle(tr("向导对话框"));
    wizard.exec();
}

QWizardPage* QUICreator::createFirstPage()//向导第一页
{
    QWizardPage *page1 = new QWizardPage;//新建向导页1
    QLabel *WPlabel1_1 = new QLabel;//介绍标签
    QVBoxLayout *layout1 = new QVBoxLayout;//垂直布局

    page1->setTitle(tr("<font size='6' color='white'>-对逆熵智商压制武器安装向导-</font>"));//设置标题
    page1->setSubTitle(tr(" "));//设置空副标题，可以填充图片

    QIcon icon(":/Dlg1.png");
    QPixmap pix(QSize(800, 78));//设定绘制大小
    pix.fill(QColor(88,163,23));//填充颜色
    page1->setPixmap(QWizard::WatermarkPixmap, icon.pixmap(256));//设置侧边图标，图标比设定的小
    page1->setPixmap(QWizard::BannerPixmap, pix);//设置侧边图标，图标比设定的小
    page1->setPixmap(QWizard::LogoPixmap, QPixmap(":/MbDlg3.ico"));//设定右上角LOGO，有副标题才行

    WPlabel1_1->setText(tr("欢迎使用对逆熵智商压制武器安装向导<br><br>"
                           "安装向导将在你的琪亚娜上安装对逆熵智商压制武器<br>"
                           "版本V5.4.22<br><br>"
                           "建议你在继续安装之前保证琪亚娜为草履虫状态，且无法挽回。<br>"
                           "单击“下一步”继续，或单击“取消”退出安装。<br>"));
    WPlabel1_1->setWordWrap(true);//如果为true，则标签文本将在必要时换行（英文单词专用）
    WPlabel1_1->setStyleSheet("font:normal 15px;"
                              "background-color: #444444;");

    layout1->addWidget(WPlabel1_1);//布局内添加部件
    page1->setLayout(layout1);//设置布局

    return page1;
}

QWizardPage* QUICreator::createSecondPage()//向导第二页
{
    QWizardPage *page2 = new QWizardPage;//新建向导页2
    QLabel *Exepwd = new QLabel;//执行密码标签
    QLabel *Twover = new QLabel;//二次验证标签
    QLineEdit *ExepwdEdit = new QLineEdit;//执行密码输入框
    QLineEdit *TwoverEdit = new QLineEdit;//二次验证输入框
    QCheckBox *LLCheckBox = new QCheckBox;//伦理复选框
    QGroupBox *groupBox = new QGroupBox;//重构造分组框
    QRadioButton *YYRadioButton = new QRadioButton;//衣原单选框
    QRadioButton *ECRadioButton = new QRadioButton;//EC单选框
    QRadioButton *KCRadioButton = new QRadioButton;//枯草单选框
    QCheckBox *ZZCheckBox = new QCheckBox;//智商复选框
    QVBoxLayout *layout2 = new QVBoxLayout;//垂直布局
    QGridLayout *Glayout1 = new QGridLayout;//网格布局

    page2->setTitle(tr("<font size='5' color='white'>安装选项</font>"));
    page2->setSubTitle(tr("下列选项将决定你的安装细节。<font color='red'>（注意：某些选项将可能造成不可逆的事态）</font>"));

    QPixmap pix(QSize(800, 78));//设定绘制大小
    pix.fill(QColor(88,163,23));//填充颜色
    page2->setPixmap(QWizard::BannerPixmap,pix);//设定横幅，有副标题才行
    page2->setPixmap(QWizard::LogoPixmap, QPixmap(":/MbDlg4.ico"));//设定右上角LOGO，有副标题才行
//     page2->setPixmap(QWizard::BackgroundPixmap, QPixmap(":/MbDlg3.ico"));//不能有部件遮挡(大概

    Exepwd->setText(tr("执行密码(&Exepwd):"));//执行密码,&后的Q为快捷键，alt+q
    Exepwd->setBuddy(ExepwdEdit);//将部件设置为搭档，当用户使用快捷键时，焦点移动至搭档部件

    Twover->setText(tr("二次验证(&Twover):"));//二次验证
    Twover->setBuddy(TwoverEdit);

    LLCheckBox->setText(tr("是否去除伦理限制"));//复选框
    groupBox->setTitle(tr("是否进行重构造"));//分组框
    groupBox->setCheckable(true);//分组框选择项

    YYRadioButton->setText(tr("衣原体模式"));//单选框
    ECRadioButton->setText(tr("E.coli模式"));
    KCRadioButton->setText(tr("枯草芽孢杆菌模式"));
    ZZCheckBox->setText(tr("智商压制领域是否最大输出"));
    KCRadioButton->setChecked(true);//默认选择

    layout2->addWidget(YYRadioButton);//组框内的布局
    layout2->addWidget(ECRadioButton);
    layout2->addWidget(KCRadioButton);
    layout2->addWidget(ZZCheckBox);
    groupBox->setLayout(layout2);

    Glayout1->addWidget(Exepwd, 0, 0); //信息页的布局
    Glayout1->addWidget(ExepwdEdit, 0, 1);
    Glayout1->addWidget(Twover, 1, 0);
    Glayout1->addWidget(TwoverEdit, 1, 1);
    Glayout1->addWidget(LLCheckBox, 2, 0, 1, 2);
    Glayout1->addWidget(groupBox, 3, 0, 1, 2);
    page2->setLayout(Glayout1);
    page2->setStyleSheet("background-color: #444444;");

    connect(KCRadioButton, SIGNAL(toggled(bool)), ZZCheckBox, SLOT(setEnabled(bool)));//当选中默认时，开启多选框

    return page2;
}

QWizardPage* QUICreator::createThirdPage()//向导第三页
{
    QWizardPage *page3 = new QWizardPage;//新建向导页3
    QCheckBox *SHCheckBox = new QCheckBox;//圣痕复选框
    QCheckBox *RRCheckBox = new QCheckBox;//RR复选框
    QLabel *RRCLabel = new QLabel;//RR标签
    QLineEdit *RRCLineEdit = new QLineEdit;//RR输入框
    QTabWidget *TabW_Arm = new QTabWidget;//标签页项
    QTreeWidget *Twidget = new QTreeWidget;//树状项
    QGridLayout *Glayout2 = new QGridLayout;//网格布局

    page3->setTitle(tr("<font size='5' color='white'>附属武装选项</font>"));
    page3->setSubTitle(tr("附属武装将经由亚空间直接传送至对象坐标"));

    QPixmap pix(QSize(800, 78));//设定绘制大小
    pix.fill(QColor(88,163,23));//填充颜色
    page3->setPixmap(QWizard::BannerPixmap,pix);//设定横幅，有副标题才行
    page3->setPixmap(QWizard::LogoPixmap, QPixmap(":/MbDlg3.ico"));

    SHCheckBox->setText(tr("是否启用圣痕"));
    SHCheckBox->setChecked(true);//初始化为勾上

    RRCheckBox->setText(tr("是否使用完全武装支配术（Release Recollection）"));
    RRCheckBox->setChecked(true);//初始化为勾上

    RRCLabel->setText(tr("&Release Recollection Code："));// label和lineEdit
    RRCLabel->setBuddy(RRCLineEdit);
    RRCLineEdit->setPlaceholderText(tr("System Call,Enhance Armament......Release Recollection"));

    //新建第一个页面的部件
    Twidget->setHeaderLabel(tr("主武器选择")); //设置头的标题
//    Twidget->setHeaderHidden(true);//隐藏表头
    QTreeWidgetItem *group1 = new QTreeWidgetItem(Twidget);//创建新组
    group1->setText(0, "主武器");
    group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group1->setCheckState(0, Qt::PartiallyChecked);//设置本组有部分勾选
    QTreeWidgetItem *subItem11 = new QTreeWidgetItem(group1);//创建新元素于组下
    subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem11->setText(0, "武器1号");
    subItem11->setCheckState(0, Qt::Checked);//设置本元素勾选
    QTreeWidgetItem *subItem12 = new QTreeWidgetItem(group1);
    subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem12->setText(0, "武器2号");
    subItem12->setCheckState(0, Qt::Unchecked);//设置本元素未勾选
    QTreeWidgetItem *subItem13 = new QTreeWidgetItem(group1);
    subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem13->setText(0, "武器3号");
    subItem13->setCheckState(0, Qt::Unchecked);
    QTreeWidgetItem *subItem311 = new QTreeWidgetItem(subItem13);
    subItem311->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem311->setText(0, "武器3-1号");
    subItem311->setCheckState(0, Qt::Unchecked);
    QTreeWidgetItem *subItem312 = new QTreeWidgetItem(subItem13);
    subItem312->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem312->setText(0, "武器3-2号");
    subItem312->setCheckState(0, Qt::Unchecked);
    Twidget->expandAll();//扩展所有可扩展项目（否，则项目都为折叠状态）

    //新建第二个页面的部件
    QLabel *label = new QLabel("Hello Qt");

    //新建第三个页面的部件
    QPushButton *pushButton3 = new QPushButton("Click Me");

    //向QTabWidget中添加页面
    TabW_Arm->addTab(Twidget, "主武器");
    TabW_Arm->addTab(label, "副武器");
    TabW_Arm->addTab(pushButton3, "圣痕");

    Glayout2->setColumnMinimumWidth(0, 20);    //设置第一列的最小宽20像素
    Glayout2->addWidget(SHCheckBox, 0, 0, 1, 10);
    Glayout2->addWidget(RRCheckBox, 1, 0, 1, 10);
    Glayout2->addWidget(RRCLabel, 2, 1, 1, 2);
    Glayout2->addWidget(RRCLineEdit, 2, 3, 1, 5);
    Glayout2->addWidget(TabW_Arm, 4, 0, 1, 8);
    Glayout2->setRowStretch(3,1);//第几行，比例(空行用)
    page3->setLayout(Glayout2);

    //以多选框来设定部件启用
    connect(RRCheckBox, SIGNAL(toggled(bool)), RRCLabel, SLOT(setEnabled(bool)));
    connect(RRCheckBox, SIGNAL(toggled(bool)), RRCLineEdit, SLOT(setEnabled(bool)));

    return page3;
}

void QUICreator::errorDialog()//错误对话框
{
    QErrorMessage box;
    box.setWindowTitle(tr("错误消息框"));
    box.showMessage(tr("错误消息框实例1"));
    box.showMessage(tr("错误消息框实例2"));
    box.exec();
}

void QUICreator::inputDialog()//输入对话框
{
    QInputDialog *input = new QInputDialog(this);
    input->setMaximumHeight(120);
    input->setMaximumWidth(240);
    if(ui->cbox1->currentText() == "姓名框")
    {
        bool ok;
        QString name = input->getText(this, tr("姓名"), tr("请输入新的姓名:"), QLineEdit::Normal, "name", &ok);
        if(ok && !name.isEmpty())
        {
            ui->plainTextEdit->setPlainText(name);
        }
    }
    else if(ui->cbox1->currentText() == "性别框")
    {
        QStringList list;
        list << tr("男") << tr("女");
        bool ok;
        QString sex = input->getItem(this, tr("性别"), tr("请选择性别:"), list,0, false, &ok);
        if (ok)
        {
            ui->plainTextEdit->setPlainText(sex);
        }
    }
    else if(ui->cbox1->currentText() == "年龄框")
    {
        bool ok;
        int age = input->getInt(this, tr("年龄"), tr("请输入年龄:"), 20, 0, 150, 1, &ok);
        if(ok)
        {
            ui->spinBox->setValue(age);
        }
    }
    else if(ui->cbox1->currentText() == "身高框")
    {
        bool ok;
        double high = input->getDouble(this,tr("身高"), tr("请输入身高:"), 175.00, 0, 230.00, 1, &ok);
        if(ok)
        {
            ui->doubleSpinBox->setValue(high);
        }
    }
}

void QUICreator::passwordDialog()//密码对话框
{
    ui->plainTextEdit->setPlainText("密码：123456");
    QDialog *dlg11 = new QDialog;//新建Dialog
    dlg11->setMinimumSize(200, 100);//设置窗口最小值
    dlg11->setAttribute(Qt::WA_DeleteOnClose);//关闭窗口删除数据
    dlg11->setWindowFlags(Qt::Dialog| Qt::FramelessWindowHint);//窗口无边框
    dlg11->setStyleSheet("QDialog{"
                         "background-color:#444444;"
                         "border: 2px solid cornflowerblue;"
                         "}");

    QLabel *Label1 = new QLabel("神秘代码",dlg11);//标签：题头（一个字25*25）
    Label1->move(20,30);//位置
    Label1->resize(60,30);//大小
    Label1->setStyleSheet(
                "QLabel{"
                "border-style:outset;"                  //边框样式（inset/outset）
                "font:bold 15px Microsoft Yahei;"       //字体，字体大小
                "}");

    QLineEdit *LE1 = new QLineEdit(dlg11);
    LE1->move(90,30);
    LE1->resize(100,30);
    LE1->setEchoMode(QLineEdit::Password);
    LE1->setStyleSheet(
                "QLineEdit{"
                "border-style:outset;"                  //边框样式（inset/outset）
                "font:bold 15px Microsoft Yahei;"       //字体，字体大小
                "}");

    QPushButton *cancel_button = new QPushButton("确定",dlg11);//按钮：确定
    cancel_button->move(75,75);//按钮位置
    cancel_button->resize(60,20);//按钮大小
    cancel_button->setStyleSheet(
                "QPushButton{"
                "border: 2px solid dodgerblue;"
                "border-style:outset;"                  //边框样式（inset/outset）
                "font:bold 16px Microsoft Yahei;"       //字体，字体大小
                "}"
                "QPushButton:pressed{"                  //鼠标按下样式
                "background-color:#4882d6;"
                "}");

    connect(cancel_button, &QPushButton::clicked, [=](){
        if(LE1->text().trimmed() == tr("123456")){dlg11->accept();ui->plainTextEdit->setPlainText("密码正确");}
        else{customDialog("警告" ,"密码错误");LE1->clear();LE1->setFocus();}
        });
    dlg11->exec();
}

void QUICreator::progressDialog()//进度对话框
{
    QProgressDialog progress(tr("正在复制文件..."), tr("取消"), 0, 1000, this);
    QFont font("ZYSong18030",10);
    progress.setFont(font);

    progress.setWindowModality(Qt::WindowModal);//单一窗口模式
    progress.setWindowTitle(tr("进度对话框"));
    progress.show();
    for (int i = 0; i < 1000; i++) {
        ui->progressBar->setValue(i);//设置进度条当前值
        progress.setValue(i);//设置当前工作量
        qApp->processEvents();
        if (progress.wasCanceled())//如果取消则终止
            break;
        QTime dieTime = QTime::currentTime().addMSecs(1);//返回比当前时间晚n毫秒的时间
        while(QTime::currentTime() < dieTime)//直到当前时间到达指定时间
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//处理所有挂起事件
        //... 复制文件处理。
    }
    progress.setValue(1000);
}

void QUICreator::customDialog(QString a ,QString b)//自定义提示窗
{
    QDialog *dlg12 = new QDialog;//新建Dialog
    dlg12->setMinimumSize(100, 50);//设置窗口最小值
    dlg12->setAttribute(Qt::WA_DeleteOnClose);//关闭窗口删除数据
    dlg12->setWindowFlags(Qt::Dialog| Qt::FramelessWindowHint);//窗口无边框
    dlg12->setStyleSheet("QDialog{"
                         "background-color:#444444;"
                         "border: 2px solid cornflowerblue;"
                         "}");

    QLabel *Label1 = new QLabel(a,dlg12);//标签：题头（一个字25*25）
    Label1->move(20,20);//位置
    Label1->resize(125,30);//大小
    Label1->setStyleSheet(
                "QLabel{"
                "border-style:outset;"                  //边框样式（inset/outset）
                "font:bold 25px Microsoft Yahei;"       //字体，字体大小
                "}");

    QLabel *Label2 = new QLabel(b,dlg12);//标签：内容（一个字20*20）
    Label2->move(50,70);//位置
    Label2->resize(400,90);//大小
    Label2->setWordWrap(true);//自动换行
    Label2->setStyleSheet(
                "QLabel{"
                "border-style:outset;"                  //边框样式（inset/outset）
                "font:bold 20px Microsoft Yahei;"       //字体，字体大小
                "}");

    QPushButton *cancel_button = new QPushButton("确定",dlg12);//按钮：确定
    cancel_button->move(440,200);//按钮位置
    cancel_button->resize(60,30);//按钮大小
    cancel_button->setStyleSheet(
                "QPushButton{"
                "border: 2px solid dodgerblue;"
                "border-style:outset;"                  //边框样式（inset/outset）
                "font:bold 16px Microsoft Yahei;"       //字体，字体大小
                "}"
                "QPushButton:pressed{"                  //鼠标按下样式
                "background-color:#4882d6;"
                "}");

    connect(cancel_button, SIGNAL(clicked()), dlg12, SLOT(reject()));
    dlg12->exec();
}

QDateTime QUICreator::TimeSelector(QString a, QString b)//时间选择器
{
    QString TSbtnSss = tr("QPushButton{"
                          "border-style:outset;"   //边框样式（inset/outset）
                          "background-color:#008b8b;"
                          "border-radius: 0px;"
                          "border: 0px solid #242424;"
                          "}"
                          "QPushButton:pressed{"   //鼠标按下样式
                          "background-color:#4882d6;"
                          "}");

    QString TSleSss = tr("QLineEdit{"
                         "border: 0px solid #242424;"
                         "background-color:#008b8b;;"
                         "border-radius: 0px;"
                         "border-style:outset;"                  //边框样式（inset/outset）
                         "font:bold 25px Microsoft Yahei;"       //字体，字体大小
                         "}");

    QDialog *dlgTime = new QDialog(this);//新建Dialog
    dlgTime->setMinimumSize(100, 50);//设置窗口最小值
    dlgTime->setAttribute(Qt::WA_DeleteOnClose);//关闭窗口删除数据
    dlgTime->setWindowFlags(Qt::Dialog| Qt::FramelessWindowHint);//窗口无边框
    dlgTime->setStyleSheet("QDialog{"
                           "background-color:#444444;"
                           "border: 8px solid :#444444;"
                           "}");

    QPushButton *addmin = new QPushButton(dlgTime);//按钮：分加
    addmin->move(0,0);//按钮位置
    addmin->resize(60,40);//按钮大小
    addmin->setStyleSheet(TSbtnSss);

    QPushButton *submin = new QPushButton(dlgTime);//按钮：分减
    submin->move(0,70);//按钮位置
    submin->resize(60,40);//按钮大小
    submin->setStyleSheet(TSbtnSss);

    QPushButton *addsec = new QPushButton(dlgTime);//按钮：秒加
    addsec->move(60,0);//按钮位置
    addsec->resize(60,40);//按钮大小
    addsec->setStyleSheet(TSbtnSss);

    QPushButton *subsec = new QPushButton(dlgTime);//按钮：秒减
    subsec->move(60,70);//按钮位置
    subsec->resize(60,40);//按钮大小
    subsec->setStyleSheet(TSbtnSss);

    QPushButton *sure = new QPushButton("确定",dlgTime);//按钮：确定
    sure->move(0,110);//按钮位置
    sure->resize(120,30);//按钮大小
    sure->setStyleSheet(TSbtnSss.append("QPushButton{font:bold 18px Microsoft Yahei;}"));

    QLineEdit *Labelmin = new QLineEdit(a,dlgTime);//标签：内容（一个字20*20）
    Labelmin->move(0,40);//位置
    Labelmin->resize(60,30);//大小
    Labelmin->setAlignment(Qt::AlignCenter);//标签文字居中
    Labelmin->setEnabled(false);//不可编辑
    Labelmin->setStyleSheet(TSleSss);

    QLineEdit *Labelsec = new QLineEdit(b,dlgTime);//标签：内容（一个字20*20）
    Labelsec->move(60,40);//位置
    Labelsec->resize(60,30);//大小
    Labelsec->setAlignment(Qt::AlignCenter);//标签文字居中
    Labelsec->setEnabled(false);//不可编辑
    Labelsec->setStyleSheet(TSleSss);

    action::instance()->setIcon(addmin, 0xf106, 30);//按钮设置
    action::instance()->setIcon(submin, 0xf107, 30);//按钮设置
    action::instance()->setIcon(addsec, 0xf106, 30);//按钮设置
    action::instance()->setIcon(subsec, 0xf107, 30);//按钮设置

    connect(addmin, &QPushButton::pressed, [=](){
        buff=1;
        while(buff)
        {
        if(Labelmin->text().toInt()==23)
        {Labelmin->setText("00");}
        else if(Labelmin->text().toInt()<9 && 0<=Labelmin->text().toInt())
        {Labelmin->setText(tr("0%1").arg(QString::number(Labelmin->text().toInt()+1)));}
        else if(Labelmin->text().toInt()<23 && 9<=Labelmin->text().toInt())
        {Labelmin->setText(QString::number(Labelmin->text().toInt()+1));}
        QTime dieTime = QTime::currentTime().addMSecs(200);//返回比当前时间晚n毫秒的时间
        while(QTime::currentTime()<dieTime)//直到当前时间到达指定时间
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//处理所有挂起事件
        }
    });
    connect(submin, &QPushButton::pressed, [=](){
        buff=1;
        while(buff)
        {
        if(Labelmin->text().toInt()==0)
        {Labelmin->setText("23");}
        else if(Labelmin->text().toInt()<=10 && 0<Labelmin->text().toInt())
        {Labelmin->setText(tr("0%1").arg(QString::number(Labelmin->text().toInt()-1)));}
        else if(Labelmin->text().toInt()<=23 && 10<Labelmin->text().toInt())
        {Labelmin->setText(QString::number(Labelmin->text().toInt()-1));}
        QTime dieTime = QTime::currentTime().addMSecs(200);//返回比当前时间晚n毫秒的时间
        while(QTime::currentTime()<dieTime)//直到当前时间到达指定时间
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//处理所有挂起事件
        }
    });
    connect(addsec, &QPushButton::pressed, [=](){
        buff=1;
        while(buff)
        {
        if(Labelsec->text().toInt()==59)
        {Labelsec->setText("00");}
        else if(Labelsec->text().toInt()<9 && 0<=Labelsec->text().toInt())
        {Labelsec->setText(tr("0%1").arg(QString::number(Labelsec->text().toInt()+1)));}
        else if(Labelsec->text().toInt()<59 && 9<=Labelsec->text().toInt())
        {Labelsec->setText(QString::number(Labelsec->text().toInt()+1));}
        QTime dieTime = QTime::currentTime().addMSecs(100);//返回比当前时间晚n毫秒的时间
        while(QTime::currentTime()<dieTime)//直到当前时间到达指定时间
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//处理所有挂起事件
        }
    });
    connect(subsec, &QPushButton::pressed, [=](){
        buff=1;
        while(buff)
        {
        if(Labelsec->text().toInt()==0)
        {Labelsec->setText("59");}
        else if(Labelsec->text().toInt()<=10 && 0<Labelsec->text().toInt())
        {Labelsec->setText(tr("0%1").arg(QString::number(Labelsec->text().toInt()-1)));}
        else if(Labelsec->text().toInt()<=59 && 10<Labelsec->text().toInt())
        {Labelsec->setText(QString::number(Labelsec->text().toInt()-1));}
        QTime dieTime = QTime::currentTime().addMSecs(100);//返回比当前时间晚n毫秒的时间
        while(QTime::currentTime()<dieTime)//直到当前时间到达指定时间
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//处理所有挂起事件
        }
    });
    connect(sure, &QPushButton::clicked, [=](){
        TSime = QDateTime::fromString(tr("%1:%2").arg(Labelmin->text()).arg(Labelsec->text()), "HH:mm");
        dlgTime->close();
    });
    connect(addmin, &QPushButton::released, [=](){buff=0;});
    connect(submin, &QPushButton::released, [=](){buff=0;});
    connect(addsec, &QPushButton::released, [=](){buff=0;});
    connect(subsec, &QPushButton::released, [=](){buff=0;});

    dlgTime->exec();
    return TSime;
}

void QUICreator::singleStateChanged(int isChecked)//多选框信号改变
{
    if(isChecked == Qt::Checked)//当多选框信号改变时改变lineEdit提示文本
    {
        ui->lineEdit->setPlaceholderText(tr("请输入自定信息框文本"));
    }
    else
    {
        ui->lineEdit->setPlaceholderText(tr("请输入想要测试的样式表"));
    }
}

void QUICreator::singleStateChanged2(int isChecked)//多选框信号改变
{
    if(isChecked == Qt::Checked)//当多选框信号改变时改变lineEdit提示文本
    {
        ui->cbox1->clear();//清空表格
        QStringList MbDlg;//设置QString表
        MbDlg << "询问信息框" << "提示信息框" << "警告信息框" << "错误信息框" << "自定信息框" << "关于Qt";
        ui->cbox1->addItems(MbDlg);//把信息填充入下拉框1
        ui->btnInput->setDisabled(1);
        ui->btnInfo->setEnabled(1);
    }
    else
    {
        ui->cbox1->clear();//清空表格
        QStringList MbDlg;//设置QString表
        MbDlg << "姓名框" << "性别框" << "年龄框" << "身高框";
        ui->cbox1->addItems(MbDlg);//把信息填充入下拉框1
        ui->btnInfo->setDisabled(1);
        ui->btnInput->setEnabled(1);
    }
}

void QUICreator::TWUpdateChild(QTreeWidgetItem *itm)//树状子递归
{
    int childCount = itm->childCount();//返回子项目数
    if(childCount>0)//当子项目大于0时
    {
        for(int i=0;i<childCount;i++)
        {
            if(Qt::PartiallyChecked != itm->checkState(0))
            itm->child(i)->setCheckState(0,itm->checkState(0));//把父状态传递给子
            if(itm->child(i)->childCount()>0)//如果还存在子项目，则继续执行
                TWUpdateChild(itm->child(i));
        }
    }
}

void QUICreator::TWSetParentPartiallyChecked(QTreeWidgetItem *itm)//树状部分选中
{
    QTreeWidgetItem *parent = itm->parent();//返回项目父级
    if(parent)//如果父存在
    {
        parent->setCheckState(0,Qt::PartiallyChecked);//设置父级状态为部分选中
        TWSetParentPartiallyChecked(parent);
    }
}

void QUICreator::TWUpdateParent(QTreeWidgetItem *itm)//树状根判断
{
    QTreeWidgetItem *parent = itm->parent();//返回项目父级
    if(parent)
    {
        int checkedCount = 0;
        int patiallyCount = 0;
        int itemCount = parent->childCount();//子节点数
        if(itemCount>0)//当子项目大于0时
        {
            for(int i=0;i<itemCount;i++)
            {
                QTreeWidgetItem *item = parent->child(i);
                if(Qt::Checked == item->checkState(0))//如果项目为选中
                    checkedCount++;//则选中数加一
                else if(Qt::PartiallyChecked == item->checkState(0))//如果项目为部分选中
                    patiallyCount++;//则部分选中加一
            }
        }
        if(checkedCount <= 0)//如果选中数小于等于0
        {
            if(patiallyCount > 0)//如果部分选中数大于0
                goto Partially;//跳转至Partially
            else
                parent->setCheckState(0,Qt::Unchecked);//父节点设为未选中
        }
        else if(checkedCount > 0 && checkedCount < itemCount)//如果选中数大于0且不大于项目数
        {
            Partially:
            parent->setCheckState(0,Qt::PartiallyChecked);//父节点设为部分选中
            TWSetParentPartiallyChecked(parent);
            return;
        }
        else if(checkedCount > 0 && checkedCount == itemCount)//如果选中数等于项目数
        {
            parent->setCheckState(0,Qt::Checked);//父节点设为选中
        }
        //递归迭代
        TWUpdateParent(parent);//子节点根据父节点设置
    }
}

void QUICreator::cbox1Changed()//CBox1信号改变
{
//    ui->plainTextEdit->setPlainText(ui->cbox1->currentText());
}

void QUICreator::cbox2Changed(int col)//CBox2信号改变
{
    QStringList colorList = QColor::colorNames();  //返回Qt已知的颜色名
    QColor color = QColor(colorList[col]);//按位数选中颜色
    QRgb mRgb = qRgb(color.toRgb().red(),color.toRgb().green(),color.toRgb().blue());//转换颜色位RGB
    QString mRgbStr = QString::number(mRgb,16);//mRgb转mRgbStr（#66ccff)
    QString CHTML = mRgbStr.mid(2,6).prepend("#");//#接颜色后6位
    QString style = tr("QProgressBar{color: %1;}QProgressBar:chunk{background-color: %2;}").arg(colorInvert(CHTML)).arg(CHTML);//设置样式表
    QString styleSheet = ui->progressBar->styleSheet();//读取文本框样式表
    styleSheet.append(style);//把设定样式添加进原样式
    ui->progressBar->setStyleSheet(styleSheet);//设置文字样式
}

void QUICreator::CBColorChanged(int col)//CBColor信号改变
{
    QStringList colorList = QColor::colorNames();  //返回Qt已知的颜色名
    colorDM = QColor(colorList[col]);//按位数选中颜色
}

QString QUICreator::colorInvert(QString color)//颜色取反
{
    QString H1 = action::instance()->decToHex(QString::number(255-(action::instance()->hexToDec(color.mid(1,2))).toInt()),2);
    QString H2 = action::instance()->decToHex(QString::number(255-(action::instance()->hexToDec(color.mid(3,2))).toInt()),2);
    QString H3 = action::instance()->decToHex(QString::number(255-(action::instance()->hexToDec(color.mid(5,2))).toInt()),2);
    QString HColor = "#"+H1+H2+H3;
    qDebug()<<color;
    qDebug()<<HColor;
    return HColor;
}

void QUICreator::TEditHighlight()//下方文本框选中高亮
{
    QPalette editpalete = ui->txtMain->palette();
    editpalete.setColor(QPalette::Highlight,QColor(33,106,197));//高亮颜色
    editpalete.setColor(QPalette::HighlightedText,QColor(25,245,159));//高亮文字颜色
    ui->plainTextEdit->setPalette(editpalete);
}

void QUICreator::hSliderValue(int num)//滑动条值改变
{
    ui->progressBar->setValue(num);
}

void QUICreator::danmuku()//弹幕小组件
{
    QPalette danmupal;//绘制
    QFont danmufont;//字体
    int danmutime;//时间
    QString danmumode;//模式
    QStringList danmulist;//列表

    if(ui->CBMode->currentText() == "DANMU")
    {
        danmufont.setFamily("Microsoft Yahei");//字体
        danmufont.setPointSize(ui->CBSize->currentText().toInt());//字体大小
        danmutime = ui->CBFont->currentText().toInt();//时间
        danmumode = "DANMU";//模式
        danmulist.append(ui->danmuLE->text());//读取输入文字
        danmupal.setColor(QPalette::Window, Qt::black);//背景色
        danmupal.setColor(QPalette::WindowText, colorDM);//字体色
    }
    else
    {
        danmufont.setFamily("ZYSong18030");//字体
        danmufont.setPointSize(30);
        danmutime = 10;//时间
        danmulist<<"233333"<<"hhhhhhh"<<"红红火火恍恍惚惚"<<"emmmmmmm";
        danmupal.setColor(QPalette::Window, Qt::black);//背景色
        danmupal.setColor(QPalette::WindowText, Qt::red);//字体色

        if(ui->CBMode->currentText() == "L2R_Model")
        {
            danmumode = "L2R_Model";//模式
        }
        else if(ui->CBMode->currentText() == "LR_Model")
        {
            danmumode = "LR_Model";//模式
        }
        else if(ui->CBMode->currentText() == "R2L_Model")
        {
            danmumode = "R2L_Model";//模式
        }
    }
    danmuku::instance()->danmukuNO1(ui->danmukuP,danmupal,danmufont,danmutime,danmumode,danmulist);//传递ui指针
}

void QUICreator::mainSBtn()//主界面start按钮
{
    if(ui->lineEdit->text() != NULL)
    {
        if(ui->ck1->isChecked())
        {
            QString ntext;
            ntext = ui->plainTextEdit->toPlainText();
            ntext.append(ui->lineEdit->text());
            ntext.append("\n");
            ui->plainTextEdit->setPlainText(ntext);
            ui->lineEdit->clear();
        }
        else
        {
            if(ui->lineEdit->text().contains("QPushButton"))
            {

            }
            else if(ui->lineEdit->text().contains("QLabel"))
            {

            }
            else if(ui->lineEdit->text().contains("QScrollBar"))
            {

            }
            else if(ui->lineEdit->text().contains("QComboBox"))
            {

            }
            else if(ui->lineEdit->text().contains("QSpinBox"))
            {

            }
            else if(ui->lineEdit->text().contains("QLineEdit"))
            {

            }
        }
    }
}

void QUICreator::btnstyler()//按钮样式
{
    OBName = "按钮";
    Btnstyler *btn = new Btnstyler();
    btn->setAttribute(Qt::WA_DeleteOnClose);//关闭窗口删除数据
    btn->show();  
}

void QUICreator::labelstyler()//按钮样式
{
    OBName = "标签";
    Btnstyler *label = new Btnstyler();
    label->setAttribute(Qt::WA_DeleteOnClose);//关闭窗口删除数据
    label->show();
}

void QUICreator::scrollbarstyler()//滚动条样式
{
    OBName = "滚动条";
    Btnstyler *scrollbar = new Btnstyler();
    scrollbar->setAttribute(Qt::WA_DeleteOnClose);//关闭窗口删除数据
    scrollbar->show();
}

void QUICreator::sliderstyler()//滑动条样式
{
    OBName = "滑动条";
    Btnstyler *slider = new Btnstyler();
    slider->setAttribute(Qt::WA_DeleteOnClose);//关闭窗口删除数据
    slider->show();
}

void QUICreator::comboboxstyler()//下拉框样式
{
    OBName = "下拉框";
    Btnstyler *combobox = new Btnstyler();
    combobox->setAttribute(Qt::WA_DeleteOnClose);//关闭窗口删除数据
    combobox->show();
}

void QUICreator::spinboxstyler()//选值框样式
{
    OBName = "选值框";
    Btnstyler *spinbox = new Btnstyler();
    spinbox->setAttribute(Qt::WA_DeleteOnClose);//关闭窗口删除数据
    spinbox->show();
}

void QUICreator::btnContextMenu(QString btn)//显示右键菜单
{
    btnRight = btn;//按钮名称存为全局变量

    actionCode->setText(QString("显示源代码"));//设置右键菜单动作名称
    actionStyleSheet->setText(QString("显示样式表"));
    actionTest->setTitle(QString("多级测试项目"));
    actionOnlyTest->setText(QString("右键菜单代码"));

    actionMenu->clear();//菜单原项目清除 
    actionMenu->addAction(actionCode);//添加动作
    actionMenu->addAction(actionStyleSheet);//添加动作
    actionMenu->addMenu(actionTest);//添加子菜单
    actionTest->addAction(actionOnlyTest);//添加动作
    actionMenu->exec(QCursor::pos());//显示在鼠标指针处
}

void QUICreator::sourceCode()//源代码
{
    QString SCode;
    //根据按钮执行函数
    if(btnRight == NULL){}
    else if(btnRight == "btnTextColor")
    {
        SCode = action::instance()->btnTextColor();//提取源代码
    }
    else if(btnRight == "btnPanelColor")
    {
        SCode = action::instance()->btnPanelColor();//提取源代码
    }
    else if(btnRight == "btnBorderColor")
    {
        SCode = action::instance()->btnBorderColor();//提取源代码
    }
    else if(btnRight == "btnFontSettings")
    {
        SCode = action::instance()->btnFont();//提取源代码
    }
    else if(btnRight == "btnPageSettings")
    {
        SCode = action::instance()->btnPage();//提取源代码
    }
    else if(btnRight == "tbtn1")
    {
        SCode = action::instance()->btnSSS();//提取源代码
    }
    ui->txtMain->setPlainText(SCode);//在主文本框显示代码
}

void QUICreator::styleSheet()//样式表
{
    QString SCode;
    if(btnRightNum == 1)
    {
        if(btnRight == "tbtn1")
        {
            SCode = action::instance()->btnSSS();//提取源代码
        }
        else if(btnRight == "tbtn2")
        {
            btnstyler();//按钮样式
        }
    }
    else if(btnRightNum == 2)
    {
        if(btnRight == "tbtn1")
        {
            SCode = action::instance()->labSSS();//提取源代码
        }
        else if(btnRight == "tbtn2")
        {
            labelstyler();//标签样式
        }
    }
    else if(btnRightNum == 3)
    {
        if(btnRight == "tbtn1")
        {
            SCode = action::instance()->scbSSS();//提取源代码
        }
        else if(btnRight == "tbtn2")
        {
            scrollbarstyler();//滚动条样式
        }
    }
    else if(btnRightNum == 4)
    {
        if(btnRight == "tbtn1")
        {
            SCode = action::instance()->sldSSS();//提取源代码
        }
        else if(btnRight == "tbtn2")
        {
            sliderstyler();//滑动条样式
        }
    }
    else if(btnRightNum == 5)
    {
        if(btnRight == "tbtn1")
        {
            SCode = action::instance()->cboxSSS();//提取源代码
        }
        else if(btnRight == "tbtn2")
        {
            comboboxstyler();//下拉框样式
        }
    }
    else if(btnRightNum == 6)
    {
        if(btnRight == "tbtn1")
        {
            SCode = action::instance()->spbSSS();//提取源代码
        }
        else if(btnRight == "tbtn2")
        {
            spinboxstyler();//选值框样式
        }
    }
    else if(btnRightNum == 7)
    {
        if(btnRight == "tbtn1")
        {
            SCode = action::instance()->leditSSS();//提取源代码
        }
    }
    else if(btnRightNum == 8)
    {
        if(btnRight == "tbtn1")
        {
            SCode = action::instance()->calSSS();//提取源代码
        }
    }
    ui->txtMain->setPlainText(SCode);//在主文本框显示代码
}


void QUICreator::newFile()//新建文件
{
    if(maybeSave())//判断文件被更改
    {
        isUntitled = true;//初始化文件为未保存状态
        curFile =tr("未命名.txt");//初始化文件名为“未命名.txt”
        ui->txtMain->clear();//清空内容
        ui->txtMain->setEnabled(true);//主文本框启用
//        ui->txtMain->setFocusPolicy(Qt::StrongFocus);//主文本框获得强焦点
//        ui->txtMain->setText("66666");
    }
    QPalette editpalete = ui->txtMain->palette();
    editpalete.setColor(QPalette::Highlight,QColor(33,106,197));//高亮颜色
    editpalete.setColor(QPalette::HighlightedText,QColor(25,245,159));//高亮文字颜色
    ui->txtMain->setPalette(editpalete);
    ui->txtMain->setPlaceholderText(tr("请以下列各式书写样式表：\n"
                                       "xx.setStyleSheet(\n"
                                       "\"QMessageBox{\"\n"
                                       "\"border-style:outset;\"\n"
                                       "\"}\"\n"));
}

bool QUICreator::maybeSave()//如果文档被更改了
{
    if(ui->txtMain->document()->isModified())//自定义一个警告对话框，检测textEdit的文档内容是否已修改
    {
        QMessageBox box;//信息盒结构体
        box.setWindowTitle(tr("警告"));//窗口标题
        box.setIcon(QMessageBox::Warning);//窗口图标
        box.setText(curFile + tr("尚未保存，是否保存？"));//窗口内容=文件名+tr内容
        QPushButton *yesBtn = box.addButton(tr("是(&Y)"),QMessageBox::YesRole);//“是”的类按钮
        box.addButton(tr("否(&N)"),QMessageBox::NoRole);//“否”的类按钮
        QPushButton *cancelBut = box.addButton(tr("取消"),QMessageBox::RejectRole);//“取消”的类按钮
        box.setStyleSheet(
                    "QMessageBox{"
                    "border-style:outset;"
                    "background-color:#484848;"
                    "}"
                    "QPushButton{"
                    " min-width:60px;"
                    " min-height:4px;"
                    "border-style:outset;"
                    "}");
        box.exec();//box结构执行
        if(box.clickedButton() == yesBtn)//如果点击yes按钮，则执行save()
            return save();
        else if(box.clickedButton() == cancelBut)//如果点击cancel按钮，则取消执行
            return false;
    }
    return true;//如果文档没有被更改，则直接返回true
}

bool QUICreator::save()//文档保存
{
    if(isUntitled)//检查isUntitled标签是否为true（未保存），执行saveAs()
        return saveAs();
    else//isUntitled标签为false（已保存），执行saveFile，保存到文件地址
        return saveFile(curFile);//窗口标题=地址+文件名
}

bool QUICreator::saveAs()//文档另存为
{
    //保存文件框，标题“另存为”，返回用户选择地址和文件名，使用路径保存文件，设置fileName=地址+文件名
    QString fileName = QFileDialog::getSaveFileName(this,tr("另存为"),curFile);
    if(fileName.isEmpty())//如果文件名为空，则保存失败
        return false;
    return saveFile(fileName);//窗口标题=地址+文件名
}

bool QUICreator::saveFile(const QString &fileName)//文件保存操作
{
    QFile file(fileName);//指向文件
    if(!file.open(QFile::WriteOnly | QFile::Text))//如果不能使用文本方式将其打开或文件不是只写
    {
        QMessageBox box;//信息盒结构体
        box.setWindowTitle(tr("多文档编辑器"));//窗口标题
        box.setIcon(QMessageBox::Warning);//窗口图标
        box.setText(tr("无法写入文档 %1： %2").arg(fileName).arg(file.errorString()));//%1文件名，%2返回错误描述
        box.addButton(tr("是(&Y)"),QMessageBox::YesRole);//“是”的类按钮
        box.setStyleSheet(
                    "QMessageBox{"
                    "border-style:outset;"
                    "background-color:#484848;"
                    "}"
                    "QPushButton{"
                    " min-width:60px;"
                    " min-height:4px;"
                    "border-style:outset;"
                    "}");
        box.exec();//box结构执行
        return false;
    }
    QTextStream out(&file);//QTextStream文本流将编辑器中的内容写入到文件中
    QApplication::setOverrideCursor(Qt::WaitCursor);//鼠标指针变为等待状态，转圈
    out << ui->txtMain->toPlainText();//将编辑器内的文本作为纯文本写入到文件中
    QApplication::restoreOverrideCursor();//鼠标指针恢复原来的状态
    isUntitled = false;//isUntitled标签为false
    curFile = QFileInfo(fileName).canonicalFilePath();//获得文件标准路径
    ui->txtMain->document()->setModified(false);//保存过后，设置文本修改标志为否
    return true;
}

bool QUICreator::loadFile(const QString &fileName)//加载文件
{
    QFile file(fileName);//指向文件
    if(!file.open(QFile::ReadOnly | QFile::Text))//如果不能使用文本方式将其打开或文件不是只读
    {
        QMessageBox box;//信息盒结构体
        box.setWindowTitle(tr("多文档编辑器"));//窗口标题
        box.setIcon(QMessageBox::Warning);//窗口图标
        box.setText(tr("无法读取文件 %1： %2").arg(fileName).arg(file.errorString()));//%1文件名，%2返回错误描述
        box.addButton(tr("是(&Y)"),QMessageBox::YesRole);//“是”的类按钮
        box.setStyleSheet(
                    "QMessageBox{"
                    "border-style:outset;"
                    "background-color:#484848;"
                    "}"
                    "QPushButton{"
                    " min-width:60px;"
                    " min-height:4px;"
                    "border-style:outset;"
                    "}");
        box.exec();//box结构执行
        return false;
    }
    QTextStream in(&file);//QTextStream文本流将文件内容写入到编辑器中
    QApplication::setOverrideCursor(Qt::WaitCursor);//鼠标指针变为等待状态，转圈
    ui->txtMain->setPlainText(in.readAll());//读取文件的全部文本内容，写入到编辑器中
    QApplication::restoreOverrideCursor();//鼠标指针恢复原来的状态
    curFile = QFileInfo(fileName).canonicalFilePath();//获得文件标准路径
    QPalette editpalete = ui->txtMain->palette();
    editpalete.setColor(QPalette::Highlight,QColor(33,106,197));//高亮颜色
    editpalete.setColor(QPalette::HighlightedText,QColor(25,245,159));//高亮文字颜色
    ui->txtMain->setPalette(editpalete);
    return true;
}

void QUICreator::openFile()//打开文件
{
    if(maybeSave())
    {
        //打开文件框，标题“打开…”，读取用户选择地址和文件名，设置fileName=地址+文件名
        QString fileName = QFileDialog::getOpenFileName(this,tr("打开…"));
        if(!fileName.isEmpty())//如果文件名不为空，则加载文件
        {
            loadFile(fileName);//读取文件
            ui->txtMain->setEnabled(true);//主文本框启用
        }
    }
}

void QUICreator::on_action_O_triggered()//打开
{
    openFile();
}

void QUICreator::on_action_N_triggered()//新建
{
    newFile();
}

void QUICreator::on_action_S_triggered()//保存
{
    save();
}

void QUICreator::on_action_AS_triggered()//另存为
{
    saveAs();
}

void QUICreator::on_action_C_triggered()//退出
{
    qApp->quit();//再退出程序，qApp是指向应用程序的全局指针
}

void QUICreator::closeEvent(QCloseEvent *event)//关闭事件
{
    if(maybeSave())//如果maybeSave返回true，则关闭程序
        event->accept();
    else//否则忽略该事件
        event->ignore();
}
