#include "commands.h"
#include "helper.h"

void exec_observe(void) {
	// Memory Full!
	if (total_obs >= 127) return;

	unsigned int depth, temp;

	set_adc_channel(0);
	delay_us(50);
	temp = read_adc();

	set_adc_channel(1);
	delay_us(50);
	depth = read_adc();

	total_obs++;
	write_eeprom(0, total_obs);
	write_eeprom(total_obs * 2 - 1, depth);
	write_eeprom(total_obs * 2, temp);

	// printf("\r\n%u. Pressure:%u Temperature:%u", total_obs, depth, temp);
}

void set_datetime(char *date, char *time) {
	int i;
	long int year = 0, pow;
	int month = 0, day = 0;
	int hour = 0, min = 0, sec = 0;

	i = 0;
	for (pow = 1000; pow >= 1; pow /= 10) {
		year += (date[i] - '0') * pow;
		if (pow <= 10) {
			month += (date[i + 2] - '0') * pow;
			day += (date[i + 4] - '0') * pow;
		}
		i++;
	}

	i = 0;
	for (pow = 10; pow >= 1; pow /= 10) {
		hour += (time[i] - '0') * pow;
		min += (time[i + 2] - '0') * pow;
		sec += (time[i + 4] - '0') * pow;
		i++;
	}

	unixtime = calc_unixtime(year, month, day, hour, min, sec);
}

unsigned long long calc_unixtime(long int year, int month, int day, int hour,
								int min, int sec) {
	long int i;
	unsigned long long total = 0;

	total += (year - BASE_OF_YEAR) * 365;
	for (i = BASE_OF_YEAR; i < year; i++) {
		if (is_leap(i)) {
			total += 1;
		}
	}

	total += (month - 1) * 31;
	for (i = 1; i < month; i++) {
		total -= ((i + (i < 8)) & 1) + (i == 2) * (2 - is_leap(year));
	}

	total += day - 1;

	total *= HOUR_IN_DAY;
	total += hour;

	total *= MIN_IN_HOUR;
	total += min;

	total *= SEC_IN_MIN;
	total += sec;

	return total;
}

void set_obs_position(char *lat, char *lon) {
	latitude = str_to_float(lat);
	longitude = str_to_float(lon);
}

void start_obs(void) {
	is_observing = !is_observing;

	if (is_observing) {
		total_obs = 0;
		PORTC = 0x0B;

		printf("\r\nObservation Started.");
	} else {
		PORTC = 0x03;

		printf("\r\nObservation Stopped.");
	}
}

void print_obs_result(void) {
	unsigned int i;

	printf("\r\n[Time:%lu Lat:%.5f Lon:%.5f]", unixtime, latitude, longitude);

	total_obs = read_eeprom(0);
	for (i = 1; i <= total_obs; i++) {
		unsigned int p = read_eeprom(i * 2 - 1);
		unsigned int t = read_eeprom(i * 2);
		printf("\r\n%u. Pressure:%u Temperature:%u", i, p, t);
	}
}

void print_obs_count(void) {
	total_obs = read_eeprom(0);
	printf("\r\n%u", total_obs);
}
