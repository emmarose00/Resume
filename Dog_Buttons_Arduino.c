#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

//graphics headers
#include <lcd.h>
#include <macros.h>
#include <ascii_font.h>
#include <graphics.h>

/////////////////////////////
//*********DEFINES*********
/////////////////////////////

#define BIT_VALUE(reg, pin)       (((reg) >> (pin)) & 1)
#define BIT_IS_SET(reg, pin)         (BIT_VALUE((reg),(pin))==1)
 
//uart
#define BAUD (9600)
#define MYUBRR (F_CPU/16/BAUD-1)
#define F_CPU 16000000UL
 
//LCD
#define LCD_CMD( op_code, args ) lcd_write(0,(op_code)|(args))
#define SET_INPUT(portddr, pin)			(portddr) &= ~(1 << (pin))
#define SET_OUTPUT(portddr, pin)		(portddr) |= (1 << (pin))

//timer clock
#define FREQ (16000000.0)
#define PRESCALE (1024.0)

/////////////////////////////
//*****GLOBAL VARIABLES******
/////////////////////////////

int result = 0;
int s1 = 1;
int s2 = 2;
int s3 = 3;
int block = 0;

char *Walkies = "Walkies";
char *Hug = "Hug";
char *Beach = "Beach";
char *Hungry = "Hungry";
char *Ball = "Ball";
char *v1 = "-";
char *v2 = "-";
char *v3 = "-";
int v = 0;

float end = 0;
float start = 0;
float total = 0;
double time = 0;
volatile double counter_overflow = 0; 
 
/////////////////////////////
//*********FUNCTIONS*********
/////////////////////////////

//Functions declaration
void setup_uart(void);
void process_uart(void);
void uart_init(unsigned int ubrr);
void uart_putchar(unsigned char data);
void uart_putstring(unsigned char* s);

void setup_uart(void) {
    uart_init(MYUBRR);	// initialise uart
}
 
void setup_led(void) {
    DDRB |= (1<<5);	//setting PB5 as output
	DDRB |= (1<<4);	//setting PB4 as output
	DDRB |= (1<<3);	//setting PB3 as output
}

void setup_lcd(void) {
	lcd_init(LCD_LOW_CONTRAST); //initialise screen with low contrast
	clear_screen(); //zero screen buffer (memory)
	show_screen();	//write buffer to LCD
}

void setup_pwm(void){
	OCR1B = 128;     // set PWM for 50% duty cycle
    TCCR1A |= (1 << COM1B1);    // set none-inverting mode
    TCCR1B = (1 << CS11); // set prescaler to 8 and starts PWM
    TCCR1A |= (1 << WGM12) | (1 << WGM11) | (1 << WGM10);    // set fast PWM Mode
}

void timer(void){
	time = ((counter_overflow*256.0+TCNT0)*PRESCALE/FREQ);		//counting in seconds
}

void process_walkies(void) {

	char *walkies = "Walkies!";
	char *w1     = "     (o) ";
	char *w2     = " ^";
	char *w3     = " ^";
	char *w4     = " ^";
	char *w5     = " ^";
	char *w6     = " |";
	
	char *w7     = "^ ^ ";
	char *w8     = "^ ^ ";
	char *w9     = "^ ^ ";
	char *w10    = "^ ^ ";
	char *w11    = "| | ";
	char *ground = ".|..........|.|.";
	char *bird     = "v";	

	//animation of walkies
	clear_screen();
	draw_string(0, 0, walkies, FG_COLOUR);
	draw_string(0, 8, w1, FG_COLOUR);
	draw_string(0, 26, w2, FG_COLOUR);
	draw_string(0, 29, w3, FG_COLOUR);
	draw_string(0, 32, w4, FG_COLOUR);
	draw_string(0, 35, w5, FG_COLOUR);
	draw_string(0, 38, w6, FG_COLOUR);
	
	draw_string(70, 26, w7, FG_COLOUR);
	draw_string(70, 29, w8, FG_COLOUR);
	draw_string(70, 32, w9, FG_COLOUR);
	draw_string(70, 35, w10, FG_COLOUR);
	draw_string(70, 38, w11, FG_COLOUR);
	draw_string(0, 40, ground, FG_COLOUR);
	draw_string(20, 32, bird, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, walkies, FG_COLOUR);
	draw_string(0, 8, w1, FG_COLOUR);
	draw_string(0, 26, w2, FG_COLOUR);
	draw_string(0, 29, w3, FG_COLOUR);
	draw_string(0, 32, w4, FG_COLOUR);
	draw_string(0, 35, w5, FG_COLOUR);
	draw_string(0, 38, w6, FG_COLOUR);
	
	draw_string(70, 26, w7, FG_COLOUR);
	draw_string(70, 29, w8, FG_COLOUR);
	draw_string(70, 32, w9, FG_COLOUR);
	draw_string(70, 35, w10, FG_COLOUR);
	draw_string(70, 38, w11, FG_COLOUR);
	draw_string(0, 40, ground, FG_COLOUR);
	draw_string(30, 30, bird, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, walkies, FG_COLOUR);
	draw_string(0, 8, w1, FG_COLOUR);
	draw_string(0, 26, w2, FG_COLOUR);
	draw_string(0, 29, w3, FG_COLOUR);
	draw_string(0, 32, w4, FG_COLOUR);
	draw_string(0, 35, w5, FG_COLOUR);
	draw_string(0, 38, w6, FG_COLOUR);
	
	draw_string(70, 26, w7, FG_COLOUR);
	draw_string(70, 29, w8, FG_COLOUR);
	draw_string(70, 32, w9, FG_COLOUR);
	draw_string(70, 35, w10, FG_COLOUR);
	draw_string(70, 38, w11, FG_COLOUR);
	draw_string(0, 40, ground, FG_COLOUR);
	draw_string(40, 25, bird, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, walkies, FG_COLOUR);
	draw_string(0, 8, w1, FG_COLOUR);
	draw_string(0, 26, w2, FG_COLOUR);
	draw_string(0, 29, w3, FG_COLOUR);
	draw_string(0, 32, w4, FG_COLOUR);
	draw_string(0, 35, w5, FG_COLOUR);
	draw_string(0, 38, w6, FG_COLOUR);
	
	draw_string(70, 26, w7, FG_COLOUR);
	draw_string(70, 29, w8, FG_COLOUR);
	draw_string(70, 32, w9, FG_COLOUR);
	draw_string(70, 35, w10, FG_COLOUR);
	draw_string(70, 38, w11, FG_COLOUR);
	draw_string(0, 40, ground, FG_COLOUR);
	draw_string(50, 20, bird, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, walkies, FG_COLOUR);
	draw_string(0, 8, w1, FG_COLOUR);
	draw_string(0, 26, w2, FG_COLOUR);
	draw_string(0, 29, w3, FG_COLOUR);
	draw_string(0, 32, w4, FG_COLOUR);
	draw_string(0, 35, w5, FG_COLOUR);
	draw_string(0, 38, w6, FG_COLOUR);
	
	draw_string(70, 26, w7, FG_COLOUR);
	draw_string(70, 29, w8, FG_COLOUR);
	draw_string(70, 32, w9, FG_COLOUR);
	draw_string(70, 35, w10, FG_COLOUR);
	draw_string(70, 38, w11, FG_COLOUR);
	draw_string(0, 40, ground, FG_COLOUR);
	draw_string(60, 15, bird, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, walkies, FG_COLOUR);
	draw_string(0, 8, w1, FG_COLOUR);
	draw_string(0, 26, w2, FG_COLOUR);
	draw_string(0, 29, w3, FG_COLOUR);
	draw_string(0, 32, w4, FG_COLOUR);
	draw_string(0, 35, w5, FG_COLOUR);
	draw_string(0, 38, w6, FG_COLOUR);
	
	draw_string(70, 26, w7, FG_COLOUR);
	draw_string(70, 29, w8, FG_COLOUR);
	draw_string(70, 32, w9, FG_COLOUR);
	draw_string(70, 35, w10, FG_COLOUR);
	draw_string(70, 38, w11, FG_COLOUR);
	draw_string(0, 40, ground, FG_COLOUR);
	draw_string(70, 10, bird, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, walkies, FG_COLOUR);
	draw_string(0, 8, w1, FG_COLOUR);
	draw_string(0, 26, w2, FG_COLOUR);
	draw_string(0, 29, w3, FG_COLOUR);
	draw_string(0, 32, w4, FG_COLOUR);
	draw_string(0, 35, w5, FG_COLOUR);
	draw_string(0, 38, w6, FG_COLOUR);
	
	draw_string(70, 26, w7, FG_COLOUR);
	draw_string(70, 29, w8, FG_COLOUR);
	draw_string(70, 32, w9, FG_COLOUR);
	draw_string(70, 35, w10, FG_COLOUR);
	draw_string(70, 38, w11, FG_COLOUR);
	draw_string(0, 40, ground, FG_COLOUR);
	draw_string(80, 8, bird, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, walkies, FG_COLOUR);
	draw_string(0, 8, w1, FG_COLOUR);
	draw_string(0, 26, w2, FG_COLOUR);
	draw_string(0, 29, w3, FG_COLOUR);
	draw_string(0, 32, w4, FG_COLOUR);
	draw_string(0, 35, w5, FG_COLOUR);
	draw_string(0, 38, w6, FG_COLOUR);
	
	draw_string(70, 26, w7, FG_COLOUR);
	draw_string(70, 29, w8, FG_COLOUR);
	draw_string(70, 32, w9, FG_COLOUR);
	draw_string(70, 35, w10, FG_COLOUR);
	draw_string(70, 38, w11, FG_COLOUR);
	draw_string(0, 40, ground, FG_COLOUR);
	draw_string(90, 7, bird, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, walkies, FG_COLOUR);
	draw_string(0, 8, w1, FG_COLOUR);
	draw_string(0, 26, w2, FG_COLOUR);
	draw_string(0, 29, w3, FG_COLOUR);
	draw_string(0, 32, w4, FG_COLOUR);
	draw_string(0, 35, w5, FG_COLOUR);
	draw_string(0, 38, w6, FG_COLOUR);
	
	draw_string(70, 26, w7, FG_COLOUR);
	draw_string(70, 29, w8, FG_COLOUR);
	draw_string(70, 32, w9, FG_COLOUR);
	draw_string(70, 35, w10, FG_COLOUR);
	draw_string(70, 38, w11, FG_COLOUR);
	draw_string(0, 40, ground, FG_COLOUR);
	draw_string(100, 5, bird, FG_COLOUR);
	show_screen();
	_delay_ms(200);

}

void process_beach(void) {

	char *beach = "Beach!";
	char *wave = "^v-^-v-^-v-^-v-^-v-^";	//waves
	char *fish1 = "><(((*>";
	char *fish2 = "  ><(((*>";
	char *fish3 = "    ><(((*>";
	char *fish4 = "      ><(((*>";		//fish
	char *fish5 = "        ><(((*>";
	char *fish6 = "          ><(((*>";
	char *fish7 = "             ><(((*>";
	char *fish8 = "                 ><(((*>";
	char *sand = "----------------------";	//sand
	
	//animation of beach
	clear_screen();
	draw_string(0, 0, beach, FG_COLOUR);
	draw_string(0, 8, wave, FG_COLOUR);	
	draw_string(0, 32, fish1, FG_COLOUR);
	draw_string(0, 40, sand, BG_COLOUR);	
	show_screen();			
	_delay_ms(200);	
	clear_screen();
	draw_string(0, 0, beach, FG_COLOUR);
	draw_string(0, 8, wave, FG_COLOUR);	
	draw_string(0, 32, fish2, FG_COLOUR);
	draw_string(0, 40, sand, BG_COLOUR);	
	show_screen();			
	_delay_ms(200);	
	clear_screen();
	draw_string(0, 0, beach, FG_COLOUR);
	draw_string(0, 8, wave, FG_COLOUR);	
	draw_string(0, 32, fish3, FG_COLOUR);
	draw_string(0, 40, sand, BG_COLOUR);	
	show_screen();			
	_delay_ms(200);	
	clear_screen();
	draw_string(0, 0, beach, FG_COLOUR);
	draw_string(0, 8, wave, FG_COLOUR);	
	draw_string(0, 24, fish4, FG_COLOUR);
	draw_string(0, 40, sand, BG_COLOUR);	
	show_screen();			
	_delay_ms(200);	
	clear_screen();
	draw_string(0, 0, beach, FG_COLOUR);
	draw_string(0, 8, wave, FG_COLOUR);	
	draw_string(0, 24, fish5, FG_COLOUR);
	draw_string(0, 40, sand, BG_COLOUR);	
	show_screen();			
	_delay_ms(200);	
	clear_screen();
	draw_string(0, 0, beach, FG_COLOUR);
	draw_string(0, 8, wave, FG_COLOUR);	
	draw_string(0, 24, fish6, FG_COLOUR);
	draw_string(0, 40, sand, BG_COLOUR);	
	show_screen();			
	_delay_ms(200);	
	clear_screen();
	draw_string(0, 0, beach, FG_COLOUR);
	draw_string(0, 8, wave, FG_COLOUR);	
	draw_string(0, 16, fish7, FG_COLOUR);
	draw_string(0, 40, sand, BG_COLOUR);	
	show_screen();			
	_delay_ms(200);	
	clear_screen();
	draw_string(0, 0, beach, FG_COLOUR);
	draw_string(0, 8, wave, FG_COLOUR);	
	draw_string(0, 16, fish8, FG_COLOUR);
	draw_string(0, 40, sand, BG_COLOUR);	
	show_screen();			
	_delay_ms(200);	

}

void process_hug(void) {

	char *hug = "Hug!";
	char *h1 = "**";
	char *h11 = "**";
	char *h2 = "************";
	char *h3 = "************";	//heart
	char *h4 = "********";
	char *h5 = "****";
	
	//animation of hug
	clear_screen();
	draw_string(0, 0, hug, FG_COLOUR);
	draw_string(20, 8, h1, FG_COLOUR);
	draw_string(50, 8, h11, FG_COLOUR);
	draw_string(10, 16, h2, FG_COLOUR);
	draw_string(10, 24, h3, FG_COLOUR);
	draw_string(20, 32, h4, FG_COLOUR);
	draw_string(30, 40, h5, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, hug, FG_COLOUR);
	draw_string(20, 8, h1, BG_COLOUR);
	draw_string(50, 8, h11, BG_COLOUR);
	draw_string(10, 16, h2, BG_COLOUR);
	draw_string(10, 24, h3, BG_COLOUR);
	draw_string(20, 32, h4, BG_COLOUR);
	draw_string(30, 40, h5, BG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, hug, FG_COLOUR);
	draw_string(20, 8, h1, FG_COLOUR);
	draw_string(50, 8, h11, FG_COLOUR);
	draw_string(10, 16, h2, FG_COLOUR);
	draw_string(10, 24, h3, FG_COLOUR);
	draw_string(20, 32, h4, FG_COLOUR);
	draw_string(30, 40, h5, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, hug, FG_COLOUR);
	draw_string(20, 8, h1, BG_COLOUR);
	draw_string(50, 8, h11, BG_COLOUR);
	draw_string(10, 16, h2, BG_COLOUR);
	draw_string(10, 24, h3, BG_COLOUR);
	draw_string(20, 32, h4, BG_COLOUR);
	draw_string(30, 40, h5, BG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, hug, FG_COLOUR);
	draw_string(20, 8, h1, FG_COLOUR);
	draw_string(50, 8, h11, FG_COLOUR);
	draw_string(10, 16, h2, FG_COLOUR);
	draw_string(10, 24, h3, FG_COLOUR);
	draw_string(20, 32, h4, FG_COLOUR);
	draw_string(30, 40, h5, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, hug, FG_COLOUR);
	draw_string(20, 8, h1, BG_COLOUR);
	draw_string(50, 8, h11, BG_COLOUR);
	draw_string(10, 16, h2, BG_COLOUR);
	draw_string(10, 24, h3, BG_COLOUR);
	draw_string(20, 32, h4, BG_COLOUR);
	draw_string(30, 40, h5, BG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, hug, FG_COLOUR);
	draw_string(20, 8, h1, FG_COLOUR);
	draw_string(50, 8, h11, FG_COLOUR);
	draw_string(10, 16, h2, FG_COLOUR);
	draw_string(10, 24, h3, FG_COLOUR);
	draw_string(20, 32, h4, FG_COLOUR);
	draw_string(30, 40, h5, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, hug, FG_COLOUR);
	draw_string(20, 8, h1, BG_COLOUR);
	draw_string(50, 8, h11, BG_COLOUR);
	draw_string(10, 16, h2, BG_COLOUR);
	draw_string(10, 24, h3, BG_COLOUR);
	draw_string(20, 32, h4, BG_COLOUR);
	draw_string(30, 40, h5, BG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, hug, FG_COLOUR);
	draw_string(20, 8, h1, FG_COLOUR);
	draw_string(50, 8, h11, FG_COLOUR);
	draw_string(10, 16, h2, FG_COLOUR);
	draw_string(10, 24, h3, FG_COLOUR);
	draw_string(20, 32, h4, FG_COLOUR);
	draw_string(30, 40, h5, FG_COLOUR);
	show_screen();
	_delay_ms(200);

}

void process_hungry(void) {

	char *hungry = "Hungry!";
	char *food1 = "  o   o  o  o";
	char *food2 = "   o o o  o ";	//food
	char *food3 = "!..oooooooo..!";
	char *food4 = "    oooooo    ";	
	char *food5 = "     ooo      ";	
	char *bowl  = "!............!";	//bowl

	//animation of hungry
	clear_screen();
	draw_string(0, 0, hungry, FG_COLOUR);
	draw_string(0, 32, bowl, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, hungry, FG_COLOUR);
	draw_string(0, 8, food1, FG_COLOUR);
	draw_string(0, 16, food2, FG_COLOUR);
	draw_string(0, 40, bowl, FG_COLOUR);			
	show_screen();	
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, hungry, FG_COLOUR);
	draw_string(0, 24, food2, FG_COLOUR);
	draw_string(0, 32, food1, FG_COLOUR);
	draw_string(0, 40, food3, FG_COLOUR);	
	show_screen();	
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, hungry, FG_COLOUR);
	draw_string(0, 8, food1, FG_COLOUR);
	draw_string(0, 16, food2, FG_COLOUR);
	draw_string(0, 33, food4, FG_COLOUR);			
	draw_string(0, 40, food3, FG_COLOUR);	
	show_screen();	
	_delay_ms(200);		
	clear_screen();
	draw_string(0, 0, hungry, FG_COLOUR);
	draw_string(0, 8, food2, FG_COLOUR);
	draw_string(0, 28, food5, FG_COLOUR);
	draw_string(0, 33, food4, FG_COLOUR);
	draw_string(0, 40, food3, FG_COLOUR);	
	show_screen();	
	_delay_ms(200);				
	clear_screen();
	draw_string(0, 0, hungry, FG_COLOUR);
	draw_string(0, 28, food5, FG_COLOUR);
	draw_string(0, 33, food4, FG_COLOUR);
	draw_string(0, 40, food3, FG_COLOUR);	
	show_screen();	
	_delay_ms(200);

}

void process_ball(void) {

	char *ball = "Ball!";
	char *b = "o";
	char *bb = "  o";
	char *bbb = "    o";
	char *bbbb = "       o";
	char *buuuu = "           o";	//ball
	char *buuu = "               o";
	char *buu = "           o";
	char *bu = "       o";	


	clear_screen();
	draw_string(0, 0, ball, FG_COLOUR);
	draw_string(0, 8, b, FG_COLOUR);	
	show_screen();			
	_delay_ms(200);			
	clear_screen();
	draw_string(0, 0, ball, FG_COLOUR);
	draw_string(0, 16, bb, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, ball, FG_COLOUR);
	draw_string(0, 24, bbb, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, ball, FG_COLOUR);
	draw_string(0, 32, bbbb, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	
	clear_screen();
	draw_string(0, 0, ball, FG_COLOUR);
	draw_string(0, 32, buuuu, FG_COLOUR);	
	show_screen();			
	_delay_ms(200);			
	clear_screen();
	draw_string(0, 0, ball, FG_COLOUR);
	draw_string(0, 24, buuu, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, ball, FG_COLOUR);
	draw_string(0, 18, buu, FG_COLOUR);
	show_screen();
	_delay_ms(200);
	clear_screen();
	draw_string(0, 0, ball, FG_COLOUR);
	draw_string(0, 8, bu, FG_COLOUR);
	show_screen();
	_delay_ms(200);

}

void process_adc(void) {
 
	char temp_buf[64];
    ADCSRA |= (1 << ADSC); // Start single conversion by setting ADSC bit in ADCSRA
    while ( ADCSRA & (1 << ADSC) ) {}	// Wait for ADSC bit to clear, signalling conversion complete.
    uint16_t pot = ADC;	// Result now available in ADC
    itoa(pot, (char *)temp_buf,10);	// convert uint16_t to string
 
  	
	char *hungry  = "Hungry";
	char *walkies  = "Walkies";
	char *ball  = "Ball";
	char *beach  = "Beach";
	char *hug  = "Hug";
 
     //list of options
     if(pot > 700){
       	clear_screen();
		draw_string(0, 0, hungry, BG_COLOUR);	//highlighted option
		draw_string(0, 8, walkies, FG_COLOUR);
		draw_string(0, 16, ball, FG_COLOUR);
		draw_string(0, 24, beach, FG_COLOUR);
		draw_string(0, 32, hug, FG_COLOUR);
		show_screen();
		_delay_ms(100); 	
		result = 1;
	 }else if (pot > 600){
       	clear_screen();
		draw_string(0, 0, hungry, FG_COLOUR);
		draw_string(0, 8, walkies, BG_COLOUR);	//highlighted option
		draw_string(0, 16, ball, FG_COLOUR);
		draw_string(0, 24, beach, FG_COLOUR);
		draw_string(0, 32, hug, FG_COLOUR);
		show_screen();
		_delay_ms(100);  
		result = 2;
     }else if (pot > 400){
       	clear_screen();
		draw_string(0, 0, hungry, FG_COLOUR);
		draw_string(0, 8, walkies, FG_COLOUR);
		draw_string(0, 16, ball, BG_COLOUR);	//highlighted option
		draw_string(0, 24, beach, FG_COLOUR);
		draw_string(0, 32, hug, FG_COLOUR);
		show_screen();
		_delay_ms(100);
		result = 3;		
     }else if (pot > 205){
        clear_screen();
		draw_string(0, 0, hungry, FG_COLOUR);
		draw_string(0, 8, walkies, FG_COLOUR);
		draw_string(0, 16, ball, FG_COLOUR);
		draw_string(0, 24, beach, BG_COLOUR);	//highlighted option
		draw_string(0, 32, hug, FG_COLOUR);
		show_screen();
		_delay_ms(100);
		result = 4;		
	 }else{
       	clear_screen();
		draw_string(0, 0, hungry, FG_COLOUR);
		draw_string(0, 8, walkies, FG_COLOUR);
		draw_string(0, 16, ball, FG_COLOUR);
		draw_string(0, 24, beach, FG_COLOUR);
		draw_string(0, 32, hug, BG_COLOUR);	//highlighted option
		show_screen();
		_delay_ms(100);
		result = 5;		
	 }
 
}

void setup_adc(void) {
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    ADMUX = (1 << REFS0);
}

/////////////////////////////
//*********MAIN*********
/////////////////////////////

int main(void) {
    //setting up
	setup_led();
	setup_lcd();
	setup_adc();
	setup_pwm();
	setup_uart();
	
	//start timer
	TCCR0A = 0;
    TCCR0B = 5;		//set prescaler
    TIMSK0 = 1;
	
	sei();	//allow interrupts
	
    while(1) {
		
		//s1(swicth 1) = B1
		//s2(swicth 2) = B0
		//s3(swicth 3) = C2
		//s4(swicth 4) = C1
		
		if ((PINB &(1<<PB1))&&block==0){		//S1 is pressed		(if block = 1 then it is in swicth 4 if statements)
			while ( BIT_IS_SET(PINB,1)) {}				// Block until switch released.
			
			 
			
			timer();	//call timer for time
			start = time;	//assign time to start
			
		    PORTB ^= (1<<5);	//turn on PB5 (LED)
			DDRB |= (1 << PB2);     // PD6 is now an output (buzzer on)
			
			if (s1==1){process_hungry(); 
			v=1; v3=v2; v2=v1; v1=Hungry;
			uart_putstring((unsigned char *)"Hungry");    //send serial data
			}		//if switch 1 is set to 1 then play hungry animation
			else if (s1==2) {process_walkies(); v=1; v3=v2; v2=v1; v1=Walkies;}
			else if (s1==3) {process_ball(); v=1; v3=v2; v2=v1; v1=Ball;}
			else if (s1==4) {process_beach(); v=1; v3=v2; v2=v1; v1=Beach;}
			else if (s1==5) {process_hug(); v=1; v3=v2; v2=v1; v1=Hug;}
						
			
			DDRB &= ~(1 << PB2);      // PD6 is now not an output (buzzer off)				
			PORTB ^= (1<<5);	//turn off PB5 (LED)
			clear_screen();		//clear buffer (LCD)
			show_screen();		//send clear buffer to LCD
			counter_overflow = 0;
			
		}else if ((PINB &(1<<PB0))&&block==0){	//S2 is pressed		(if block = 1 then it is in swicth 4 if statements)
			while ( BIT_IS_SET(PINB,0) ) {}	 //Block until switch released.
	
			static char sent_char = 'B';   //define a character to sent
			uart_putchar(sent_char);    //send serial data 
	
			timer();		//call timer for time
			start = time;	//assign time to start
			
		    PORTB ^= (1<<4);	//turn on PB4 (LED)
			DDRB |= (1 << PB2);     // PD6 is now an output (buzzer on)
			
			if (s2==1){process_hungry(); v=1; v3=v2; v2=v1; v1=Hungry;}		//if switch 2 is set to 1 then play hungry animation
			else if (s2==2) {process_walkies(); v=1; v3=v2; v2=v1; v1=Walkies;}
			else if (s2==3) {process_ball();v=1; v3=v2; v2=v1; v1=Ball;}
			else if (s2==4) {process_beach(); v=1; v3=v2; v2=v1; v1=Beach;}
			else if (s2==5) {process_hug(); v=1; v3=v2; v2=v1; v1=Hug;}
			
			DDRB &= ~(1 << PB2);      // PD6 is now not an output (buzzer off)
			PORTB ^= (1<<4);	//turn off PB5 (LED)
			clear_screen();		//clear LCD
			show_screen();
			counter_overflow = 0;

		}else if ((PINC &(1<<PC2))&&block==0){	//S3 is pressed		(if block = 1 then it is in swicth 4 if statements)
			while ( BIT_IS_SET(PINC,2) ) {}	 //Block until switch released.

			static char sent_char = 'C';   //define a character to sent
			uart_putchar(sent_char);    //send serial data 

			timer();		//call timer for time
			start = time;	//assign time to start
			
		    PORTB ^= (1<<3);	//turn on PB3 (LED)
			DDRB |= (1 << PB2);     // PD6 is now an output (buzzer on)

			if (s3==1){process_hungry(); v=1; v3=v2; v2=v1; v1=Hungry;}	//if switch 3 is set to 1 then play hungry animation
			else if (s3==2) {process_walkies(); v=1; v3=v2; v2=v1; v1=Walkies;}
			else if (s3==3) {process_ball(); v=1; v3=v2; v2=v1; v1=Ball;}
			else if (s3==4) {process_beach(); v=1; v3=v2; v2=v1; v1=Beach;}
			else if (s3==5) {process_hug(); v=1; v3=v2; v2=v1; v1=Hug;}
			
			
			DDRB &= ~(1 << PB2);      // PD6 is now not an output (buzzer off)
			PORTB ^= (1<<3);	//turn off PB3 (LED)
			clear_screen();		//clear LCD
			show_screen();
			counter_overflow = 0;

		}else if ((PINC &(1<<PC1))){		//S4 is pressed	
			while ( BIT_IS_SET(PINC,1)) {}	 //Block until switch released.
												
			uint8_t answer = 0;
			while(answer == 0){		//waiting for s4 to be pressed to choose highlighted option on LCD
				process_adc();		//displaying list on LCD
				_delay_ms(50);
				
				if ((PINC &(1<<PC1))){ 	//S4 is pressed
					while ( BIT_IS_SET(PINC,1) ) {}	//waiting for swicth 4 to be released
					
					answer = 1;		//answer has been selected
					clear_screen();
					show_screen();
					
					char *button = "Choose a Button";
					clear_screen();			//writing on LCD screen
					draw_string(0, 16, button, FG_COLOUR);
					show_screen();
					_delay_ms(500);
					
					block =1;			//blocking from other buttons overriding
										
					while (block==1){
							
						if ((PINB &(1<<PB1))){	//switch 1 chosen
							while ( BIT_IS_SET(PINB,1)) {}	 //Block until switch released.
							s1 = result;	// set button to a new word
							block =0;		//unblock other buttons
							
							char *sw = "Switch 1 Set";
							clear_screen();			//writing on LCD screen
							draw_string(0, 16, sw, FG_COLOUR);
							show_screen();
							_delay_ms(800);
							clear_screen();
							show_screen();
						}else if ((PINB &(1<<PB0))){	//switch 2 chosen
							while ( BIT_IS_SET(PINB,0)) {}	 //Block until switch released.
							s2 = result;
							block =0;
							
							char *sw = "Switch 2 Set";
							clear_screen();			//writing on LCD screen
							draw_string(0, 16, sw, FG_COLOUR);
							show_screen();
							_delay_ms(800);							
							clear_screen();
							show_screen();
						}else if ((PINC &(1<<PC2))){	//switch 3 chosen
							while ( BIT_IS_SET(PINC,2)) {}	 //Block until switch released.
							s3 = result;
							block =0;
							
							char *sw = "Switch 3 Set";
							clear_screen();			//writing on LCD screen
							draw_string(0, 16, sw, FG_COLOUR);
							show_screen();
							_delay_ms(800);							
							clear_screen();
							show_screen();
						}else if ((PINC &(1<<PC1))){
							while ( BIT_IS_SET(PINC,1)) {}	 //Block until switch released.
							block = 0;
							
							char *back = "Exiting";
							clear_screen();			//writing on LCD screen
							draw_string(0, 16, back, FG_COLOUR);
							show_screen();
							_delay_ms(800);							
							clear_screen();
							show_screen();
						}
					}
				}
			}
		}else if ((PINC &(1<<PC3))){					//*******S5**************
			
			clear_screen();			//writing on LCD screen
			draw_string(0, 8, v1, FG_COLOUR);	//last button pressed
			draw_string(0, 16, v2, FG_COLOUR);	//2nd last button pressed
			draw_string(0, 24, v3, FG_COLOUR);	//3rd last button pressed
			
			if (v != 0){	//only show a timer if a button has been pressed
				timer();
				end = time;
				total = (end-start)/60;	//time from button press till now in minutes
				if (total<1.0){										//if less then 1 minute
					draw_string( 50, 8, "Now", FG_COLOUR );
				}else if(total<2.0){								//if less then 2 minutes
					draw_string( 40, 8, "1min ago", FG_COLOUR );
				}else if(total<3.0){								//if less then 3 minutes
					draw_string( 40, 8, "2min ago", FG_COLOUR );
				}else if(total<4.0){								//if less then 4 minutes
					draw_string( 40, 8, "3min ago", FG_COLOUR );
				}else if(total>4.0){								//if less then 5 minutes
					draw_string( 40, 8, "4min ago", FG_COLOUR );
				}else if(total>4.5){								//if greater then 5 minutes
					draw_string( 40, 8, "+5min ago", FG_COLOUR );
				}
			}
			
			show_screen();
			_delay_ms(1000);
			clear_screen();
			show_screen();
			
		}
    } 
}

void uart_init(unsigned int ubrr){
 
	//setting up uart
    UBRR0H = (unsigned char)(ubrr >>8);
    UBRR0L = (unsigned char)(ubrr);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C =(3 << UCSZ00);
 
    }
 
void uart_putchar(unsigned char data){    //transmit data
 
   while (!( UCSR0A & (1 << UDRE0))); /* Wait for empty transmit buffer*/
     UDR0 = data;            /* Put data into buffer, sends the data */
                                         
}

void uart_putstring(unsigned char* s){
	while(*s>0) uart_putchar(*s++);
}
 
 volatile uint8_t pressed = 0;
 volatile unsigned int state1 = 0;
 volatile unsigned int state2 = 0;
 volatile unsigned int state3 = 0;
 volatile unsigned int state4 = 0;
 volatile unsigned int state5 = 0;
 volatile uint8_t mask = 0b00000111;
//interupt debouncing
ISR (TIMER0_OVF_vect){
		
		counter_overflow++;
		
		state1=((state1<<1)&mask)| BIT_IS_SET(PINB,1);
		if (state1 ==0){
			pressed = 0;
		}else if(state1==mask){
			pressed = 1;
		}
		
		state2=((state2<<1)&mask)| BIT_IS_SET(PINB,0);
		if (state2 ==0){
			pressed = 0;
		}else if(state2==mask){
			pressed = 1;
		}
		
		state3=((state3<<1)&mask)| BIT_IS_SET(PINC,2);
		if (state3 ==0){
			pressed = 0;
		}else if(state3==mask){
			pressed = 1;
		}
		
		state4=((state4<<1)&mask)| BIT_IS_SET(PINC,1);
		if (state4 ==0){
			pressed = 0;
		}else if(state4==mask){
			pressed = 1;
		}
		
		state5=((state5<<1)&mask)| BIT_IS_SET(PINC,3);
		if (state5 ==0){
			pressed = 0;
		}else if(state5==mask){
			pressed = 1;
		}
}
