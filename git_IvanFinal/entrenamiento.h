#ifndef ENTRENAMIENTO_H
#define ENTRENAMIENTO_H

#include <QString>
#include "json.hpp"
#include "ejercicio.h"
#include <QSqlDatabase>

using JSON = nlohmann::json;
class Entrenamiento
{
public:
    Entrenamiento();
    //cargar JSON
        void load(QSqlDatabase db , JSON recibido);
    //base de datos
        void load(QSqlDatabase db ,int id);
        bool save(QSqlDatabase db ,int idUser);
        bool remove(QSqlDatabase db);
        JSON listar(QSqlDatabase db ,int id , int idUser , JSON recibido);
        void getLast(QSqlDatabase db);
    //from entrenamiento to JSON
        JSON toJSON();
    //respuestas al cliente
        JSON crearEntrenamiento(int id ,JSON recibido);
        JSON actualizarEntrenamiento(int id , JSON recibido);
        JSON eliminarEntrenamiento(int id , JSON recibido);

private:
    int m_id;
    QString m_objetivo;
    int m_numeroJugadores;
    QString m_material;
    int m_tiempoDuracion;
    Ejercicio m_parteInicial;
    Ejercicio m_partePrincipal;
    Ejercicio m_parteFinal;
};

#endif // ENTRENAMIENTO_H
