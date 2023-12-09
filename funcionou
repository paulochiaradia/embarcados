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

unsigned int luminosidade, gas, solo;
int ucRead;
char valor;
void main(){


   UART1_Init(9600);

     delay_ms(500);
     ADCON1  = 0x0E;

     Lcd_Init();                               //Inicializa módulo LCD
     Lcd_Cmd(_LCD_CURSOR_OFF);                 //Apaga cursor
     Lcd_Cmd(_LCD_CLEAR);                      //Limpa display
     
     while(1)
     {
      if(UART1_Data_Ready()){  // Verifica se um dado foi recebido no buffer
         ucRead = UART1_Read();
         IntToStr(ucRead, valor);
         Delay_ms(50);   // Pausa de 50ms.
         {lcd_out(2,1,"Rec.= ");
          lcd_out_cp (valor);
         }
       }
     }
}
