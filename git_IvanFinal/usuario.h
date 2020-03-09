#ifndef USUARIO_H
#define USUARIO_H
#include "json.hpp"
#include <QString>
#include <QSqlDatabase>
using JSON = nlohmann::json;
class Usuario
{
public:

    Usuario();
    //getters
        int getId();
    //cargar JSON
        void load(JSON datos);
    //base de datos
        void load(QSqlDatabase db ,int id);
        bool save(QSqlDatabase db);
        bool remove(QSqlDatabase db);
        bool logear(QSqlDatabase db ,JSON recibido);
    //responder al cliente
        JSON Login(int id ,JSON recibido , bool ok);
        JSON Logout(int id,JSON recibido);
        JSON Register(int id);


private:
    int m_id;
    QString m_nombre;
    QString m_correo;
    QString m_contrasenya;


};
#endif // USUARIO_H
