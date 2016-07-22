boolean stat = false;
int counter = 0;

void setup() {
  Serial.begin(115200);
  pinMode(7, INPUT);
}

void loop() {
//  Serial.println(analogRead(0));
  if(Serial.available()){
    Serial.read();
    Serial.println(counter);
    counter = 0;
    Serial.println( map( analogRead(0), 270, 820, 0, 200));
  }
  if(digitalRead(7) != stat){
    stat = !stat;
    counter++;
  }  
}
