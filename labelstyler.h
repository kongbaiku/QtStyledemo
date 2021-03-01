#ifndef LABELSTYLER_H
#define LABELSTYLER_H

#include <QMainWindow>

namespace Ui
{
class Labelstyler;
}

class Labelstyler : public QMainWindow
{
    Q_OBJECT

public:
    explicit Labelstyler(QWidget *parent = 0);
    ~Labelstyler();


private slots:
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



private:
    Ui::Labelstyler *ui;
    QString styleText;//样式表

    QString color;//字体颜色
    int border;//边框宽
    QString solid;//按钮边框颜色
    int minheight;//最小高度
    int minwidth;//最小宽度
    int borderRadius;//边框圆角半径
    int padding;//按钮衬垫
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

    void updateStylesheet();//更新样式表
    QString prependZeros(QString);//颜色6位预置零（没应用）
};


#endif // LABELSTYLER_H
