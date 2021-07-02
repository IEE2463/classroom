/*
 * Ayudantia 5: IoT 
 * MQTT y ESP32 
 * 
 * Codigo ESP32 Arduino
 *
 * Autor: Francisco Fonseca - Camila Turrieta
 * Curso: SEP 2021-1
 * 
 */

// Librerias utilizadas
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>


// Conexion Wifi
#ifndef STASSID
#define STASSID "Flancisco"
#define STAPSK  "foquiiii"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;


// MQTT
char host[] = "broker.mqttdashboard.com"; // Broker publico
char clientid[] = "...";
char username[] = "...";
char topicname[] = "SEP/ayudantia5/test"; // topico como parametro
const int mqttPort = 1883;
const char* mqttUser =  "...";
const char* mqttPassword =  "...";


// Funciones propias
void setup_wifi();
void Connect(void); 
void mqtt_send_msg(String str_1, char * topicname);


WiFiClient wificlient;
PubSubClient client(host, 1883, wificlient);


void setup() 
{  
  // Monitor Serial ESP MONITOR 115200 por default
  Serial.begin(115200);

  // Inicializacion del Wifi
  Serial.println("");
  Serial.println("Iniciando WiFi...");
  setup_wifi();


  // Conectarse al servidor
  Serial.println("");
  Serial.println("Conectandose al servidor...");
  client.setServer(host, 1883);

  // Conectar el cliente
  Serial.println("Conectando el cliente...");
  Connect();

}

void loop() 
{

  // Si el cliente no esta conectado, vuelve a conectar.   
  if (!client.connected()) 
  {
    Connect();
  }
  //Publicar al topico
  mqtt_send_msg("MSG TEST 3",topicname);

  // Delay 2 segundos
  delay(2000);
  
  // permite recibir los mensajes 
  client.loop();

}


void Connect(void) 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    
    if (client.connect("ESPClient")) 
    {
      Serial.println("connected");
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void mqtt_send_msg(char * str_1, char * topicname)
{
  int i = 0;
  int len = strlen(str_1);
  
  client.publish(topicname,(uint8_t *) str_1,len,true);
  
}
