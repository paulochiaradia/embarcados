unsigned char ucTexto[10];
unsigned char ucTexto1[10];
unsigned int leituraAD = 0;
unsigned int leituraAD1 = 0;
unsigned int i = 0;
unsigned int tempVent=0;

// Selecionando pinos utilizados para comunicação com display LCD
sbit LCD_RS at RE2_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D7 at RD7_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D4 at RD4_bit;

// Selecionando direção de fluxo de dados dos pinos utilizados para a comunicação com display LCD
sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D7_Direction at TRISD7_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD4_bit;

void clearLine(int line) {
    Lcd_Out(line, 1, "                    "); // 20 espaços em branco para limpar a linha
}

void delay_1s() {
    Delay_ms(1000);
}

void main() {
    TRISB.RB0 = 1;
    TRISC.RC5 = 0;
    TRISC.RC2 = 0;
    TRISC.RC1 = 0;
    TRISE = 0;
    PORTB = 0;

    ADCON0 = 0b00000001;
    ADCON1 = 0b00001100;
    ADCON2 = 0b11111110;

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_out(1, 1, "Projeto Estufa");

    // Contagem regressiva de 20 segundos
    for (i = 1; i <= 2; i++) {
        // Atualiza a segunda linha do LCD com a contagem
        clearLine(2);
        Lcd_out(2, 1, "Iniciando ");
        Lcd_Chr(2, 11, i / 10 + '0');
        Lcd_Chr(2, 12, i % 10 + '0');

        delay_1s();
    }

    clearLine(2); // Limpa a segunda linha do LCD
    Lcd_Cmd(_LCD_CLEAR);
    
    while (1) {

        leituraAD = ADC_Read(2);
        leituraAD1 = ADC_Read(0);
        leituraAD /= 2;

        WordToStr(leituraAD, ucTexto);
        tempVent = leituraAD;

        if(tempVent>=30){
        PORTC.RC2 = 1;
        }else{
        PORTC.RC2 = 0;
        }

        if (PORTB.RB0 == 1) {
            PORTC.RC5 = 0;
        } else {
            PORTC.RC5 = 1;
        }
        WordToStr(leituraAD1, ucTexto1);
        Lcd_Out(1,1, "T:");
        Lcd_Out_cp(ucTexto);
        Lcd_out_cp(" L:")  ;
        Lcd_out_cp("50"); //Deve ser trocado pela variavel luz
        Lcd_out_cp(" G:");
        Lcd_out_cp("90");
    
    
    
    
    }


}
