/*  RPM Simulador de pulsos    Gustavo Murta 18/out/2017    Ligacao do Potenciometro 10K ohms - pino central A0 - outras extremidades +5V e GND
    Conecte a entrada do medidor de RPM no pino HallPin do Arduino simulador
    RPM = RPS x 60   RPS (Frequencia)
    exemplos : 600 RPM = 10Hz x 60    6000 RPM = 100Hz x 60
    Periodo = 1 / Frequencia

*/

/* 
 *  Esse Sketch simula pulsos para um conta-giros, os pulsos sao gerados atraves do seu pino D8, usado em conjunto com o sketch rpm-reader, que le os pulsos gerados por esse programa.
 *  Bastando conectar ambos arduino usando o pino Digital 8 de ambos, so ligar um cabo direto do pino D8 de um ao D8 do outro.
 *  precisamos conectar um potenciometro de 10K, o pino 1 do potenciomentro vai no GND do arduino, o pino 2 vai no A0 do arduino e o pno 3 vai no 5V do arduino.
 *  Ao girar o POT teremos um gerador de RPM que vai de 600RPM ate 6000RPM
 */

float RPS = 0;               //  Frequencia
int   RPM = 0;               //  RPM
float Periodo = 0;           //  Periodo 
int   HallPin = 8;          //  Pino de saida do Sensor Hall

void setup()
{
  Serial.begin(115200);       // configure a console para 115200 bps
  pinMode(HallPin, OUTPUT);   // Pino Hall como saida
  digitalWrite(HallPin, LOW);
}

void loop()
{
  int POT = analogRead(0);                          // Potenciometro - pino central no pino A0
  Periodo = (map(POT, 0, 1023, 1000, 100)/10);      // Variando o valor do Periodo 100 a 10 ms
  RPS = 1000 / Periodo ;                            // RPS = frequencia
  RPM = 60 * RPS;                                   // Calculo do RPM 

  digitalWrite(HallPin, HIGH);              // Pulso positivo do sensor Hall = 1 milisegundo
  
  delay(1);
  
  digitalWrite(HallPin, LOW);               // Pulso negativo variavel do sensor Hall 
  
  delay(Periodo-1.4);                       // subtracao dos atrasos

  Serial.print(Periodo,0);
  Serial.print(" ms  ");
  Serial.print(RPS,0);
  Serial.print(" Hz  ");
  Serial.print(RPM);
  Serial.println(" rpm ");
  
}
