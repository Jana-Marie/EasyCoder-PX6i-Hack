#define AIN     A0
#define OUT     9
#define FILT    0.45F
#define TRIG    0.01F
#define ONTIME  20
#define DELAY   10
#define STEP    2

struct var {
  float ain;
  float avg;
  float delt;
  volatile uint16_t cnt;
  bool state;
} v;

void cnt_isr() {
  v.cnt++;
}

void setup() {
  pinMode(AIN, INPUT);
  pinMode(OUT, OUTPUT);
  pinMode(STEP, INPUT);
  digitalWrite(OUT, HIGH);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  v.state = 1;
  v.ain = analogRead(AIN);
  v.avg = analogRead(AIN);

  attachInterrupt(digitalPinToInterrupt(STEP), cnt_isr, RISING);
}

void loop() {
  if (analogRead(AIN) > 200) {
    v.ain = analogRead(AIN);
    v.avg = FILT * v.avg + ((1.0F - FILT) * v.ain);

    //Serial.print(v.ain);
    //Serial.print(" ");
    Serial.println(v.cnt);

    v.delt = v.ain - v.avg;
    if ( v.delt > TRIG) {
      v.cnt = 0;
      while (true) {
        if (v.cnt > DELAY) break;
      }
      Serial.println(v.cnt);
      WriteIO(OUT, 0);
      delay(ONTIME);
      WriteIO(OUT, 1);
    }
  } else {
    v.ain = analogRead(AIN);
    v.avg = analogRead(AIN);
  }
  //Serial.println(v.cnt);
}

void WriteIO(int io, bool state) {
  digitalWrite(LED_BUILTIN, state);
  //if (state == 1) pinMode(io, INPUT);
  if (state == 1) digitalWrite(io, HIGH);
  if (state == 0) {
    //pinMode(io, OUTPUT);
    digitalWrite(io, LOW);
  }
}
