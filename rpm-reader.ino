/* RPM - tacometro
   Gustavo Murta - 19/out/2017  baseado no exemplo :
   http://www.pjrc.com/teensy/td_libs_FreqMeasure.html
   Instale antes a biblioteca FreqMeasure, atraves da IDE do Arduino
   pino D08 para medição de RPM / frequencia    
*/

/*
 * Este programa serve para ler atraves dos pulsos gerados de uma fonte externa o RPM e a frequencia do pulso.
 * uso em consjunto com o sketch rpm-simulator, que atraves do seu pino D8 gera os pulsos para que esse sketch possa ler tambem conectado ao seu pino D8. basta ligar dois arduinos
 * e conectalos atraves do pino Digital 8.
 * Nesse sketch nao da pra ver a referencia ao pino D8 pois a referencua do pino esta no arquivo importado FreqMeasure.h
 */

#include <FreqMeasure.h>

void setup() {
  Serial.begin(115200);
  FreqMeasure.begin();
}

double sum = 0;
int count = 0;

void loop() {
  if (FreqMeasure.available())
  {
    sum = sum + FreqMeasure.read();     // Calcula a media das medicoes
    count = count + 1;
    if (count > 15)                      // numero de medicoes 
    {
      float frequency = FreqMeasure.countToFrequency(sum / count);
      float freq = round(frequency * 10) / 10.0;       // arredonda a frequencia 
      int RPM = freq * 60;                             // calcula o RPM
      Serial.print(freq);
      Serial.print(" Hz   ");
      Serial.print((RPM/2)-500);
      Serial.println(" rpm ");
      sum = 0;
      count = 0;
      delay(1000);
    }
  }
}
