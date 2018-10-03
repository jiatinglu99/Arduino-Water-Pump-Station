//Code for Arduino Water Pumping Station 
//Can be activated wirelessly or locally by a button
//June 18th, 2018 by Terry Lu

char commandLine[] = "-0000000000|"; //sample
bool pumpOn = false;

void setup() {
  pinMode(3, INPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);
}

bool isNum(char t){
  if (t - '0' < 10 && t - '0' >= 0) return true;
  return false;
}

void receiveData() {
  //if (Serial.available()){
  //  char c = Serial.read();
  //  Serial.print(c);
  //}
  if (Serial.available()){
    char checkStart = Serial.read();
    if (checkStart == '-'){
      delay(5);
      int count = 0;
      while (Serial.available()){
        char temp = Serial.read();
        if (isNum(temp)) commandLine[++count] = temp;
        else if (temp == "|") break;
        delay(5);//data recognition buffer 
      }
    }
  }
}

void turnOffPump(){
  pumpOn = false;
  //Serial.println("off");
}

void turnOnPump(){
  pumpOn = true;
  //Serial.println("on");
}

void commandAnalyze(){
  int state = digitalRead(3);
  if (commandLine[10] - '0' >= 5 or state == HIGH) turnOnPump();
  else turnOffPump();
  //Serial.println(commandLine[10]-'0');
}

void pumpExecute(){
  if (pumpOn) digitalWrite(2, HIGH);
  else digitalWrite(2, LOW);
}

void loop() {
  receiveData();
  commandAnalyze();
  pumpExecute();
  delay(20);
  //Serial.println(digitalRead(3));
}
