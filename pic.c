unsigned char luminosidade, gas, solo;

void main() {
  delay_ms(500);      // Delay 0,5 segundo espera o Arduino se estabilizar.

  I2C1_Init(100000);  // Inicializa i2c com o clock de 100KHz

  while(1) {

    //Leitura de dados enviados pelo Arduino
    I2C1_Start();                 // Inicia a comunicação i2c
    I2C1_Wr(0x01);                // Envia o endereço do Arduino
    luminosidade = I2C1_Rd(0);    // Leitura do sensor de luminosidade
    gas = I2C1_Rd(0);             // Leitura do sensor de gás
    solo = I2C1_Rd(1);            // Leitura do sensor de umidade do solo
    I2C1_Stop();                  // Finaliza a comunicação i2c
    

      delay_ms(500);    // Delay 0,5 segundo
  }
}