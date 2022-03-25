#include "widget.h"
#include "CocoaInitializer.h"
#include "SparkleUpdater.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CocoaInitializer initializer;
    CSparkleUpdater::Instance()->Init("http://localhost:8000/SparkleTest/2.0/appcast.xml");
    CSparkleUpdater::Instance()->checkAndMaybeShowUI();

    Widget w;
    w.show();
    return a.exec();
}
