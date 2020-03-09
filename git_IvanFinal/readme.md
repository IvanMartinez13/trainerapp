
*************************************************************************************************************************************************************************

**En qué consiste TrainerApp**

TrainerApp es una aplicación orientada a los entrenadores de fútbol, que te permite crear ejercicios y entrenamientos para que puedan usarlos con sus respectivos equipos.

La aplicación está conectada a una base de datos donde se guardan los ejercicios y entrenamientos de cada usuario. Por el momento es una aplicación web, pero no se descarta la idea de crear una aplicación para dispositivos Android y iOS. El cliente se conecta al servidor utilizando un socket, a partir de ahí el cliente realiza peticiones al servidor enviando mensajes en formato JSON. El servidor se encarga de resolver dichas peticiones.

La base de datos esta creada con PostgreSQL. La aplicación del cliente está hecha con HTML , CSS y JavaScript. Y el servidor está hecho con c++, en un entorno de desarrollo de QT y he utilizado dos proyectos de Github (nholman JSON y IXWebSocket).

Me hubiera gustado añadirle cosas como por ejemplo: exportar los entrenamientos como PDF y haberle dedicado más tiempo a la página web.

**Pasos para poder utilizar la aplicación.**

1) Importa la base de datos con el archivo BBDD.sql. Crea la base de datos con el nombre "trainerapp".

2) Realiza el Make dentro de la misma carpeta.

3) Ejecutar primero el servidor. "TrainerApp".

4) Utilizar la aplicacion del cliente. "Dentro de la carpeta Cliente, abrir el archivo index.html".

5) Existe un usuario de prueba (Nombre de usuario: Test , Contraseña : 1234).

**Gestión de errores**

Todos estos errores comentados aquí han sido resueltos mediante búsquedas en la documentación de Qt , búsquedas por internet y pedir ayuda al profesor.

1) Problemas  al crear los certificados y al establecer las opciones TLS.

2) Problemas con el formato de los valores de cada campo de un mensaje JSON.

3) Al realizar los tests me di cuenta que tenia que cambiar el código del proyecto principal. Estableciendo así la base de datos como una variable estática.

4) Problemas con el git. Tuve que reiniciar la carpeta .git perdiendo así las primeras entradas.

5) Tuve que consultar la documentación de la página W3Schools para ver como hacer algunas cosas con JavaScript y con HTML.

6) Tuve problemas al utilizar la base de datos de los tests, hasta que me di cuenta que tenia que pasarle a las funciones del proyecto la base de datos como un parámetro.

7) Cuando quería listar ejercicios, me di cuenta que necesitaba si o si un método toJSON().

8) Al principio no tenía bien ordenado el HTML con el CSS y el JavaScript en archivos separados.

9) Problemas con la guía de estilo, al principio no seguía ninguna guía de estilo, hasta que empecé a cometer errores debido a no seguir una guia de estilo.

10) No he podido incluir algunas funcionalidades que me hubiera gustado tener por falta de tiempo. Pero la parte principal de la aplicación es funcional.

*************************************************************************************************************************************************************************
