#ifndef CONEXION_H
#define CONEXION_H

#include <iostream>
#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <map>

class Conexion
{

public:
    Conexion();
    bool open();
    void close();
    QSqlDatabase getDatabase();

private:
    QSqlDatabase m_db;
    QString m_hostName;
    QString m_databaseName;
    int m_port;
    QString m_userName;
    QString m_password;
    std::map<std::string, std::string> m_propiedades;
    void loadProperties();
    void readFile();
    void processLine(std::string line);

};
#endif // CONEXION_H
