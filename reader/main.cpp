#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "kqoauthmanager.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/reader/main.qml"));
    viewer->showExpanded();

    KQOAuthManager man;

    return app->exec();
}
