#include <ESP8266WiFi.h>  // Biblioteca Wi-Fi para ESP8266
#include "ThingSpeak.h"  // Biblioteca para comunicar com o ThingSpeak

#define WLAN_SSID   "x"   // nome da sua rede Wi-Fi
#define WLAN_PASS   "x"       // senha do Wi-Fi

WiFiClient client;  // Cria um cliente Wi-Fi

unsigned long myChannelNumber = X;  // Substitua com o número do seu canal ThingSpeak
const char * myWriteAPIKey = "X";  // Substitua com sua API Key de escrita do ThingSpeak

const int sensorPin = A0;  // Pino analógico para ler o MQ-02 no ESP8266 (A0 é o único pino ADC)

void setup() {
  Serial.begin(115200);
  
  // Conectar à rede Wi-Fi
  WiFi.mode(WIFI_STA);
  connectToWiFi();  // Função para conectar ao Wi-Fi

  // Inicializa a comunicação com o ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Garantir que o ESP8266 está conectado ao Wi-Fi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi desconectado. Tentando reconectar...");
    connectToWiFi();  // Tentar reconectar ao Wi-Fi
  }

  // Ler o valor do sensor MQ-02
  int sensorValue = analogRead(sensorPin);
  
  // Verificação de erros no sensor
  if (sensorValue < 0 || sensorValue > 1023) {
    Serial.println("Erro na leitura do sensor MQ-02. Valor fora do esperado.");
    delay(5000);  // Aguardar antes de tentar ler novamente
    return;  // Não prosseguir com o envio se a leitura for inválida
  }

  // Converter o valor lido para voltagem (opcional, para fins de depuração)
  float voltage = (sensorValue / 1023.0) * 3.3;

  Serial.print("Valor do sensor MQ-02: ");
  Serial.println(sensorValue);
  Serial.print("Voltagem correspondente: ");
  Serial.println(voltage);

  // Conectar ao ThingSpeak e enviar o valor do sensor
  if (client.connect("api.thingspeak.com", 80)) {
    Serial.println("Conectado ao ThingSpeak");

    // Enviar o valor do sensor para o campo 1 do ThingSpeak
    ThingSpeak.setField(1, sensorValue);
    int responseCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    // Verificação do código de resposta
    if (responseCode == 200) {
      Serial.println("Atualização bem-sucedida no ThingSpeak");
    } else {
      Serial.print("Falha na atualização. Código de resposta: ");
      Serial.println(responseCode);
    }
  } else {
    Serial.println("Falha na conexão com o ThingSpeak");
  }

  delay(3000);  // Espera 3 segundos antes de enviar novamente
}

// Função para conectar ao Wi-Fi com tentativas e feedback
void connectToWiFi() {
  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  int retryCount = 0;  // Contador para tentativas de reconexão

  // Aguarda a conexão com tentativas limitadas
  while (WiFi.status() != WL_CONNECTED && retryCount < 10) {
    delay(1000);
    Serial.print(".");
    retryCount++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print("Conectado ao Wi-Fi! Endereço IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println();
    Serial.println("Falha na conexão com o Wi-Fi. Verifique as credenciais.");
  }
}
