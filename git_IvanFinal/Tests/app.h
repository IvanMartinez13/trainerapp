#ifndef APP_H
#define APP_H
#include "doctest.h"
#include "json.hpp"
#include "../entrenamiento.h"
#include "../usuario.h"
#include "../ejercicio.h"
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
using JSON = nlohmann::json;


class Db
{
public:
    QSqlDatabase getDatabase();
    Db();
    ~Db();
    bool init();
    void close();
    QSqlError lastError();

private:
     QSqlDatabase m_db;

};



class App : public QObject
{
    Q_OBJECT

    doctest::Context m_context;

public:
    App(QObject *parent = nullptr);

public slots:
    void run();
};

#endif // APP_H
