
#include "CApp.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));


#ifdef TARGET_BUILD
    qputenv("XDG_RUNTIME_DIR","/tmp/runtime-root");
#ifdef USE_WAYLAND
    qputenv("QT_QPA_PLATFORM","wayland");
#else
    qputenv("QT_QPA_PLATFORM","eglfs");
#endif
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    CApp app(argc, argv);

    return app.exec();
}
