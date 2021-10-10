#include <Arduino.h>
#include "app.hh"
#include "keypad.hh"

const String card_password = "1234";
const String card_uid = "A4 13 09 55";
String input_password;

void setup()
{
  Serial.begin(9600);
  input_password.reserve(32); // maximum input characters is 33, change if needed
  SPI.begin();        // Initiate  SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
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

void authorizeAccess() {
    // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("\nUID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == card_uid) //change here the UID of the card/cards that you want to give access
  {
    if(checkPassword()) {
      Serial.println("Authorized access. Password accepted.");
    }
    else {
      Serial.println("Access denied. Reason: Incorrect password for card.");
    }
    delay(3000);
  }
  else
  {
    Serial.println(String("Access denied. Reason: Unathorized card UID: " + content.substring(1)));
    delay(3000);
  }
}
