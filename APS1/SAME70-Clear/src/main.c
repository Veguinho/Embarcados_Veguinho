/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"
#include <stdlib.h>
#include <stdio.h>

/************************************************************************/
/* defines                                                              */
/************************************************************************/

#define BUZZ_PIO           PIOC                  // periferico que controla o buzzer
#define BUZZ_PIO_ID        ID_PIOC               // ID do periférico PIOC (controla buzzer)
#define BUZZ_PIO_IDX       17u                   // ID do buzzer no PIO
#define BUZZ_PIO_IDX_MASK  (1u << BUZZ_PIO_IDX)  // Mascara para CONTROLARMOS o buzzer

#define LED_VERMELHO_PIO           PIOB                // periferico que controla o LED
#define LED_VERMELHO_PIO_ID        ID_PIOB               // ID do periférico PIOC (controla LED)
#define LED_VERMELHO_PIO_IDX       1u                   // ID do LED no PIO
#define LED_VERMELHO_PIO_IDX_MASK  (1u << LED_VERMELHO_PIO_IDX)  // Mascara para CONTROLARMOS o LED

#define LED_VERDE_PIO           PIOD               // periferico que controla o LED
#define LED_VERDE_PIO_ID        ID_PIOD               // ID do periférico PIOC (controla LED)
#define LED_VERDE_PIO_IDX       21u                   // ID do LED no PIO
#define LED_VERDE_PIO_IDX_MASK  (1u << LED_VERDE_PIO_IDX)  // Mascara para CONTROLARMOS o LED


// Configuracoes do botao SW300 , id 10, PA11

#define BUT_START_PIO			PIOC
#define BUT_START_PIO_ID		ID_PIOC
#define BUT_START_PIO_IDX		30u
#define BUT_START_PIO_IDX_MASK (1u << BUT_START_PIO_IDX)

#define BUT_SWITCH_PIO			PIOA
#define BUT_SWITCH_PIO_ID		ID_PIOA
#define BUT_SWITCH_PIO_IDX		4u
#define BUT_SWITCH_PIO_IDX_MASK (1u << BUT_SWITCH_PIO_IDX)



/************************************************************************/
/* constants                                                            */
/************************************************************************/



/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

char notesJingle[] = {NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_G4, NOTE_C3, NOTE_D3, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
	 NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D3, NOTE_D3, NOTE_E4, NOTE_D3, NOTE_G4,};
	 
int durationJingle[] = {125, 125, 250, 125, 125, 250, 125, 125, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 250, 250};
	
	
//Musica retirada de: https://github.com/xitangg/-Pirates-of-the-Caribbean-Theme-Song/blob/master/Pirates_of_the_Caribbean_-_Theme_Song.ino
int notesPirates[] = {       //Note of the song, 0 is a rest/pulse
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_A4, NOTE_A4, 
   //Repeat of first part
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,
   //End of Repeat

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};
//*****************************************
int durationPirates[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

  250, 125,
  //Rpeat of First Part
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  //End of Repeat
  
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};
//Musica do mario retirada de: https://www.princetronics.com/supermariothemesong/
//Pequenas modificacoes foram feitas na melodia
int melodyMario[] = {
	NOTE_E7, NOTE_E7, 0, NOTE_E7,
	0, NOTE_C7, NOTE_E7, 0,
	NOTE_G7, 0, 0,  0,
	NOTE_G6, 0, 0, 0,

	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,

	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0,

	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,

	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int durationMario[] = {
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
};

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

// Função de inicialização do uC
void init(void){
	// Initialize the board clock
	sysclk_init();
	
	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(BUZZ_PIO_ID);
	pmc_enable_periph_clk(LED_VERMELHO_PIO_ID);
	pmc_enable_periph_clk(LED_VERDE_PIO_ID);


	
	// Inicializa como saída.
	pio_set_output(BUZZ_PIO, BUZZ_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED_VERMELHO_PIO, LED_VERMELHO_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED_VERDE_PIO, LED_VERDE_PIO_IDX_MASK, 0, 0, 0);


	
	// Inicializa PIO do botao
	pmc_enable_periph_clk(BUT_START_PIO_ID);
	pmc_enable_periph_clk(BUT_SWITCH_PIO_ID);

	// configura pino ligado ao botão como entrada com um pull-up.
	pio_set_input(BUT_START_PIO,BUT_START_PIO_IDX,PIO_DEFAULT);
	pio_set_input(BUT_SWITCH_PIO,BUT_SWITCH_PIO_IDX,PIO_DEFAULT);

	
	pio_pull_up(BUT_START_PIO,BUT_START_PIO_IDX_MASK,1);
	pio_pull_up(BUT_SWITCH_PIO,BUT_SWITCH_PIO_IDX_MASK,1);

	
	

}



/************************************************************************/
/* Main                                                                 */
/************************************************************************/
const int songspeedPirates = 2; //Quanto maior mais rapida a musica
const int songspeedMario = 12; //Quanto maior mais rapida a musica

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
  init();
	int chooseSong = 0;
  // super loop
  // aplicacoes embarcadas não devem sair do while(1).
  while(1)
  {
	if(!pio_get(BUT_SWITCH_PIO, PIO_INPUT, BUT_SWITCH_PIO_IDX_MASK)){
		if (chooseSong==0){
			chooseSong = 1;
			pio_clear(LED_VERDE_PIO, LED_VERDE_PIO_IDX_MASK); // Coloca 0 no pino LED verde
			pio_set(LED_VERMELHO_PIO, LED_VERMELHO_PIO_IDX_MASK); // Coloca 1 no pino LED vermelho
			delay_ms(500);
		}
		else{
			chooseSong = 0;
			pio_set(LED_VERDE_PIO, LED_VERDE_PIO_IDX_MASK); // Coloca 1 no pino LED verde
			pio_clear(LED_VERMELHO_PIO, LED_VERMELHO_PIO_IDX_MASK); // Coloca 0 no pino LED vermelho
			delay_ms(500);
		}
	}
	
	if(pio_get(BUT_START_PIO, PIO_INPUT, BUT_START_PIO_IDX_MASK)){
		pio_clear(PIOC, BUZZ_PIO_IDX_MASK);    // Coloca 0 no pino do BUZZERZ
		if(chooseSong==0){
			pio_set(LED_VERDE_PIO, LED_VERDE_PIO_IDX_MASK); // Coloca 1 no pino LED verde
			pio_clear(LED_VERMELHO_PIO, LED_VERMELHO_PIO_IDX_MASK); // Coloca 0 no pino LED vermelho
		}
		else{
			pio_clear(LED_VERDE_PIO, LED_VERDE_PIO_IDX_MASK); // Coloca 0 no pino LED verde
			pio_set(LED_VERMELHO_PIO, LED_VERMELHO_PIO_IDX_MASK); // Coloca 1 no pino LED vermelho
		}

	}
	else{
		if(chooseSong==0){
		pio_set(LED_VERDE_PIO, LED_VERDE_PIO_IDX_MASK); // Coloca 1 no pino LED verde
		pio_clear(LED_VERMELHO_PIO, LED_VERMELHO_PIO_IDX_MASK); // Coloca 0 no pino LED vermelho
		for (int i=0;i<203;i++){              //203 is the total number of music notes in the song PIRATAS
			int wait = durationPirates[i]/songspeedPirates;
			pio_set(LED_VERDE_PIO, LED_VERDE_PIO_IDX_MASK); // Coloca 1 no pino LED vermelho
			for(double k=0; k < wait; k++){
				pio_set(BUZZ_PIO, BUZZ_PIO_IDX_MASK); // Coloca 1 no pino BUZZER
				delay_us(500000/notesPirates[i]);	//deixa tocando pelo tempo/frequencia que resulta na nota necessaria
				pio_clear(BUZZ_PIO, BUZZ_PIO_IDX_MASK); // Coloca 0 no pino BUZZER
				delay_us(500000/notesPirates[i]);
				if(!pio_get(BUT_SWITCH_PIO, PIO_INPUT, BUT_SWITCH_PIO_IDX_MASK)){
					chooseSong = 1;
					break;
				}
				
				}
			if(!pio_get(BUT_SWITCH_PIO, PIO_INPUT, BUT_SWITCH_PIO_IDX_MASK)){
				chooseSong = 1;
				break;
			}
			pio_clear(LED_VERDE_PIO, LED_VERDE_PIO_IDX_MASK); // Coloca 1 no pino BUZZER
			delay_ms(wait);
			}
		}
		else{
		pio_clear(LED_VERDE_PIO, LED_VERDE_PIO_IDX_MASK); // Coloca 0 no pino LED verde
		pio_set(LED_VERMELHO_PIO, LED_VERMELHO_PIO_IDX_MASK); // Coloca 1 no pino LED vermelho
		for (int i=0;i<78;i++){              //78 is the total number of music notes in the song MARIO
			int wait = durationMario[i]*125/songspeedMario;
			pio_set(LED_VERMELHO_PIO, LED_VERMELHO_PIO_IDX_MASK); // Coloca 1 no pino BUZZER
			for(double k=0; k < wait; k++){
				pio_set(BUZZ_PIO, BUZZ_PIO_IDX_MASK); // Coloca 1 no pino BUZZER
				delay_us(500000/melodyMario[i]);	//deixa tocando pelo tempo/frequencia que resulta na nota necessaria
				
				pio_clear(BUZZ_PIO, BUZZ_PIO_IDX_MASK); // Coloca 0 no pino BUZZER
				delay_us(500000/melodyMario[i]);
				if(!pio_get(BUT_SWITCH_PIO, PIO_INPUT, BUT_SWITCH_PIO_IDX_MASK)){
					chooseSong = 0;
					break;
				}
			}
			if(!pio_get(BUT_SWITCH_PIO, PIO_INPUT, BUT_SWITCH_PIO_IDX_MASK)){
				chooseSong = 0;
				break;
			}
			pio_clear(LED_VERMELHO_PIO, LED_VERMELHO_PIO_IDX_MASK); // Coloca 0 no pino BUZZER
			delay_ms(wait);
		}
		}
	}
	}
  return 0;
}
