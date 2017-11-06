#include <16F1825.h>
#include "config.h"
#include "globals.h"
//#include <input.c>
#include "commands.h"
#include "helper.h"

/*
int1 is_observing = FALSE;
unsigned int obs_count = 0;
unsigned long long unixtime = 0;
float latitude = 0.0, longitude = 0.0;
*/

void process(char *received);

void init(void);

void main(void) {
	init();

	// LED Blink Demo
	for (int i = 0; i < 2; i++) {
		PORTA = 0x20;
		delay_ms(200);
		PORTA = 0x00;
		delay_ms(200);
	}

	enable_interrupts(int_rda);
	enable_interrupts(global);

	while (TRUE) {
		if (is_observing) {
			exec_observe();
		}
		delay_ms(1000);
	}
}

#INT_RDA
void rcv_rs232() {
	char received[30];
	gets(received);
	process(received);
}

void process(char *cmd) {
	int1 has_args = 0;
	char *args;

	has_args = divide_data(received, args);  // Example: @UTC,20150310,143211

	if (is_equal(cmd, commands[0])) {  // @UTC
		char *time;
		divide_data(args, time);  // = date, time
		set_datetime(args, time);
		printf("\r\n%lu", unixtime);
	} else if (is_equal(cmd, commands[1])) {  // @POS
		char *lon;
		divide_data(args, lon);  // = lat, lon
		set_obs_position(args, lon);
		printf("\r\n%.5f %.5f", latitude, longitude);
	} else if (is_equal(cmd, commands[2])) {  // @SET
		toggle_obs_state();
	} else if (is_equal(cmd, commands[3])) {  // @GET
		print_obs_results();
	} else if (is_equal(cmd, commands[4])) {  // @NUM
		print_obs_count();
	} else if (is_equal(cmd, commands[5])) {  // @BAT
		// TODO: Implement battery telemetry service.
	}
}

void init(void) {
	delay_ms(1000);

	/*
	 * PIC Init
	 */
	OSCCON = 0x70;  // 8 MHz, Stop INTOSC
	TRISA = 0xDF;   // 0b11011111, RA5 Output
	TRISC = 0xF4;   // 0b11110100, RC0,1,3 Output
	PORTA = 0x00;   // 0b00000000, RA5 OFF
	PORTC = 0x03;   // 0b00000011, RC0 ON, RC1 ON

	/*
	 * Bluetooth Module Init
	 */
	LATC1 = 0;		 // RC1 BT RESET
	delay_ms(100);   // Reset Wait
	LATC1 = 1;		 // RC1 BT RESET OUT
	delay_ms(500);   // Init Wait
	TXSTA = 0x24;	// Send Mode, BRGH=1
	RCSTA = 0x90;	// Receive Mode
	BAUDCON = 0x08;  // 16bitz
	SPBRG = 207;	 // Communication Speed

	RCIF = 0;

	setup_adc_ports(sAN0 | sAN1);
	setup_adc(ADC_CLOCK_INTERNAL);
}
