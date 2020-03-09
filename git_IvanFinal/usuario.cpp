#include "usuario.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
Usuario::Usuario(){

}
/*! \file */

/**
 * @brief Usuario::load Función para cargar los datos del formulario de registro.
 * @param recibido
 *
 */
void Usuario::load(JSON recibido){

            m_id = -1;
            m_nombre = QString::fromStdString(recibido["user"]);
            m_correo = QString::fromStdString(recibido["email"]);
            m_contrasenya = QString::fromStdString(recibido["password"]);

}
/**
 * @brief Usuario::load Función para cargar los datos de la base de datos
 * @param id
 *
 */
void Usuario::load(QSqlDatabase db , int id){
    QSqlQuery q(db);
    q.prepare("SELECT * FROM usuario WHERE id_usuario = :idUsuario LIMIT 1");
    q.bindValue(":idUsuario", id);
    bool result {q.exec()};
    if (result)
        {
            q.next();
            m_id = q.value("id_usuario").toInt();
            m_nombre = q.value("nombre").toString();
            m_correo = q.value("correo_electronico").toString();
            m_contrasenya = q.value("contrasenya").toString();

        } // end if
}
/**
 * @brief Usuario::logear Función para cargar los datos del inicio de sesión y los comparan con los datos de la base de datos
 * @param recibido
 * @return bool
 *
 */
bool Usuario::logear(QSqlDatabase db ,JSON recibido){
    QSqlQuery q(db);
    q.prepare("SELECT * FROM public.usuario WHERE nombre = :nombre and contrasenya = crypt(:contrasenya , contrasenya)");
    q.bindValue(":nombre", QString::fromStdString(recibido["user"]));
    q.bindValue(":contrasenya", QString::fromStdString(recibido["password"]));
    bool result {q.exec()};
    bool ok  = true;
    if (result)
    {
        if(q.size() > 0)
        {
            q.next();
            m_id = q.value("id_usuario").toInt();
            m_nombre = q.value("nombre").toString();
            m_correo = q.value("correo_electronico").toString();
            m_contrasenya = q.value("contrasenya").toString();
        }else {
            qDebug() << "No coniciden la contraseña";
            ok = false;
        }
    } // end if
    return ok;
}
/**
 * @brief Usuario::remove Elimina el usuario de la base de datos
 * @return bool
 *
 */
bool Usuario::remove(QSqlDatabase db)
{
    QSqlQuery q(db);
    bool result {false};

    if (m_id > 0)
    {
        q.prepare("DELETE FROM Usuario WHERE id_usuario = :idUsuario");
        q.bindValue(":idUsuario", m_id);
        result = q.exec();
    } // end if

    return result;
}

/**
 * @brief Usuario::save Guarda los datos en la base de datos. Si es un usuario nuevo se hace un INSERT, de lo contrario se hace un UPDATE.
 * @return bool
 *
 */
bool Usuario::save(QSqlDatabase db)
{
    QSqlQuery q(db);

    if (m_id > 0)
    {
        qDebug() << "save update";
        /// UPDATE
        q.prepare("UPDATE usuario SET nombre = :nombre , correo_electronico = :correo , contrasenya = crypt(:contrasenya, gen_salt('bf')) WHERE id_usuario = :idUsuario");
        q.bindValue(":nombre", m_nombre);
        q.bindValue(":correo", m_correo);
        q.bindValue(":contrasenya", m_contrasenya);
        q.bindValue(":idUsuario" , m_id);
    }
    else
    {
        qDebug() << "save insert";
        /// INSERT
        q.prepare("INSERT INTO usuario (nombre , correo_electronico , contrasenya) VALUES (:nombre , :correo , crypt(:contrasenya, gen_salt('bf')))");
        q.bindValue(":nombre", m_nombre);
        q.bindValue(":correo", m_correo);
        q.bindValue(":contrasenya", m_contrasenya);
    } // end if

    bool result {q.exec()};
    qDebug() << q.lastError();
    q.next();
    if (result){qDebug()<<"inserta bien";}

    return result;
}
/**
 * @brief Usuario::getId Devuelve el id del usuario.
 * @return int
 *
 */
int Usuario::getId(){
    return this->m_id;
}

/**
 * @brief Usuario::Login Responde al cliente después de que intente iniciar sesión.
 * @param id
 * @param recibido
 * @return JSON
 *
 */
JSON Usuario::Login(int id ,JSON recibido , bool ok){
    JSON jsonMessage;
    if (ok){

        jsonMessage["idmsgServer"] = id;
        jsonMessage["type"] = "respuesta";
        jsonMessage["respuesta"] = "se ha iniciado sesión";
        jsonMessage["idmsgCliente"] = recibido["msgIdCliente"];
    }else{
        jsonMessage["idmsgServer"] = id;
        jsonMessage["type"] = "respuesta";
        jsonMessage["respuesta"] = "La contraseña y el nombre de usuario no coinciden";
        jsonMessage["idmsgCliente"] = recibido["msgCliente"];
    }

    return jsonMessage;
}
/**
 * @brief Usuario::Logout Responde al cliente después de que cierre la sesión.
 * @param id
 * @param recibido
 * @return JSON
 *
 */
JSON Usuario::Logout(int id ,JSON recibido){
    JSON jsonMessage;
    jsonMessage["idmsgServer"] = id;
    jsonMessage["type"] = "respuesta";
    jsonMessage["respuesta"] = "logout";
    jsonMessage["idmsgCliente"] = recibido["msgCliente"];
    return jsonMessage;
}
/**
 * @brief Usuario::Register Responde al cliente después de que registre un usuario.
 * @param id
 * @return JSON
 *
 */
JSON Usuario::Register(int id){
    JSON jsonMessage;
    jsonMessage["idmsgServer"] = id;
    jsonMessage["type"] = "respuesta";
    jsonMessage["respuesta"] = "usuario registrado";
    return jsonMessage;
}
