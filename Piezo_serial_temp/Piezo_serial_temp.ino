/*
   Analog piezo using serial data from p5 sketch as frequency interval
   11/29
 */

/////////////////////piezo////////////////////

const int pie = 5;
const int pot = A0;

unsigned long last_pulse_time, current_time;
int pulse, frequency;
float delay_min, delay_max;




void setup() {

  Serial.begin(9600);

  last_pulse_time = 0;
  current_time = 0;
  frequency = 0;
  pulse = 1;
  delay_min = 1;
  delay_max = 100;
  
  pinMode(pie, OUTPUT);

}

void loop() {



  current_time = millis();
  makeSound();
  updatePulse();
}

void makeSound(){
  if(current_time-last_pulse_time > frequency){
    frequency = updateFrequency();
    last_pulse_time = current_time;
  }
}

int updateFrequency(){

 //if (Serial.available() > 0) { // if there's serial data available
 int inByte = Serial.read();   // read it
 
  
  //float nf = map(inByte, 0, 100, delay_min, delay_max);
  float nf = map(inByte, 0, 1023, delay_min, delay_max);
  return int(nf);
 //}
//  return int(delay_min + float(analogRead(pot)) / 1023.0 * (delay_max - delay_min));
}

void updatePulse(){
  if (current_time - last_pulse_time < pulse){
    digitalWrite(pie, HIGH);
  }else{
    digitalWrite(pie, LOW);
  }
}
