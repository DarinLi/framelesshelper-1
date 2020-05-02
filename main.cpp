#include <QApplication>
#include <QWidget>

#include "qwinwidget.h"

int main(int argc, char *argv[]) {
    // High DPI scaling is enabled by default from Qt 6
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    // Windows: we are using the manifest file to get maximum compatibility
    // because some APIs are not supprted on older systems such as Windows 7
    // and 8. And once we set the DPI awareness level in the manifest file, any
    // attemptation to try to change it through API will fail. In other words,
    // Qt won't be able to enable or disable the DPI awareness level once we
    // have set it in the manifest file. So the following two lines are uesless
    // actually (However, they are still useful on other platforms).
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    // Don't round the scale factor.
    // This will break QWidget applications because they can't render correctly.
    // Qt Quick applications won't have this issue.
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif

    QApplication application(argc, argv);

    QWidget widget;
    QWinWidget winWidget(&widget);
    winWidget.show();

    return QApplication::exec();
}
