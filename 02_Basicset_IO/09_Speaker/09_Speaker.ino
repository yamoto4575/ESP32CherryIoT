const int spkrPin = 3; //3:ConnectorA 4:ConnectorB

#define DO 261.6
#define _DO 277.18
#define RE 293.665
#define _RE 311.127
#define MI 329.63
#define FA 349.228
#define _FA 369.994
#define SO 391.995
#define _SO 415.305
#define RA 440
#define _RA 466.164
#define TI 493.883
#define octDO 523.251
#define lowDO 130.81
#define _lowDO 138.59
#define lowRE 146.83
#define _lowRE 155.56
#define lowMI 164.81
#define lowFA 174.61
#define _lowFA 185.00
#define lowSO 196.00
#define _lowSO 207.65
#define lowRA 220.00
#define _lowRA 233.08
#define lowTI 246.94
#define _octDO 554.37
#define octRE 587.33
#define _octRE 622.25
#define octMI 659.25
#define octFA 698.46
#define _octFA 739.99
#define octSO 783.99
#define _octSO 830.61
#define octRA 880.00
#define _octRA 932.33
#define octTI 987.77
#define highDO 1046.50

#define DO 261.6
#define RE 293.665
#define MI 329.63
#define FA 349.228
#define SO 391.995
#define RA 440
#define REST 0 // 休符

// 楽譜データ（音符）
const double melody[] = {
  DO, RE, MI, FA, MI, RE, DO, REST,
  MI, FA, SO, RA, SO, FA, MI, REST,
  DO, REST, DO, REST, DO, REST, DO, REST,
  DO, DO, RE, RE, MI, MI, FA, FA, MI, RE, DO
};

// 音の長さ（リズム）
const int noteDurations[] = {
  300, 300, 300, 300, 300, 300, 300, 300,
  300, 300, 300, 300, 300, 300, 300, 300,
  300, 300, 300, 300, 300, 300, 300, 300,
  150, 150, 150, 150, 150, 150, 150, 150, 300, 300, 600
};

void playFrogSong() {
  int totalNotes = sizeof(melody) / sizeof(melody[0]);
  
  for (int i = 0; i < totalNotes; i++) {
    if (melody[i] > 0) {
      ledcWriteTone(spkrPin, melody[i]);
    } else {
      ledcWriteTone(spkrPin, 0);
    }
    delay(noteDurations[i]);
    
    // スタッカート効果（歯切れを良くする）
    ledcWriteTone(spkrPin, 0);
    delay(30);
  }
}

void setup() {
  pinMode(spkrPin, OUTPUT);
  ledcAttach(spkrPin, 12000, 8);
}

void loop() {
  playFrogSong();
  delay(3000);
}