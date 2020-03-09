#ifndef EJERCICIO_H
#define EJERCICIO_H
#include "json.hpp"
#include <QString>
#include <QLinkedList>
#include <QSqlDatabase>
using JSON = nlohmann::json;

class Ejercicio
{
public:
    Ejercicio();
    //geters
        int getID();
    //cargar JSON
        void load(JSON recibido);
    //base de datos
        void load(QSqlDatabase db , int id);
        bool save(QSqlDatabase db , int idUser);
        bool remove(QSqlDatabase db );
        JSON listar(QSqlDatabase db , int id , int idUser , JSON recibido);
    //From JSON to Ejercicio y from Ejercicio to JSON
        JSON toJSON();
        Ejercicio toEjercicio(QSqlDatabase db , JSON Mensaje);

    //respuestas al cliente
        JSON crearEjercicio(int id , JSON recibido);
        JSON acualizarEjercicio(int id , JSON recibido);
        JSON eliminarEjercicio(int id , JSON recibido , bool eliminado);


private:
    int m_id = 0;
    QString m_objetivo;
    QString m_espacio;
    QString m_explicacion;
    QString m_reglas;
    int m_tiempoTrabajo;
    int m_tiempoRecuperacion;
    int m_TiempoTotal;



};

#endif // EJERCICIO_H
