boolean stat = false;
int counter = 0;

void setup() {
  Serial.begin(115200);
  pinMode(7, INPUT);
}

void loop() {
  if(Serial.available()){
    Serial.read();
    Serial.print(counter, DEC);
    counter = 0;
    Serial.println( map( analogRead(0), 0, 332, 0, 200), DEC);
  }
  if(digitalRead(7) != stat){
    stat = !stat;
    counter++;
  }  
}
