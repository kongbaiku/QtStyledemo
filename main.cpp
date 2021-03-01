#include "quicreator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//载入了Qt（应用程序类）的架构
    a.setFont(QFont("Microsoft Yahei", 9));//设置应用程序字体
    a.setWindowIcon(QIcon(":/main.ico"));//设置应用程序图标

    QUICreator w;
    w.setWindowTitle("Qt样式表设定程序");//设置应用程序标题
    w.show();//显示窗口

    return a.exec();
}
