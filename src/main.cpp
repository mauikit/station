#include <QIcon>
#include <QQmlApplicationEngine>

#include "station_version.h"

#ifdef Q_OS_ANDROID
#include <QGuiApplication>
#else
#include <QApplication>
#endif

#include <KI18n/KLocalizedString>
#include <KAboutData>
#include <KI18n/KLocalizedString>

#include "helpers/keyshelper.h"
#include <QDate>

#define STATION_URI "org.maui.station"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    QCoreApplication::setAttribute(Qt::AA_DisableSessionManager, true);

#ifdef Q_OS_ANDROID
    QGuiApplication app(argc, argv);
#else
    QApplication app(argc, argv);
#endif

    app.setOrganizationName("Maui");
    app.setWindowIcon(QIcon(":/station.svg"));

	KLocalizedString::setApplicationDomain("station");
	KAboutData about(QStringLiteral("station"), i18n("Station"), STATION_VERSION_STRING, i18n("Convergent terminal emulator."),
                     KAboutLicense::LGPL_V3, i18n("© 2019-%1 Nitrux Development Team", QString::number(QDate::currentDate().year())));
	about.addAuthor(i18n("Camilo Higuita"), i18n("Developer"), QStringLiteral("milo.h@aol.com"));
	about.setHomepage("https://mauikit.org");
	about.setProductName("maui/station");
	about.setBugAddress("https://invent.kde.org/maui/station/-/issues");
	about.setOrganizationDomain(STATION_URI);
	about.setProgramLogo(app.windowIcon());

    KAboutData::setApplicationData(about);

	qmlRegisterAnonymousType<Key> (STATION_URI, 1);
	qmlRegisterType<KeysHelper> (STATION_URI, 1, 0, "KeysModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
