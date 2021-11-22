
int sensorpin=36;   //setting the sensor pin
int outputpin=33;   //setting the output pin
int moisture;  //the variable to control

void setup(){
  Serial.begin(115200);         //must begin to use serial monitor
  pinMode(sensorpin,INPUT);    //setting sensor pin to be input
  pinMode(outputpin,OUTPUT);   //setting output pin to be output
}

void loop(){
  moisture=analogRead(sensorpin);  //read the value from sensor pin
  Serial.println(moisture);  //show the value receive in serial monitor  
  
  if(moisture<=600){                //the criticall value to trigger the solenoid
    digitalWrite(outputpin,LOW);}   //you can alternate it depends on yourself
  
  else{
    digitalWrite(outputpin,HIGH);}
  
}
