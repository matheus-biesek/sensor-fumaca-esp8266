# Projeto ESP8266 com Sensor MQ-02

Este projeto utiliza um **ESP8266** conectado a um sensor de gás MQ-02 para monitorar a qualidade do ar e enviar dados para a plataforma **ThingSpeak**. O objetivo deste projeto é coletar dados analógicos do sensor e disponibilizá-los para análise e visualização em tempo real.

## Estrutura do Projeto

O código do projeto consiste em um arquivo principal que gerencia a conexão com o Wi-Fi, a leitura do sensor e o envio dos dados para o ThingSpeak. 

### Dependências

- **ESP8266WiFi**: Biblioteca para conectar o ESP8266 a uma rede Wi-Fi.
- **ThingSpeak**: Biblioteca para interagir com a API do ThingSpeak.

## Configuração do Hardware

### Pinos Utilizados

- **A0**: Pino analógico do ESP8266 utilizado para ler o valor do sensor MQ-02. Este é o único pino ADC disponível no ESP8266.

### Conexão do Sensor MQ-02

- **VCC**: Conecte ao pino de 5V do ESP8266.
- **GND**: Conecte ao pino GND do ESP8266.
- **AO**: Conecte ao pino A0 do ESP8266 para leitura analógica. Este pino irá fornecer um valor proporcional à concentração de gás detectado.

## Funcionamento do Código

O código realiza as seguintes funções principais:

1. **Conexão ao Wi-Fi**: O ESP8266 tenta se conectar à rede Wi-Fi especificada.
2. **Leitura do Sensor**: O valor analógico do sensor é lido pelo pino A0.
3. **Envio dos Dados**: O valor lido é enviado ao ThingSpeak, onde pode ser visualizado em gráficos e relatórios.

### Tipo de Dados Enviados

O valor lido do sensor MQ-02 é um número inteiro que representa a concentração do gás detectado, variando de 0 a 1023. Este valor é enviado para um campo específico no ThingSpeak.

### Exemplo de Envio de Dados

O código a seguir ilustra como o valor do sensor é lido e enviado:

```cpp
// Ler o valor do sensor MQ-02
int sensorValue = analogRead(A0); // Leitura do pino A0

// Enviar o valor do sensor para o campo 1 do ThingSpeak
ThingSpeak.setField(1, sensorValue);
int responseCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
```

Exemplos de Resposta do ThingSpeak
Após a execução da função writeFields, o código verifica o código de resposta:

```cpp
if (responseCode == 200) {
  Serial.println("Atualização bem-sucedida no ThingSpeak");
} else {
  Serial.print("Falha na atualização. Código de resposta: ");
  Serial.println(responseCode);
}
```

Os códigos de resposta comuns incluem:

    200: Atualização bem-sucedida.
    400: Requisição inválida (pode indicar que o campo está vazio ou o número do canal está incorreto).
    403: Acesso negado (verifique a chave de API).
    404: Canal não encontrado (o número do canal pode estar incorreto).

### Considerações Finais

Este projeto é uma excelente base para desenvolver aplicações de monitoramento ambiental e pode ser expandido com mais sensores ou diferentes plataformas de visualização. Ao modificar ou expandir este projeto, considere a estrutura do código e a manutenção da clareza nas funções para facilitar a colaboração e a evolução do projeto.
Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests.
Licença

Este projeto está licenciado sob a MIT License.

### Explicações Inclusas:

1. **Estrutura do Projeto**: Uma visão geral do que o projeto faz e quais bibliotecas são necessárias.
2. **Configuração do Hardware**: Instruções sobre como conectar o sensor MQ-02 ao ESP8266.
3. **Funcionamento do Código**: Detalhes sobre como o código opera, incluindo a leitura do sensor e o envio de dados.
4. **Tipo de Dados e Exemplos**: Informações sobre os dados enviados e exemplos práticos.
5. **Considerações Finais**: Sugestões para expandir o projeto e informações sobre contribuições e licenciamento.

Sinta-se à vontade para modificar ou expandir esse `README.md` conforme necessário! Se precisar de mais detalhes ou ajustes, é só avisar.

