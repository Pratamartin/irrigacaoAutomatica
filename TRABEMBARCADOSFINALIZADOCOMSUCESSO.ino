#define BLYNK_TEMPLATE_ID "TMPL2N_d-jOqA"
#define BLYNK_TEMPLATE_NAME "Irrigação automática"

#include <Wire.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>


int valor_analogico;
int umidade_percentual;


char auth[] = "sua_chave";
char ssid[] = "Redmi Note 11";
char pass[] = "12345678";

BlynkTimer timer;

void moisture() {
  valor_analogico = analogRead(35); //pino do sensot
  Serial.print(valor_analogico);
  valor_analogico = map(valor_analogico, 4095, 1100, 0, 100);
  Blynk.virtualWrite(V0, valor_analogico);
 
 if(valor_analogico < 30){
    Serial.print("Status: Umidade do solo em ");
    Serial.print(valor_analogico);
    Serial.println("%");
    Serial.println("Solo seco, deve ser regado por 2 segundos!!");
    acionarBomba();
  }else if(valor_analogico > 30 && valor_analogico < 60){
    Serial.print("Status: Umidade do solo em ");
    Serial.print(valor_analogico);
    Serial.println("%");
    Serial.println("Solo úmido");
  }else{
    Serial.print("Status: Umidade do solo em ");
    Serial.print(valor_analogico);
    Serial.println("%");
    Serial.println("Solo molhado, não deve ser regado");
  }
  delay(5000);
}

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);
  pinMode(14, OUTPUT);//Pino do relé
  digitalWrite(14, HIGH);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, moisture);
}

void loop() {
  Blynk.run();
  timer.run();

}
void acionarBomba() {
  digitalWrite(14, HIGH); // Liga o relé para acionar a bomba
  Blynk.virtualWrite(V1, 1);
  Serial.println("Bomba ligada ");
  delay(7000); // Mantém a bomba ligada por 2 segundo (ajuste conforme necessário)
  digitalWrite(14, LOW); // Desliga o relé
  Blynk.virtualWrite(V1, 0);
}
