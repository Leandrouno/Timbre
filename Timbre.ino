// Incluyo Librerias
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>
// Defino Pines
#define BOTON_PIN D5
#define LED_BUILTIN D2
volatile bool BanderaBotonPresionado = false;

// Inicializa la conexión Wifi al router
const char* ssid  = "XXXXXXXXXXX"; // Nombre de la RED WIFI
const char* password = "XXXXXXXX"; // Contraseña de la Red Wifi
const char  id_chat[]="XXXXX"; // ID del Chat de Telegram
// Inicializa Telegram BOT
const char BotToken[] = "XXXXXXXX:YYYYYYYYYYYYYYYYYY"; // BotToken de Telegram
// Respuesta
const char respuesta[] = "Timbre" , iniciado[]="Sistema Iniciado....";


WiFiClientSecure net_ssl;
TelegramBot bot (BotToken, net_ssl);
int BanderaInicio=0, BanderaBoton=0;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  while (!Serial); // Espera a que el Monitor Serial este abierto

  // Intenta conectarse a la red Wifi
  Serial.print("Connectando Wifi: ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
                                          delay(500);
                                          Serial.print(".");
                                        }
                                        
  Serial.println("");
  Serial.println("WiFi connectado");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  bot.begin();
  pinMode(BOTON_PIN, INPUT);
  attachInterrupt(BOTON_PIN, BotonPresionado, RISING);

  Serial.println(" ");
 

} // FIN SETUP

void BotonPresionado() {    
                        int button = digitalRead(BOTON_PIN);
                        if(button == HIGH && BanderaBoton == 0)
                          {
                          BanderaBotonPresionado = true; 
                          Serial.println("Boton Presionado");
                          BanderaBoton = 1;
                          }                                                    
                        return;
                       } // FIN  Boton Presionado
                      
void loop() { 
			        if(BanderaInicio == 0){ mensaje_inicio ();}
              if ( BanderaBotonPresionado ) {  envio_mensaje ();} 
              if (WiFi.status() == WL_CONNECTED) {
                            digitalWrite(LED_BUILTIN, HIGH);
                                        } else {digitalWrite(LED_BUILTIN, LOW);}
              }// FIN LOOP
			  
			  
void mensaje_inicio (){
	
						  Serial.println("Iniciado...");
                          Serial.println("Enviando Mensaje de Inicio....."); 
                          bot.sendMessage(id_chat, iniciado);
                          Serial.println("Mensaje Enviado"); 
                          Serial.println(" "); 
                          BanderaInicio=1;
                          
	
} // FIN Mensaje de inicio
			  
void envio_mensaje (){
	
						Serial.println("Enviando Mensaje.....");  
                        BanderaBotonPresionado = false;
                        bot.sendMessage(id_chat, respuesta);
                        Serial.println("Mensaje Enviado");
                        Serial.println(" "); 
                        BanderaBoton = 0;
                                         
}	// FIN Envio de Mensaje		 
