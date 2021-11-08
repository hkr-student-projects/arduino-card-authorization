byte readValue = digitalRead(BUTTON_PIN);
if (readValue != lastButtonState) {
lastButtonDebounceTime = millis();
}
if (millis() - lastButtonDebounceTime > buttonDebounceDelay) {
if (readValue != currentButtonState) {
currentButtonState = readValue;
if (currentButtonState == HIGH) {
Serial.write(18);
}
}
}
lastButtonState = readValue;
