#define AIN     A0
#define OUT     9
#define FILT    0.45F
#define TRIG    0.02F
#define ONTIME  80
#define DELAY   100

struct var {
  float ain;
  float avg;
  float delt;
  uint16_t tim;
  bool state;
} v;

void setup() {
  pinMode(AIN, INPUT);
  pinMode(OUT, OUTPUT);
  digitalWrite(OUT,HIGH);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  v.state = 1;
  v.ain = analogRead(AIN);
  v.avg = analogRead(AIN);
}

void loop() {
  if (analogRead(AIN) > 200) {
    v.ain = analogRead(AIN);
    v.avg = FILT * v.avg + ((1.0F - FILT) * v.ain);
    
    Serial.print(v.ain);
    Serial.print(" ");
    Serial.println(v.avg);

    v.delt = v.ain - v.avg;
    if ( v.delt > TRIG) {
      delay(DELAY);
      WriteIO(OUT, 0);
      delay(ONTIME);
      WriteIO(OUT, 1);
    }
  } else {
    v.ain = analogRead(AIN);
    v.avg = analogRead(AIN);
  }
//  Serial.println(v.avg);
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
