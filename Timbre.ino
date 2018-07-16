#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>


#define BUTTON_PIN D5
#define LED_BUILTIN D2
volatile bool ButonPresionadoFlag = false;

// Initialize Wifi connection to the router


const char* ssid  = "xxxxx";
const char* password = "yyyy";


// Respuesta
const char respuesta[] = "Timbre";


// Initialize Telegram BOT
const char BotToken[] = "566903986:AAEs-5oiAimxg5HJXgbV_WuJjSoTXmTzLtM";

WiFiClientSecure net_ssl;
TelegramBot bot (BotToken, net_ssl);
int band=0,  milis = 0, milisant = 0;

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
  digitalWrite(LED_BUILTIN, HIGH);
  bot.begin();
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(BUTTON_PIN, ButonPresionado, RISING);

} // FIN SETUP


void ButonPresionado() {    
  
                        int button = digitalRead(BUTTON_PIN);
                        milis = millis();
                                if(milis-milisant < 10 || milis-milisant > 2000){ if(button == HIGH){
                                                                                                       Serial.println("Boton Presionado");
                                                                                                        ButonPresionadoFlag = true;
                                                                                                        milisant=milis; 
                                                                                                      }
                                                                                }
                     return;
                      } // FIN  Boton Presionado
                      
void loop() { if(band==0){
                          Serial.println("Iniciado...");
                          Serial.println(" ");
                          band=1;
                          }

                            if ( ButonPresionadoFlag ) {  Serial.println("Enviando Mensaje.....");  bot.sendMessage("590173240", "Timbre");
                                                          Serial.println("Mensaje Enviado");  Serial.println( milis/1000);  Serial.println(" ");
                                                          ButonPresionadoFlag = false;
                                                          milisant=milis;
                                                        } // FIN ButonPresionadoFlag
                        }// FIN LOOP
