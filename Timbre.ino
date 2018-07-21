#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
// Inicializamos la conexion WIFI con el Router
char ssid[] = "xxxxxxx";     // el nombre de tu Red
char password[] = "xxxxxxx"; // la clave de tu Red
const char  id_chat[]="xxxxxx";
const char respuesta[] = "Timbre" , iniciado[]="Sistema Iniciado....";
int BanderaInicio=0, BanderaBoton=0;
volatile bool BanderaBotonPresionado = false;

// Initialize Telegram BOT
#define BOTtoken "xxxxxxx:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  // el token de tu BOT, lo obtenemos de BotFather

#define BOTON_PIN D1
#define LED_BUILTIN D2
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
        Serial.begin(9600);
        // Establecer el modo WiFi y desconectarse de un AP si fue Anteriormente conectada
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        delay(100);
        // Intentar conectarse a la red
        Serial.print("Conectando a la Red Wifi: ");
        Serial.println(ssid);
        WiFi.begin(ssid, password);        
        while (WiFi.status() != WL_CONNECTED) {Serial.print("."); delay(500);}        
        Serial.println("");
        Serial.println("WiFi conectada");   
                Serial.print("IP address: ");
        Serial.println(WiFi.localIP());    
        pinMode(BOTON_PIN, INPUT_PULLUP);
        pinMode(LED_BUILTIN, OUTPUT);
        attachInterrupt(BOTON_PIN, BotonPresionado, FALLING);
      } // Fin Setup


                      
void loop() { 
              if (BanderaInicio == 0){ mensaje_inicio ();}
              if ( BanderaBotonPresionado ) {  envio_mensaje ();} 
              if (WiFi.status() == WL_CONNECTED) {
                            digitalWrite(LED_BUILTIN, HIGH);
                                        } else {digitalWrite(LED_BUILTIN, LOW);}
              }// FIN LOOP

void BotonPresionado() {    
                        int button = digitalRead(BOTON_PIN);
                        if(button == LOW && BanderaBoton == 0)
                          {
                          BanderaBotonPresionado = true; 
                          Serial.println("Boton Presionado");
                          BanderaBoton = 1;
                          }                                                    
                        return;
                       } // FIN  Boton Presionado        
        
void mensaje_inicio (){
  
              Serial.println("Iniciado...");
                          Serial.println("Enviando Mensaje de Inicio ....."); 
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
                                         
} // FIN Envio de Mensaje    		 
