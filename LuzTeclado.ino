/*Created by RicardoKeso  - V1*/

const int ultrassomEcho = 2;
const int ultrassomPing = 3;
const int movPower = 5;
const int movData = 6;
const int saidaRele = 12;
const int ledPlaca = 13;
const int sensorLuz = 3; //analogico

bool paused = false;
int luzAmb;

void setup(){
  Serial.begin(9600);
  pinMode(ledPlaca, OUTPUT);
  pinMode(movPower, OUTPUT);
  pinMode(ultrassomPing, OUTPUT);
  pinMode(saidaRele, OUTPUT);
  
  pinMode(movData, INPUT);
  pinMode(ultrassomEcho, INPUT);
}

void loop(){  
  digitalWrite(ledPlaca, LOW);  
  Luzteclado();
}

void Luzteclado(){
  luzAmb = analogRead(sensorLuz);
  if(luzAmb < 40){
    if (Movimento(movPower, HIGH, movData) == 1){
      SinalPlaca(ledPlaca, 1, 0);
      Rele(Distancia(ultrassomPing, ultrassomEcho, 90, 249));
    } 
  } else {
    Movimento(movPower, LOW, movData);
    Rele(LOW);
  }
}

int Movimento(int pinoPW, int estado, int pinoDT){
  if(estado == 1){
    digitalWrite(pinoPW, HIGH);
    return digitalRead(pinoDT);
  } else {
    return 0;    
  } 
}

int Distancia(int ping, int echo, int distancia, int atraso){
    digitalWrite(ping, LOW);
    delayMicroseconds(2);
    digitalWrite(ping, HIGH);
    delayMicroseconds(10);
    digitalWrite(ping, LOW);
    long duration = pulseIn(echo, HIGH);
    long _distancia = duration /29 / 2 ;  
    
  if(_distancia < distancia){
    delay(atraso);
    return 1;
  } else{
    delay(atraso);
    return 0;
  }
}

void Rele(int estado){
  digitalWrite(saidaRele, estado);//utiliza um transistor
}

void SinalPlaca(int pino, int atrasoOn, int atrasoOff){
  digitalWrite(pino, HIGH);
  delay(atrasoOn);
  digitalWrite(pino, LOW);
  delay(atrasoOff);
}
