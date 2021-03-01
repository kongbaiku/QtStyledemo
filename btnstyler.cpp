#include "btnstyler.h"
#include "ui_btnstyler.h"
#include "quicreator.h"
#include <QColorDialog>

extern QString OBName;

Btnstyler::Btnstyler(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Btnstyler)
{
    ui->setupUi(this);  
    initPreview();//预览初始化
    initCheck();//勾选初始化
    initForm();//初始化界面
    initTreeWidget();//树状控件初始化
    initSignalSlot();//信号槽初始化
    updateStylesheet();//更新样式表
}

Btnstyler::~Btnstyler()//析构函数
{
    delete ui;
}

void Btnstyler::initPreview()//预览初始化
{
    if(OBName == "标签")
    {
        textLabel = new QLabel(ui->groupBox);
        textLabel->setText("textLabel");
        textLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        textLabel->setAlignment(Qt::AlignCenter);
        ui->groupBox->layout()->replaceWidget(ui->pushButton, textLabel);
        delete ui->pushButton;
    }
    else if(OBName == "滚动条")
    {
        vScrollBar = new QScrollBar(ui->groupBox);
        vScrollBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        ui->groupBox->layout()->replaceWidget(ui->pushButton, vScrollBar);
        delete ui->pushButton;
        ui->FontBox->setChecked(0);//取消字体勾选
    }
    else if(OBName == "滑动条")
    {
        vSlider = new QSlider(ui->groupBox);
        vSlider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        ui->groupBox->layout()->replaceWidget(ui->pushButton, vSlider);
        delete ui->pushButton;
        ui->FontBox->setChecked(0);//取消字体勾选
    }
    else if(OBName == "下拉框")
    {
        cbox = new QComboBox(ui->groupBox);
        cbox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        cbox->addItem("例示1");
        cbox->addItem("例示2");
        cbox->addItem("例示3");
        ui->groupBox->layout()->replaceWidget(ui->pushButton, cbox);
        delete ui->pushButton;
    }
    else if(OBName == "选值框")
    {
        sbox = new QSpinBox(ui->groupBox);
        sbox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        ui->groupBox->layout()->replaceWidget(ui->pushButton, sbox);
        delete ui->pushButton;
    }
}

void Btnstyler::initCheck()//勾选初始化
{
    //树状图勾选初始化
    group1_flag = 0;
    subItem11_flag = 0;
    subItem12_flag = 0;
    subItem13_flag = 0;
    group2_flag = 0;
    subItem21_flag = 0;
    subItem211_flag = 0;
    subItem212_flag = 0;
    subItem213_flag = 0;
    subItem214_flag = 0;
    subItem31_flag = 0;
    subItem311_flag = 0;
    subItem312_flag = 0;
    subItem313_flag = 0;
    subItem41_flag = 0;
    subItem411_flag = 0;
    subItem412_flag = 0;
    subItem413_flag = 0;

    //控件启用标志
    FrameBox_Flag=ui->FrameBox->isChecked();
    BtnBox_Flag=ui->BtnBox->isChecked();
    FontBox_Flag=ui->FontBox->isChecked();
    PadBox_Flag=ui->PadBox->isChecked();
    GradBox_Flag=ui->GradBox->isChecked();
}

void Btnstyler::initForm()//初始化界面
{
    //设置样式对象名称
    QFont ft;
    ft.setPointSize(14);//14号字
    ui->label_OBN->setText(OBName);//设置名称
    ui->label_OBN->setFont(ft);//设置字体

    //设置样式初值
    //边角
    borderRadius=11;//圆角半径初值
    border=2;//按钮边框宽度初值
    solid="#000000";//按钮边框颜色初值

    //大小
    minheight=15;//最小高
    minwidth=80;//最小宽

    //字体
    fontFamily="MS Shell Dlg 2";//初始字体-宋体
    fontSize=8;//字体大小初值
    color="#000000";//字体颜色初值

    //衬垫
    padding_U=8;//按钮衬垫
    padding_D=8;//按钮衬垫
    padding_L=8;//按钮衬垫
    padding_R=8;//按钮衬垫

    //渐变
    gradyanType="None";//渐变类型初值
    bgGrad_cx=0.3;//主光轴点初值
    bgGrad_cy=-0.4;
    bgGrad_fx=0.3;//焦距初值
    bgGrad_fy=-0.4;

    bgGrad2_cx=0.4;//主光轴点初值
    bgGrad2_cy=-0.1;
    bgGrad2_fx=0.4;//焦距初值
    bgGrad2_fy=-0.1;

    bgGrad_radius=1.35;//渐变半径初值

    bgGrad_stop0="#ffffff";//渐变普通颜色初值（上沿）
    bgGrad_stop11="#98928c";//渐变普通颜色初值（下沿）
    bgGrad_stop12="#989592";//渐变悬停颜色初值（下沿）
    bgGrad_stop13="#989795";//渐变按下颜色初值（下沿）

    //滑动条
    ui->minheightSlider->setValue(minheight);//设置高度滑动条初值
    ui->minwidthSlider->setValue(minwidth);//设置宽度滑动条初值
    ui->bordThickSlider->setValue(border);//设置边框宽度滑动条初值
    ui->fontSizeSlider->setValue(fontSize);//设置字体大小滑动条初值
    ui->bordRadSlider->setValue(borderRadius);//设置圆角半径滑动条初值
    ui->PadUpSlider->setValue(padding_U);//设置衬垫滑动条初值
    ui->PadDownSlider->setValue(padding_D);//设置衬垫滑动条初值
    ui->PadLeftSlider->setValue(padding_L);//设置衬垫滑动条初值
    ui->PadRightSlider->setValue(padding_R);//设置衬垫滑动条初值
    ui->gRadiusSlider->setValue(bgGrad_radius*100);//设置渐变半径滑动条初值

    //颜色标签
    ui->grenkLabel1->setPalette(QPalette(QColor(bgGrad_stop0)));//设置渐变颜色预览标签
    ui->grenkLabel1->setAutoFillBackground(true);//小部件背景自动填充
    ui->grenkLabel2->setPalette(QPalette(QColor(bgGrad_stop11)));//设置渐变颜色预览标签
    ui->grenkLabel2->setAutoFillBackground(true);//小部件背景自动填充
    ui->grenkLabel3->setPalette(QPalette(QColor(bgGrad_stop12)));//设置渐变颜色预览标签
    ui->grenkLabel3->setAutoFillBackground(true);//小部件背景自动填充
    ui->grenkLabel4->setPalette(QPalette(QColor(bgGrad_stop13)));//设置渐变颜色预览标签
    ui->grenkLabel4->setAutoFillBackground(true);//小部件背景自动填充
    ui->renkLabel->setPalette(QPalette(QColor(color)));//设置字体颜色预览标签
    ui->renkLabel->setAutoFillBackground(true);//小部件背景自动填充
    ui->renkLabel2->setPalette(QPalette(QColor(solid)));//设置边框颜色预览标签
    ui->renkLabel2->setAutoFillBackground(true);//小部件背景自动填充
    ui->fontComboBox->setCurrentFont(QFont(fontFamily));//设置当前选中字体
}

void Btnstyler::initTreeWidget()//树状控件初始化
{
    ui->treeWidget->clear();//清除树状控件所有项目
    ui->treeWidget->setHeaderLabel(" 树状列表控件");//设置标题头标签

    group1 = new QTreeWidgetItem(ui->treeWidget);//创建新组
    group1->setText(0, "主样式");
    //设置组可以可以由用户勾选（否，则本元素不可以勾选）
    //设置组启用用户互交（否，则本组都不可改变）
    //设置组可以被选中（否，则本元素不可选中）
    group1->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group1->setCheckState(0, Qt::Checked);//设置本组有部分勾选

    subItem11 = new QTreeWidgetItem(group1);//创建新元素于组下
    subItem11->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem11->setText(0, "正常样式");
    subItem11->setCheckState(0, Qt::Checked);//设置本元素勾选

    subItem12 = new QTreeWidgetItem(group1);
    subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem12->setText(0, "悬停样式");
    subItem12->setCheckState(0, Qt::Unchecked);//设置本元素未勾选

    subItem13 = new QTreeWidgetItem(group1);
    subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem13->setText(0, "按压样式");
    subItem13->setCheckState(0, Qt::Unchecked);

    if(OBName == "滚动条")
    {
        group2 = new QTreeWidgetItem(ui->treeWidget);
        group2->setText(0, "局部样式");
        group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        group2->setCheckState(0, Qt::Unchecked);

        subItem21 = new QTreeWidgetItem(group2);
        subItem21->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem21->setText(0, "滑块");
        subItem21->setCheckState(0, Qt::Unchecked);

        subItem211 = new QTreeWidgetItem(subItem21);
        subItem211->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem211->setText(0, "滑块悬停");
        subItem211->setCheckState(0, Qt::Unchecked);

        subItem212 = new QTreeWidgetItem(subItem21);
        subItem212->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem212->setText(0, "滑块按压");
        subItem212->setCheckState(0, Qt::Unchecked);

        subItem213 = new QTreeWidgetItem(subItem21);
        subItem213->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem213->setText(0, "滑块上槽");
        subItem213->setCheckState(0, Qt::Unchecked);

        subItem214 = new QTreeWidgetItem(subItem21);
        subItem214->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem214->setText(0, "滑块下槽");
        subItem214->setCheckState(0, Qt::Unchecked);

        subItem31 = new QTreeWidgetItem(group2);
        subItem31->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem31->setText(0, "上箭头");
        subItem31->setCheckState(0, Qt::Unchecked);

        subItem311 = new QTreeWidgetItem(subItem31);
        subItem311->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem311->setText(0, "上箭头悬停");
        subItem311->setCheckState(0, Qt::Unchecked);

        subItem312 = new QTreeWidgetItem(subItem31);
        subItem312->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem312->setText(0, "上箭头按压");
        subItem312->setCheckState(0, Qt::Unchecked);

        subItem313 = new QTreeWidgetItem(subItem31);
        subItem313->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem313->setText(0, "上箭头边线");
        subItem313->setCheckState(0, Qt::Unchecked);

        subItem41 = new QTreeWidgetItem(group2);
        subItem41->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem41->setText(0, "下箭头");
        subItem41->setCheckState(0, Qt::Unchecked);

        subItem411 = new QTreeWidgetItem(subItem41);
        subItem411->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem411->setText(0, "下箭头悬停");
        subItem411->setCheckState(0, Qt::Unchecked);

        subItem412 = new QTreeWidgetItem(subItem41);
        subItem412->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem412->setText(0, "下箭头按压");
        subItem412->setCheckState(0, Qt::Unchecked);

        subItem413 = new QTreeWidgetItem(subItem41);
        subItem413->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem413->setText(0, "下箭头边线");
        subItem413->setCheckState(0, Qt::Unchecked);
    }

    if(OBName == "滑动条")
    {
        group2 = new QTreeWidgetItem(ui->treeWidget);
        group2->setText(0, "局部样式");
        group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        group2->setCheckState(0, Qt::Unchecked);

        subItem21 = new QTreeWidgetItem(group2);
        subItem21->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem21->setText(0, "滑块");
        subItem21->setCheckState(0, Qt::Unchecked);

        subItem211 = new QTreeWidgetItem(subItem21);
        subItem211->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem211->setText(0, "滑块悬停");
        subItem211->setCheckState(0, Qt::Unchecked);

        subItem212 = new QTreeWidgetItem(subItem21);
        subItem212->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem212->setText(0, "滑块按压");
        subItem212->setCheckState(0, Qt::Unchecked);

        subItem213 = new QTreeWidgetItem(subItem21);
        subItem213->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem213->setText(0, "滑块上槽");
        subItem213->setCheckState(0, Qt::Unchecked);

        subItem214 = new QTreeWidgetItem(subItem21);
        subItem214->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem214->setText(0, "滑块下槽");
        subItem214->setCheckState(0, Qt::Unchecked);

        subItem31 = new QTreeWidgetItem(group2);
        subItem31->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem31->setText(0, "滑动槽");
        subItem31->setCheckState(0, Qt::Unchecked);
    }

    if(OBName == "下拉框")
    {
        group2 = new QTreeWidgetItem(ui->treeWidget);
        group2->setText(0, "局部样式");
        group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        group2->setCheckState(0, Qt::Unchecked);

        subItem21 = new QTreeWidgetItem(group2);
        subItem21->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem21->setText(0, "下拉按钮");
        subItem21->setCheckState(0, Qt::Unchecked);

        subItem211 = new QTreeWidgetItem(subItem21);
        subItem211->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem211->setText(0, "按钮悬停");
        subItem211->setCheckState(0, Qt::Unchecked);

        subItem212 = new QTreeWidgetItem(subItem21);
        subItem212->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem212->setText(0, "按钮按压");
        subItem212->setCheckState(0, Qt::Unchecked);

        subItem213 = new QTreeWidgetItem(subItem21);
        subItem213->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem213->setText(0, "按钮箭头");
        subItem213->setCheckState(0, Qt::Unchecked);

        subItem31 = new QTreeWidgetItem(group2);
        subItem31->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem31->setText(0, "下拉列表");
        subItem31->setCheckState(0, Qt::Unchecked);
    }

    if(OBName == "选值框")
    {
        group2 = new QTreeWidgetItem(ui->treeWidget);
        group2->setText(0, "局部样式");
        group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        group2->setCheckState(0, Qt::Unchecked);

        subItem21 = new QTreeWidgetItem(group2);
        subItem21->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem21->setText(0, "减值按钮");
        subItem21->setCheckState(0, Qt::Unchecked);

        subItem211 = new QTreeWidgetItem(subItem21);
        subItem211->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem211->setText(0, "按钮悬停");
        subItem211->setCheckState(0, Qt::Unchecked);

        subItem212 = new QTreeWidgetItem(subItem21);
        subItem212->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem212->setText(0, "按钮按压");
        subItem212->setCheckState(0, Qt::Unchecked);

        subItem213 = new QTreeWidgetItem(subItem21);
        subItem213->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem213->setText(0, "按钮箭头");
        subItem213->setCheckState(0, Qt::Unchecked);

        subItem214 = new QTreeWidgetItem(subItem21);
        subItem214->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem214->setText(0, "按钮封值");
        subItem214->setCheckState(0, Qt::Unchecked);

        subItem31 = new QTreeWidgetItem(group2);
        subItem31->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem31->setText(0, "增值按钮");
        subItem31->setCheckState(0, Qt::Unchecked);

        subItem311 = new QTreeWidgetItem(subItem31);
        subItem311->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem311->setText(0, "按钮悬停");
        subItem311->setCheckState(0, Qt::Unchecked);

        subItem312 = new QTreeWidgetItem(subItem31);
        subItem312->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem312->setText(0, "按钮按压");
        subItem312->setCheckState(0, Qt::Unchecked);

        subItem313 = new QTreeWidgetItem(subItem31);
        subItem313->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem313->setText(0, "按钮箭头");
        subItem313->setCheckState(0, Qt::Unchecked);

        subItem314 = new QTreeWidgetItem(subItem31);
        subItem314->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem314->setText(0, "按钮封值");
        subItem314->setCheckState(0, Qt::Unchecked);
    }

    ui->treeWidget->expandAll();//扩展所有可扩展项目（否，则项目都为折叠状态）
}

void Btnstyler::initSignalSlot()//信号槽初始化
{
    connect(ui->FrameBox, &QGroupBox::clicked, this, &Btnstyler::FrameBoxChecked);//启用标志槽
    connect(ui->BtnBox, &QGroupBox::clicked, this, &Btnstyler::BtnBoxChecked);
    connect(ui->FontBox, &QGroupBox::clicked, this, &Btnstyler::FontBoxChecked);
    connect(ui->PadBox, &QGroupBox::clicked, this, &Btnstyler::PadBoxChecked);
    connect(ui->GradBox, &QGroupBox::clicked, this, &Btnstyler::GradBoxChecked);

    connect(ui->treeWidget,SIGNAL(itemChanged(QTreeWidgetItem *,int)),this,SLOT(treeChanged(QTreeWidgetItem* ,int)));
}

void Btnstyler::treeChanged(QTreeWidgetItem* item,int col)//树状图选择改变
{
    int treestate;
    treestate = item->checkState(0);
    if(item == subItem12)//主样式-悬停样式
    {
        subItem12_flag = treestate;
        updateStylesheet();
    }
    else if(item == subItem13)//主样式-按压样式
    {
        subItem13_flag = treestate;
        updateStylesheet();
    }
    if(OBName == "滚动条")
    {
        if(item == group2)//局部样式
        {
            group2_flag = treestate;
            if(group2_flag == 2)
            {
                subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem31->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem41->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            }
            else
            {
                subItem21->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem21->setCheckState(0, Qt::Unchecked);
                subItem31->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem31->setCheckState(0, Qt::Unchecked);
                subItem41->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem41->setCheckState(0, Qt::Unchecked);
            }
        }
        else if(item == subItem21)//滑块
        {
            subItem21_flag = treestate;
            if(subItem21_flag == 2)
            {
                subItem211->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem212->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem213->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem214->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                updateStylesheet();
            }
            else
            {
                subItem211->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem211->setCheckState(0, Qt::Unchecked);
                subItem212->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem212->setCheckState(0, Qt::Unchecked);
                subItem213->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem213->setCheckState(0, Qt::Unchecked);
                subItem214->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem214->setCheckState(0, Qt::Unchecked);
                updateStylesheet();
            }
        }
        else if(item == subItem211)//滑块悬停
        {
            subItem211_flag = treestate;
            if(subItem211_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem212)//滑块按压
        {
            subItem212_flag = treestate;
            if(subItem212_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem213)//滑块上槽
        {
            subItem213_flag = treestate;
            if(subItem213_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem214)//滑块下槽
        {
            subItem214_flag = treestate;
            if(subItem214_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem31)//上箭头
        {
            subItem31_flag = treestate;
            if(subItem31_flag == 2)
            {
                subItem311->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem312->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem313->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                updateStylesheet();
            }
            else
            {
                subItem311->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem311->setCheckState(0, Qt::Unchecked);
                subItem312->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem312->setCheckState(0, Qt::Unchecked);
                subItem313->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem313->setCheckState(0, Qt::Unchecked);
                updateStylesheet();
            }
        }
        else if(item == subItem311)//上箭头悬停
        {
            subItem311_flag = treestate;
            if(subItem311_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem312)//上箭头按压
        {
            subItem312_flag = treestate;
            if(subItem312_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem313)//上箭头边线
        {
            subItem313_flag = treestate;
            if(subItem313_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem41)//下箭头
        {
            subItem41_flag = treestate;
            if(subItem41_flag == 2)
            {
                subItem411->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem412->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem413->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                updateStylesheet();
            }
            else
            {
                subItem411->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem411->setCheckState(0, Qt::Unchecked);
                subItem412->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem412->setCheckState(0, Qt::Unchecked);
                subItem413->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem413->setCheckState(0, Qt::Unchecked);
                updateStylesheet();
            }
        }
        else if(item == subItem411)//下箭头悬停
        {
            subItem411_flag = treestate;
            if(subItem411_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem412)//下箭头按压
        {
            subItem412_flag = treestate;
            if(subItem412_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem413)//下箭头边线
        {
            subItem413_flag = treestate;
            if(subItem413_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
    }

    if(OBName == "滑动条")
    {
        if(item == group2)//局部样式
        {
            group2_flag = treestate;
            if(group2_flag == 2)
            {
                subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem31->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            }
            else
            {
                subItem21->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem21->setCheckState(0, Qt::Unchecked);
                subItem31->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem31->setCheckState(0, Qt::Unchecked);
            }
        }
        else if(item == subItem21)//滑块
        {
            subItem21_flag = treestate;
            if(subItem21_flag == 2)
            {
                subItem211->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem212->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem213->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem214->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                updateStylesheet();
            }
            else
            {
                subItem211->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem211->setCheckState(0, Qt::Unchecked);
                subItem212->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem212->setCheckState(0, Qt::Unchecked);
                subItem213->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem213->setCheckState(0, Qt::Unchecked);
                subItem214->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem214->setCheckState(0, Qt::Unchecked);
                updateStylesheet();
            }
        }
        else if(item == subItem211)//滑块悬停
        {
            subItem211_flag = treestate;
            if(subItem211_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem212)//滑块按压
        {
            subItem212_flag = treestate;
            if(subItem212_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem213)//滑块上槽
        {
            subItem213_flag = treestate;
            if(subItem213_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem214)//滑块下槽
        {
            subItem214_flag = treestate;
            if(subItem214_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem31)//上箭头
        {
            subItem31_flag = treestate;
            if(subItem31_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
    }

    if(OBName == "下拉框")
    {
        if(item == group2)//局部样式
        {
            group2_flag = treestate;
            if(group2_flag == 2)
            {
                subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem31->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            }
            else
            {
                subItem21->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem21->setCheckState(0, Qt::Unchecked);
                subItem31->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem31->setCheckState(0, Qt::Unchecked);
            }
        }
        else if(item == subItem21)//下拉按钮
        {
            subItem21_flag = treestate;
            if(subItem21_flag == 2)
            {
                subItem211->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem212->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem213->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                updateStylesheet();
            }
            else
            {
                subItem211->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem211->setCheckState(0, Qt::Unchecked);
                subItem212->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem212->setCheckState(0, Qt::Unchecked);
                subItem213->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem213->setCheckState(0, Qt::Unchecked);
                updateStylesheet();
            }
        }
        else if(item == subItem211)//按钮悬停
        {
            subItem211_flag = treestate;
            if(subItem211_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem212)//按钮按压
        {
            subItem212_flag = treestate;
            if(subItem212_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem213)//按钮箭头
        {
            subItem213_flag = treestate;
            if(subItem213_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem31)//下拉列表
        {
            subItem31_flag = treestate;
            if(subItem31_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
    }

    if(OBName == "选值框")
    {
        if(item == group2)//局部样式
        {
            group2_flag = treestate;
            if(group2_flag == 2)
            {
                subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem31->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            }
            else
            {
                subItem21->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem21->setCheckState(0, Qt::Unchecked);
                subItem31->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem31->setCheckState(0, Qt::Unchecked);
            }
        }
        else if(item == subItem21)//下拉按钮
        {
            subItem21_flag = treestate;
            if(subItem21_flag == 2)
            {
                subItem211->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem212->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem213->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem214->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                updateStylesheet();
            }
            else
            {
                subItem211->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem211->setCheckState(0, Qt::Unchecked);
                subItem212->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem212->setCheckState(0, Qt::Unchecked);
                subItem213->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem213->setCheckState(0, Qt::Unchecked);
                subItem214->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem214->setCheckState(0, Qt::Unchecked);
                updateStylesheet();
            }
        }
        else if(item == subItem211)//按钮悬停
        {
            subItem211_flag = treestate;
            if(subItem211_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem212)//按钮按压
        {
            subItem212_flag = treestate;
            if(subItem212_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem213)//按钮箭头
        {
            subItem213_flag = treestate;
            if(subItem213_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem214)//按钮箭头
        {
            subItem214_flag = treestate;
            if(subItem214_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem31)//下拉按钮
        {
            subItem31_flag = treestate;
            if(subItem31_flag == 2)
            {
                subItem311->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem312->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem313->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem314->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                updateStylesheet();
            }
            else
            {
                subItem311->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem311->setCheckState(0, Qt::Unchecked);
                subItem312->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem312->setCheckState(0, Qt::Unchecked);
                subItem313->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem313->setCheckState(0, Qt::Unchecked);
                subItem314->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);subItem314->setCheckState(0, Qt::Unchecked);
                updateStylesheet();
            }
        }
        else if(item == subItem311)//按钮悬停
        {
            subItem311_flag = treestate;
            if(subItem311_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem312)//按钮按压
        {
            subItem312_flag = treestate;
            if(subItem312_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem313)//按钮箭头
        {
            subItem313_flag = treestate;
            if(subItem313_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
        else if(item == subItem314)//按钮箭头
        {
            subItem314_flag = treestate;
            if(subItem314_flag == 2)
            {
                updateStylesheet();
            }
            else
            {
                updateStylesheet();
            }
        }
    }
}

void Btnstyler::updateStylesheet()//更新样式表
{
    if(OBName == "按钮")
    {
        styleText= QString("QPushButton{");
        publicStyle("QPushButton");//通用样式
        ui->pushButton->setStyleSheet(styleText);//根据样式表更新样式
    }
    else if(OBName == "标签")
    {
        styleText= QString("QLabel{");
        publicStyle("QLabel");//通用样式
        textLabel->setStyleSheet(styleText);//根据样式表更新样式
    }
    else if(OBName == "滚动条")
    {
        styleText= QString("QScrollBar{");
        publicStyle("QScrollBar");//通用样式
        partStyle("QScrollBar");//局部样式
        vScrollBar->setStyleSheet(styleText);//根据样式表更新样式
    }
    else if(OBName == "滑动条")
    {
        styleText= QString("QSlider{");
        publicStyle("QSlider");//通用样式
        partStyle("QSlider");//局部样式——滚动条
        vSlider->setStyleSheet(styleText);//根据样式表更新样式
    }
    else if(OBName == "下拉框")
    {
        styleText= QString("QComboBox{");
        publicStyle("QComboBox");//通用样式
        partStyle2("QComboBox");//局部样式——滚动条
        cbox->setStyleSheet(styleText);//根据样式表更新样式
    }
    else if(OBName == "选值框")
    {
        styleText= QString("QSpinBox{");
        publicStyle("QSpinBox");//通用样式
        partStyle2("QSpinBox");//局部样式——滚动条
        sbox->setStyleSheet(styleText);//根据样式表更新样式
    }

    ui->styleOutput->setText(styleText);//把样式表显示至文本框
}

QString Btnstyler::prependZeros(QString col)//颜色6位预置零（没应用）
{
    QString rightColor=col;
    while(rightColor.size()<6)
        rightColor.prepend("0");

    return rightColor;
}

void Btnstyler::FrameBoxChecked()//边框控件启用标志
{
    FrameBox_Flag=ui->FrameBox->isChecked();
    updateStylesheet();
}

void Btnstyler::BtnBoxChecked()//按钮控件启用标志
{
    BtnBox_Flag=ui->BtnBox->isChecked();
    updateStylesheet();
}

void Btnstyler::FontBoxChecked()//字体控件启用标志
{
    FontBox_Flag=ui->FontBox->isChecked();
    updateStylesheet();
}

void Btnstyler::PadBoxChecked()//衬垫控件启用标志
{
    PadBox_Flag=ui->PadBox->isChecked();
    updateStylesheet();
}

void Btnstyler::GradBoxChecked()//渐变控件启用标志
{
    GradBox_Flag=ui->GradBox->isChecked();
    updateStylesheet();
}

void Btnstyler::on_btnOK_clicked()//应用样式表按钮
{
    if(OBName == "按钮")
    {
        ui->pushButton->setStyleSheet(ui->styleOutput->toPlainText());//根据样式表更新样式
    }
    else if(OBName == "标签")
    {
        textLabel->setStyleSheet(ui->styleOutput->toPlainText());//根据样式表更新样式
    }
    else if(OBName == "滚动条")
    {
        vScrollBar->setStyleSheet(ui->styleOutput->toPlainText());//根据样式表更新样式
    }
    else if(OBName == "滑动条")
    {
        vSlider->setStyleSheet(ui->styleOutput->toPlainText());//根据样式表更新样式
    }
    else if(OBName == "下拉框")
    {
        cbox->setStyleSheet(ui->styleOutput->toPlainText());//根据样式表更新样式
    }
    else if(OBName == "选值框")
    {
        sbox->setStyleSheet(ui->styleOutput->toPlainText());//根据样式表更新样式
    }
}

void Btnstyler::on_btncancel_clicked()//取消按钮
{
    this->close();
}

void Btnstyler::on_renkButton_clicked()//字体选色按钮
{
    QColorDialog diag;//颜色对话框
    QColor bColor=diag.getColor(QColor(bgGrad_stop0));//得到之前的颜色

    if(bColor.isValid())//如果颜色值有效
    {
        ui->renkLabel->setPalette(bColor);//设置标签颜色
        ui->renkLabel->setAutoFillBackground(true);//小部件背景自动填充
        color=bColor.name();//储存颜色
        updateStylesheet();//更新样式表
    }
}

void Btnstyler::on_renkButton2_clicked()//边框选色按钮
{
    QColorDialog diag;//颜色对话框
    QColor bColor=diag.getColor(QColor(bgGrad_stop11));//得到之前的颜色

    if(bColor.isValid())//如果颜色值有效
    {
        ui->renkLabel2->setPalette(bColor);//设置标签颜色
        ui->renkLabel2->setAutoFillBackground(true);//小部件背景自动填充
        solid=bColor.name();//储存颜色
        updateStylesheet();//更新样式表
    }
}

void Btnstyler::on_grenkButton1_clicked()//渐变选色按钮1
{
    QColorDialog diag;//颜色对话框
    QColor bColor=diag.getColor(QColor(bgGrad_stop0));//得到之前的颜色

    if(bColor.isValid())//如果颜色值有效
    {
        ui->grenkLabel1->setPalette(bColor);//设置标签颜色
        ui->grenkLabel1->setAutoFillBackground(true);//小部件背景自动填充
        bgGrad_stop0=bColor.name();//储存颜色
        updateStylesheet();//更新样式表
    }
}

void Btnstyler::on_grenkButton2_clicked()//渐变选色按钮2
{
    QColorDialog diag;//颜色对话框
    QColor bColor=diag.getColor(QColor(bgGrad_stop11));//得到之前的颜色

    if(bColor.isValid())//如果颜色值有效
    {
        ui->grenkLabel2->setPalette(bColor);//设置标签颜色
        ui->grenkLabel2->setAutoFillBackground(true);//小部件背景自动填充
        bgGrad_stop11=bColor.name();//储存颜色

        int h,s,v;
        bColor.getHsv(&h,&s,&v);//得到HSV值，色调、饱和度、明度
        s= s/2;//饱和度一半
        bColor.setHsv(h,s,v);//设置HSV值

        ui->grenkLabel3->setPalette(bColor);//设置标签颜色
        ui->grenkLabel3->setAutoFillBackground(true);//小部件背景自动填充
        bgGrad_stop12=bColor.name();//储存颜色

        bColor.getHsv(&h,&s,&v);//得到HSV值
        s= s/2;//饱和度一半的一半
        bColor.setHsv(h,s,v);//设置HSV值

        ui->grenkLabel4->setPalette(bColor);//设置标签颜色
        ui->grenkLabel4->setAutoFillBackground(true);//小部件背景自动填充
        bgGrad_stop13=bColor.name();//储存颜色

        updateStylesheet();//更新样式表
    }
}

void Btnstyler::on_grenkButton3_clicked()//渐变选色按钮3
{
    QColorDialog diag;//颜色对话框
    QColor bColor=diag.getColor(QColor(bgGrad_stop12));//得到之前的颜色

    if(bColor.isValid())//如果颜色值有效
    {
        ui->grenkLabel3->setPalette(bColor);//设置标签颜色
        ui->grenkLabel3->setAutoFillBackground(true);//小部件背景自动填充
        bgGrad_stop12=bColor.name();//储存颜色
        updateStylesheet();//更新样式表
    }
}

void Btnstyler::on_grenkButton4_clicked()//渐变选色按钮4
{
    QColorDialog diag;//颜色对话框
    QColor bColor=diag.getColor(QColor(bgGrad_stop13));//得到之前的颜色

    if(bColor.isValid())//如果颜色值有效
    {
        ui->grenkLabel4->setPalette(bColor);//设置标签颜色
        ui->grenkLabel4->setAutoFillBackground(true);//小部件背景自动填充
        bgGrad_stop13=bColor.name();//储存颜色
        updateStylesheet();//更新样式表
    }
}

void Btnstyler::on_bordRadSlider_valueChanged(int value)//圆角半径滑动条值改变
{
    borderRadius= value;//设置值
    updateStylesheet();//更新样式表
}

void Btnstyler::on_bordThickSlider_valueChanged(int value)//边框宽度滑动条值改变
{
    border=value;//设置值
    updateStylesheet();//更新样式表
}

void Btnstyler::on_gRadiusSlider_valueChanged(int value)//渐变分布滑动条值改变
{
    bgGrad_radius=value / 100.0;//设置值
    updateStylesheet();//更新样式表
}

void Btnstyler::on_fontSizeSlider_valueChanged(int value)//字体大小滑动条值改变
{
    fontSize=value;//设置值
    updateStylesheet();//更新样式表
}

void Btnstyler::on_PadUpSlider_valueChanged(int value)//按钮衬垫滑动条值改变(上)
{
    padding_U=value;//设置值
    updateStylesheet();//更新样式表
}

void Btnstyler::on_PadDownSlider_valueChanged(int value)//渐变分布滑动条值改变(下)
{
    padding_D=value;//设置值
    updateStylesheet();//更新样式表
}

void Btnstyler::on_PadLeftSlider_valueChanged(int value)//渐变分布滑动条值改变(左)
{
    padding_L=value;//设置值
    updateStylesheet();//更新样式表
}

void Btnstyler::on_PadRightSlider_valueChanged(int value)//渐变分布滑动条值改变(右)
{
    padding_R=value;//设置值
    updateStylesheet();//更新样式表
}

void Btnstyler::on_minheightSlider_valueChanged(int value)//渐变分布滑动条值改变(右)
{
    minheight=value;//设置值
    updateStylesheet();//更新样式表
}

void Btnstyler::on_minwidthSlider_valueChanged(int value)//渐变分布滑动条值改变(右)
{
    minwidth=value;//设置值
    updateStylesheet();//更新样式表
}

void Btnstyler::on_fontComboBox_currentFontChanged(QFont font)//字体下拉框选项改变
{
//    fontFamily=ui->fontComboBox->currentFont().family();//设置值
    fontFamily=font.family();
    updateStylesheet();//更新样式表
}

void Btnstyler::on_RadcomboBox_currentIndexChanged(int value)//渐变下拉框选项改变
{
    gradyanType=ui->RadcomboBox->currentText();//设置值
    updateStylesheet();//更新样式表
}

void Btnstyler::publicStyle(QString OBJ)//通用样式
{
    if(FrameBox_Flag == 1)//边框
    {
        styleText+= sssNULL//防错空字符
                    +"\nborder-radius: "+QString::number(borderRadius)//圆角半径
                    +";\nborder: "+QString::number(border)//边框厚度
                    +"px solid "+solid//边框颜色
                    +";";
    }

    if(BtnBox_Flag == 1)//大小
    {
        styleText+= sssNULL//防错空字符
                    +"\nmin-height: "+QString::number(minheight)//最小高度
                    +"px;\nmin-width: "+QString::number(minwidth)//最小宽度
                    +"px;";
    }

    if(FontBox_Flag == 1)//字体
    {
        styleText+= sssNULL//防错空字符
                    +"\nfont: "+QString::number(fontSize)+"pt \""+fontFamily+"\""//字体大小、字体种类
                    +";\ncolor: "+color//文字颜色
                    +";";
    }

    if(PadBox_Flag == 1)//衬垫
    {
        styleText+= sssNULL//防错空字符
                    +"\npadding: "+QString::number(padding_U)//衬垫
                    +"px "+QString::number(padding_R)
                    +"px "+QString::number(padding_D)
                    +"px "+QString::number(padding_L)
                    +"px;";
    }

    if(GradBox_Flag == 1)//渐变
    {
        if(gradyanType == "None")
        {
            styleText+= "\nbackground: "+bgGrad_stop11
                        +";\n}\n\n";

            if(subItem12_flag == 2)
            {
                styleText+= QString("%1:hover{\n").arg(OBJ)
                            +"background: "+bgGrad_stop12
                            +";\n}\n\n";
            }
            if(subItem13_flag == 2)
            {
                styleText+= QString("%1:pressed{\n").arg(OBJ)
                            +"background: "+bgGrad_stop13
                            +";\n}\n\n";
            }
        }
        else if(gradyanType == "Radial Gradyan")
        {
            styleText+= "\nbackground: qradialgradient(cx: "+QString::number(bgGrad_cx)
                        +", cy: "+QString::number(bgGrad_cy)
                        +",\nfx: "+QString::number(bgGrad_fx)
                        +", fy: "+QString::number(bgGrad_fy)
                        +",\nradius: "+QString::number(bgGrad_radius)
                        +", stop: 0 "+bgGrad_stop0
                        +", stop: 1 "+bgGrad_stop11
                        +");\n}\n\n";

            if(subItem12_flag == 2)
            {
                styleText+= QString("%1:hover{\n").arg(OBJ)
                            +"background: qradialgradient(cx: "+QString::number(bgGrad_cx)
                            +", cy: "+QString::number(bgGrad_cy)
                            +",\nfx: "+QString::number(bgGrad_fx)
                            +", fy: "+QString::number(bgGrad_fy)
                            +",\nradius: "+QString::number(bgGrad_radius)
                            +", stop: 0 "+bgGrad_stop0
                            +", stop: 1 "+bgGrad_stop12
                            +");\n}\n\n";
            }
            if(subItem13_flag == 2)
            {
                styleText+= QString("%1:pressed{\n").arg(OBJ)
                            +"background: qradialgradient(cx: "+QString::number(bgGrad2_cx)
                            +", cy: "+QString::number(bgGrad2_cy)
                            +",\nfx: "+QString::number(bgGrad2_fx)
                            +", fy: "+QString::number(bgGrad2_fy)
                            +",\nradius: "+QString::number(bgGrad_radius)
                            +", stop: 0 "+bgGrad_stop0
                            +", stop: 1 "+bgGrad_stop13
                            +");\n}\n\n";
            }
        }
        else if(gradyanType == "Lineer Gradyan")
        {
            styleText+= "\nbackground: qlineargradient("+QString("spread:pad,")
                        +"x1:1,y1:0,x2:0,y2:0,\n"
                        +"stop: 0 "+bgGrad_stop0
                        +", stop: 1 "+bgGrad_stop11
                        +");\n}\n\n";

            if(subItem12_flag == 2)
            {
                styleText+= QString("%1:hover{\n").arg(OBJ)
                            +"background: qlineargradient(spread:pad,"
                            +"x1:1,y1:0,x2:0,y2:0,\n"
                            +"stop: 0 "+bgGrad_stop0
                            +", stop: 1 "+bgGrad_stop12
                            +");\n}\n\n";
            }
            if(subItem13_flag == 2)
            {
                styleText+= QString("%1:pressed{\n").arg(OBJ)
                            +"background: qlineargradient(spread:pad,"
                            +"x1:1,y1:0,x2:0,y2:0,\n"
                            +"stop: 0 "+bgGrad_stop0
                            +", stop: 1 "+bgGrad_stop13
                            +");\n}\n\n";
            }
        }
    }
    else
    {
        styleText+= sssNULL//防错空字符
                    +"\n}\n\n";
    }
}

void Btnstyler::partStyle(QString OBJ)//局部样式
{
    if(subItem21_flag == 2)
    {
        styleText+= QString("%1:handle{").arg(OBJ);

        if(FrameBox_Flag == 1)//边框
        {
            styleText+= "\nborder-radius: "+QString::number(borderRadius)//圆角半径
                        +";\nborder: "+QString::number(border)//边框厚度
                        +"px solid "+solid//边框颜色
                        +";";
        }

        if(BtnBox_Flag == 1)//大小
        {
            if(OBName == "滚动条")//大小
            {
                styleText+= "\nmin-height: "+QString::number(minheight/10)//最小高度
                            +"px;\nmin-width: "+QString::number(minwidth/10)//最小宽度
                            +"px;";
            }

            if(OBName == "滑动条")//大小
            {
                styleText+= "\nheight: "+QString::number(minheight/10)//最小高度
                            +"px;\nwidth: "+QString::number(minwidth/10)//最小宽度
                            +"px;";
            }
        }

        if(PadBox_Flag == 1)//衬垫
        {
            styleText+= "\npadding: "+QString::number(padding_U)//衬垫
                        +"px "+QString::number(padding_R)
                        +"px "+QString::number(padding_D)
                        +"px "+QString::number(padding_L)
                        +"px;";
        }

        if(GradBox_Flag == 1)//渐变
        {
            if(gradyanType == "None")
            {
                styleText+= "\nbackground: "+bgGrad_stop11
                            +";\n}\n\n";

                if(subItem211_flag == 2)
                {
                    styleText+= QString("%1:handle:hover{\n").arg(OBJ)
                                +"background: "+bgGrad_stop12
                                +";\n}\n\n";
                }
                if(subItem212_flag == 2)
                {
                    styleText+= QString("%1:handle:pressed{\n").arg(OBJ)
                                +"background: "+bgGrad_stop13
                                +";\n}\n\n";
                }
            }
            else if(gradyanType == "Radial Gradyan")
            {
                styleText+= "\nbackground: qradialgradient(cx: "+QString::number(bgGrad_cx)
                            +", cy: "+QString::number(bgGrad_cy)
                            +",\nfx: "+QString::number(bgGrad_fx)
                            +", fy: "+QString::number(bgGrad_fy)
                            +",\nradius: "+QString::number(bgGrad_radius)
                            +", stop: 0 "+bgGrad_stop0
                            +", stop: 1 "+bgGrad_stop11
                            +");\n}\n\n";

                if(subItem211_flag == 2)
                {
                    styleText+= QString("%1:handle:hover{\n").arg(OBJ)
                                +"background: qradialgradient(cx: "+QString::number(bgGrad_cx)
                                +", cy: "+QString::number(bgGrad_cy)
                                +",\nfx: "+QString::number(bgGrad_fx)
                                +", fy: "+QString::number(bgGrad_fy)
                                +",\nradius: "+QString::number(bgGrad_radius)
                                +", stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop12
                                +");\n}\n\n";
                }
                if(subItem212_flag == 2)
                {
                    styleText+= QString("%1:handle:pressed{\n").arg(OBJ)
                                +"background: qradialgradient(cx: "+QString::number(bgGrad2_cx)
                                +", cy: "+QString::number(bgGrad2_cy)
                                +",\nfx: "+QString::number(bgGrad2_fx)
                                +", fy: "+QString::number(bgGrad2_fy)
                                +",\nradius: "+QString::number(bgGrad_radius)
                                +", stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop13
                                +");\n}\n\n";
                }
            }
            else if(gradyanType == "Lineer Gradyan")
            {
                styleText+= "\nbackground: qlineargradient("+QString("spread:pad,")
                            +"x1:1,y1:0,x2:0,y2:0,\n"
                            +"stop: 0 "+bgGrad_stop0
                            +", stop: 1 "+bgGrad_stop11
                            +");\n}\n\n";

                if(subItem211_flag == 2)
                {
                    styleText+= QString("%1:handle:hover{\n").arg(OBJ)
                                +"background: qlineargradient(spread:pad,"
                                +"x1:1,y1:0,x2:0,y2:0,\n"
                                +"stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop12
                                +");\n}\n\n";
                }
                if(subItem212_flag == 2)
                {
                    styleText+= QString("%1:handle:pressed{\n").arg(OBJ)
                                +"background: qlineargradient(spread:pad,"
                                +"x1:1,y1:0,x2:0,y2:0,\n"
                                +"stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop13
                                +");\n}\n\n";
                }
            }
        }
        else
        {
            styleText+= sssNULL//防错空字符
                        +"\n}\n\n";
        }

        if(subItem213_flag == 2)//滑块上槽
        {
            styleText+= QString("%1:sub-page{").arg(OBJ)
                        +"\nborder-radius: "+QString::number(borderRadius)//圆角半径
                        +";\nborder: "+QString::number(border)//边框厚度
                        +"px solid "+solid//边框颜色
                        +";\nbackground: "+bgGrad_stop0
                        +";\n}\n\n";
        }

        if(subItem214_flag == 2)//滑块下槽
        {
            styleText+= QString("%1:add-page{").arg(OBJ)
                        +"\nborder-radius: "+QString::number(borderRadius)//圆角半径
                        +";\nborder: "+QString::number(border)//边框厚度
                        +"px solid "+solid//边框颜色
                        +";\nbackground: "+bgGrad_stop0
                        +";\n}\n\n";
        }
    }

    if(subItem31_flag == 2 && OBName == "滚动条")//上箭头
    {
        styleText+= sssNULL//防错空字符
                    +"QScrollBar:sub-line:vertical{"
                    +"\nsubcontrol-position:top;";

        if(FrameBox_Flag == 1)//边框
        {
            styleText+= "\nborder-radius: "+QString::number(borderRadius/2)//圆角半径
                        +";\nborder: "+QString::number(border)//边框厚度
                        +"px solid "+solid//边框颜色
                        +";";
        }

        if(BtnBox_Flag == 1)//大小
        {
            styleText+= "\nheight: "+QString::number(minheight/2)//最小高度
                        +"px;\nwidth: "+QString::number(minwidth)//最小宽度
                        +"px;";
        }

        if(PadBox_Flag == 1)//衬垫
        {
            styleText+= "\npadding: "+QString::number(padding_U/2)//衬垫
                        +"px "+QString::number(padding_R/2)
                        +"px "+QString::number(padding_D/2)
                        +"px "+QString::number(padding_L/2)
                        +"px;";
        }

        if(GradBox_Flag == 1)//渐变
        {
            if(gradyanType == "None")
            {
                styleText+= "\nbackground: "+bgGrad_stop0
                            +";\n}\n\n";

                if(subItem311_flag == 2)
                {
                    styleText+= sssNULL//防错空字符
                                +"QScrollBar:sub-line:vertical:hover{\n"
                                +"background: "+bgGrad_stop12
                                +";\n}\n\n";
                }
                if(subItem312_flag == 2)
                {
                    styleText+= sssNULL//防错空字符
                                +"QScrollBar:sub-line:vertical:pressed{\n"
                                +"background: "+bgGrad_stop13
                                +";\n}\n\n";
                }
            }
            else if(gradyanType == "Radial Gradyan")
            {
                styleText+= "\nbackground: qradialgradient(cx: "+QString::number(bgGrad_cx)
                            +", cy: "+QString::number(bgGrad_cy)
                            +",\nfx: "+QString::number(bgGrad_fx)
                            +", fy: "+QString::number(bgGrad_fy)
                            +",\nradius: "+QString::number(bgGrad_radius)
                            +", stop: 0 "+bgGrad_stop0
                            +", stop: 1 "+bgGrad_stop11
                            +");\n}\n\n";

                if(subItem311_flag == 2)
                {
                    styleText+= sssNULL//防错空字符
                                +"QScrollBar:sub-line:vertical:hover{\n"
                                +"background: qradialgradient(cx: "+QString::number(bgGrad_cx)
                                +", cy: "+QString::number(bgGrad_cy)
                                +",\nfx: "+QString::number(bgGrad_fx)
                                +", fy: "+QString::number(bgGrad_fy)
                                +",\nradius: "+QString::number(bgGrad_radius)
                                +", stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop12
                                +");\n}\n\n";
                }
                if(subItem312_flag == 2)
                {
                    styleText+= sssNULL//防错空字符
                                +"QScrollBar:sub-line:vertical:pressed{\n"
                                +"background: qradialgradient(cx: "+QString::number(bgGrad2_cx)
                                +", cy: "+QString::number(bgGrad2_cy)
                                +",\nfx: "+QString::number(bgGrad2_fx)
                                +", fy: "+QString::number(bgGrad2_fy)
                                +",\nradius: "+QString::number(bgGrad_radius)
                                +", stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop13
                                +");\n}\n\n";
                }
            }
            else if(gradyanType == "Lineer Gradyan")
            {
                styleText+= "\nbackground: qlineargradient("+QString("spread:pad,")
                            +"x1:1,y1:0,x2:0,y2:0,\n"
                            +"stop: 0 "+bgGrad_stop0
                            +", stop: 1 "+bgGrad_stop11
                            +");\n}\n\n";

                if(subItem311_flag == 2)
                {
                    styleText+= sssNULL//防错空字符
                                +"QScrollBar:sub-line:vertical:hover{\n"
                                +"background: qlineargradient(spread:pad,"
                                +"x1:1,y1:0,x2:0,y2:0,\n"
                                +"stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop12
                                +");\n}\n\n";
                }
                if(subItem312_flag == 2)
                {
                    styleText+= sssNULL//防错空字符
                                +"QScrollBar:sub-line:vertical:pressed{\n"
                                +"background: qlineargradient(spread:pad,"
                                +"x1:1,y1:0,x2:0,y2:0,\n"
                                +"stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop13
                                +");\n}\n\n";
                }
            }
            if(subItem313_flag == 2)//上箭头边线
            {
                styleText+= sssNULL//防错空字符
                            +"QScrollBar:sub-line{\n\n}\n\n";
            }
        }
        else
        {
            styleText+= sssNULL//防错空字符
                        +"\n}\n\n";
        }
    }

    if(subItem41_flag == 2 && OBName == "滚动条")//下箭头
    {
        styleText+= sssNULL//防错空字符
                    +"QScrollBar:add-line:vertical{"
                    +"\nsubcontrol-position:bottom;";

        if(FrameBox_Flag == 1)//边框
        {
            styleText+= "\nborder-radius: "+QString::number(borderRadius/2)//圆角半径
                        +";\nborder: "+QString::number(border)//边框厚度
                        +"px solid "+solid//边框颜色
                        +";";
        }

        if(BtnBox_Flag == 1)//大小
        {
            styleText+= "\nheight: "+QString::number(minheight/2)//最小高度
                        +"px;\nwidth: "+QString::number(minwidth)//最小宽度
                        +"px;";
        }

        if(PadBox_Flag == 1)//衬垫
        {
            styleText+= "\npadding: "+QString::number(padding_U/2)//衬垫
                        +"px "+QString::number(padding_R/2)
                        +"px "+QString::number(padding_D/2)
                        +"px "+QString::number(padding_L/2)
                        +"px;";
        }

        if(GradBox_Flag == 1)//渐变
        {
            if(gradyanType == "None")
            {
                styleText+= "\nbackground: "+bgGrad_stop0
                            +";\n}\n\n";

                if(subItem411_flag == 2)
                {
                    styleText+= sssNULL//防错空字符
                                +"QScrollBar:add-line:vertical:hover{\n"
                                +"background: "+bgGrad_stop12
                                +";\n}\n\n";
                }
                if(subItem412_flag == 2)
                {

                    styleText+= sssNULL//防错空字符
                                +"QScrollBar:add-line:vertical:pressed{\n"
                                +"background: "+bgGrad_stop13
                                +";\n}\n\n";
                }
            }
            else if(gradyanType == "Radial Gradyan")
            {
                styleText+= "\nbackground: qradialgradient(cx: "+QString::number(bgGrad_cx)
                            +", cy: "+QString::number(bgGrad_cy)
                            +",\nfx: "+QString::number(bgGrad_fx)
                            +", fy: "+QString::number(bgGrad_fy)
                            +",\nradius: "+QString::number(bgGrad_radius)
                            +", stop: 0 "+bgGrad_stop0
                            +", stop: 1 "+bgGrad_stop11
                            +");\n}\n\n";

                if(subItem411_flag == 2)
                {
                    styleText+= sssNULL//防错空字符
                                +"QScrollBar:add-line:vertical:hover{\n"
                                +"background: qradialgradient(cx: "+QString::number(bgGrad_cx)
                                +", cy: "+QString::number(bgGrad_cy)
                                +",\nfx: "+QString::number(bgGrad_fx)
                                +", fy: "+QString::number(bgGrad_fy)
                                +",\nradius: "+QString::number(bgGrad_radius)
                                +", stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop12
                                +");\n}\n\n";
                }
                if(subItem412_flag == 2)
                {
                    styleText+= sssNULL//防错空字符
                                +"QScrollBar:add-line:vertical:pressed{\n"
                                +"background: qradialgradient(cx: "+QString::number(bgGrad2_cx)
                                +", cy: "+QString::number(bgGrad2_cy)
                                +",\nfx: "+QString::number(bgGrad2_fx)
                                +", fy: "+QString::number(bgGrad2_fy)
                                +",\nradius: "+QString::number(bgGrad_radius)
                                +", stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop13
                                +");\n}\n\n";
                }
            }
            else if(gradyanType == "Lineer Gradyan")
            {
                styleText+= "\nbackground: qlineargradient("+QString("spread:pad,")
                            +"x1:1,y1:0,x2:0,y2:0,\n"
                            +"stop: 0 "+bgGrad_stop0
                            +", stop: 1 "+bgGrad_stop11
                            +");\n}\n\n";

                if(subItem411_flag == 2)
                {
                    styleText+= sssNULL//防错空字符
                                +"QScrollBar:add-line:vertical:hover{\n"
                                +"background: qlineargradient(spread:pad,"
                                +"x1:1,y1:0,x2:0,y2:0,\n"
                                +"stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop12
                                +");\n}\n\n";
                }
                if(subItem412_flag == 2)
                {
                    styleText+= sssNULL//防错空字符
                                +"QScrollBar:add-line:vertical:pressed{\n"
                                +"background: qlineargradient(spread:pad,"
                                +"x1:1,y1:0,x2:0,y2:0,\n"
                                +"stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop13
                                +");\n}\n\n";
                }
            }
            if(subItem413_flag == 2)//上箭头边线
            {
                styleText+= sssNULL//防错空字符
                            +"QScrollBar:add-line{\n\n}";
            }
        }
        else
        {
            styleText+= sssNULL//防错空字符
                        +"\n}\n\n";
        }
    }

    if(subItem31_flag == 2 && OBName == "滑动条")//滑动槽
    {
        styleText+= sssNULL//防错空字符
                    +"QSlider::groove{"
                    +"\nborder-radius: "+QString::number(borderRadius)//圆角半径
                    +";\nborder: "+QString::number(border)//边框厚度
                    +"px solid "+solid//边框颜色
                    +";\nbackground: "+bgGrad_stop13
                    +";\nheight: "+QString::number(minheight*1.5)//最小高度
                    +"px;\nwidth: "+QString::number(minwidth/4)//最小宽度
                    +"px;\npadding: "+QString::number(padding_U)//衬垫
                    +"px "+QString::number(padding_R)
                    +"px "+QString::number(padding_D)
                    +"px "+QString::number(padding_L)
                    +"px;\nmargin: -9px;"
                    +";\n}\n\n";
    }
}

void Btnstyler::partStyle2(QString OBJ)//局部样式2
{
    if(subItem21_flag == 2)
    {
        if(OBName == "下拉框")
        {
            styleText+= QString("%1:drop-down{").arg(OBJ);
        }

        if(OBName == "选值框")
        {
            styleText+= QString("%1:down-button{").arg(OBJ);
        }

        if(FrameBox_Flag == 1)//边框
        {
            styleText+= "\nborder-radius: "+QString::number(borderRadius)//圆角半径
                        +";\nborder: "+QString::number(border)//边框厚度
                        +"px solid "+solid//边框颜色
                        +";";
        }

        if(BtnBox_Flag == 1)//大小
        {
            styleText+= "\nmin-height: "+QString::number(minheight/10)//最小高度
                        +"px;\nmin-width: "+QString::number(minwidth/10)//最小宽度
                        +"px;";
        }

        if(PadBox_Flag == 1)//衬垫
        {
            styleText+= "\npadding: "+QString::number(padding_U)//衬垫
                        +"px "+QString::number(padding_R)
                        +"px "+QString::number(padding_D)
                        +"px "+QString::number(padding_L)
                        +"px;";
        }

        if(GradBox_Flag == 1)//渐变
        {
            if(gradyanType == "None")
            {
                styleText+= "\nbackground: "+bgGrad_stop11
                            +";\n}\n\n";

                if(subItem211_flag == 2)
                {
                    if(OBName == "下拉框")
                    {
                        styleText+= QString("%1:drop-down:hover{\n").arg(OBJ);

                    }

                    if(OBName == "选值框")
                    {
                        styleText+= QString("%1:down-button:hover{\n").arg(OBJ);
                    }

                    styleText+= sssNULL
                                +"background: "+bgGrad_stop12
                                +";\n}\n\n";
                }
                if(subItem212_flag == 2)
                {
                    if(OBName == "下拉框")
                    {
                        styleText+= QString("%1:drop-down:pressed{\n").arg(OBJ);

                    }

                    if(OBName == "选值框")
                    {
                        styleText+= QString("%1:down-button:pressed{\n").arg(OBJ);
                    }

                    styleText+= sssNULL
                                +"background: "+bgGrad_stop13
                                +";\n}\n\n";
                }
            }
            else if(gradyanType == "Radial Gradyan")
            {
                styleText+= "\nbackground: qradialgradient(cx: "+QString::number(bgGrad_cx)
                            +", cy: "+QString::number(bgGrad_cy)
                            +",\nfx: "+QString::number(bgGrad_fx)
                            +", fy: "+QString::number(bgGrad_fy)
                            +",\nradius: "+QString::number(bgGrad_radius)
                            +", stop: 0 "+bgGrad_stop0
                            +", stop: 1 "+bgGrad_stop11
                            +");\n}\n\n";

                if(subItem211_flag == 2)
                {
                    if(OBName == "下拉框")
                    {
                        styleText+= QString("%1:drop-down:hover{\n").arg(OBJ);

                    }

                    if(OBName == "选值框")
                    {
                        styleText+= QString("%1:down-button:hover{\n").arg(OBJ);
                    }

                    styleText+= sssNULL
                                +"background: qradialgradient(cx: "+QString::number(bgGrad_cx)
                                +", cy: "+QString::number(bgGrad_cy)
                                +",\nfx: "+QString::number(bgGrad_fx)
                                +", fy: "+QString::number(bgGrad_fy)
                                +",\nradius: "+QString::number(bgGrad_radius)
                                +", stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop12
                                +");\n}\n\n";
                }
                if(subItem212_flag == 2)
                {
                    if(OBName == "下拉框")
                    {
                        styleText+= QString("%1:drop-down:pressed{\n").arg(OBJ);

                    }

                    if(OBName == "选值框")
                    {
                        styleText+= QString("%1:down-button:pressed{\n").arg(OBJ);
                    }

                    styleText+= sssNULL
                                +"background: qradialgradient(cx: "+QString::number(bgGrad2_cx)
                                +", cy: "+QString::number(bgGrad2_cy)
                                +",\nfx: "+QString::number(bgGrad2_fx)
                                +", fy: "+QString::number(bgGrad2_fy)
                                +",\nradius: "+QString::number(bgGrad_radius)
                                +", stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop13
                                +");\n}\n\n";
                }
            }
            else if(gradyanType == "Lineer Gradyan")
            {
                styleText+= "\nbackground: qlineargradient("+QString("spread:pad,")
                            +"x1:1,y1:0,x2:0,y2:0,\n"
                            +"stop: 0 "+bgGrad_stop0
                            +", stop: 1 "+bgGrad_stop11
                            +");\n}\n\n";

                if(subItem211_flag == 2)
                { 
                    if(OBName == "下拉框")
                    {
                        styleText+= QString("%1:drop-down:hover{\n").arg(OBJ);

                    }

                    if(OBName == "选值框")
                    {
                        styleText+= QString("%1:down-button:hover{\n").arg(OBJ);
                    }

                    styleText+= sssNULL
                                +"background: qlineargradient(spread:pad,"
                                +"x1:1,y1:0,x2:0,y2:0,\n"
                                +"stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop12
                                +");\n}\n\n";
                }
                if(subItem212_flag == 2)
                {
                    if(OBName == "下拉框")
                    {
                        styleText+= QString("%1:drop-down:pressed{\n").arg(OBJ);

                    }

                    if(OBName == "选值框")
                    {
                        styleText+= QString("%1:down-button:pressed{\n").arg(OBJ);
                    }

                    styleText+= sssNULL
                                +"background: qlineargradient(spread:pad,"
                                +"x1:1,y1:0,x2:0,y2:0,\n"
                                +"stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop13
                                +");\n}\n\n";
                }
            }
        }
        else
        {
            styleText+= sssNULL//防错空字符
                        +"\n}\n\n";
        }

        if(subItem213_flag == 2)//按钮箭头
        {          
            styleText+= QString("%1:down-arrow{").arg(OBJ)
                        +"\nborder-radius: "+QString::number(borderRadius)//圆角半径
                        +";\nborder: "+QString::number(border)//边框厚度
                        +"px solid "+solid//边框颜色
                        +";\nbackground: "+bgGrad_stop11
                        +";\nmin-height: "+QString::number(minheight/3)//最小高度
                        +"px;\nmin-width: "+QString::number(minwidth/3)//最小宽度
                        +"px;\npadding: "+QString::number(padding_U)//衬垫
                        +"px "+QString::number(padding_R)
                        +"px "+QString::number(padding_D)
                        +"px "+QString::number(padding_L)
                        +"px;\n}\n\n";
        }

        if(subItem214_flag == 2)//按钮封值
        {
            styleText+= QString("%1:down-arrow:disabled, %1::down-arrow:off{").arg(OBJ)
                        +"background: "+bgGrad_stop11
                        +";\n}\n\n";
        }
    }

    if(OBName == "选值框")
    {
        if(subItem31_flag == 2)
        {
            styleText+= QString("%1:up-button{").arg(OBJ);

            if(FrameBox_Flag == 1)//边框
            {
                styleText+= "\nborder-radius: "+QString::number(borderRadius)//圆角半径
                            +";\nborder: "+QString::number(border)//边框厚度
                            +"px solid "+solid//边框颜色
                            +";";
            }

            if(BtnBox_Flag == 1)//大小
            {
                styleText+= "\nmin-height: "+QString::number(minheight/10)//最小高度
                            +"px;\nmin-width: "+QString::number(minwidth/10)//最小宽度
                            +"px;";
            }

            if(PadBox_Flag == 1)//衬垫
            {
                styleText+= "\npadding: "+QString::number(padding_U)//衬垫
                            +"px "+QString::number(padding_R)
                            +"px "+QString::number(padding_D)
                            +"px "+QString::number(padding_L)
                            +"px;";
            }

            if(GradBox_Flag == 1)//渐变
            {
                if(gradyanType == "None")
                {
                    styleText+= "\nbackground: "+bgGrad_stop11
                                +";\n}\n\n";

                    if(subItem311_flag == 2)
                    {
                        styleText+= QString("%1:up-button:hover{\n").arg(OBJ)
                                    +"background: "+bgGrad_stop12
                                    +";\n}\n\n";
                    }
                    if(subItem312_flag == 2)
                    {
                        styleText+= QString("%1:up-button:pressed{\n").arg(OBJ)
                                    +"background: "+bgGrad_stop13
                                    +";\n}\n\n";
                    }
                }
                else if(gradyanType == "Radial Gradyan")
                {
                    styleText+= "\nbackground: qradialgradient(cx: "+QString::number(bgGrad_cx)
                                +", cy: "+QString::number(bgGrad_cy)
                                +",\nfx: "+QString::number(bgGrad_fx)
                                +", fy: "+QString::number(bgGrad_fy)
                                +",\nradius: "+QString::number(bgGrad_radius)
                                +", stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop11
                                +");\n}\n\n";

                    if(subItem311_flag == 2)
                    {
                        styleText+= QString("%1:up-button:hover{\n").arg(OBJ)
                                    +"background: qradialgradient(cx: "+QString::number(bgGrad_cx)
                                    +", cy: "+QString::number(bgGrad_cy)
                                    +",\nfx: "+QString::number(bgGrad_fx)
                                    +", fy: "+QString::number(bgGrad_fy)
                                    +",\nradius: "+QString::number(bgGrad_radius)
                                    +", stop: 0 "+bgGrad_stop0
                                    +", stop: 1 "+bgGrad_stop12
                                    +");\n}\n\n";
                    }
                    if(subItem312_flag == 2)
                    {
                        styleText+= QString("%1:up-button:pressed{\n").arg(OBJ)
                                    +"background: qradialgradient(cx: "+QString::number(bgGrad2_cx)
                                    +", cy: "+QString::number(bgGrad2_cy)
                                    +",\nfx: "+QString::number(bgGrad2_fx)
                                    +", fy: "+QString::number(bgGrad2_fy)
                                    +",\nradius: "+QString::number(bgGrad_radius)
                                    +", stop: 0 "+bgGrad_stop0
                                    +", stop: 1 "+bgGrad_stop13
                                    +");\n}\n\n";
                    }
                }
                else if(gradyanType == "Lineer Gradyan")
                {
                    styleText+= "\nbackground: qlineargradient("+QString("spread:pad,")
                                +"x1:1,y1:0,x2:0,y2:0,\n"
                                +"stop: 0 "+bgGrad_stop0
                                +", stop: 1 "+bgGrad_stop11
                                +");\n}\n\n";

                    if(subItem311_flag == 2)
                    {
                        styleText+= QString("%1:up-button:hover{\n").arg(OBJ)
                                    +"background: qlineargradient(spread:pad,"
                                    +"x1:1,y1:0,x2:0,y2:0,\n"
                                    +"stop: 0 "+bgGrad_stop0
                                    +", stop: 1 "+bgGrad_stop12
                                    +");\n}\n\n";
                    }
                    if(subItem312_flag == 2)
                    {
                        styleText+= QString("%1:up-button:pressed{\n").arg(OBJ)
                                    +"background: qlineargradient(spread:pad,"
                                    +"x1:1,y1:0,x2:0,y2:0,\n"
                                    +"stop: 0 "+bgGrad_stop0
                                    +", stop: 1 "+bgGrad_stop13
                                    +");\n}\n\n";
                    }
                }
            }
            else
            {
                styleText+= sssNULL//防错空字符
                            +"\n}\n\n";
            }

            if(subItem313_flag == 2)//按钮箭头
            {
                styleText+= QString("%1:up-arrow{").arg(OBJ)
                            +"\nborder-radius: "+QString::number(borderRadius)//圆角半径
                            +";\nborder: "+QString::number(border)//边框厚度
                            +"px solid "+solid//边框颜色
                            +";\nbackground: "+bgGrad_stop11
                            +";\nmin-height: "+QString::number(minheight/3)//最小高度
                            +"px;\nmin-width: "+QString::number(minwidth/3)//最小宽度
                            +"px;\npadding: "+QString::number(padding_U)//衬垫
                            +"px "+QString::number(padding_R)
                            +"px "+QString::number(padding_D)
                            +"px "+QString::number(padding_L)
                            +"px;\n}\n\n";
            }

            if(subItem314_flag == 2)//按钮封值
            {
                styleText+= QString("%1:up-arrow:disabled, %1::up-arrow:off{").arg(OBJ)
                            +"background: "+bgGrad_stop11
                            +";\n}\n\n";
            }
        }

    }

    if(OBName == "下拉框")
    {
        if(subItem31_flag == 2)//下拉列表
        {
            styleText+= QString("QComboBox QAbstractItemView{")
                        +"\nborder-radius: 30"//圆角半径
                        +";\nborder: "+QString::number(border)//边框厚度
                        +"px solid "+solid//边框颜色
                        +";\nbackground: "+bgGrad_stop0
                        +";\ncolor: "+bgGrad_stop11
                        +";\nselection-color: "+bgGrad_stop12
                        +";\nselection-background-color: "+bgGrad_stop13
                        +";\nmin-height: "+QString::number(minheight*3)//最小高度
                        +"px;\nmin-width: "+QString::number(minwidth*3)//最小宽度
                        +"px;\npadding: "+QString::number(padding_U)//衬垫
                        +"px "+QString::number(padding_R)
                        +"px "+QString::number(padding_D)
                        +"px "+QString::number(padding_L)
                        +"px;\n}\n\n";
        }
    }

}


