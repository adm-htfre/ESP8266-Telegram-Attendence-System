
//Including the one library
#include <UniversalTelegramBot.h>


#include <SPI.h>
#include <MFRC522.h>


#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//------- WiFi Settings -------
char ssid[] = "/- SSID";       // your network SSID (name)
char password[] = "/- Password";  // your network key

//#define TELEGRAM_BUTTON_PIN D4
#define MISO_PIN D6  
#define RST_PIN D3
#define SS_PIN D4 



// ------- Telegram config --------
#define BOT_TOKEN "Bot token"  // your Bot Token (Get from Botfather)
#define CHAT_ID "Chat-ID" // Chat ID of where you want the message to go (You can use MyIdBot to get the chat ID)

// SSL client needed for both libraries
WiFiClientSecure client;


UniversalTelegramBot bot(BOT_TOKEN, client);

String ipAddress = "";

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;

void setup() {

  Serial.begin(115200);
  SPI.begin();            // Initiate  SPI bus
  mfrc522.PCD_Init();     // Initiate MFRC522


  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid); 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  ipAddress = ip.toString();

}


void sendTelegramMessage() {
  String message = "Thankyou!";
  
  if(bot.sendMessage(CHAT_ID, message, "Markdown")){
    Serial.println();
    Serial.println("TELEGRAM Successfully sent");
  }

}

void loop() { 
  if(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() )
  { 
    Serial.println();
    Serial.println("cardSwiped");
    sendTelegramMessage();
     
    

//---------------Sending the Card data to serial Monitor------------//
Serial.print("UID size : ");
Serial.println(mfrc522.uid.size);

Serial.print("Printing HEX UID : ");
for (byte i = 0; i < mfrc522.uid.size; i++) {
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
}
Serial.println("");

unsigned long UID_unsigned;
UID_unsigned = mfrc522.uid.uidByte[0] << 24;
UID_unsigned += mfrc522.uid.uidByte[1] << 16;
UID_unsigned += mfrc522.uid.uidByte[2] << 8;
UID_unsigned += mfrc522.uid.uidByte[3];

Serial.println();

String UID_string = (String)UID_unsigned;

Serial.println("UID String :");
Serial.println(UID_string);
    
    delay(1000);
    }
  return;
    
  }
 

  

