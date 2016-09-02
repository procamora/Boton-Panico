/*******************************************************************
    this is a basic example how to program a Telegram Bot
    using TelegramBOT library on ESP8266
 *                                                                 *
    Open a conversation with the bot, it will echo your messages
    https://web.telegram.org/#/im?p=@EchoBot_bot
 *                                                                 *
    written by Giacarlo Bacchio
 *******************************************************************/


#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266TelegramBOT.h>


const int LED_OK = D7;
const int BUTTON = D4;

// Initialize Wifi connection to the router
const char* ssid = "WIFI";
const char* password = "pass";



// Initialize Telegram BOT
#define BOTtoken "API"  //token of TestBOT
#define BOTname "Avisos_Yayo"
#define BOTusername "avisos_yayo_bot"
TelegramBOT bot(BOTtoken, BOTname, BOTusername);
const char* user_tg = "USER";
int Bot_mtbs = 100; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done


/********************************************
   EchoMessages - function to Echo messages
 ********************************************/
/*void Bot_EchoMessages() {
  for (int i = 1; i < bot.message[0][0].toInt() + 1; i++)      {
    bot.sendMessage(bot.message[i][4], bot.message[i][5], "");
  }
  bot.message[0][0] = "";   // All messages have been replied - reset new messages
}*/


void setup() {
  pinMode(LED_OK, OUTPUT);
  pinMode(BUTTON, INPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  bot.begin();      // launch Bot functionalities
  bot.sendMessage(user_tg, "Inicio arduino", "");
}



void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    if (digitalRead(BUTTON) == LOW) {
      digitalWrite(LED_OK, LOW);
    }
    else {
      digitalWrite(LED_OK, HIGH);
      bot.sendMessage(user_tg, "Envio desde Arduino", "");
      delay(1500);
      /*
        bot.getUpdates(bot.message[0][1]);   // launch API GetUpdates up to xxx message
        Bot_EchoMessages();   // reply to message with Echo
      */
    }
    Bot_lasttime = millis();
  }
}



