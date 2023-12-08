//teste
#include <Wire.h>

// Contantes do programa
const int PinoLumininosidade = A0;       // Pino do sensor de luminosidade
const int PinoGas = A1;         // Pino do sensor de gás
const int PinoSolo = A2;        // Pino do sensor de umidade do solo
const int LedVerdeLuminosidade = 13;    // Pino do LED verde do sensor de luminosidade
const int LedAmareloLuminosidade = 12;  // Pino do LED amarelo do sensor de luminosidade
const int LedVermelhoLuminosidade = 11; // Pino do LED vermelho do sensor de luminosidade
const int LedVerdeGas = 10;      // Pino do LED verde do sensor de gás
const int LedAmareloGas = 9;    // Pino do LED amarelo do sensor de gás
const int LedVermelhoGas = 8;   // Pino do LED vermelho do sensor de gás
const int LedVerdeSolo = 7;     // Pino do LED verde do sensor de umidade do solo
const int LedAmareloSolo = 6;   // Pino do LED amarelo do sensor de umidade do solo
const int LedVermelhoSolo = 5;  // Pino do LED vermelho do sensor de umidade do solo
const int intervaloImpressaoSerial = 1000;  // Intervalo de tempo para impressão na serial
const unsigned long tempoLimiteluminosidadeAlta = 5000;  // 5 segundos
const unsigned long tempoLimiteGasAlto = 10000;  // 10 segundos
const unsigned long tempoLimiteSoloAlto = 10000;  // 10 segundos

// Variaveis do Programa
int gas = 0;  // Variável para armazenar o valor lido do sensor de gás
int solo = 0; // Variável para armazenar o valor lido do sensor de umidade do solo
unsigned long ultimaSerialPrint = 0; // Variável para armazenar o tempo da última impressão na serial
unsigned long tempoInicialLuminosidadeAlta = 0; // Variável para armazenar o tempo inicial da luminosidade alta
unsigned long tempoInicialGasAlto = 0; // Variável para armazenar o tempo inicial do gás alto
unsigned long tempoInicialSoloAlto = 0; // Variável para armazenar o tempo inicial do solo alto

void setup() {
  Serial.begin(9600);  // Inicia a comunicação serial
  pinMode(PinoLumininosidade, INPUT);  // Define o pino do sensor de luminosidade como entrada
  pinMode(PinoGas, INPUT);  // Define o pino do sensor de gás como entrada
  pinMode(PinoSolo, INPUT);  // Define o pino do sensor de umidade do solo como entrada
  pinMode(LedVerdeLuminosidade, OUTPUT); // Define o pino do LED verde do sensor de luminosidade como saída
  pinMode(LedAmareloLuminosidade, OUTPUT); // Define o pino do LED amarelo do sensor de luminosidade como saída
  pinMode(LedVermelhoLuminosidade, OUTPUT); // Define o pino do LED vermelho do sensor de luminosidade como saída
  pinMode(LedVerdeGas, OUTPUT); // Define o pino do LED verde do sensor de gás como saída
  pinMode(LedAmareloGas, OUTPUT); // Define o pino do LED amarelo do sensor de gás como saída
  pinMode(LedVermelhoGas, OUTPUT); // Define o pino do LED vermelho do sensor de gás como saída
  Wire.begin(0x2C); // Inicia a comunicação I2C com o endereço 0x2C
  Wire.setClock(100000); // Define a velocidade da comunicação I2C
}

void loop() {
  int valor = analogRead(PinoLumininosidade); // Lê o valor do sensor de luminosidade
  float luminosidade = map(valor, 0, 1023, 0, 100); // Mapeia o valor lido para o intervalo de 0 a 100
  gas = analogRead(PinoGas); // Lê o valor do sensor de gás
  solo = analogRead(PinoSolo); // Lê o valor do sensor de umidade do solo

  delay(1000); // Aguarda 1 segundo
  
  enviarDadosI2C(luminosidade, gas, solo);  // Envia dados via I2C


    // Imprime os valores na serial
  if (millis() - ultimaSerialPrint > intervaloImpressaoSerial) {
    Serial.print("luminosidade: ");
    Serial.print(luminosidade);
    Serial.print("C - Gas: ");
    Serial.print(gas);
    Serial.print(" - Solo: ");
    Serial.print(solo);
    Serial.println();
    ultimaSerialPrint = millis();
  }

//Logica para acender os leds de acordo com os valores lidos em gas
  if (gas > 750) {
    if (tempoInicialGasAlto == 0) {
      tempoInicialGasAlto = millis();  // Inicia a contagem do tempo
    }

    if (millis() - tempoInicialGasAlto > tempoLimiteGasAlto) {
      // Se gas ficar alta por mais de 5 segundos, faz os LEDs piscarem
      piscarLEDsGas();
    } else {
      digitalWrite(LedVerdeGas, LOW);
      digitalWrite(LedAmareloGas, LOW);
      digitalWrite(LedVermelhoGas,HIGH);
    }
  } else {
    // Reseta a contagem do tempo se gas estiver abaixo de 40
    tempoInicialGasAlto = 0;

    if (gas > 500) {
      digitalWrite(LedVerdeGas, LOW);
      digitalWrite(LedAmareloGas, HIGH);
      digitalWrite(LedVermelhoGas, LOW);
    } else {
      digitalWrite(LedVerdeGas, HIGH);
      digitalWrite(LedAmareloGas, LOW);
      digitalWrite(LedVermelhoGas, LOW);
    }
  }

//Logica para acender os leds de acordo com os valores lidos em solo
    if (solo > 750) {
        if (tempoInicialSoloAlto == 0) {
        tempoInicialSoloAlto = millis();  // Inicia a contagem do tempo
        }
    
        if (millis() - tempoInicialSoloAlto > tempoLimiteSoloAlto) {
        // Se solo ficar alta por mais de 5 segundos, faz os LEDs piscarem
        piscarLEDsSolo();
        } else {
        digitalWrite(LedVerdeSolo, LOW);
        digitalWrite(LedAmareloSolo, LOW);
        digitalWrite(LedVermelhoSolo, HIGH);
        }
    } else {
        // Reseta a contagem do tempo se solo estiver abaixo de 40
        tempoInicialSoloAlto = 0;
    
        if (solo > 500) {
        digitalWrite(LedVerdeSolo, LOW);
        digitalWrite(LedAmareloSolo, HIGH);
        digitalWrite(LedVermelhoSolo, LOW);
        } else {
        digitalWrite(LedVerdeSolo, HIGH);
        digitalWrite(LedAmareloSolo, LOW);
        digitalWrite(LedVermelhoSolo, LOW);
        }
    }
    

//Logica para acender os leds de acordo com os valores lidos em luminosidade
  if (luminosidade > 250) {
    if (tempoInicialLuminosidadeAlta == 0) {
      tempoInicialLuminosidadeAlta = millis();  // Inicia a contagem do tempo
    }

    if (millis() - tempoInicialLuminosidadeAlta > tempoLimiteluminosidadeAlta) {
      // Se a luminosidade ficar alta por mais de 5 segundos, faz os LEDs piscarem
      piscarLEDsTemp();
    } else {
      digitalWrite(LedVerdeLuminosidade, LOW);
      digitalWrite(LedAmareloLuminosidade, LOW);
      digitalWrite(LedVermelhoLuminosidade, HIGH);
    }
  } else {
    // Reseta a contagem do tempo se a luminosidade estiver abaixo de 40
    tempoInicialLuminosidadeAlta = 0;

    if (luminosidade > 100) {
      digitalWrite(LedVerdeLuminosidade, LOW);
      digitalWrite(LedAmareloLuminosidade, HIGH);
      digitalWrite(LedVermelhoLuminosidade, LOW);
    } else {
      digitalWrite(LedVerdeLuminosidade, HIGH);
      digitalWrite(LedAmareloLuminosidade, LOW);
      digitalWrite(LedVermelhoLuminosidade, LOW);
    }
  }
}

// Função para fazer os LEDs luminosidade piscarem
void piscarLEDsTemp() {
    digitalWrite(LedVerdeLuminosidade, LOW);
    digitalWrite(LedAmareloLuminosidade, LOW);
    digitalWrite(LedVermelhoLuminosidade, LOW);
    delay(500);
    digitalWrite(LedVerdeLuminosidade, HIGH);
    digitalWrite(LedAmareloLuminosidade, HIGH);
    digitalWrite(LedVermelhoLuminosidade, HIGH);
    delay(500);
}

// Função para fazer os LEDs gas piscarem
void piscarLEDsGas() {
    digitalWrite(LedVerdeGas, LOW);
    digitalWrite(LedAmareloGas, LOW);
    digitalWrite(LedVermelhoGas, LOW);
    delay(500);
    digitalWrite(LedVerdeGas, HIGH);
    digitalWrite(LedAmareloGas, HIGH);
    digitalWrite(LedVermelhoGas, HIGH);
    delay(500);
}

// Função para fazer os LEDs solo piscarem
void piscarLEDsSolo() {
    digitalWrite(LedVerdeSolo, LOW);
    digitalWrite(LedAmareloSolo, LOW);
    digitalWrite(LedVermelhoSolo, LOW);
    delay(500);
    digitalWrite(LedVerdeSolo, HIGH);
    digitalWrite(LedAmareloSolo, HIGH);
    digitalWrite(LedVermelhoSolo, HIGH);
    delay(500);
}


// Função para enviar os dados via I2C
void enviarDadosI2C(float luminosidade, int gas, int solo) {
  Wire.beginTransmission(0x2C);  // Inicia a transmissão com o endereço 0x2C
  Wire.write("L:");  // Identificador para luminosidade
  Wire.write((byte*)&luminosidade, sizeof(luminosidade));  // Envia dados de luminosidade
  Wire.write(" G:");  // Identificador para gás
  Wire.write((byte*)&gas, sizeof(gas));  // Envia dados de gás
  Wire.write(" S:");  // Identificador para solo
  Wire.write((byte*)&solo, sizeof(solo));  // Envia dados de solo
  Wire.endTransmission();  // Finaliza a transmissão
}

