#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>


#define BUTTON_PIN D5
#define LED_BUILTIN D2
volatile bool ButonPresionadoFlag = false;

// Initialize Wifi connection to the router


const char* ssid  = "xxxxx";
const char* password = "xxxxx";






// Initialize Telegram BOT
const char BotToken[] = "xxxxxx:yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy";

WiFiClientSecure net_ssl;
TelegramBot bot (BotToken, net_ssl);
int BanderaInicio=0, BanderaBoton=0;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  while (!Serial); // Wait for the Serial monitor to be opened

  // attempt to connect to Wifi network:
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
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(BUTTON_PIN, ButonPresionado, RISING);

  Serial.println(" ");
 

} // FIN SETUP


void ButonPresionado() {    
                        int button = digitalRead(BUTTON_PIN);
                        if(button == HIGH && BanderaBoton == 0)
                          {
                          ButonPresionadoFlag = true; 
                          Serial.println("Boton Presionado");
                          BanderaBoton = 1;
                          }                                                    
                        return;
                       } // FIN  Boton Presionado
                      
void loop() { if(BanderaInicio == 0){
                          Serial.println("Iniciado...");
                          Serial.println("Enviando Mensaje de Inicio....."); 
                          bot.sendMessage("xxxxxxx", "Iniciado");
                          Serial.println("Mensaje Enviado"); 
                          Serial.println(" "); 
                          BanderaInicio=1;
                          }

              if ( ButonPresionadoFlag ) {  Serial.println("Enviando Mensaje.....");  
                                             ButonPresionadoFlag = false;
                                            bot.sendMessage("xxxxxxxx", "Timbre");
                                            Serial.println("Mensaje Enviado");
                                            Serial.println(" "); 
                                            BanderaBoton = 0;
                                         } // FIN ButonPresionadoFlag


              if (WiFi.status() == WL_CONNECTED) {
                            digitalWrite(LED_BUILTIN, HIGH);
                                        } else {digitalWrite(LED_BUILTIN, LOW);}
              }// FIN LOOP
