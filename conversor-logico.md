# Usando um Conversor Lógico com o Sensor MQ-02 e ESP8266

## Introdução

Um conversor lógico é um dispositivo que permite a comunicação entre dois sistemas que operam em diferentes níveis de tensão. Neste guia, vamos usar um conversor lógico para conectar um sensor de gás MQ-02 a um ESP8266, garantindo que o sinal do sensor seja convertido adequadamente para o nível de tensão que o ESP8266 pode entender.

## Componentes Necessários

- **Conversor Lógico**: Um módulo conversor lógico com os seguintes pinos:
  - BVCC → AVCC
  - BSCL → ASCL
  - BSDA → ASDA
  - BGNG → AGND
- **Sensor MQ-02**
- **ESP8266**
- **Fios de Conexão**

## Pinagem do Conversor Lógico

A pinagem do conversor lógico é essencial para garantir que a comunicação entre o MQ-02 e o ESP8266 funcione corretamente. Abaixo estão as conexões necessárias:

- **BVCC**: Conecte ao **AVCC** do sensor MQ-02 (tensão de alimentação do sensor).
- **BSCL**: Conecte ao **ASCL** da porta de comunicação (SCL).
- **BSDA**: Conecte ao **ASDA** da porta de comunicação (SDA).
- **BGNG**: Conecte ao **AGND** (terra) do sensor e do ESP8266.

## Conexões

### 1. Conexões do MQ-02

- **VCC** do MQ-02 → **BVCC** do Conversor Lógico
- **GND** do MQ-02 → **BGNG** do Conversor Lógico
- **AO** do MQ-02 → **BSDA** do Conversor Lógico (para a conversão analógica)

### 2. Conexões do ESP8266

- **5V** do ESP8266 → **AVCC** do Conversor Lógico
- **GND** do ESP8266 → **AGND** do Conversor Lógico
- **D2 (GPIO4)** do ESP8266 → **BSCL** do Conversor Lógico (para SCL)

## Funcionamento

1. **Alimentação**: O conversor lógico deve ser alimentado corretamente, garantindo que a tensão de saída (AVCC) e a entrada (BVCC) estejam em níveis compatíveis.
2. **Sinal de Saída**: O sensor MQ-02 fornece um sinal analógico na porta AO. O conversor lógico converte esse sinal para um nível que o ESP8266 pode processar.
3. **Leitura do Sinal**: Você pode usar a função de leitura analógica do ESP8266 para capturar o sinal convertido e processá-lo conforme necessário em seu código.

## Código de Exemplo

Aqui está um exemplo de código para ler o sinal do sensor MQ-02 no ESP8266:

```cpp
void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(A0); // Leitura do sinal convertido
  Serial.println(sensorValue); // Exibe o valor no Serial Monitor
  delay(1000); // Atraso de 1 segundo
}
```

## Conclusão

Usar um conversor lógico para conectar o sensor MQ-02 ao ESP8266 permite que você opere eficientemente em diferentes níveis de tensão. Siga as instruções de conexão e use o código de exemplo para iniciar sua leitura de gás com o MQ-02.

