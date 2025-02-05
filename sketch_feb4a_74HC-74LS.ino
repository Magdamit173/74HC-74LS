// My 2nd shift register is broken so im forced to do shift register (74hc595) and 74ls47 XD.


const int schp_pin = 8;
const int latch_pin = 9;
const int data_pin = 10;

const int A_pin = 7;
const int B_pin = 6;
const int C_pin = 5;
const int D_pin = 4;

const int BCD_order[4] = { D_pin, C_pin, B_pin, A_pin };

const int beep_pin = 11;

int interval = 99;  // max at 99 please

const int base10[10][8] = {
  { 0, 1, 1, 1, 1, 1, 1, 0 },
  { 0, 0, 0, 0, 1, 1, 0, 0 },
  { 1, 0, 1, 1, 0, 1, 1, 0 },
  { 1, 0, 0, 1, 1, 1, 1, 0 },
  { 1, 1, 0, 0, 1, 1, 0, 0 },
  { 1, 1, 0, 1, 1, 0, 1, 0 },
  { 1, 1, 1, 1, 1, 0, 1, 0 },
  { 0, 0, 0, 0, 1, 1, 1, 0 },
  { 1, 1, 1, 1, 1, 1, 1, 0 },
  { 1, 1, 0, 1, 1, 1, 1, 0 }
};

void setup() {
  Serial.begin(9600);
  pinMode(schp_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);

  pinMode(A_pin, OUTPUT);
  pinMode(B_pin, OUTPUT);
  pinMode(C_pin, OUTPUT);
  pinMode(D_pin, OUTPUT);

  pinMode(beep_pin, OUTPUT);

  int binary[32];
  int size = 0;
}

void loop() {

  if (interval < 0) {
    Serial.println(interval);
    tone(beep_pin, 9000);
    delay(1000);

    return;
  }

  digitalWrite(latch_pin, LOW);

  int secondDigit = (int)floor(interval / 10);

  int bit1 = (secondDigit >> 0) % 2;
  int bit2 = (secondDigit >> 1) % 2;
  int bit3 = (secondDigit >> 2) % 2;
  int bit4 = (secondDigit >> 3) % 2;

  digitalWrite(A_pin, bit1);
  digitalWrite(B_pin, bit2);
  digitalWrite(C_pin, bit3);
  digitalWrite(D_pin, bit4);

  Serial.print(bit4);
  Serial.print(bit3);
  Serial.print(bit2);
  Serial.println(bit1);



  for (int i = 0; i < 8; i++) {
    digitalWrite(schp_pin, LOW);
    digitalWrite(data_pin, base10[interval % 10][i]);
    digitalWrite(schp_pin, HIGH);
    // Serial.println(base10[interval % 10][i]);
  }


  digitalWrite(latch_pin, HIGH);

  int frequency = (int)1000 + floor(400 * 20 / interval);

  if (interval < 40) {

    tone(beep_pin, frequency);
    int beep_speed = int(500 * interval / 40);


    delay(beep_speed);
    noTone(beep_pin);
    delay(beep_speed);
    Serial.println(beep_speed);
  }

  else {
    tone(beep_pin, frequency);
    delay(500);
    noTone(beep_pin);
    delay(500);
  }

  interval -= 1;
}