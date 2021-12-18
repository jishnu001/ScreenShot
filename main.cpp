#include <QCommandLineParser>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QPixmap>
#include <QScreen>
#include <iostream>
int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Shot");
    parser.addHelpOption();

    const QCommandLineOption fileNameOption("f", "Filename for the screenshot", "filename, default is shot");
    const QCommandLineOption screenNumberOption("n", "Screen number", "screen number, default is 0");

    parser.addOption(fileNameOption);
    parser.addOption(screenNumberOption);

    parser.process(a);

    QString fileName = "shot.png";
    int screenNumber = 0;

    if (parser.isSet(fileNameOption))
    {
        fileName = parser.value(fileNameOption);
    }
    if (parser.isSet(screenNumberOption))
    {
        screenNumber = parser.value(screenNumberOption).toInt();
    }

    QScreen *screen = QGuiApplication::primaryScreen();

    if (!screen)
    {
        std::cerr << "Error getting screenshot";
        return 0;
    }

    const auto& originalPixmap = screen->grabWindow(screenNumber);
    if (!originalPixmap.save(fileName))
    {
        std::cerr << "Error saving to file: " << fileName.toStdString();
    }
    else
    {
        std::cerr << "Saved screenshot to: " << fileName.toStdString();
    }
    return 0;
}
