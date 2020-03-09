#define DOCTEST_CONFIG_IMPLEMENT
#include <QCoreApplication>
#include "app.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    App app;

    return a.exec();
}
