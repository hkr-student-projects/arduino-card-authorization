#include <Arduino.h>
#include "app.hh"
#include "keypad.hh"

const String card_password = "8255";
const String card_uid = "DE D3 4D C4";
String last_uuid;
String responseCode;
String input_password;


void setup()
{
  Serial.begin(9600);
  input_password.reserve(32); // maximum input characters is 33, change if needed
  SPI.begin();        // Initiate  SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
  Serial.print("Approximate your card to the reader...");
}

void loop()
{ 
  authorizeAccess();
}

bool checkPassword() {
  Serial.print("Card accepted. Enter password for card followed by '#': ");
  while (true)
  {
    char key = keypad.getKey();
    if (key) {
      Serial.print(key);

      if(key == '*') {
        input_password = ""; // clear input password
      } 
      else if(key == '#') {
        if(card_password == input_password) {
          Serial.println("\npassword is correct");
          input_password = "";
          return true;
        } 
        else {
          Serial.println("\npassword is incorrect, try again");
          input_password = "";
          return false;
        }
      } 
      else {
        input_password += key;
      }
    }
    delay(100);
  }
}

String getPassword() {
  Serial.println("Card accepted. Enter password for card followed by '#': ");
  input_password = "";
  
  while(true) {
      char key = keypad.getKey();
      if (key) {
        if(key == '*') {
          input_password = "";
        } 
        else if(key == '#') {
          return input_password;
        } 
        else {
          input_password += key;
        }
      }
      delay(100);
  }
}

String getUUID() {
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "-0" : "-"));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  return content.substring(1);
}

void authorizeAccess() {
  if(Serial.available() > 0) {
    responseCode = Serial.readStringUntil('\n');
    //Serial.print(String("responseCode: " + responseCode));

    if(responseCode == "406" || responseCode == "401") {// card with such UUID was not found
        //flash RED light
        Serial.print(String("Flashing RED light to indicate error."));
        Serial.print(String("/led red")); 
    }
    else if(responseCode == "202") {
        //flash YELLOW light
        Serial.println(String("Flashing YELLOW light to indicate that password needed.")); 
        Serial.print(String("/led yellow")); 
        String password = getPassword();
        Serial.print(String("/password " + last_uuid + " " + password)); 
    }
    else if(responseCode == "200") {
        //flash GREEN light
        //trigger some engine to open door/gate/smth...
        Serial.print(String("Flashing GREEN light to indicate successful authorization."));  
        Serial.print(String("/led green")); 
    }

    return;
  }
  
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
      return;
  }
  
  String uuid = getUUID();
  if(uuid == last_uuid)
      return;
      
  last_uuid = uuid;    
  Serial.print(String("/uuid " + last_uuid));
  
//  while(Serial.available() == 0) {
//    Serial.println("Waiting");
//  }
//  String responseCode = Serial.readStringUntil('\n');
//  Serial.print(String("[ARDUINO] responseCode: " + responseCode));  
  
//  if (content.substring(1) == card_uid) //change here the UID of the card/cards that you want to give access
//  {
//    if(checkPassword()) {
//      Serial.println("Authorized access. Password accepted.");
//    }
//    else {
//      Serial.println(String("Access denied. Reason: Incorrect password for card: " + card_uid));
//    }
//    delay(3000);
//  }
//  else
//  {
//    Serial.println(String("Access denied. Reason: Unathorized card UID: " + content.substring(1)));
//    delay(3000);
//  }
  delay(3000);
}
