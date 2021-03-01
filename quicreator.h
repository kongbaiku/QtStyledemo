//预处理指令，避免该头文件多重包含
#ifndef QUICREATOR_H
#define QUICREATOR_H

#include <QMainWindow>
#include <QSignalMapper>//信号映射
#include <QVBoxLayout>
#include <QFile>
#include <QTranslator>
#include <QDebug>
#include <QColorDialog>
#include <QFontDialog>
#include <QPrinter>
#include <QPageSetupDialog>
#include <QPrintDialog>
#include <QWizardPage>
#include <QCheckBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QTreeWidget>
#include <QErrorMessage>
#include <QInputDialog>
#include <QProgressDialog>
#include <QTime>
#include <QTimer>
#include <QScrollBar>
#include <QGraphicsView>
#include <QScroller>

class QLineEdit;
class QDialog;
class QLabel;

//把ui_quicreator.h做独立声明,为了调用quicreator.ui
//定义了命名空间Ui，并在其中前置声明了QUICreator类
namespace Ui
{
class QUICreator;
}

class QUICreator : public QMainWindow//新定义QUICreator，继承QMainWindow
{
    Q_OBJECT//Q_OBJECT宏，使用信号槽需添加

public://共用函数
    explicit QUICreator(QWidget *parent = 0);//显式构造函数，并制定父窗口，指明了组件的父组件为QWidget
    ~QUICreator();//析构函数

//    static QUICreator *instance();//单例模式
//    QString Filecontent();//文件内容
//    QString Fileaddress();//文件地址


private://私有对象定义
    Ui::QUICreator *ui;//ui代表的就是quicreator.ui这整个图形化界面，*ui是指向类quicreator对象的一个指针

    bool isUntitled;//isUntitled标签为真表示文件没有保存过，为假表示文件已经被保存过了
    QString curFile;//curFile=文件名，保存当前文件的路径
    QString btnRight;//右键按钮名称
    QLineEdit *findLineEdit;
    QDialog *findDlg;
    QLabel *statusLabel;
    QLabel *permanent;
    QSignalMapper * btnMapper;
    QVBoxLayout *myvbox; //垂直布局

    QMenu *actionMenu = new QMenu;
    QMenu *actionTest = new QMenu;
    QAction *actionOnlyTest = new QAction;
    QAction *actionCode = new QAction;
    QAction *actionStyleSheet = new QAction;

    QDateTime TSime;
    QColor colorDM = Qt::white;

    int btnRightNum = 1;//右键按钮标号
    int day1 = 0;
    int hour1 = 0;
    int min1 = 0;
    int sec1 = 0;
    int buff = 1;

private slots://槽函数
    void initForm();//初始化界面
    void initTableWidget();//表格控件初始化
    void initTreeWidget();//树状控件初始化
    void initListWidget();//列表控件初始化
    void initOther();//其他项初始化
    void initStyle();//样式初始化
    void initTranslator();//翻译初始化
    void iniSignalSlot();//信号槽初始化
    void iniSignalMapper();//信号映射初始化

private slots://槽函数（文件相关）
    void newFile();//新建文件
    bool maybeSave();//判断是否需要保存
    bool save();//保存
    bool saveAs();//另存为
    bool saveFile(const QString &fileName);//保存文件
    bool loadFile(const QString &fileName);//加载文件
    void openFile();//打开文件
    void on_action_O_triggered();//打开
    void on_action_N_triggered();//新建
    void on_action_AS_triggered();//另存为
    void on_action_S_triggered();//保存
    void on_action_C_triggered();//退出

private slots://槽函数（对话框相关）
    void colorDialog1();//颜色对话框（文字颜色）
    void colorDialog2();//颜色对话框（背景颜色）
    void colorDialog3();//颜色对话框（边框颜色）
    void fontDialog();//字体对话框
    void pageDialog();//页面对话框
    void printDialog();//打印对话框
    void messageBoxDialog();//信息对话框
    void wizardDialog();//向导对话框
    QWizardPage* createFirstPage();//向导第一页
    QWizardPage* createSecondPage();//向导第二页
    QWizardPage* createThirdPage();//向导第三页
    void errorDialog();//错误对话框
    void inputDialog();//输入对话框
    void passwordDialog();//密码对话框
    void progressDialog();//进度对话框
    void customDialog(QString a ,QString b);//自定义提示窗
    QDateTime TimeSelector(QString a, QString b);//时间选择器
    void TWUpdateChild(QTreeWidgetItem *itm);//树状子递归
    void TWSetParentPartiallyChecked(QTreeWidgetItem *itm);//树状部分选中
    void TWUpdateParent(QTreeWidgetItem *itm);//树状根判断

private slots://槽函数（其他相关）
    void btnContextMenu(QString btn);//显示右键菜单
    void sourceCode();//查看源代码
    void styleSheet();//查看样式表
    void singleStateChanged(int isChecked);//单选框信号改变
    void singleStateChanged2(int isChecked);
    void cbox1Changed();//CBox1信号改变
    void cbox2Changed(int col);//CBox2信号改变
    void CBColorChanged(int col);//CBColor信号改变
    QString colorInvert(QString color);//颜色取反
    void TEditHighlight();//下方文本框选中高亮
    void hSliderValue(int num);//滑动条值改变
    void danmuku();//弹幕小组件
    void mainSBtn();//主界面start按钮
    void btnstyler();//按钮样式
    void labelstyler();//标签样式
    void scrollbarstyler();//滚动条样式
    void sliderstyler();//滚动条样式
    void comboboxstyler();//下拉框样式
    void spinboxstyler();//选值框样式

protected:
    void closeEvent(QCloseEvent *event);//关闭事件

};

#endif // QUICREATOR_H
