void setup() {
  Serial.begin(9600);              //Starting serial communication
  pinMode(13, INPUT_PULLUP);
}
  
void loop() {
  if (digitalRead(13) == LOW)                          
  {
    Serial.println("on");          // send the data
    while(digitalRead(13) != HIGH)
    {
      delay(50);
    }
    Serial.println("off");
  } 
}
