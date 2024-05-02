#include "DHT.h" // Importa a biblioteca DHT que é usada para comunicar com o sensor DHT de temperatura e umidade
#include <LiquidCrystal.h> // Importa a biblioteca para o display LCD.

#define DHTPIN 2 // Define o pino digital 2 para o DHT
#define DHTTYPE DHT22 // Define o tipo de sensor DHT usado: DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE); // Cria um objeto 'dht' da classe DHT, inicializando-o com o pino e o tipo do sensor, já definidos anteriormente

/*
Descrição Pinos LCD:
  Pino 1 --- Terra
  Pino 2 --- Alimentação VDD para o LCD
  Pino 3 --- Ajuste de contraste
  Pino 4 --- Seleção de registro (RS)
  Pino 5 --- Seleção de leitura/gravação (R/W)
  Pino 6 --- Habilitar (E)
  Pino 7 --- Não utilizado
  Pino 8 --- Não utilizado
  Pino 9 --- Não utilizado
  Pino 10 -– Não utilizado
  Pino 11 -– Linha de dados (D4) 4 bits por vez
  Pino 12 -– Linha de dados (D5) 4 bits por vez
  Pino 13 -– Linha de dados (D6) 4 bits por vez
  Pino 14 -– Linha de dados (D7) 4 bits por vez
  Pino 15 -- Potência de luz de fundo
  Pino 16 -- Terra da luz de fundo (GND)
  */

// Caracteres personalizados criados para exibição no LCD.
const int rs = 7;   // Pino 7  no Arduino para pino 4  (RS) no LCD
const int en = 6;   // Pino 6  no Arduino para pino 6  (E)  no LCD
const int d4 = 12;  // Pino 12 no Arduino para pino 11 (D4) no LCD
const int d5 = 10;  // Pino 10 no Arduino para pino 12 (D5) no LCD
const int d6 = 9;   // Pino 9  no Arduino para pino 13 (D6) no LCD
const int d7 = 8;   // Pino 8  no Arduino para pino 14 (D7) no LCD

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Cria uma instância do LCD

// Cria um caractere personalizado para o símbolo de grau
byte grau[8] = { B01110, B01010, B01110, B00000, B00000, B00000, B00000, B00000 };

// Cria caracteres personalizado para a logo
byte logo1[8] = { B00000, B00000, B00001, B00010, B00100, B00110, B01001, B01000 };
byte logo2[8] = { B01000, B01100, B00111, B00100, B00010, B00001, B00000, B00000 };
byte logo3[8] = { B00000, B01111, B10100, B01000, B01000, B10001, B11110, B10000 };
byte logo4[8] = { B10000, B10000, B10000, B01111, B01000, B10100, B01111, B00000 };
byte logo5[8] = { B00000, B00000, B11000, B00100, B01110, B10010, B00001, B00001 };
byte logo6[8] = { B00011, B00101, B11010, B00010, B00100, B11000, B00000, B00000 };

// Define os pinos para os LEDs
int ledVermelho = 5; 
int ledAmarelo = 4; 
int ledVerde = 3; 
int buzzer = 13; // Pino para o buzzer
int LDR = A0; // Pino analógico para o LDR
int valorLDR = 0; // Variável para armazenar a leitura do LDR
int intensidadeLuz; //Transforma a leitura em uma escala de 0 a 100

int tempo = 150; // Tempo de delay utilizado para efeitos de transição no LCD.

const unsigned long intervaloEvento = 2000;  // Intervalo de tempo para mudar as informações no display.
unsigned long tempoPrevio = 0; // Armazena a última vez que o display foi atualizado.

int estadoDisplay = 0; // Controla o estado da exibição de informações no LCD.

void setup() {
  Serial.begin(115200); // Inicia a comunicação serial a 115200 bits por segundo

  dht.begin(); // Inicializa o sensor DHT.
  lcd.begin(16,2); // Inicializa o LCD com 16 colunas e 2 linhas.
  lcd.clear(); // Limpa o display.

  lcd.createChar(0, grau); // Registra o caractere personalizado de grau no LCD.

  // Registra os caracteres personalizados da logo no LCD.
  lcd.createChar(1, logo1);
  lcd.createChar(2, logo2);
  lcd.createChar(3, logo3);
  lcd.createChar(4, logo4);
  lcd.createChar(5, logo5);
  lcd.createChar(6, logo6);

  // Desenha a primeira parte da logo
  lcd.setCursor(1,0);
  lcd.write(byte(1));
  lcd.setCursor(1,1);
  lcd.write(byte(2));

  delay(tempo); // Espera 150 milissegundos

  // Desenha a segunda parte da logo
  lcd.setCursor(2,0);
  lcd.write(byte(3));
  lcd.setCursor(2,1);
  lcd.write(byte(4));

  delay(tempo); // Espera 150 milissegundos

  // Desenha a terceira parte da logo
  lcd.setCursor(3,0);
  lcd.write(byte(5));
  lcd.setCursor(3,1);
  lcd.write(byte(6));

  // Escreve EMBRACE FIAP no display
  lcd.setCursor(5,0);           
  lcd.print("E");    
  lcd.setCursor(5,1);           
  lcd.print("F");
  
  delay(tempo);
  lcd.setCursor(6,0);           
  lcd.print("M");    
  lcd.setCursor(6,1);           
  lcd.print("I");
  
  delay(tempo);
  lcd.setCursor(7,0);           
  lcd.print("B");    
  lcd.setCursor(7,1);           
  lcd.print("A");
  
  delay(tempo);
  lcd.setCursor(8,0);           
  lcd.print("R");    
  lcd.setCursor(8,1);           
  lcd.print("P");
  
  delay(tempo);
  lcd.setCursor(9,0);           
  lcd.print("A");
  
  delay(tempo);
  lcd.setCursor(10,0);           
  lcd.print("C"); 
  
  delay(tempo);
  lcd.setCursor(11,0);           
  lcd.print("E"); 
  
  delay(1000); // Espera 1 segundo antes de apagar a logo e começar o loop

  // Configura os pinos dos LEDs como saída
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
    
  pinMode(LDR, INPUT); // Configura o pino do LDR como entrada
  
  digitalWrite(LDR, LOW); // Define o estado inicial do sensor como desligado

  pinMode(buzzer, OUTPUT); // Configura o pino do buzzer como saída
}

void loop() {
  unsigned long tempoAtual = millis(); // Armazena o tempo atual em milissegundos desde que o Arduino foi reiniciado

  float temperatura = dht.readTemperature(); // Lê a temperatura do sensor e armazena o valor na variável
  
  float umidade = dht.readHumidity(); // Lê a umidade do sensor e armazena o valor na variável

  // Verifica se a leitura falhou
  if (isnan(temperatura) || isnan(umidade)) { // A função utilizada para isso é a isnan ('is not a number', não é um número). Ela retorna 'true' se o valor da variável não for válido
    Serial.println(F("Houve uma falha ao ler o sensor DHT!")); // Exibe uma mensagem de erro
    
    return; // Sai do loop atual e iniciar o próximo
  }
  
  int numeroLeituras = 10; // Número de leituras do sensor
  int sensorSoma = 0; // Soma das leituras do sensor
  
  for (int i = 0; i < numeroLeituras; i++) {
    valorLDR = analogRead(LDR); // Faz a leitura do valor do LDR
    intensidadeLuz = map(valorLDR, 0, 990, 0, 100); //Converte o valor para uma escala de 0 a 100
    sensorSoma += intensidadeLuz; // Acumula a intensidade de luz mapeada na variável 'sensorSoma'
    delay(1); // Pausa a execução por 1 milissegundo antes da próxima leitura
  }
  
  int sensorMedia = sensorSoma / numeroLeituras; // Média das leituras do sensor

  if (tempoAtual - tempoPrevio >= intervaloEvento) { // Verifica se o intervalo de tempo especificado passou para atualizar o display
    switch (estadoDisplay) { // Estrutura condicional que controla qual informação será exibida no display.
      case 0: // No estado 0:
        mostrarLuz(sensorMedia); // Mostra a média da luminosidade.
        estadoDisplay = 1; // Altera o estado do display para 1.
        break; // Sai da estrutura condicional
      case 1: // No estado 1:
        mostrarUmidade(umidade); // Mostra a umidade atual.
        estadoDisplay = 2; // Altera o estado do display para 2.
        break; // Sai da estrutura condicional
      case 2: // No estado 2:
        mostrarTemperatura(temperatura); // Mostra a temperatura atual.
        estadoDisplay = 0; // Altera o estado do display para 0.
        break; // Sai da estrutura condicional
    }

    // Luminosidade ideal
    if (sensorMedia < 33 && umidade >= 50 && umidade <= 70 && temperatura >= 10 && temperatura <= 15) {
      acendeLedVerde();  // Aciona o LED verde se as condições ideais de luminosidade, umidade e temperatura forem atendidas
    }
      
    // Luminosidade em alerta
    if ((sensorMedia >= 33 && sensorMedia <= 66 || temperatura < 10 || temperatura > 15) && !(sensorMedia > 66) && !(umidade < 50 || umidade > 70)) {
      acendeLedAmarelo(); // Aciona o LED amarelo se as condições de alerta para luminosidade ou temperatura forem atendidas, mas ainda não críticas
    }
      
    // Luminosidade crítica
    if (sensorMedia > 66 || umidade < 50 || umidade > 70) {
      acendeLedVermelho(); // Aciona o LED vermelho se qualquer uma das condições críticas de luminosidade ou umidade for atendida
    }

    // Imprime os valores de temperatura e umidade na saída serial.
    Serial.print(F("Temperatura: "));
    Serial.print(temperatura);
    Serial.print(F("°C Umidade: "));
    Serial.print(umidade);
    Serial.println(F("%"));

    // Imprime os valores de luminosidade de 0 a 1023 e de 0% a 100%
    Serial.print("Intensidade de Luz 0 - 1023 = ");
    Serial.println(valorLDR);
    Serial.print("Intensidade de Luz 0 - 100% = ");
    Serial.println(sensorMedia);

    tempoPrevio = tempoAtual; // Atualiza o tempo anterior com o tempo atual para marcar o momento da última atualização.
  }

}

// Função que acende o led verde
void acendeLedVerde() {
  apagaLeds(); // Ativa a função para apagar os Leds
  digitalWrite(ledVerde, HIGH); // Acende o LED verde
  digitalWrite(buzzer, LOW); // Desativa o buzzer
}

// Função que acende o led amarelo
void acendeLedAmarelo() {
  apagaLeds(); // Ativa a função para apagar os Leds
  digitalWrite(ledAmarelo, HIGH); // Acende o LED amarelo
  digitalWrite(buzzer, HIGH); // Ativa o buzzer
  tone(buzzer, 220, 100); // Define o tom do buzzer
}

// Função que acende o led vermelho
void acendeLedVermelho() {
  apagaLeds(); // Ativa a função para apagar os Leds
  digitalWrite (ledVermelho, HIGH); // Acende o LED vermelho
  digitalWrite(buzzer, HIGH); // Ativa o buzzer
  tone(buzzer, 220, 900); // Define o tom do buzzer
}

// Função para apagar todos os LEDs
void apagaLeds () {
  digitalWrite(ledVerde, LOW); 
  digitalWrite(ledAmarelo, LOW); 
  digitalWrite(ledVermelho, LOW); 
}

// Função que exibe a luminosidade do ambiente no display
void mostrarLuz(int sensorMedia) {
  lcd.clear(); // Limpa o display LCD para a nova mensagem.

  if (sensorMedia >= 33 && sensorMedia <= 66) { // Exibe a mensagem indicando luz média.
    lcd.setCursor(0,0);
    lcd.print("Ambiente a meia");
    lcd.setCursor(0,1);
    lcd.print("luz");
  } else if (sensorMedia < 33) { // Exibe a mensagem indicando luz ideal.
    lcd.setCursor(0,0);
    lcd.print("Ambiente com");
    lcd.setCursor(0,1);
    lcd.print("luz ideal");
  } else { // Exibe a mensagem indicando excesso de luz.
    lcd.setCursor(0,0);
    lcd.print("Ambiente muito");
    lcd.setCursor(0,1);
    lcd.print("claro");
  }
}

// Função que exibe a umidade do ambiente no display
void mostrarUmidade(float umidade) {
  lcd.clear(); // Limpa o display LCD para a nova mensagem.

  if (umidade >= 50 && umidade <= 70) {  // Exibe a mensagem indicando umidade ideal.
    lcd.setCursor(0,0);
    lcd.print("Umidade OK");
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
    lcd.print(umidade);
    lcd.print("%");
  } else if (umidade < 50) { // Exibe a mensagem indicando baixa umidade.
    lcd.setCursor(0,0);
    lcd.print("Umidade BAIXA");
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
    lcd.print(umidade);
    lcd.print("%");
  } else { // Exibe a mensagem indicando alta umidade.
    lcd.setCursor(0,0);
    lcd.print("Umidade ALTA");
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
    lcd.print(umidade);
    lcd.print("%");
  }
}

// Função que exibe a temperatura do ambiente no display
void mostrarTemperatura(float temperatura) {
  lcd.clear(); // Limpa o display LCD para a nova mensagem.

  if (temperatura >= 10 && temperatura <= 15) { // Exibe a mensagem indicando temperatura ideal.
    lcd.setCursor(0,0);
    lcd.print("Temperatura OK");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print("C");
  } else if (temperatura < 10) { // Exibe a mensagem indicando temperatura baixa.
    lcd.setCursor(0,0);
    lcd.print("Temp. BAIXA");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print("C");
  } else {  // Exibe a mensagem indicando temperatura alta.
    lcd.setCursor(0,0);
    lcd.print("Temp. ALTA");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print("C");
  }
}