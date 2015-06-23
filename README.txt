# LuzTeclado V2 (com botao IR)
Acender a luz de iluminacao do teclado apenas quando o usuario estiver sentado a frente do mesmo.

COMPONENTES:
Arduino mini ou nano;
Light Dependent Resistor (LDR);
Sensor de movimento;
Sensor ultrassonico;
Rele 5v 1ch;
Sensor IR de reflexao;

LIGAÇÃO DOS COMPONENTES:

fotosensor: 
  T1 em +5;
  T2 em A3 e em T1 do r12k;
  T2 do r12k em GND.
  
sensorDeMovimento: 
  GND em GND;
  DATA em T1 do r12k e em D6;
  VCC em T2 do r12k e em D5.
  
ultrassom: 
  VCC em +5;
  GND em GND;
  TRIG em D3;
  ECHO em D2.
  
transistor c549c:
  COLETOR ligado no T2 do RELE e em T1 do r12k;
  T2 do r12k ligado em +5;
  BASE ligada em T1 do r12k;
  T2 do r12k ligado em D12;
  EMISSOR ligado em T1 do r150;
  T2 do r150 ligado em gnd.
  
rele: 
  T1 ligado em +5;
  T2 ligado no COLETOR do transistor; 
  T3 ligado em GND.
  
sensorOpticoDeReflexao: 
  catodo do emissor e do receptor ligados em GND;
  anodo do emissor em T1 do r150;
  T2 do r150 +5;
  anodo do receptor em T1 do r12k e em D7;
  T2 do r12k em +5.
