//Variaveis do Programa
unsigned char tempCharTemp[10];
unsigned char tempCharSolo[10];
unsigned char tempCharGas[10];
unsigned char tempCharLuz[10];
unsigned int leituraAD = 0;
unsigned int i = 0;
unsigned int tempInt = 0;
unsigned int solo = 10;
unsigned int gas = 20;
unsigned int luz = 20;
bit atencaoFlag;

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

//Funcao para limpar a linha do LCD
void clearLine(int line)
{
	Lcd_Out(line, 1, "                    ");	// 20 espaços em branco para limpar a linha
}

//Funcao para delay de 1s
void delay_1s()
{
	Delay_ms(1000);
}

void main()
{
	//COnfiguracoes dos pinos
	TRISB.RB0 = 1;
	TRISC.RC5 = 0;
	TRISC.RC2 = 0;
	TRISC.RC1 = 0;
	TRISC.RC0 = 0;
	PORTC.RC0 = 0;
	TRISE.RE0 = 0;
	PORTE.RE0 = 0;
	TRISD.RD0 = 0;
	TRISD.RD1 = 0;
	TRISD.RD2 = 0;
	TRISD.RD3 = 0;
	PORTB = 0;

	//Configuracoes dos pinos AD
	ADCON0 = 0b00000001;
	ADCON1 = 0b00001100;
	ADCON2 = 0b11111110;

	WordToStr(solo, tempCharSolo);
	Ltrim(tempCharSolo);

	WordToStr(luz, tempCharLuz);
	Ltrim(tempCharLuz);

	WordToStr(gas, tempCharGas);
	Ltrim(tempCharGas);

	//Inicia o Projeto
	Lcd_Init();
	Lcd_Cmd(_LCD_CLEAR);
	Lcd_Cmd(_LCD_CURSOR_OFF);
	Lcd_out(1, 1, "Projeto Estufa");

	// Contagem regressiva de 10 segundos
	for (i = 1; i <= 2; i++)
	{
		// Atualiza a segunda linha do LCD com a contagem
		clearLine(2);
		Lcd_out(2, 1, "Iniciando ");
		Lcd_Chr(2, 11, i / 10 + '0');
		Lcd_Chr(2, 12, i % 10 + '0');

		delay_1s();
	}

	clearLine(1);	// Limpa a primeira linha do LCD
	clearLine(2);	// Limpa a segunda linha do LCD

	while (1)
	{
		//Leitura sensor LM35
		leituraAD = ADC_Read(2);
		leituraAD /= 2;

		//Conversao do valor lido para char e para int
		WordToStr(leituraAD, tempCharTemp);
		Ltrim(tempCharTemp);
		tempInt = leituraAD;

		//Impressao no LCD das variaveis
		//T-> Temperatura; L-> Luminosidade; G-> Gas; S-> Umidade do Solo
		Lcd_Out(1, 1, "T:");
		Lcd_Out_cp(tempCharTemp);
		Lcd_out_cp(" L:");
		Lcd_out_cp(tempCharLuz);
		Lcd_out_cp(" G:");
		Lcd_out_cp(tempCharGas);
		Lcd_out(2, 0, " S:");
		Lcd_out_cp(tempCharSolo);

		//Liga o cooler caso temperatura >= 35
		if ((gas > 50) || (tempInt >= 35))
		{
			PORTC.RC2 = 1;
		}
		else
		{
			PORTC.RC2 = 0;
		}

		if ((gas > 50) || (luz < 50))
		{
			PORTE.RE0 = 1;
		}
		else
		{
			PORTE.RE0 = 0;
		}

		if (PORTB.RB0 == 1)
		{
			PORTC.RC5 = 0;
		}
		else
		{
			PORTC.RC5 = 1;
		}

		//Aciona a valvula solenoide da mangueira de agua caso umidade do solo < 50
		if (solo < 50)
		{
			PORTC.RC0 = 1;
		}
		else
		{
			PORTC.RC0 = 0;
		}

		atencaoFlag = ~atencaoFlag;

		if ((solo < 50) && (gas > 50) && (tempInt >= 20))
		{
			PORTC.RC1 = 0;
			if (atencaoFlag)
			{
				Lcd_out_cp("  ATENCAO!   ");
				delay_ms(30);
			}
			else
			{
				Lcd_out_cp("             ");
			}

			delay_ms(50);
		}

		//Mensagem de Atencao
		// if((solo < 50)&&(gas>50)&&(tempVent>=20)){
		// Lcd_out_cp("  ATENCAO ");
		//}
	}
}