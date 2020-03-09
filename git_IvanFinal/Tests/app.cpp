#include "app.h"
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include <QSqlQuery>

App::App(QObject *parent) : QObject(parent)
{
    QTimer::singleShot(0, this, SLOT(run()));
}


void App::run()
{
    qDebug() << "running...";

    m_context.run(); // run
    if (m_context.shouldExit())
    {
        QCoreApplication::quit();
    } // end if

}

QSqlDatabase Db::getDatabase(){
    return m_db;
}

Db::~Db()
{
    if (m_db.isOpen())
    {
        m_db.close();
    } // end if
}


Db::Db()
{
    if (!QSqlDatabase::contains( "MyDb"))
    {
        m_db = QSqlDatabase::addDatabase("QPSQL", "MyDb");
    }
    else
    {
        m_db = QSqlDatabase::database("MyDb");
    } // end if
    m_db.setHostName("localhost");
    m_db.setPort(5432);
    m_db.setUserName("postgres");
    m_db.setPassword("");

}


void Db::close()
{
    m_db.close();
}

bool Db::init()
{
    bool result = 0;

    m_db.close();
    m_db.setDatabaseName("template1");

    bool ok = m_db.open();

    if (ok)
    {

        qDebug() << "Borrando...";
        QSqlQuery q0("DROP DATABASE IF EXISTS prueba_doctest", m_db);
        if (q0.lastError().type() == QSqlError::NoError)
        {
            qDebug() << "Creando...";
            QSqlQuery q1("CREATE DATABASE prueba_doctest", m_db);
            if (q1.lastError().type() == QSqlError::NoError)
            {
                m_db.close();
                m_db.setDatabaseName("prueba_doctest");
                m_db.open();

                /// Crea estructura en la base de datos
                QString sql {"CREATE TABLE usuario (\
                    id_usuario     SERIAL, \
                    nombre    varchar(50), \
                    correo_electronico    varchar(50),\
                    contrasenya varchar(50),\
                    PRIMARY KEY(id_usuario))"};

                QString sql2 {"CREATE TABLE ejercicio (\
                    id_ejercicio     SERIAL, \
                    objetivo     varchar(50), \
                    espacio     varchar(50), \
                    explicacion     varchar(50), \
                    reglas     varchar(50), \
                    tiempotrabajo     integer, \
                    tiempodescanso     integer, \
                    tiempototal     integer, \
                    id_usuario  integer, \
                    PRIMARY KEY(id_ejercicio), \
                    FOREIGN KEY (id_usuario) REFERENCES usuario (id_usuario))"};

               QString sql3 {"CREATE TABLE entrenamiento(\
                    id_entrenamiento   SERIAL, \
                    objetivo  varchar(50) ,\
                    numero_jugadores integer, \
                    material  varchar(30) , \
                    tiempo_duracion  integer , \
                    parteinicial  integer , \
                    partefinal  integer , \
                    parteprincipal  integer , \
                    id_usuario integer, \
                    PRIMARY KEY(id_entrenamiento), \
                    FOREIGN KEY (id_usuario) REFERENCES usuario (id_usuario) , \
                    FOREIGN KEY (parteinicial) REFERENCES ejercicio (id_ejercicio) , \
                    FOREIGN KEY (partefinal) REFERENCES ejercicio (id_ejercicio) , \
                    FOREIGN KEY (parteprincipal) REFERENCES ejercicio (id_ejercicio))"};

                qDebug() << "Iniciando...";
                QSqlQuery q2(sql, m_db);
                QSqlQuery q3(sql2, m_db);
                QSqlQuery q4(sql3, m_db);
                if (q2.lastError().type() == QSqlError::NoError)
                {
                    result = true;
                }else{
                    qDebug() << "CC:" << q2.lastError().text();
                } // end if
            }
            else
            {
                qDebug() << "BB:" << q1.lastError().text();
            } // end if

        }
        else
        {
            qDebug() << "AA:" << q0.lastError().text();
        } // end if

    } // end if

    return result;
}

QSqlError Db::lastError()
{
    return m_db.lastError();
}



TEST_CASE("Usuario"){
Db db;
bool ok = db.init();
JSON datosUsuario;
Usuario usuario;
datosUsuario["user"] = "Ivan";
datosUsuario["email"] = "ivan@email.com";
datosUsuario["password"] = "1234";

if (ok){
    usuario.load(datosUsuario);
    CHECK(usuario.save(db.getDatabase()) == true);
    usuario.logear(db.getDatabase() , datosUsuario);
    CHECK(usuario.save(db.getDatabase()) == true);
    CHECK(usuario.remove(db.getDatabase()) == true);
}

}

TEST_CASE("Ejercicio"){
Db db;
bool ok = db.init();

JSON datosUsuario;
Usuario usuario;
datosUsuario["user"] = "Ivan";
datosUsuario["email"] = "ivan@email.com";
datosUsuario["password"] = "1234";

Ejercicio ejercicio;
JSON datosEjercicio;
datosEjercicio["id"] = "-1";
datosEjercicio["objetivo"] = "pase";
datosEjercicio["reglas"] = "dos toques";
datosEjercicio["explicacion"] = "realizar el circuito de pases";
datosEjercicio["espacio"] = "medio campo";
datosEjercicio["tiempotrabajo"] = "30";
datosEjercicio["tiemporecuperacion"] = "2";

if(ok){
    usuario.load(datosUsuario);
    usuario.save(db.getDatabase());
    usuario.logear(db.getDatabase() , datosUsuario);
    ejercicio.load(datosEjercicio);
    CHECK(ejercicio.save(db.getDatabase() , usuario.getId()) == true);
    ejercicio.load(db.getDatabase() , 1);
    CHECK(ejercicio.save(db.getDatabase() , usuario.getId()) == true);
    JSON jsonEjercicio;
    jsonEjercicio["ejercicios"] = ejercicio.toJSON();
    CHECK(jsonEjercicio["ejercicios"]["ejercicio"]["id"] > 0);
    CHECK(ejercicio.remove(db.getDatabase()) == true);

}
}

TEST_CASE("Entrenamiento"){
Db db;
bool ok = db.init();

JSON datosUsuario;
Usuario usuario;
datosUsuario["user"] = "Ivan";
datosUsuario["email"] = "ivan@email.com";
datosUsuario["password"] = "1234";

Ejercicio ejercicio;
JSON datosEjercicio;
datosEjercicio["id"] = "-1";
datosEjercicio["objetivo"] = "pase";
datosEjercicio["reglas"] = "dos toques";
datosEjercicio["explicacion"] = "realizar el circuito de pases";
datosEjercicio["espacio"] = "medio campo";
datosEjercicio["tiempotrabajo"] = "30";
datosEjercicio["tiemporecuperacion"] = "2";

Entrenamiento entrenamiento;
JSON datosEntrenamiento;
datosEntrenamiento["id"] = "-1";
datosEntrenamiento["objetivo"] = "pases";
datosEntrenamiento["numero_jugadores"] = "11";
datosEntrenamiento["material"] = "conos";
datosEntrenamiento["tiempoDuracion"] = "30";
datosEntrenamiento["parteInicial"]["id"] = "1";
datosEntrenamiento["partePrincipal"]["id"] = "1";
datosEntrenamiento["parteFinal"]["id"] = "1";

if(ok){
    usuario.load(datosUsuario);
    usuario.save(db.getDatabase());
    usuario.logear(db.getDatabase() , datosUsuario);
    ejercicio.load(datosEjercicio);
    ejercicio.save(db.getDatabase() , usuario.getId());
    ejercicio.load(db.getDatabase() , 1);
    entrenamiento.load(db.getDatabase() , datosEntrenamiento);
    CHECK(entrenamiento.save(db.getDatabase() , 1) == true);
    entrenamiento.load(db.getDatabase() , 1);
    CHECK(entrenamiento.remove(db.getDatabase()) == true);

}


}
