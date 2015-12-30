#include <avr/wdt.h>
int dcsw=12; //dc switch
int acsw=11;//AC SWITCH
int dclwt=0; //time delay till next PIR check
void setup() {
  Serial.begin(9600); 
  wdt_enable (WDTO_2S);  // reset after two second, if no "pat the dog" received
    pinMode(2, INPUT);
    pinMode(13, OUTPUT);
    pinMode(dcsw, OUTPUT);
    pinMode(acsw, OUTPUT);
    digitalWrite(dcsw,LOW);
    digitalWrite(acsw,LOW);
    Serial.println("Setup");
}

void loop() {
   digitalWrite(13,HIGH);
  int lightSence = 0;
  lightSence = analogRead(0);    // read the input pin

//check PIR
if(digitalRead(2)==HIGH){
  if(dclwt < 101){
  dclwt=dclwt+10;
  }
}


//Switch on DC
if(dclwt > 2 ){
  if(lightSence == 0){
    wdt_reset ();
    switch_ondc();
  }
  
}else{
  switch_offdc();
}

  
  if(dclwt > 0){
  dclwt=dclwt-1;
  }
  Serial.print("ls=");
  Serial.print(lightSence);
  Serial.print("--dcswitch w t=");
  Serial.println(dclwt);
  delay(250);
  digitalWrite(13,LOW);
  wdt_reset ();
  delay(250);
}

void switch_ondc(){
 
    digitalWrite(dcsw,HIGH);
 
  
}
void switch_offdc(){
    
    digitalWrite(dcsw,LOW);

  
}

