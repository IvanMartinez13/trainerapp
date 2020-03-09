#include <iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"
#include "usuario.h"
#include "ejercicio.h"
#include "entrenamiento.h"
#include "conexion.h"
#include "json.hpp"
#include <QCoreApplication>
#include <QTranslator>
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

using JSON = nlohmann::json;
static int g_id = 0;
static Conexion con;


/*! \file */
/**
 * @brief exists Comprueba si existe algun objeto en un JSON.
 * @param json
 * @param key
 * @return bool
 */
bool exists(const JSON& json, const std::string& key)
{
    return json.find(key) != json.end();
}

/**
 * @brief nuevoId Crea un nuevo ID para los mensajes del servidor.
 * @return int
 */
int nuevoId(){
    g_id ++;
    return g_id;
}

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    QTranslator myappTranslator;
    myappTranslator.load("myapp_es_ES","../");
    a.installTranslator(&myappTranslator);

    //1) Conectar con bbdd
    bool ok = con.open();

    if (ok) {
        qDebug() << "conecta con la base de datos";
    }else {
        qDebug() << "no conecta con la base de datos";
        exit(0);
    }
    //2) Configurar Servidor y opciones TLS
    ix::WebSocketServer server(9990, "0.0.0.0");
    /*ix::SocketTLSOptions tlsOptions;

    tlsOptions.tls = true;
    tlsOptions.certFile = "../cert/localhost.crt";
    tlsOptions.keyFile = "../cert/localhost.key";
    tlsOptions.caFile = "NONE";

    if(tlsOptions.isValid()){
        std::cerr << "SSL valid" << std::endl;
    }

    server.setTLSOptions(tlsOptions);*/

    //3)Inicializar Servidor
    server.setOnConnectionCallback(
        [&server](std::shared_ptr<ix::WebSocket> webSocket,
                  std::shared_ptr<ix::ConnectionState> connectionState)
        {
        //Si el cliente envia un mensaje...
            webSocket->setOnMessageCallback(
                [webSocket, connectionState, &server](const ix::WebSocketMessagePtr msg)
                {
                //RECOGIDA DE DATOS
                    if (msg->type == ix::WebSocketMessageType::Open)
                    {
                        std::cout << "New connection" << std::endl;
                        qDebug() << QObject::tr("New connection");

                    }
                    else if (msg->type == ix::WebSocketMessageType::Close)
                    {
                        std::cout << "Bye bye connection" << std::endl;
                        qDebug() << QObject::tr("Bye bye connection");
                    }
                    else if (msg->type == ix::WebSocketMessageType::Message)
                    {
                        if (!msg->binary)
                        {
                            /// Text format
                            std::cout << "Received message: " << msg->str << std::endl;
                            qDebug() << QObject::tr("Received message: ");
                        }
                        //Parseamos el mensaje a JSON y comprobamos si es valido
                         JSON recivedObject = JSON::parse(msg->str);

                        if(recivedObject.is_discarded())
                        {
                            //JSON erroneo
                            std::cout << "error, no has enviado un JSON" << std::endl;
                        }
                        else
                        {
                            //JSON válido
                            if(exists(recivedObject , "type"))
                            {
                                //RECOGIDA DE DATOS
                                 Usuario user;
                                 Ejercicio ejercicio;
                                 Entrenamiento entrenamiento;
                                //1) Mirar el type del objeto JSON y actuará en consecuencia

                                if(recivedObject["type"] == "crearEntrenamiento")
                                {
                                    //cargar datos
                                    entrenamiento.load(con.getDatabase() , recivedObject);
                                    //guardar datos en la bbdd
                                    entrenamiento.save(con.getDatabase() , user.getId());
                                    //responder al cliente
                                   JSON respuesta = entrenamiento.crearEntrenamiento(nuevoId() , recivedObject);
                                   webSocket->send(respuesta.dump());
                                }//endif

                                if(recivedObject["type"] == "actualizarEntrenamiento")
                                {
                                    //cargar datos
                                    entrenamiento.load(con.getDatabase() , recivedObject);
                                    //guarda datos en bbdd
                                    entrenamiento.save(con.getDatabase() , user.getId());
                                    //responder al cliente
                                    JSON respuesta = entrenamiento.crearEntrenamiento(nuevoId(), recivedObject);
                                    webSocket->send(respuesta.dump());
                                }//endif

                                if(recivedObject["type"] == "borrarEntrenamiento")
                                {
                                    //cargar daros
                                    entrenamiento.load(con.getDatabase() , QString::fromStdString(recivedObject["entrenamientoId"]).toInt());
                                    //eliminar de la base de datos
                                    entrenamiento.remove(con.getDatabase());
                                    //responder al cliente
                                    JSON respuesta = entrenamiento.crearEntrenamiento(nuevoId(), recivedObject);
                                    webSocket->send(respuesta.dump());
                                }//endif


                                if(recivedObject["type"] == "listarEntrenamientos")
                                {
                                    //enviar mensaje JSON al cliente
                                    JSON respuesta = entrenamiento.listar(con.getDatabase() , nuevoId() , user.getId() , recivedObject);
                                    webSocket->send(respuesta.dump());
                                }//endif

                                if(recivedObject["type"] == "login")
                                {
                                    //Comrpobar si el login es valido
                                    bool ok = user.logear(con.getDatabase() , recivedObject);
                                    //responder al cliente
                                    JSON respuesta = user.Login(nuevoId(), recivedObject , ok);
                                    webSocket->send(respuesta.dump());

                                }//endif
                                if(recivedObject["type"] == "logout")
                                {
                                    //responder al cliente
                                    JSON respuesta = user.Logout(nuevoId() ,recivedObject);
                                    webSocket->send(respuesta.dump());
                                }//endif
                                if(recivedObject["type"] == "registrarUsuario")
                                {
                                    //cargar los datos
                                    user.load(recivedObject);
                                    //guardar en la base de datos
                                    user.save(con.getDatabase());
                                    //responder al cliente
                                    JSON respuesta = user.Register(nuevoId());
                                    webSocket->send(respuesta.dump());
                                }//endif
                                if(recivedObject["type"] == "crearEjercicio")
                                {
                                    //cargar los datos
                                    ejercicio.load(recivedObject);
                                    //guardar en la base de datos
                                    ejercicio.save(con.getDatabase() , user.getId());
                                    //responder al cliente
                                    JSON respuesta = ejercicio.crearEjercicio(nuevoId(), recivedObject);
                                    webSocket->send(respuesta.dump());
                                }//endif

                                if(recivedObject["type"] == "actualizarEjercicio")
                                {
                                    //cargar los datos
                                    ejercicio.load(recivedObject);
                                    //guardar en la base de datos
                                    ejercicio.save(con.getDatabase() , user.getId());
                                    //responder al cliente
                                    JSON respuesta = ejercicio.acualizarEjercicio(nuevoId(), recivedObject);
                                    webSocket->send(respuesta.dump());
                                }//endif
                                if(recivedObject["type"] == "borrarEjercicio")
                                {
                                    //cargar los datos
                                    ejercicio.load(con.getDatabase() , QString::fromStdString(recivedObject["ejercicioId"]).toInt());
                                    //eliminar de la base de datos
                                    bool eliminado = ejercicio.remove(con.getDatabase());
                                    //responder al cliente
                                    JSON respuesta = ejercicio.eliminarEjercicio(nuevoId(), recivedObject , eliminado);
                                    webSocket->send(respuesta.dump());
                                }//endif


                                if(recivedObject["type"] == "listarEjercicios")
                                {
                                    //Enviar mensaje JSON al cliente
                                    JSON respuesta = ejercicio.listar(con.getDatabase() , nuevoId() , user.getId() , recivedObject);
                                    webSocket->send(respuesta.dump());
                                }//endif

                                if(recivedObject["type"] == "verEjercicio")
                                {
                                    //cargar datos
                                    ejercicio.load(con.getDatabase() , QString::fromStdString(recivedObject["ejercicioId"]).toInt());
                                    //responder al cliente
                                    JSON respuesta ;
                                    respuesta["ejercicios"]= ejercicio.toJSON();
                                    respuesta["type"] = "ejercicio";
                                    respuesta["idmsgServer"] = nuevoId();
                                    respuesta["idMsgCliente"] = recivedObject["msgIdCliente"];
                                    webSocket->send(respuesta.dump());
                                }
                                if(recivedObject["type"] == "verEntrenamiento")
                                {
                                    //cargar datoss
                                    entrenamiento.load(con.getDatabase() , QString::fromStdString(recivedObject["entrenamientoId"]).toInt());
                                    //responder al cliente
                                    JSON respuesta ;
                                    respuesta["entrenamientos"]= entrenamiento.toJSON();
                                    respuesta["type"] = "entrenamiento";
                                    respuesta["idmsgServer"] = nuevoId();
                                    respuesta["idMsgCliente"] = recivedObject["msgIdCliente"];
                                    webSocket->send(respuesta.dump());
                                }

                            }
                        }//endif




                    }

                }
            );
        }
    );



    auto res = server.listen();
    if (!res.first)
    {
        // Error handling
        return 1;
    }

    server.start();
    server.wait();
    server.stop();



}

