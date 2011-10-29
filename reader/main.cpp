#include <QtGui/QApplication>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include "qmlapplicationviewer.h"
#include "googlelogin.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QCoreApplication::setOrganizationName("DocFight");
    QCoreApplication::setApplicationName("GoogleLogin");

    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());
    //QDeclarativeView viewer;
    //viewer.showFullScreen();
    //viewer.setSource(QUrl::fromLocalFile("qml/reader/main.qml"));

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/reader/main.qml"));
    viewer->showExpanded();

    GoogleLogin* loggeri = new GoogleLogin;
    loggeri->getAccess();

    //viewer.engine()->rootContext()->setContextProperty("loggeri", loggeri);
    viewer->getEngine()->rootContext()->setContextProperty("loggeri", loggeri);

    return app->exec();
}
