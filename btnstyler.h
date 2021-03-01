#ifndef BTNSTYLER_H
#define BTNSTYLER_H

#include <QMainWindow>
#include <QTreeWidget>

class QPushButton;
class QLabel;
class QScrollBar;
class QSlider;
class QComboBox;
class QSpinBox;

//把ui_Btnstyler.h做独立声明,为了调用Btnstyler.ui
//定义了命名空间Ui，并在其中前置声明了Btnstyler类
namespace Ui
{
class Btnstyler;
}

class Btnstyler : public QMainWindow//新定义Btnstyler，继承QMainWindow
{
    Q_OBJECT
    
public:
    explicit Btnstyler(QWidget *parent = 0);
    ~Btnstyler();

private:
    Ui::Btnstyler *ui;
    QString styleText;//样式表
    QString sssNULL = "";
    QLabel  *textLabel;
    QScrollBar *vScrollBar;
    QSlider *vSlider;
    QComboBox *cbox;
    QSpinBox *sbox;

    int FrameBox_Flag;//控件启用标签
    int BtnBox_Flag;
    int FontBox_Flag;
    int PadBox_Flag;
    int GradBox_Flag;

    QString color;//字体颜色
    int border;//边框宽
    QString solid;//按钮边框颜色
    int minheight;//最小高度
    int minwidth;//最小宽度
    int borderRadius;//边框圆角半径
    int padding_U;//按钮衬垫
    int padding_D;//按钮衬垫
    int padding_L;//按钮衬垫
    int padding_R;//按钮衬垫

    double bgGrad_x1;//主光轴点
    double bgGrad_x2;
    double bgGrad_y1;//焦距
    double bgGrad_y2;

    double bgGrad_cx;
    double bgGrad_cy;
    double bgGrad_fx;
    double bgGrad_fy;

    double bgGrad2_cx;
    double bgGrad2_cy;
    double bgGrad2_fx;
    double bgGrad2_fy;

    float bgGrad_radius;//渐变半径
    QString bgGrad_stop0;//渐变颜色
    QString bgGrad_stop11;
    QString bgGrad_stop12;
    QString bgGrad_stop13;
    QString fontFamily;//字体名称
    QString gradyanType;//渐变类型
    int fontSize;//字体大小

    QTreeWidgetItem *group1;
    QTreeWidgetItem *subItem11;
    QTreeWidgetItem *subItem12;
    QTreeWidgetItem *subItem13;
    QTreeWidgetItem *group2;
    QTreeWidgetItem *subItem21;
    QTreeWidgetItem *subItem211;
    QTreeWidgetItem *subItem212;
    QTreeWidgetItem *subItem213;
    QTreeWidgetItem *subItem214;
    QTreeWidgetItem *subItem31;
    QTreeWidgetItem *subItem311;
    QTreeWidgetItem *subItem312;
    QTreeWidgetItem *subItem313;
    QTreeWidgetItem *subItem314;
    QTreeWidgetItem *subItem41;
    QTreeWidgetItem *subItem411;
    QTreeWidgetItem *subItem412;
    QTreeWidgetItem *subItem413;

    int group1_flag;
    int subItem11_flag;
    int subItem12_flag;
    int subItem13_flag;
    int group2_flag;
    int subItem21_flag;
    int subItem211_flag;
    int subItem212_flag;
    int subItem213_flag;
    int subItem214_flag;
    int subItem31_flag;
    int subItem311_flag;
    int subItem312_flag;
    int subItem313_flag;
    int subItem314_flag;
    int subItem41_flag;
    int subItem411_flag;
    int subItem412_flag;
    int subItem413_flag;


    
private slots:
    void initCheck();//勾选初始化
    void initPreview();//预览初始化
    void initForm();//初始化界面
    void initTreeWidget();//树状控件初始化
    void initSignalSlot();//信号槽初始化

    void treeChanged(QTreeWidgetItem *item, int col);//树状图选择改变
    void updateStylesheet();//更新样式表

    QString prependZeros(QString col);//颜色6位预置零（没应用）

    void FrameBoxChecked();//边框控件启用标志
    void BtnBoxChecked();//按钮控件启用标志
    void FontBoxChecked();//字体控件启用标志
    void PadBoxChecked();//衬垫控件启用标志
    void GradBoxChecked();//渐变控件启用标志

    void on_renkButton_clicked();//字体选色按钮
    void on_renkButton2_clicked();//边框选色按钮
    void on_grenkButton1_clicked();//渐变选色按钮1（上沿）
    void on_grenkButton2_clicked();//渐变选色按钮2（下沿普通）
    void on_grenkButton3_clicked();//渐变选色按钮3（下沿悬停）
    void on_grenkButton4_clicked();//渐变选色按钮4（下沿按下）
    void on_bordRadSlider_valueChanged(int value);//圆角半径滑动条值改变
    void on_bordThickSlider_valueChanged(int value);//边框宽度滑动条值改变
    void on_gRadiusSlider_valueChanged(int value);//渐变分布滑动条值改变
    void on_PadUpSlider_valueChanged(int value);//按钮衬垫滑动条值改变(上)
    void on_PadDownSlider_valueChanged(int value);//渐变分布滑动条值改变(下)
    void on_PadLeftSlider_valueChanged(int value);//渐变分布滑动条值改变(左)
    void on_PadRightSlider_valueChanged(int value);//渐变分布滑动条值改变(右)
    void on_fontSizeSlider_valueChanged(int value);//字体大小滑动条值改变
    void on_minheightSlider_valueChanged(int value);//按钮高度滑动条值改变
    void on_minwidthSlider_valueChanged(int value);//按钮宽度滑动条值改变
    void on_fontComboBox_currentFontChanged(QFont font);//字体下拉框选项改变
    void on_RadcomboBox_currentIndexChanged(int value);//渐变下拉框选项改变

    void on_btnOK_clicked();//应用样式表按钮
    void on_btncancel_clicked();//取消按钮
    void publicStyle(QString OBJ);//通用样式
    void partStyle(QString OBJ);//局部样式
    void partStyle2(QString OBJ);//局部样式
};

#endif // BTNSTYLER_H
