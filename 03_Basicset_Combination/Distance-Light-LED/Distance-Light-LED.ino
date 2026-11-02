
// 超音波センサーで距離を測って、近いほどLEDがピカッと光るプログラム
// たまにセンサーが値をロストして0になっちゃうので、
// そのときは直前の値をキープして誤魔化す仕様にしてます。

const int trig_Pin = 3;
const int echo_Pin = 1; 
const int led_Pin  = 4;  

// うまく値が取れなかったとき用の退避変数（適当な初期値を入れておく）
float prevDist = 20.0;
int prevBright = 128;

void setup() {
  Serial.begin(115200);
  
  pinMode(trig_Pin, OUTPUT);
  pinMode(echo_Pin, INPUT);
  pinMode(led_Pin,  OUTPUT);
}

void loop() {
  digitalWrite(trig_Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_Pin, LOW);

  long duration = pulseIn(echo_Pin, HIGH, 30000);

  float distCm;
  int bright;

  if (duration > 0) {
    distCm = duration * 0.034 / 2.0;

    bright = map(distCm, 2, 50, 255, 0);
    bright = constrain(bright, 0, 255);

    prevDist = distCm;
    prevBright = bright;
    
  } else {

    distCm = prevDist;
    bright = prevBright;
  }

  analogWrite(led_Pin, bright);

  Serial.print("Dist: ");
  Serial.print(distCm);
  Serial.print(" cm  -> LED: ");
  Serial.print(bright);
  
  if (duration == 0) {
    Serial.println("  (※前回値をキープ中)");
  } else {
    Serial.println("");
  }

  delay(150);
}