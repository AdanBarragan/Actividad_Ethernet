
Facultad de Telemática
Ingenieria en Tecnologias de Internet
Asignatura: Entornos Inteligentes y Tecnologías Disruptivas
Docente: Castellanos Berján Esli
7°B


Integrantes:
Lopez Montero Jonathan Jesus 
Barragán Sanchez Adan Jacob
Martinez Martinez Edgar Jesús
Montes Cardenas David
Rolón Vazquez Edgar Donaldo
Martinez Guzmán Ignacio


1. Objetivo General	
2. Objetivos Específicos	
3. Competencias	
4. Tabla de Contenidos	
5. Descripción	
6. Requisitos	
7. Instalación y Configuración	
8. Conexiones de Hardware	
9. Parámetros Técnicos del ENC28J60	
10. Uso y ejemplos de Código	
11. Resultados de Prueba	
12. Consideraciones Éticas y de Seguridad	
13. Solución de Problemas	
14. Contribuciones	
15. Referencias	

 #1. Objetivo General
Implementar un servidor web embebido utilizando un ESP32 y el módulo Ethernet ENC28J60 para establecer comunicación mediante una red local y controlar el encendido y apagado de un LED desde un navegador web. 
 2. Objetivos Específicos
Configurar el módulo ENC28J60 para proporcionar conectividad Ethernet al ESP32.
Establecer una dirección IP estática para permitir el acceso al dispositivo dentro de la red local.
Implementar un servidor web utilizando el protocolo HTTP y el puerto 80.
Programar el ESP32 para recibir y procesar solicitudes HTTP provenientes de un navegador.
Controlar el estado de un LED mediante comandos enviados desde una interfaz web.
Diseñar una página web sencilla que permita visualizar el estado actual del LED.
Comprobar la comunicación entre el ESP32, el ENC28J60 y un equipo conectado a la misma red.

 #3. Competencias
Configuración de redes Ethernet.
Programación de microcontroladores ESP32.
Implementación de servidores web embebidos.
Manejo del protocolo HTTP.
Configuración de direcciones IP.
Uso de interfaces de comunicación SPI.
Integración de hardware y software.
Diagnóstico de problemas de conectividad.
Control de dispositivos mediante interfaces web.
Documentación de proyectos de redes e IoT.


 #5. Descripción
En esta actividad se desarrolló un servidor web embebido utilizando una placa ESP32 junto con un módulo Ethernet ENC28J60. El propósito fue establecer una comunicación mediante una red local utilizando una conexión Ethernet y permitir que el ESP32 recibiera solicitudes desde un navegador web. Para realizar la práctica se configuró una dirección IP estática y se utilizó la biblioteca UIP Ethernet, que permite establecer la comunicación entre el ESP32 y el módulo ENC28J60. Como aplicación práctica, se desarrolló una interfaz web desde la cual es posible encender y apagar un LED conectado al ESP32. Esta práctica es relevante para los entornos inteligentes debido a que demuestra cómo un dispositivo físico puede ser controlado remotamente mediante una red, siendo un ejemplo básico de interacción entre dispositivos IoT y servicios web. 



#6. Requisitos
Hardware necesario:
ESP32.
Módulo Ethernet ENC28J60.
Cable Ethernet.
Cable de red armado para la práctica.
LED.
Resistencia para el LED, aproximadamente 220 Ω a 330 Ω.
Protoboard.
Cables Dupont.
Computadora o laptop.
Router o switch Ethernet.

 Software y bibliotecas requeridas:
Arduino IDE.
Soporte para tarjetas ESP32 en Arduino IDE.
Biblioteca UIPEthernet.
Biblioteca SPI, incluida normalmente con el entorno de Arduino.
Navegador web.
Monitor Serie del Arduino IDE.






Conocimientos previos imprescindibles:

Conceptos básicos de redes Ethernet.
Direcciones IPv4.
Funcionamiento básico de una red LAN.
Conceptos básicos de HTTP.
Programación básica en C/C++ para Arduino.
Uso de ESP32.
Conceptos básicos de comunicación SPI.
Conexión de LEDs y resistencias.

7. Instalación y Configuración
Arduino IDE:
Instalar y abrir Arduino IDE.
Verificar que el soporte para ESP32 esté instalado.
Seleccionar la placa ESP32 correspondiente.
Seleccionar el puerto COM donde se encuentra conectada la placa.
Instalar la biblioteca UIPEthernet desde el administrador de bibliotecas.

Hardware:
Conectar el módulo ENC28J60 al ESP32.
Realizar las conexiones correspondientes de alimentación y comunicación SPI.
Conectar el LED al pin GPIO 33 del ESP32.
Utilizar una resistencia en serie con el LED para limitar la corriente.
Conectar el módulo ENC28J60 mediante un cable Ethernet al router o switch.

Configurar la dirección MAC :

Establecer una dirección MAC para identificar el módulo dentro de la red local.
La dirección MAC debe ser diferente a la de otros dispositivos de la misma red para evitar conflictos. 

Configurar la dirección IP :
Esta dirección debe pertenecer al mismo segmento de red que la computadora utilizada para acceder al servidor. 

Configurar el servidor web:
El servidor se configura utilizando el puerto HTTP estándar 80.

Cargar y ejecutar el programa:
Compilar el programa.
Cargarlo al ESP32.
Abrir el Monitor Serie.
Configurar una velocidad de 9600 baudios.
Verificar que se muestre la dirección IP configurada.
Desde una computadora conectada a la misma red, abrir un navegador.
Introducir la dirección IP del ESP32.
Utilizar los botones ENCENDER y APAGAR para controlar el LED.

8. Conexiones de Hardware

<img width="619" height="283" alt="image" src="https://github.com/user-attachments/assets/7e3107c0-c41a-4ba0-ac93-d999504d3771" />



9. Parámetros Técnicos del ENC28J60

<img width="613" height="281" alt="image" src="https://github.com/user-attachments/assets/0b36761d-beb6-484e-921d-d6084b234fda" />



10. Uso y ejemplos de Código
Librería
La librería UIPEthernet permite utilizar el módulo ENC28J60 para establecer comunicación con el ESP32.
	
#include <UIPEthernet.h>

Configuración de la red.
Se establece la dirección MAC del módulo Ethernet y una dirección IP estática para el ESP32.
/ MAC address del módulo (debe ser única en la red local)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Definimos la IP estática solicitada
IPAddress ip(192, 168, 1, 10);

Configuración del servidor web.
crea un objeto EthernetServer y establece el puerto 80, que corresponde al puerto utilizado normalmente para las comunicaciones HTTP. 
	
// Servidor web en el puerto 80
EthernetServer server(80);

Configuración del led.
Para controlar el LED se utiliza el GPIO 33 del ESP32. 
// Pin seguro para el LED en el ESP32
const int ledPin = 33; 
String estadoLED = "APAGADO";

Inicialización del sistema 


void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.println("Iniciando modulo ENC28J60 con IP estatica...");
  
  // Iniciamos la conexión pasando tanto la MAC como la IP
  Ethernet.begin(mac, ip);
  
  server.begin();
  
  // Confirmación en el Monitor Serie
  Serial.print("Conexion exitosa. Servidor web iniciado en la IP: ");
  Serial.println(Ethernet.localIP());
}

Recepción de solicitudes HTTP 

void loop() {
  EthernetClient client = server.available();
  
  if (client) {
    String peticion = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        peticion += c;
        
        if (c == '\n' && peticion.endsWith("\r\n\r\n")) {
          
          // Procesamiento de comandos HTTP
          if (peticion.indexOf("GET /LED=ON") >= 0) {
            digitalWrite(ledPin, HIGH);
            estadoLED = "ENCENDIDO";
            Serial.println("Comando: Encender LED");
          } 
          else if (peticion.indexOf("GET /LED=OFF") >= 0) {
            digitalWrite(ledPin, LOW);
            estadoLED = "APAGADO";
            Serial.println("Comando: Apagar LED");
          }

          // Respuesta HTML
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>ESP32 Ethernet</title>");
          client.println("<style>body{font-family:Arial; text-align:center; margin-top:50px;} .btn{padding:15px 30px; font-size:20px; text-decoration:none; color:white; border-radius:5px;} .btn-on{background-color:#4CAF50;} .btn-off{background-color:#f44336;}</style></head>");
          client.println("<body>");
          
          client.println("<h1>Control de LED via ESP32 y ENC28J60</h1>");
          client.print("<h3>Estado actual del LED: <b>");
          client.print(estadoLED);
          client.println("</b></h3><br>");
          
          client.println("<a href='/LED=ON' class='btn btn-on'>ENCENDER</a>");
          client.println("<a href='/LED=OFF' class='btn btn-off'>APAGAR</a>");
          
          client.println("</body></html>");
          break;
        }
      }
    }
    delay(10);
    client.stop();
    
  }
}"
11. Resultados de Prueba
Conexión del hardware.
ESP32.
ENC28J60.
Cable Ethernet.
Protoboard.
LED.
Cableado utilizado

<img width="479" height="511" alt="image" src="https://github.com/user-attachments/assets/ab8d8b04-cf13-4d0c-94ce-4df19b1690a4" />


Captura del navegador mostrando la interfaz del servidor web.

<img width="630" height="455" alt="image" src="https://github.com/user-attachments/assets/5d2d834a-b050-41a3-8f61-378ea1c49840" />


Evidencia del led encendido.

<img width="625" height="461" alt="image" src="https://github.com/user-attachments/assets/2a960d5c-7cde-431f-b833-109579a27b52" />



12. Consideraciones Éticas y de Seguridad
Privacidad de datos: La aplicación debe evitar recopilar o transmitir información personal que no sea necesaria para el funcionamiento del sistema.
Exposición de la dirección IP:  Al utilizar una IP estática, el dispositivo puede ser localizado dentro de la red local.
Tráfico HTTP no cifrado: Dado que la plataforma opera sobre HTTP estándar, la información transmitida carece de encriptación. En entornos de producción, es fundamental incorporar protocolos de transferencia segura.
Riesgos de seguridad en la interfaz web: Resulta indispensable verificar y filtrar adecuadamente las peticiones entrantes para prevenir la ejecución no autorizada de instrucciones imprevistas.

    
13. Solución de Problemas

Problema 
Causa Probable
Solución 
ENC28J60
Alimentación o cable defectuoso
Verificar 3.3V en VCC y GND 


ESP 32 no detecta el ENC28J60
Pines SPI mal conectados 
Revisar SCK, MISO, MOSI Y CS
No aparece la IP configurada
Error en la configuración de RED 
Revisar Monitor Serial y Confirmar ip estática 
No se puede acceder desde el navegador 
Dispositivos en redes distintas
Conectar ambos a la misma red y verificar IP
Servidor web no responde 
Servidor no inició bien 
Confirmar inicialización correcta en setup() 
LED no enciende 
Pin mal configurado o cableado incorrecto 
Verificar cableado y que el pin coincida con el código 
LED no se apaga 
LED no se apaga 
Revisar que las rutas ON/OFF se reconozcan bien 
Página incorrecta en el navegador 
Error en la respuesta HTML 
Revisar etiquetas y contenido enviado 
Conexión se pierde constantemente 
Cableado, alimentación o red inestable 
Revisar cables, alimentación y conexión Ethernet 
Monitor Serie no muestra nada 
Velocidad (baud rate) incorrecta 
Igualar velocidad con Serial.begin() 
No compila el programa 
Librería faltante o incompatible 
Revisar error del compilador e instalar librería correcta 
Otro dispositivo con la misma IP 
Conflicto de direcciones IP 
Asignar una IP libre en la red 


14. Contribuciones
Describe el flujo de trabajo para aportar mejoras: fork del repositorio, creación de ramas,
convenciones de nombres y apertura de pull requests.

#1. Fork del repositorio
Haz un fork del repositorio a tu cuenta de GitHub usando el botón Fork en la esquina superior derecha.
#2. Clona tu fork
bash
git clone https://github.com/tu-usuario/nombre-del-repositorio.git
cd nombre-del-repositorio
#3. Crea una rama para tu cambio
No trabajes directamente sobre main. Crea una rama descriptiva:
bash
git checkout -b tipo/descripcion-breve
Convención de nombres de ramas:
Prefijo
Uso
feature/
Nueva funcionalidad (ej. feature/soporte-multiples-leds)
fix/
Corrección de errores (ej. fix/led-no-apaga)
docs/
Cambios en documentación (ej. docs/actualizar-readme)
refactor/
Reestructuración de código sin cambiar funcionalidad
test/
Adición o mejora de pruebas

#4. Realiza tus cambios
Sigue el estilo de código existente en el proyecto.
Comenta las secciones relevantes si el cambio no es evidente.
Prueba los cambios en hardware real (ESP32 + ENC28J60) antes de subirlos.
#5. Haz commit de tus cambios
Usa mensajes de commit claros y en tiempo presente:
bash
git add .
git commit -m "fix: corrige el manejo de la ruta /led/off"
#6. Sube la rama a tu fork
bash
git push origin tipo/descripcion-breve
#7. Abre un Pull Request
Ve a tu fork en GitHub y haz clic en Compare & pull request.
Describe claramente:
Qué problema resuelve o qué mejora aporta.
Cómo se probó el cambio.
Capturas de pantalla o logs del Monitor Serie si aplica.
Asegúrate de que tu rama esté actualizada con main antes de enviarlo (git pull origin main o rebase).
#8. Revisión y fusión
El pull request será revisado por los mantenedores del proyecto. Es posible que se soliciten ajustes antes de fusionarlo. Una vez aprobado, se integrará a la rama principal.

#15. Referencias
Solicita un listado de fuentes bibliográficas y recursos consultados, aplicando un estilo de
citación uniforme (APA, IEEE, etc.).

