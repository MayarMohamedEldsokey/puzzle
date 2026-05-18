#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    // 1. حل مشكلة الشاشة البيضاء وأخطاء الألوان: إجبار الـ QML على إستخدام الـ Basic Style
    qputenv("QT_QUICK_CONTROLS_STYLE", "Basic");

    // 2. استخدام QGuiApplication لأننا بنشغل واجهة QML مباشرة بدون C++ Widgets
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // 3. مسار صفحة النتيجة مباشرة جوه الـ Resources لتقرأ أول ما البرنامج يفتح
    const QUrl url(QStringLiteral("qrc:/qt/qml/CrossWordPP/GameResultPage.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}