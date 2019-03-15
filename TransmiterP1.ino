volatile unsigned char currentchar; //0100 0001 
volatile int bitsLeft;
char bit;

ISR(TIMER1_COMPA_vect){  
 //start bit sound
  if (bitsLeft == 10) {
    Serial.print("START bit tone for: ");
    Serial.println(currentchar);
    Serial.println(0);
    zero();
    Serial.println("----------");
    bitsLeft--;
  }
  //tones for char bits
  else if(bitsLeft >= 2 && bitsLeft <= 9) {
    Serial.println(currentchar, BIN);
    bit = currentchar & 1;
    Serial.println(bit, BIN);
    if (bit == 0) {
      zero();
      Serial.println("----------");
    }
    else if (bit == 1){
      one();
      Serial.println("----------");
    }
    currentchar = currentchar >> 1;
    bitsLeft--;
  }
  //stop bit sound 
  else if (bitsLeft == 1) {
    Serial.println("STOP bit tone");
    Serial.println(1);
    one();
    Serial.println("----------");
    bitsLeft--;
  }
  else if (bitsLeft == 0) {
    Serial.println("IDLE tone");
    Serial.println(1);
    one();
    Serial.println("----------");
  }      
}

void setup() {
  Serial.begin(9600);

  cli();//stop interrupts
  
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
 
}

void loop() {
  while (Serial.available() && bitsLeft == 0) {
    bitsLeft=10;
    currentchar = Serial.read();
  }
}

// plays a 330mhz sound to pin 10 for 1000ms
void zero() {
  noTone(10);
  tone(10, 300);

}

// plays a 650mhz sound to pin 10 for 1000ms
void one() {
  noTone(10);
  tone(10, 387);
 
}
