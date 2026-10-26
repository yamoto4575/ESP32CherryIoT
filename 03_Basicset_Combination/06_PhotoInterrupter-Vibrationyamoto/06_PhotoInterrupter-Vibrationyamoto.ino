const int ruptPin = 3; //3:ConnectorA 4:ConnectorB
const int vibPin = 4;

int Count = 0;       

void setup(){
  pinMode(ruptPin, INPUT);
  pinMode(vibPin, OUTPUT);
  Serial.begin(115200);

digitalWrite(vibPin, LOW); 
}

void loop(){
 if (digitalRead(ruptPin) == LOW) {
    Count++;
    Serial.println("カウント");
    delay(300);
  }

  if (Count >= 5) {
    digitalWrite(vibPin, HIGH);
    delay(1000);
    digitalWrite(vibPin, LOW);
    Count = 0;
    Serial.println("5つ商品が通ります");
  }
  
  delay(100);
}