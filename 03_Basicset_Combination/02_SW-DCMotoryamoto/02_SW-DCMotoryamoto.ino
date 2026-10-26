const int swPin = 3; //3:ConnectorA 4:ConnectorB
const int motorPin = 4;

void setup() {
  Serial.begin(115200);
  pinMode(swPin, INPUT);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  if (digitalRead(swPin) == HIGH) {
    //Look at the serial monitor
    Serial.println("Pushed"); 
    digitalWrite(motorPin, HIGH);
    delay(1000);
  } else {
    Serial.println("Not Pushed");
    digitalWrite(motorPin, LOW);
    delay(3000);
  }
}
