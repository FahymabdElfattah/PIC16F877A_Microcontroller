#include <xc.h>
#include <pic16f877a.h>

#define _XTAL_FREQ 20000000
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

unsigned char timer_count = 0;
unsigned short nb = 96;
unsigned char segment[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned char i=0,j=0;
unsigned char R,Rd,Ru,L,Ld,Lu;

void int_Port();
void display_Seg(unsigned short a);
void select_Seg(unsigned short rc0,unsigned short rc1,unsigned short rc2,unsigned short rc3);


void main(void) {
    
    int_Port();
    while (1){
        display_Seg(nb);
        select_Seg(0,1,1,1);
        PORTB = segment[Ld];
        __delay_ms(10); 
        select_Seg(1,0,1,1);
        PORTB = segment[Lu];
    }
    
    return;
}
void int_Port(){
    TRISB = 0x00;
    TRISC = 0x00;
    PORTC = 0x00;
    PORTB = 0x00;
};
void display_Seg(unsigned short a ){
    R = a/100;
    Rd = R/10;
    Ru = R%10;
    L = a%100;
    Ld = L/10;
    Lu = L%10;
};
void select_Seg(unsigned short rc0,unsigned short rc1,unsigned short rc2,unsigned short rc3){
    PORTCbits.RC0 = rc0 ;                   // PORTC = b 0000 0001
    PORTCbits.RC1 = rc1 ;
    PORTCbits.RC2 = rc2 ;
    PORTCbits.RC3 = rc3 ;
}

