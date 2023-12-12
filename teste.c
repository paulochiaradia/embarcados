//********************************************************************************
//
//                      PROGRAMA EXEMPLO: Display LCD 16x2.
//             OBJETIVO: Aprender a utilizar o LCD com o PIC18F4520.
//
//********************************************************************************

// --- Ligações entre PIC e LCD ---
sbit LCD_RS at RE2_bit;   // PINO 2 DO PORTD LIGADO AO RS DO DISPLAY
sbit LCD_EN at RE1_bit;   // PINO 3 DO PORTD LIGADO AO EN DO DISPLAY
sbit LCD_D7 at RD7_bit;  // PINO 7 DO PORTD LIGADO AO D7 DO DISPLAY
sbit LCD_D6 at RD6_bit;  // PINO 6 DO PORTD LIGADO AO D6 DO DISPLAY
sbit LCD_D5 at RD5_bit;  // PINO 5 DO PORTD LIGADO AO D5 DO DISPLAY
sbit LCD_D4 at RD4_bit;  // PINO 4 DO PORTD LIGADO AO D4 DO DISPLAY

// Selecionando direção de fluxo de dados dos pinos utilizados para a comunicação com display LCD
sbit LCD_RS_Direction at TRISE2_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 2 DO PORTD
sbit LCD_EN_Direction at TRISE1_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 3 DO PORTD
sbit LCD_D7_Direction at TRISD7_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 7 DO PORTD
sbit LCD_D6_Direction at TRISD6_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 6 DO PORTD
sbit LCD_D5_Direction at TRISD5_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 5 DO PORTD
sbit LCD_D4_Direction at TRISD4_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 4 DO PORTD

int numero = 42;
int numero_converter=0;
char str_numero[10];
char ucRead;
char numero_char[]="9";
// --- Função Principal ---



void int_to_str(int num, char *str) {
    int i = 0;
    int j=0;
    int is_negative = 0;

    // Verifica se o número é negativo
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Converte os dígitos individualmente
    do {
        str[i++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);

    // Adiciona o sinal negativo, se necessário
    if (is_negative) {
        str[i++] = '-';
    }

    // Inverte a string
    for (j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }

    // Adiciona o caractere nulo ao final da string
    str[i] = '\0';
}

void main()
{
     ADCON1  = 0x0F;                           //Configura os pinos como digitais
     TRISB=0;
     Lcd_Init();                               //Inicializa módulo LCD
     Lcd_Cmd(_LCD_CURSOR_OFF);                 //Apaga cursor
     Lcd_Cmd(_LCD_CLEAR);                      //Limpa display

    while (1) {
    
          ucRead = numero_char;// Lê o dado recebido do buffer.
    
    
    
    
    
        Lcd_Out(1, 1, "Teste -> ");  // Descomente esta linha se deseja exibir um texto fixo
        int_to_str(numero, str_numero);
        Lcd_Out_CP(ucRead);
        
        numero_converter=atoi(ucRead);

        
        
    }
}


