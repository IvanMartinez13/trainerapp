var g_idMensaje = 0;
var g_sesion = 0;
var g_dentro = false;
var g_ejercicio = 0;

function darIdmsg(){
    g_idMensaje++;
    return g_idMensaje;
}

//Gestion de Menus
function mostrarRegistro(){
 document.getElementById("registro").style.display = "block";
 document.getElementById("login").style.display = "none";
}

function Inicio(){
    document.getElementById("login").style.display = "block";
    document.getElementById("registro").style.display = "none";
    document.getElementById("menu").style.display = "none";
    document.getElementById("ejercicios").style.display = "none";
    document.getElementById("crearEjercicio").style.display = "none";
    document.getElementById("verEjercicios").style.display = "none";
    document.getElementById("entrenamientos").style.display = "none";
    document.getElementById("crearEntrenamiento").style.display = "none";
    document.getElementById("verEntrenamientos").style.display = "none";
    document.getElementById("error").style.display = "none";
}

function Menu(){
    if(g_dentro == true){
        console.log(g_dentro);
        document.getElementById("login").style.display = "none";
        document.getElementById("menu").style.display = "block";
        document.getElementById("error").style.display = "none";
    }else if(g_dentro == false){
        document.getElementById("error").style.display = "block";
    }
}
function resetBontones(){
    document.getElementById("actualizarEjercicio").disabled = true;
    document.getElementById("borrarEjercicio").disabled = true;
    document.getElementById("actualizarEntrenamiento").disabled = true;
    document.getElementById("borrarEntrenamiento").disabled = true;
}
function activarbotonesEjercicios(){
    var ok = document.getElementById("lista").value
    if (ok != null){
        document.getElementById("actualizarEjercicio").disabled = false;
        document.getElementById("borrarEjercicio").disabled = false;
    }

}

function activarbotonesEntrenamientos(){
    var ok = document.getElementById("listaEntrenamientos").value
    if (ok =! null){
        document.getElementById("actualizarEntrenamiento").disabled = false;
        document.getElementById("borrarEntrenamiento").disabled = false; 
    }

}

function resetCrearEjercicio(){
    document.getElementById("tituloEjercicio").innerHTML = "Crear ejercicio";

    document.getElementById("form1").reset();
}
function resetCrearEntrenamiento(){
    document.getElementById("tituloEntrenamiento").innerHTML = "Crear entrenamiento";


    document.getElementById("parteInicial_old").style.display ="none";

    document.getElementById("partePrincipal_old").style.display ="none";

    document.getElementById("parteFinal_old").style.display ="none";

    document.getElementById("antes").style.display = "none"; 
    document.getElementById("antes1").style.display = "none";  
    document.getElementById("antes2").style.display = "none";
    document.getElementById("form2").reset();
}
function mostarCrearEjercicio(){
    document.getElementById("crearEjercicio").style.display = "block";
    document.getElementById("ejercicios").style.display = "none";
    document.getElementById("entrenamientos").style.display = "none";
    document.getElementById("crearEntrenamiento").style.display = "none";
    document.getElementById("verEjercicios").style.display = "none";
    document.getElementById("verEntrenamientos").style.display = "none";
    
}
function mostarVerEjercicios(){
    listarEjercicios();
    resetBontones();
    document.getElementById("errorBorrar").style.display = "none";
    document.getElementById("ejercicios").style.display = "none";
    document.getElementById("crearEjercicio").style.display = "none";
    document.getElementById("entrenamientos").style.display = "none";
    document.getElementById("crearEntrenamiento").style.display = "none";
    document.getElementById("verEjercicios").style.display = "block";
    document.getElementById("verEntrenamientos").style.display = "none";
}


function mostrarEjercicios(){
    document.getElementById("ejercicios").style.display = "block";
    document.getElementById("crearEjercicio").style.display = "none";
    document.getElementById("verEjercicios").style.display = "none";
    document.getElementById("entrenamientos").style.display = "none";
    document.getElementById("verEntrenamientos").style.display = "none";
    document.getElementById("crearEntrenamiento").style.display = "none";
    document.getElementById("errorEjercicio").style.display = "none";
}

function mostrarEntrenamientos(){
    document.getElementById("entrenamientos").style.display = "block";
    document.getElementById("ejercicios").style.display = "none";
    document.getElementById("crearEjercicio").style.display = "none";
    document.getElementById("crearEntrenamiento").style.display = "none";
    document.getElementById("verEjercicios").style.display = "none";
    document.getElementById("verEntrenamientos").style.display = "none";
    document.getElementById("errorEntrenamiento").style.display = "none";
}

function mostrarCrearEntrenamientos(){
    listarEjercicios();
    document.getElementById("entrenamientos").style.display = "none";
    document.getElementById("ejercicios").style.display = "none";
    document.getElementById("crearEjercicio").style.display = "none";
    document.getElementById("crearEntrenamiento").style.display = "block";
    document.getElementById("verEjercicios").style.display = "none";
    document.getElementById("verEntrenamientos").style.display = "none";
}

function mostrarVerEntrenamientos(){
    listarEntrenamientos();
    resetBontones();
    document.getElementById("entrenamientos").style.display = "none";
    document.getElementById("ejercicios").style.display = "none";
    document.getElementById("crearEjercicio").style.display = "none";
    document.getElementById("crearEntrenamiento").style.display = "none";
    document.getElementById("verEjercicios").style.display = "none";
    document.getElementById("verEntrenamientos").style.display = "block";
}
function entrar(event) {
  var object = JSON.parse(event.data);
  if (object.respuesta == "se ha iniciado sesión"){
    g_dentro = true;
    Menu();
  }
}
//Funciones Gestion BDD

function crearEntrenamiento(){
        if(g_dentro == true){
            var idmsgCliente = darIdmsg();
            var valueType = "crearEntrenamiento";
            if(document.getElementById("idEntrenamiento").value == null){
                var valueID= -1;
            }else{
                var valueID= document.getElementById("idEntrenamiento").value;

            }
            var valueObjetivo = document.getElementById("objetivoEntrenamiento").value;
            var valueNumeroJugadores = document.getElementById("numeroJugadores").value;
            var valueMaterial = document.getElementById("material").value;
            var valueTiempoDuracion = document.getElementById("tiempoDuracionEntrenamiento").value;
            var valueparteInicial = document.getElementById("parteInicial").value;
            var valueIDEjercicioInicial = valueparteInicial.split(" ");
            var JsonInicial = {id : valueIDEjercicioInicial[1]}

            var valuepartePrincipal = document.getElementById("partePrincipal").value;
            var valueIDEjercicioPrincipal = valuepartePrincipal.split(" ");
            var JsonPrincipal = {id : valueIDEjercicioPrincipal[1]}

            var valueparteFinal = document.getElementById("parteFinal").value;
            var valueIDEjercicioFinal = valueparteFinal.split(" ");
            var JsonFinal = {id : valueIDEjercicioFinal[1]}

            var ok = /^([0-9]+)$/.test(valueTiempoDuracion);
            if(valueObjetivo != "" && valueNumeroJugadores  != "" && valueMaterial  != "" && valueTiempoDuracion != "" && valueparteInicial != "" && valueIDEjercicioInicial != "" && valueIDEjercicioPrincipal != "" && valueIDEjercicioFinal != ""){
                if(ok){
                    var crearEntrenamientoJson ={msgIdCliente: idmsgCliente, type: valueType, id: valueID ,objetivo: valueObjetivo, numero_jugadores: valueNumeroJugadores ,material: valueMaterial ,  tiempoDuracion: valueTiempoDuracion, parteInicial: JsonInicial, partePrincipal: JsonPrincipal , parteFinal: JsonFinal};
                    socket.send(JSON.stringify(crearEntrenamientoJson));
                    mostrarVerEntrenamientos();
                    document.getElementById("errorEntrenamiento").style.display = "none";
                }else{
                    document.getElementById("errorEntrenamiento").innerHTML = "El campo Tiempo de entrenamiento ha de ser un número";
                    document.getElementById("errorEntrenamiento").style.display = "block";
                }
            }else{
                    document.getElementById("errorEntrenamiento").innerHTML = "Hay campos obligatorios vacíos";
                    document.getElementById("errorEntrenamiento").style.display = "block";
            }


        }
}

function updateEjercicio(){
    if(document.getElementById("lista").value != ""){
        var idmsgCliente = darIdmsg();
        var cadena= document.getElementById("lista").value;
        var idEjercicio = cadena.split(" ");
        var valueType = "verEjercicio";
        var Json = {msgIdCliente: idmsgCliente, type: valueType, ejercicioId: idEjercicio[1]}
        socket.send(JSON.stringify(Json));   
    }
}

function deleteEntrenamiento(){
    if(document.getElementById("listaEntrenamientos").value != ""){
        var idmsgCliente = darIdmsg();
        var cadena= document.getElementById("listaEntrenamientos").value;
        var idEntrenamiento = cadena.split(" ");
        var valueType = "borrarEntrenamiento";
        var Json = {msgIdCliente: idmsgCliente, type: valueType, entrenamientoId: idEntrenamiento[1]}
        socket.send(JSON.stringify(Json));
        listarEntrenamientos();   
    }
}

function updateEntrenamiento(){
    if(document.getElementById("listaEntrenamientos").value != ""){
        var idmsgCliente = darIdmsg();
        var cadena= document.getElementById("listaEntrenamientos").value;
        var idEntrenamiento = cadena.split(" ");
        var valueType = "verEntrenamiento";
        var Json = {msgIdCliente: idmsgCliente, type: valueType, entrenamientoId: idEntrenamiento[1]}
        socket.send(JSON.stringify(Json));
        document.getElementById("antes").style.display = "block"; 
        document.getElementById("antes1").style.display = "block";  
        document.getElementById("antes2").style.display = "block";    
    }
}

function deleteEjercicio(){
    if(document.getElementById("lista").value != ""){
        var idmsgCliente = darIdmsg();
        var cadena= document.getElementById("lista").value;
        var idEjercicio = cadena.split(" ");
        var valueType = "borrarEjercicio";
        var Json = {msgIdCliente: idmsgCliente, type: valueType, ejercicioId: idEjercicio[1]}
        socket.send(JSON.stringify(Json));
        listarEjercicios();   
    }
}

function verEjercicio(element){
    mostarCrearEjercicio();
    document.getElementById("tituloEjercicio").innerHTML = "Actualizar ejercicio";
    document.getElementById("idEjercicio").value = element.id;
    document.getElementById("objetivo").value = element.objetivo;
    document.getElementById("reglas").value = element.reglas;
    document.getElementById("explicacion").value = element.explicacion;
    document.getElementById("espacio").value = element.espacio;
    document.getElementById("tiempotrabajo").value = element.tiempoTrabajo;
    document.getElementById("tiemporecuperacion").value = element.tiempoRecuperacion;
}

function verEntrenamiento(element){
    mostrarCrearEntrenamientos();
    document.getElementById("tituloEntrenamiento").innerHTML = "Actualizar entrenamiento";
    document.getElementById("idEntrenamiento").value = element.id;
    document.getElementById("objetivoEntrenamiento").value = element.objetivo;
    document.getElementById("numeroJugadores").value = element.numero_jugadores;
    document.getElementById("material").value = element.material;
    document.getElementById("tiempoDuracionEntrenamiento").value = element.tiempoDuracion;
    var ID = "ID: "
    document.getElementById("parteInicial_old").style.display ="block";
    document.getElementById("parteInicial_old").value = ID + element.parteInicial;

    document.getElementById("partePrincipal_old").style.display ="block";
    document.getElementById("partePrincipal_old").value = ID + element.partePrincipal;

    document.getElementById("parteFinal_old").style.display ="block";
    document.getElementById("parteFinal_old").value = ID + element.parteFinal;

    document.getElementByClassName("antes").style.display = "block";
}




function crearEjercicio(){
    console.log(g_dentro);
        if(g_dentro == true){
            var idmsgCliente = darIdmsg();
            if(document.getElementById("tituloEjercicio").innerHTML == "Actualizar ejercicio"){
                var valueType = "actualizarEjercicio";
            }else{
                var valueType = "crearEjercicio";
            }
            
            if(document.getElementById("idEjercicio").value == null){
                var valueID= -1;
            }else{
                var valueID= document.getElementById("idEjercicio").value;
            }
            var valueObjetivo = document.getElementById("objetivo").value;
            var valueReglasProvocacionConsignas = document.getElementById("reglas").value;
            var valueExplicacion = document.getElementById("explicacion").value;
            var valueEspacio = document.getElementById("espacio").value;
            var valueTiempoTrabajo = document.getElementById("tiempotrabajo").value;
            var valueTiempoRecuperacion = document.getElementById("tiemporecuperacion").value;
            var ok1 = /^([0-9]+)$/.test(valueTiempoTrabajo);
            var ok2 = /^([0-9]+)$/.test(valueTiempoRecuperacion);
            if(valueObjetivo != "" && valueReglasProvocacionConsignas  != "" && valueExplicacion  != "" && valueEspacio != "" && valueTiempoTrabajo != "" && valueTiempoRecuperacion != ""){
                if(ok1 == true && ok2 == true){
                    var crearEjercicioJson ={msgIdCliente: idmsgCliente, type: valueType,id: valueID ,objetivo: valueObjetivo , reglas: valueReglasProvocacionConsignas , explicacion: valueExplicacion , espacio: valueEspacio, tiempotrabajo: valueTiempoTrabajo, tiemporecuperacion: valueTiempoRecuperacion};
                    socket.send(JSON.stringify(crearEjercicioJson));
                    mostarVerEjercicios();
                    document.getElementById("errorEjercicio").style.display = "none";
                } else{
   
                    document.getElementById("errorEjercicio").style.display = "block";
                    document.getElementById("errorEjercicio").innerHTML = "El campo Tiempo de trabajo y Tiempo de recuperación ha de ser un número";
                }
            }else{
                document.getElementById("errorEjercicio").style.display = "block";    
                document.getElementById("errorEjercicio").innerHTML = "Hay campos obligatorios vacíos";
            }





        }
}



function listarEjercicios(){
    var idmsgCliente = darIdmsg();
    var valueType = "listarEjercicios";
    var listarEjerciciosJSon = {msgIdCliente: idmsgCliente, type: valueType};
     socket.send(JSON.stringify(listarEjerciciosJSon));
}

function listarEntrenamientos(){
    var idmsgCliente = darIdmsg();
    var valueType = "listarEntrenamientos";
    var listarEjerciciosJSon = {msgIdCliente: idmsgCliente, type: valueType};
     socket.send(JSON.stringify(listarEjerciciosJSon));
}

function login(){
    var idmsgCliente = darIdmsg();
    var valueType = "login";
    var valueUser = document.getElementById("nombre").value;
    var passwordValue = document.getElementById("contrasenya").value;
    var loginJson = {msgIdCliente: idmsgCliente, type: valueType, user: valueUser, password: passwordValue};
    socket.send(JSON.stringify(loginJson));


}

function logout(){
    var idmsgCliente = darIdmsg();
    var valueType = "logout";
    g_dentro = false;
    var logoutJson = {msgIdCliente: idmsgCliente, type: valueType};
    socket.send(JSON.stringify(logoutJson));
}

function register(){
    var idmsgCliente = darIdmsg();
    var valueType = "registrarUsuario";
    var valueUser = document.getElementById("nombreRegistro").value;
    var valueCorreoElectronico = document.getElementById("correoElectronico").value;
    var passwordValue = document.getElementById("contrasenyaRegistro").value;
    var partes_correo = valueCorreoElectronico.split("@");
    var ok = false;
    if(partes_correo[0] != null && partes_correo[1] != null){
        ok = true;
    }
    
    if(valueUser !="" && valueCorreoElectronico !=""  && passwordValue != ""){    
        if(ok){

            var registerJson = {msgIdCliente: idmsgCliente, type: valueType,user: valueUser, email: valueCorreoElectronico, password: passwordValue};
            socket.send(JSON.stringify(registerJson));
            Inicio();;
            document.getElementById("errorRegistro").style.display = "none";
        }else{
            document.getElementById("errorRegistro").innerHTML = "El campo correo correo electrónico ha de ser un correo electrónico (ejemplo@ejemplo)";
            document.getElementById("errorRegistro").style.display = "block";
        }
    }else{
            document.getElementById("errorRegistro").innerHTML = "Hay campos obligatorios vacíos";
            document.getElementById("errorRegistro").style.display = "block";    
    }
    document.getElementById("form").reset();
}




function listaDeEntrenamientos(element){
    var listaEntrenamientos = document.getElementById("listaEntrenamientos");
    var idEntrenamiento  = element.entrenamiento.id;
    console.log(idEntrenamiento);
    var objetivoEntrenamiento = element.entrenamiento.objetivo;
    var optionEntrenamiento = document.createElement("option");
    optionEntrenamiento.text = "Id: "+ idEntrenamiento + " Objetivo: "+ objetivoEntrenamiento;
    listaEntrenamientos.add(optionEntrenamiento);
    
}

function recogerDatos(element){
    var lista = document.getElementById("lista");
    var id = element.ejercicio.id;
    var objetivo = element.ejercicio.objetivo;
    var option = document.createElement("option");
    option.text = "Id: "+ id + " Objetivo: "+ objetivo ;
    lista.add(option);
}
function recogerDatos1(element){
    var parteInicial = document.getElementById("parteInicial");
    var id = element.ejercicio.id;
    var objetivo = element.ejercicio.objetivo;
    var option = document.createElement("option");
    option.text = "Id: "+ id + " Objetivo: "+ objetivo;
    parteInicial.add(option);
}
function recogerDatos2(element){
    var partePrincipal = document.getElementById("partePrincipal");
    var id = element.ejercicio.id;
    var objetivo = element.ejercicio.objetivo;
    var option = document.createElement("option");
    option.text = "Id: "+ id + " Objetivo: "+ objetivo;
    partePrincipal.add(option);
}
    document.getElementById("login").style.display = "block";
    document.getElementById("registro").style.display = "none";
    document.getElementById("menu").style.display = "none";
function recogerDatos3(element){
    var parteFinal = document.getElementById("parteFinal");
    var id = element.ejercicio.id;
    var objetivo = element.ejercicio.objetivo;
    var option = document.createElement("option");
    option.text = "Id: "+ id + " Objetivo: "+ objetivo;
    parteFinal.add(option);
}
  function vaciarListas(){
  
        var lista = document.getElementById("lista");
        lista.length=0;

        var parteInicial = document.getElementById("parteInicial");
        parteInicial.length=0;

        var partePrincipal= document.getElementById("partePrincipal");
        partePrincipal.length=0;
        
        var parteFinal= document.getElementById("parteFinal");
        parteFinal.length=0;
   
  }
  
  function llenarListas(array1){
  
        array1.forEach(element => recogerDatos(element));
        array1.forEach(element => recogerDatos1(element));
        array1.forEach(element => recogerDatos2(element));
        array1.forEach(element => recogerDatos3(element));
        
  }