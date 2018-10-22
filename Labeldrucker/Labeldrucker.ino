#define AIN     A0
#define OUT     9
#define FILT    0.99F
#define TRIG    0.25F
#define ONTIME  80

struct var {
  float ain;
  float avg;
  float delt;
  uint16_t tim;
  bool state;
} v;

void setup() {
  pinMode(AIN, INPUT);
  pinMode(OUT, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  //Serial.begin(115200);
  v.state = 1;
  v.ain = analogRead(AIN);
  v.avg = analogRead(AIN);
}

void loop() {
  if (analogRead(AIN) > 400) {
    v.ain = analogRead(AIN);
    v.avg = FILT * v.avg + ((1.0F - FILT) * v.ain);
    v.delt = v.ain - v.avg;
    if ( v.delt > TRIG) {
      digitalWrite(LED_BUILTIN, 0);
      WriteIO(OUT, 0);
      delay(ONTIME);
      digitalWrite(LED_BUILTIN, 1);
      WriteIO(OUT, 1);
    }
  } else {
    v.ain = analogRead(AIN);
    v.avg = analogRead(AIN);
  }
  //Serial.println(v.delt);
}

void WriteIO(int io, bool state) {
  if (state == 1) pinMode(io, INPUT);
  if (state == 0) {
    pinMode(io, OUTPUT);
    digitalWrite(io, LOW);
  }
}
