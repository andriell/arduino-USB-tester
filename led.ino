void ledSetup() {
  pinMode(LED_BUILTIN, OUTPUT);  // initialize onboard LED as output
  delay(10);
}

void ledBlink(int n, unsigned long d) {
  for (int i = 0; i <= n; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(d);
    digitalWrite(LED_BUILTIN, LOW);
    delay(d);
  }
}

void ledOn() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void ledOff() {
  digitalWrite(LED_BUILTIN, LOW);
}
