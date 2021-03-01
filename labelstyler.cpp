#include "Labelstyler.h"
#include "ui_Labelstyler.h"
#include <QColorDialog>

Labelstyler::Labelstyler(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Labelstyler)
{
    ui->setupUi(this);
    color="#000000";//字体颜色初值
    border=2;//按钮边框宽度初值
    minheight=15;
    minwidth=80;
    ui->minheightSlider->setValue(minheight);//设置衬垫滑动条初值
    ui->minwidthSlider->setValue(minwidth);//设置衬垫滑动条初值
    ui->bordThickSlider->setValue(border);//设置边框宽度滑动条初值
    ui->renkLabel->setPalette(QPalette(QColor(color)));//设置字体颜色预览标签
    ui->renkLabel->setAutoFillBackground(true);//小部件背景自动填充

    solid="#000000";//按钮边框颜色初值
    ui->renkLabel2->setPalette(QPalette(QColor(solid)));//设置边框颜色预览标签
    ui->renkLabel2->setAutoFillBackground(true);//小部件背景自动填充

    fontFamily="MS Shell Dlg 2";//初始字体-宋体
    ui->fontComboBox->setCurrentFont(QFont(fontFamily));//设置当前选中字体
    fontSize=8;//字体大小初值
    ui->fontSizeSlider->setValue(fontSize);//设置字体大小滑动条初值
    borderRadius=11;//圆角半径初值
    ui->bordRadSlider->setValue(borderRadius);//设置圆角半径滑动条初值

    padding=8;
    padding_U=8;//按钮衬垫
    padding_D=8;//按钮衬垫
    padding_L=8;//按钮衬垫
    padding_R=8;//按钮衬垫
    ui->PadUpSlider->setValue(padding);//设置衬垫滑动条初值
    ui->PadDownSlider->setValue(padding);//设置衬垫滑动条初值
    ui->PadLeftSlider->setValue(padding);//设置衬垫滑动条初值
    ui->PadRightSlider->setValue(padding);//设置衬垫滑动条初值

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
    ui->gRadiusSlider->setValue(bgGrad_radius*100);//设置渐变半径滑动条初值

    bgGrad_stop0="#ffffff";//渐变普通颜色初值（上沿）
    bgGrad_stop11="#98928c";//渐变普通颜色初值（下沿）
    bgGrad_stop12="#989592";//渐变悬停颜色初值（下沿）
    bgGrad_stop13="#989795";//渐变按下颜色初值（下沿）

    ui->grenkLabel1->setPalette(QPalette(QColor(bgGrad_stop0)));//设置渐变颜色预览标签
    ui->grenkLabel1->setAutoFillBackground(true);//小部件背景自动填充

    ui->grenkLabel2->setPalette(QPalette(QColor(bgGrad_stop11)));//设置渐变颜色预览标签
    ui->grenkLabel2->setAutoFillBackground(true);//小部件背景自动填充

    ui->grenkLabel3->setPalette(QPalette(QColor(bgGrad_stop12)));//设置渐变颜色预览标签
    ui->grenkLabel3->setAutoFillBackground(true);//小部件背景自动填充

    ui->grenkLabel4->setPalette(QPalette(QColor(bgGrad_stop13)));//设置渐变颜色预览标签
    ui->grenkLabel4->setAutoFillBackground(true);//小部件背景自动填充
    updateStylesheet();
}

Labelstyler::~Labelstyler()//析构函数
{
    delete ui;
}

void Labelstyler::updateStylesheet()//更新样式表
{
    styleText= QString("QLabel{\ncolor: "
                       +color
                       +";\nborder: "+QString::number(border)
                       +"px solid "+solid
                       +";\nfont: "+QString::number(fontSize)+"pt \""+fontFamily+"\""+
                       +";\nborder-radius: "+QString::number(borderRadius)
                       +"px;\npadding: "+QString::number(padding_U)
                       +"px "+QString::number(padding_R)
                       +"px "+QString::number(padding_D)
                       +"px "+QString::number(padding_L)
                       +"px;\n");

    if(gradyanType == "None")
    {
        styleText+=     "background: "+bgGrad_stop11
                       +";\nmin-height: "+QString::number(minheight)
                       +"px;\nmin-width: "+QString::number(minwidth)
                       +"px;\n}\n\n";

    }
    else if(gradyanType == "Radial Gradyan")
    {
        styleText+=     "background: qradialgradient(cx: "+QString::number(bgGrad_cx)
                       +", cy: "+QString::number(bgGrad_cy)
                       +",\nfx: "+QString::number(bgGrad_fx)
                       +", fy: "+QString::number(bgGrad_fy)
                       +",\nradius: "+QString::number(bgGrad_radius)
                       +", stop: 0 "+bgGrad_stop0
                       +", stop: 1 "+bgGrad_stop11
                       +");\nmin-height: "+QString::number(minheight)
                       +"px;\nmin-width: "+QString::number(minwidth)
                       +"px;\n}\n\n";
    }
    else if(gradyanType == "Lineer Gradyan")
    {
        styleText+=     "background: qlineargradient("+QString("spread:pad,")
                       +"x1:1,y1:0,x2:0,y2:0,\n"
                       +"stop: 0 "+bgGrad_stop0
                       +", stop: 1 "+bgGrad_stop11
                       +");\nmin-height: "+QString::number(minheight)
                       +"px;\nmin-width: "+QString::number(minwidth)
                       +"px;\n}\n\n";
    }

    ui->TextLabel->setStyleSheet(styleText);//根据样式表更新样式
    ui->styleOutput->setText(styleText);//把样式表显示至文本框
}

QString Labelstyler::prependZeros(QString col)//颜色6位预置零（没应用）
{
    QString rightColor=col;
    while(rightColor.size()<6)
        rightColor.prepend("0");

    return rightColor;
}

void Labelstyler::on_renkButton_clicked()//字体选色按钮
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

void Labelstyler::on_renkButton2_clicked()//边框选色按钮
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

void Labelstyler::on_grenkButton1_clicked()//渐变选色按钮1
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

void Labelstyler::on_grenkButton2_clicked()//渐变选色按钮2
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

void Labelstyler::on_grenkButton3_clicked()//渐变选色按钮3
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

void Labelstyler::on_grenkButton4_clicked()//渐变选色按钮4
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

void Labelstyler::on_bordRadSlider_valueChanged(int value)//圆角半径滑动条值改变
{
    borderRadius= value;//设置值
    updateStylesheet();//更新样式表
}

void Labelstyler::on_bordThickSlider_valueChanged(int value)//边框宽度滑动条值改变
{
    border=value;//设置值
    updateStylesheet();//更新样式表
}

void Labelstyler::on_gRadiusSlider_valueChanged(int value)//渐变分布滑动条值改变
{
    bgGrad_radius=value / 100.0;//设置值
    updateStylesheet();//更新样式表
}

void Labelstyler::on_fontSizeSlider_valueChanged(int value)//字体大小滑动条值改变
{
    fontSize=value;//设置值
    updateStylesheet();//更新样式表
}

void Labelstyler::on_PadUpSlider_valueChanged(int value)//按钮衬垫滑动条值改变(上)
{
    padding_U=value;//设置值
    updateStylesheet();//更新样式表
}

void Labelstyler::on_PadDownSlider_valueChanged(int value)//渐变分布滑动条值改变(下)
{
    padding_D=value;//设置值
    updateStylesheet();//更新样式表
}

void Labelstyler::on_PadLeftSlider_valueChanged(int value)//渐变分布滑动条值改变(左)
{
    padding_L=value;//设置值
    updateStylesheet();//更新样式表
}

void Labelstyler::on_PadRightSlider_valueChanged(int value)//渐变分布滑动条值改变(右)
{
    padding_R=value;//设置值
    updateStylesheet();//更新样式表
}

void Labelstyler::on_minheightSlider_valueChanged(int value)//渐变分布滑动条值改变(右)
{
    minheight=value;//设置值
    updateStylesheet();//更新样式表
}

void Labelstyler::on_minwidthSlider_valueChanged(int value)//渐变分布滑动条值改变(右)
{
    minwidth=value;//设置值
    updateStylesheet();//更新样式表
}

void Labelstyler::on_fontComboBox_currentFontChanged(QFont font)//字体下拉框选项改变
{
//    fontFamily=ui->fontComboBox->currentFont().family();//设置值
    fontFamily=font.family();
    updateStylesheet();//更新样式表
}

void Labelstyler::on_RadcomboBox_currentIndexChanged(int value)//渐变下拉框选项改变
{
    gradyanType=ui->RadcomboBox->currentText();//设置值
    updateStylesheet();//更新样式表
}
