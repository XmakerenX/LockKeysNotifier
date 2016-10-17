#include "myeventfilter.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QWindow>
#include <QtX11Extras/QX11Info>

#include <X11/XKBlib.h>
#include <X11/extensions/shape.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:/main.qml")));
    QObject* object = component.create();
    QWindow* win = static_cast<QWindow*>(object);

    // Make Window click-through
    Pixmap mask;
    mask = XCreatePixmap(QX11Info::display(),
                win->winId(),
                1, /* width  */
                1, /* height */
                1  /* depth  */);
    XShapeCombineMask(QX11Info::display(),
                win->winId(),
                ShapeInput,
                0, /* x-offset */
                0, /* y-offset */
                mask,
                ShapeSet);
    XFreePixmap(QX11Info::display(), mask);

    app.installEventFilter(new myEventFilter(object));

    if (!XkbSelectEvents(QX11Info::display(), XkbUseCoreKbd, XkbIndicatorStateNotifyMask, XkbIndicatorStateNotifyMask))
        return 1;

    return app.exec();
}
