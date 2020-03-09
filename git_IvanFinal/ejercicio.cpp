#include "ejercicio.h"
#include "entrenamiento.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

Ejercicio::Ejercicio()
{

}
/*! \file */

/**
 * @brief Ejercicio::load Carga los datos del formulario para crear un ejercicio.
 * @param recibido
 *
 */
void Ejercicio::load(JSON recibido){
    m_id =QString::fromStdString(recibido["id"]).toInt();
    m_objetivo = QString::fromStdString(recibido["objetivo"]);
    m_reglas = QString::fromStdString(recibido["reglas"]);
    m_explicacion =QString::fromStdString(recibido["explicacion"]);
    m_espacio = QString::fromStdString(recibido["espacio"]);
    m_tiempoTrabajo = QString::fromStdString(recibido["tiempotrabajo"]).toInt();
    m_tiempoRecuperacion = QString::fromStdString(recibido["tiemporecuperacion"]).toInt();
    m_TiempoTotal = m_tiempoTrabajo + m_tiempoRecuperacion;
}

/**
 * @brief Ejercicio::load Cargar los datos de los ejercicios de la base de datos
 * @param db
 * @param id
 *
 */
void Ejercicio::load(QSqlDatabase db , int id){
    QSqlQuery q(db);
    q.prepare("SELECT * FROM ejercicio WHERE id_ejercicio = :idEjercicio LIMIT 1");
    q.bindValue(":idEjercicio", id);
    bool result {q.exec()};
    if (result)
        {
            q.next();
            m_id = q.value("id_ejercicio").toInt();
            m_objetivo = q.value("objetivo").toString();
            m_reglas = q.value("reglas").toString();
            m_explicacion = q.value("explicacion").toString();
            m_espacio = q.value("espacio").toString();
            m_tiempoTrabajo = q.value("tiempotrabajo").toInt();
            m_tiempoRecuperacion = q.value("tiempodescanso").toInt();
            m_TiempoTotal = m_tiempoTrabajo + m_tiempoRecuperacion;
        } // end if
}

/**
 * @brief Ejercicio::toJSON parsea el Ejercicio a JSON
 * @return JSON
 *
 */
JSON Ejercicio::toJSON()
{
    JSON respuesta;

    respuesta["ejercicio"]["id"] = m_id;
    respuesta["ejercicio"]["objetivo"] = m_objetivo.toStdString();
    respuesta["ejercicio"]["reglas"] = m_reglas.toStdString();
    respuesta["ejercicio"]["explicacion"] = m_explicacion.toStdString();
    respuesta["ejercicio"]["espacio"] =  m_espacio.toStdString();
    respuesta["ejercicio"]["tiempoTrabajo"] = m_tiempoTrabajo;
    respuesta["ejercicio"]["tiempoRecuperacion"] = m_tiempoRecuperacion;
    respuesta["ejercicio"]["tiempoTotal"] = m_TiempoTotal;


    return respuesta;
}


/**
 * @brief Ejercicio::listar Devuelve un JSON con un listado de los ejercicios de un usuario en concreto.
 * @param db
 * @param id
 * @param idUser
 * @return JSON
 *
 */
JSON Ejercicio::listar(QSqlDatabase db , int id , int idUser , JSON recibido) {
    QSqlQuery q(db);
    JSON respuesta;
    q.prepare("SELECT * FROM ejercicio WHERE id_usuario = :idUser order by id_ejercicio");
    q.bindValue(":idUser" , idUser);
    bool result {q.exec()};
    if (result)
    {
        respuesta["idmsgServer"] = id;
        bool exito = false;
        while(q.next()){
            exito = true;
            Ejercicio ejercicio;
            ejercicio.load(db , q.value("id_ejercicio").toInt());
            if(ejercicio.getID() > 0){
                respuesta["type"] =  "respuesta";
                respuesta["idMsgCliente"] = recibido["msgIdCliente"];
                respuesta["respuesta"] = "lista de ejercicios";
                respuesta["ejercicios"].push_back(ejercicio.toJSON());
            }

      }
        if (exito == false){
            respuesta["respuesta"] = "no hay ejercicios";
        }

    }



    return respuesta;
}

/**
 * @brief Ejercicio::remove Elimina un ejercicio de la bbdd.
 * @param db
 * @return bool
 *
 */
bool Ejercicio::remove(QSqlDatabase db)
{
    QSqlQuery q(db);
    bool result {false};
    bool ok = false;
    bool borrar = false;


    if (m_id > 0)
    {
        q.prepare("SELECT * FROM entrenamiento WHERE parteinicial = :idEjercicio OR parteprincipal = :idEjercicio OR partefinal = :idEjercicio");
        q.bindValue(":idEjercicio", m_id);
        result = q.exec();
        if(q.size() > 0){
            ok = true;
        }
    } // end if
    if(ok == false){
        if (m_id > 0)
        {
            borrar = true;
            q.prepare("DELETE FROM ejercicio WHERE id_ejercicio = :idEjercicio");
            q.bindValue(":idEjercicio", m_id);
            result = q.exec();
        } // end if

    }// end if


    return borrar;
}

/**
 * @brief Ejercicio::save  Guarda un ejercicio en la bbdd. Si es un ejercicio nuevo se hace un INSERT, de lo contrario se realiza un UPDATE.
 * @param db
 * @param idUser
 * @return bool
 *
 */
bool Ejercicio::save(QSqlDatabase db , int idUser)
{
    QSqlQuery q(db);

    if (m_id > 0)
    {
        qDebug() << "save update";
        // UPDATE
        q.prepare("UPDATE ejercicio SET objetivo = :objetivo , espacio = :espacio , explicacion = :explicacion , reglas = :reglas , tiempoTrabajo = :tiempoTrabajo , tiempoDescanso = :tiempoDescanso , tiempoTotal = :tiempoTotal , id_usuario = :idUser WHERE id_ejercicio = :idEjercicio");
        q.bindValue(":objetivo", m_objetivo);
        q.bindValue(":espacio", m_espacio);
        q.bindValue(":explicacion", m_explicacion);
        q.bindValue(":reglas", m_reglas);
        q.bindValue(":tiempoTrabajo", m_tiempoTrabajo);
        q.bindValue(":tiempoDescanso", m_tiempoRecuperacion);
        q.bindValue(":tiempoTotal", m_TiempoTotal);
        q.bindValue(":idUser", idUser);
        q.bindValue(":idEjercicio", m_id);
    }
    else
    {
        qDebug() << "save insert";
        // INSERT
        q.prepare("INSERT INTO ejercicio (objetivo , espacio , explicacion , reglas , tiempotrabajo , tiempodescanso , tiempototal ,id_usuario) VALUES (:objetivo , :espacio , :explicacion , :reglas , :tiempotrabajo , :tiempodescanso , :tiempototal , :idUser)");
        q.bindValue(":objetivo", m_objetivo);
        q.bindValue(":espacio", m_espacio);
        q.bindValue(":explicacion", m_explicacion);
        q.bindValue(":reglas", m_reglas);
        q.bindValue(":tiempotrabajo", m_tiempoTrabajo);
        q.bindValue(":tiempodescanso", m_tiempoRecuperacion);
        q.bindValue(":tiempototal", m_TiempoTotal);
        q.bindValue(":idUser", idUser);
    } // end if

    bool result {q.exec()};
    qDebug() << q.lastError();
    q.next();
    return result;
}

/**
 * @brief Ejercicio::toEjercicio Transforma un JSON a Ejercicio.
 * @param db
 * @param Mensaje
 * @return Ejercicio
 *
 */
Ejercicio Ejercicio::toEjercicio(QSqlDatabase db , JSON Mensaje){
    Ejercicio ejercicio;
    ejercicio.load(db , QString::fromStdString(Mensaje["id"]).toInt());
    qDebug()<< "funciona";
    return ejercicio;
}

/**
 * @brief Ejercicio::crearEjercicio Respuesta al cliente por crear un ejercicio.
 * @param id
 * @param recibido
 * @return JSON
 *
 */
JSON Ejercicio::crearEjercicio(int id, JSON recibido){
    JSON jsonMessage;
    jsonMessage["idmsgServer"] = id;
    jsonMessage["type"] =  "respuesta";
    jsonMessage["respuesta"] = "ejercicio guardado";
    jsonMessage["idmsgCliente"] = recibido["msgIdCliente"];
    return jsonMessage;
}
/**
 * @brief Ejercicio::acualizarEjercicio Respuesta al cliente por actualizar un ejercicio
 * @param id
 * @param recibido
 * @return JSON
 *
 */
JSON Ejercicio::acualizarEjercicio(int id, JSON recibido){
    JSON jsonMessage;
    jsonMessage["idmsgServer"] = id;
    jsonMessage["type"] = "respuesta";
    jsonMessage["respuesta"] = "ejercicio actualizado";
    jsonMessage["idmsgCliente"] = recibido["msgIdCliente"];
    return jsonMessage;
}
/**
 * @brief Ejercicio::eliminarEjercicio Respuesta al cliente por eleiminar un ejercicio
 * @param id
 * @param recibido
 * @param eliminado
 * @return JSON
 *
 */
JSON Ejercicio::eliminarEjercicio(int id, JSON recibido , bool eliminado){
    JSON jsonMessage;
    jsonMessage["idmsgServer"] = id;
    jsonMessage["type"] = "respuesta";
    if(eliminado){
        jsonMessage["respuesta"] = "ejercicio borrado";
    }else{
        jsonMessage["respuesta"] = "Este ejercicio forma parte de uno o varios entrenamientos, elimina o cambia esos entrenamientos";
    }

    jsonMessage["idmsgCliente"] = recibido["msgIdCliente"];
    return jsonMessage;
}


/**
 * @brief Ejercicio::getID
 * @return int
 *
 */
int Ejercicio::getID(){
    return m_id;
}
