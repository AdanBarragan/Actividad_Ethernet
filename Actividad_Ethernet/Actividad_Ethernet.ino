"#include <UIPEthernet.h>

// MAC address del módulo (debe ser única en la red local)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Definimos la IP estática solicitada
IPAddress ip(192, 168, 1, 10);

// Servidor web en el puerto 80
EthernetServer server(80);

// Pin seguro para el LED en el ESP32
const int ledPin = 33; 
String estadoLED = "APAGADO";

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