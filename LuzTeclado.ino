/*Created by RicardoKeso - V5 (com botao IR, buzzer, IR remoto, funcoes)*/

#include <NewTone.h>
#include <IRremote.h>

const int ultrassomEcho = 2;
const int ultrassomPing = 3;
const int movPower = 5;
const int movData = 6;
const int sensorReflex = 7;
const int buzzer = 10;
const int sensorIRremoto = 11;
const int saidaRele = 12;
const int ledPlaca = 13;
const int sensorLuz = 3; //analogico

bool paused = false;
int luzAmb;
int tempoAlertaMov = 30;
int funcaoAtiva = 0;
int funcaoAtivaOld = 0;

IRrecv irrecv(sensorIRremoto);  
decode_results results;

void setup(){
  Serial.begin(9600);
  pinMode(ledPlaca, OUTPUT);
  pinMode(movPower, OUTPUT);
  pinMode(ultrassomPing, OUTPUT);
  pinMode(saidaRele, OUTPUT);
  pinMode(buzzer,OUTPUT);
  irrecv.enableIRIn();
  pinMode(movData, INPUT);
  pinMode(ultrassomEcho, INPUT);
  pinMode(sensorReflex, INPUT);
}

void loop(){  
  digitalWrite(ledPlaca, LOW);   
  
  if(digitalRead(sensorReflex) == 0){
    Buzzer(buzzer, 2000, 20, 1);
    paused = !paused;
    if(paused){
      funcaoAtivaOld = funcaoAtiva;
      funcaoAtiva = 1;
    } else {
      funcaoAtiva = funcaoAtivaOld;
    }
    while(digitalRead(sensorReflex) == 0){}    
  } else if(irrecv.decode(&results)){
      float valorIR = (results.value); 
      if(valorIR == 0x40BF609F){  //codigo controle remoto
        Buzzer(buzzer, 2000, 20, 1);
        paused = !paused;
        if(paused){
          funcaoAtivaOld = funcaoAtiva;
          funcaoAtiva = 1;
        } else {
          funcaoAtiva = funcaoAtivaOld;
        }  
      } else if(valorIR == 0xFFFFFFFF){ //codigo controle remoto
        for(int cont = 0; cont < 15; cont++){
          Buzzer(buzzer, 2000, 20, 1); 
          delay(1000); 
        }
        funcaoAtiva = 2;
      } else if(valorIR == 0x00000000){ //codigo controle remoto
        Buzzer(buzzer, 2000, 20, 1);
        funcaoAtiva = 0;
      }
  }
  
  switch (funcaoAtiva) {
    case 1:
      PauseSensor(paused);    
      break;
    case 2:
      AlertaMovimento();
      break;
    default:
      LuzTeclado();
  }
}

void AlertaMovimento(){
  if (Movimento(movPower, HIGH, movData) == 1){
    Buzzer(buzzer, 2000, 250, tempoAlertaMov);
  }
}

void PauseSensor(bool _paused){
  if(_paused){
    SinalPlaca(ledPlaca, 5, 495);
  } else {
    SinalPlaca(ledPlaca, 0, 0);
  }
}

void LuzTeclado(){  
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

void Buzzer(int pino, int tom, int duracao, int repeticao){
  for(int cont = 0; cont < repeticao; cont ++){    
    NewTone(pino, tom, duracao);
    delay(duracao);
  }
}
