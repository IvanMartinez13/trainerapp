#include "entrenamiento.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

Entrenamiento::Entrenamiento()
{

}
/*! \file */

/**
 * @brief Entrenamiento::load  Carga los datos de un formulario para crear o actualizar un Entrenamiento.s
 * @param db
 * @param recibido
 *
 */
void Entrenamiento::load(QSqlDatabase db , JSON recibido){
    m_id =QString::fromStdString(recibido["id"]).toInt();
    m_objetivo = QString::fromStdString(recibido["objetivo"]);
    m_numeroJugadores = QString::fromStdString(recibido["numero_jugadores"]).toInt();
    m_material =  QString::fromStdString(recibido["material"]);
    m_tiempoDuracion =  QString::fromStdString(recibido["tiempoDuracion"]).toInt();
    m_parteInicial = m_parteInicial.toEjercicio(db , recibido["parteInicial"]);
    m_partePrincipal = m_partePrincipal.toEjercicio(db , recibido["partePrincipal"]);
    m_parteFinal = m_parteFinal.toEjercicio(db , recibido["parteFinal"]);
}

/**
 * @brief Entrenamiento::load  Carga los datos de un Entrenamiento de la bbdd.
 * @param db
 * @param id
 *
 */
void Entrenamiento::load(QSqlDatabase db , int id){
    QSqlQuery q(db);
    q.prepare("SELECT * FROM entrenamiento WHERE entrenamiento.id_entrenamiento = :idEntrenamiento LIMIT 1");
    q.bindValue(":idEntrenamiento", id);
    bool result {q.exec()};
    if (result)
        {
            q.next();
            m_id = q.value("id_entrenamiento").toInt();
            m_objetivo = q.value("objetivo").toString();
            m_numeroJugadores = q.value("numero_jugadores").toInt();
            m_material = q.value("material").toString();
            m_tiempoDuracion = q.value("tiempo_duracion").toInt();
            m_parteInicial.load(db , q.value("parteinicial").toInt());
            m_partePrincipal.load(db , q.value("parteprincipal").toInt());
            m_parteFinal.load(db , q.value("partefinal").toInt());

        } // end if
}

/**
 * @brief Entrenamiento::toJSON Transforma un entrenamiento a JSON.
 * @return JSON
 *
 */
JSON Entrenamiento::toJSON()
{
    JSON respuesta;
    qDebug() << m_id;
    respuesta["entrenamiento"]["id"] = m_id;
    respuesta["entrenamiento"]["objetivo"] = m_objetivo.toStdString();
    respuesta["entrenamiento"]["numero_jugadores"] = m_numeroJugadores;
    respuesta["entrenamiento"]["material"] = m_material.toStdString();
    respuesta["entrenamiento"]["tiempoDuracion"] =  m_tiempoDuracion;
    respuesta["entrenamiento"]["parteInicial"] =  m_parteInicial.getID();
    respuesta["entrenamiento"]["partePrincipal"] =  m_partePrincipal.getID();
    respuesta["entrenamiento"]["parteFinal"] =  m_parteFinal.getID();


    return respuesta;
}

/**
 * @brief Entrenamiento::listar Devuelve un JSON con todos los entrenamientos de un usuario.
 * @param db
 * @param id
 * @param idUser
 * @param recibido
 * @return JSON
 *
 */

JSON Entrenamiento::listar(QSqlDatabase db , int id , int idUser , JSON recibido) {
    QSqlQuery q(db);
    JSON respuesta;
    q.prepare("SELECT * FROM entrenamiento WHERE id_usuario = :idUser ORDER BY id_entrenamiento");
    q.bindValue(":idUser" , idUser);
    bool result {q.exec()};
    bool exito = false;
    if (result)
    {
        respuesta["idmsgServer"] = id;

        while(q.next()){
            exito = true;
            Entrenamiento entrenamiento;
            entrenamiento.load(db , q.value("id_entrenamiento").toInt());
            respuesta["type"] =  "respuesta";
            respuesta["respuesta"] = "lista de entrenamientos";
            respuesta["idMsgCliente"] = recibido["msgIdCliente"];
            if(entrenamiento.m_id > 0){
                respuesta["entrenamientos"].push_back(entrenamiento.toJSON());
            }


      }

    }
    if (exito == false){
        respuesta["respuesta"] = "no hay entrenamientos";
    }

    return respuesta;
}

/**
 * @brief Entrenamiento::remove Elimina un Entrenamiento
 * @param db
 * @return bool
 *
 */
bool Entrenamiento::remove(QSqlDatabase db )
{
    QSqlQuery q(db);
    bool result {false};

    if (m_id > 0)
    {
        qDebug() << "entra en borrar";
        q.prepare("DELETE FROM entrenamiento WHERE id_entrenamiento = :idEntrenamiento");
        q.bindValue(":idEntrenamiento", m_id);
        result = q.exec();
    } // end if

        qDebug() << q.lastError();

    return result;
}

/**
 * @brief Entrenamiento::save  Guarda un Entrenamiento en la bbdd, si es un entrenamiento nuevo se hace un INSERT, de lo contrario se hace un UPDATE.
 * @param db
 * @param idUser
 * @return bool
 *
 */
bool Entrenamiento::save(QSqlDatabase db  , int idUser)
{
    QSqlQuery q(db);
    bool result = false;

    if (m_id > 0)
    {
        qDebug() << "save update";
        // UPDATE
        q.prepare("UPDATE entrenamiento SET objetivo = :objetivo , numero_jugadores = :numeroJugadores , material = :material, tiempo_duracion = :tiempo_duracion, id_usuario = :idUsuario , parteinicial = :parteInicial , parteprincipal = :partePrincipal , partefinal = :parteFinal WHERE id_entrenamiento = :idEntrenameinto");
        q.bindValue(":objetivo", m_objetivo);
        q.bindValue(":numeroJugadores", m_numeroJugadores);
        q.bindValue(":material", m_material);
        q.bindValue(":tiempo_duracion", m_tiempoDuracion);
        q.bindValue(":idUsuario", idUser);
        q.bindValue(":parteInicial", m_parteInicial.getID());
        q.bindValue(":partePrincipal", m_partePrincipal.getID());
        q.bindValue(":parteFinal", m_parteFinal.getID());
        q.bindValue(":idEntrenameinto", m_id);
        result = q.exec();
    }
    else
    {
        qDebug() << "save insert";
        // INSERT
        q.prepare("INSERT INTO entrenamiento (objetivo , numero_jugadores , material , tiempo_duracion , id_usuario ,parteinicial, parteprincipal, partefinal) VALUES (:objetivo , :numeroJugadores , :material , :tiempoDuracion , :idUsuario , :parteInicial, :partePrincipal, :parteFinal)");
        q.bindValue(":objetivo", m_objetivo);
        q.bindValue(":numeroJugadores", m_numeroJugadores);
        q.bindValue(":material", m_material);
        q.bindValue(":tiempoDuracion", m_tiempoDuracion);
        q.bindValue(":parteInicial", m_parteInicial.getID());
        q.bindValue(":partePrincipal", m_partePrincipal.getID());
        q.bindValue(":parteFinal", m_parteFinal.getID());
        q.bindValue(":idUsuario", idUser);
        result = q.exec();
    } // end if


    qDebug() << q.lastError();
    q.next();
    return result;
}

/**
 * @brief Entrenamiento::getLast Recoge el ultimo Entrenamiento creado.
 * @param db
 *
 */
void Entrenamiento::getLast(QSqlDatabase db){
    QSqlQuery q(db);
    q.prepare("SELECT * FROM public.entrenamiento ORDER BY id_entrenamiento DESC limit 1");
    bool result {q.exec()};
    if (result)
        {
            q.next();
            m_id = q.value("id_entrenamiento").toInt();
            m_objetivo = q.value("objetivo").toString();
            m_numeroJugadores = q.value("numero_jugadores").toInt();
            m_material = q.value("material").toString();
            m_tiempoDuracion = q.value("tiempo_duracion").toInt();
        } // end if
}

/**
 * @brief Entrenamiento::crearEntrenamiento Responde al cliente por crear un entrenameinto.
 * @param id
 * @param recibido
 * @return JSON
 *
 */
JSON Entrenamiento::crearEntrenamiento(int id, JSON recibido){
    JSON jsonMessage;
    jsonMessage["idmsgServer"] = id;
    jsonMessage["type"] =  "respuesta";
    jsonMessage["respuesta"] = "entrenamiento guardado";
    jsonMessage["idmsgCliente"] = recibido["msgIdCliente"];
    return jsonMessage;
}
/**
 * @brief Entrenamiento::actualizarEntrenamiento Responde al cliente por actualizar un entrenamiento
 * @param id
 * @param recibido
 * @return JSON
 *
 */
JSON Entrenamiento::actualizarEntrenamiento(int id, JSON recibido){
    JSON jsonMessage;
    jsonMessage["idmsgServer"] = id;
    jsonMessage["type"] =  "respuesta";
    jsonMessage["respuesta"] = "entrenamiento actualizado";
    jsonMessage["idmsgCliente"] = recibido["msgIdCliente"];
    return jsonMessage;
}
/**
 * @brief Entrenamiento::eliminarEntrenamiento Responde al cliente por eliminar un entrenamiento
 * @param id
 * @param recibido
 * @return JSON
 *
 */
JSON Entrenamiento::eliminarEntrenamiento(int id, JSON recibido){
    JSON jsonMessage;
    jsonMessage["idmsgServer"] = id;
    jsonMessage["type"] =  "respuesta";
    jsonMessage["respuesta"] = "entrenamiento eliminado";
    jsonMessage["idmsgCliente"] = recibido["msgIdCliente"];
    return jsonMessage;
}
