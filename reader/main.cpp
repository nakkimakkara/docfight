#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "googlelogin.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QCoreApplication::setOrganizationName("DocFight");
    QCoreApplication::setApplicationName("GoogleLogin");

    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/reader/main.qml"));
    viewer->showExpanded();

    GoogleLogin login;
    login.getAccess();

    return app->exec();
}
