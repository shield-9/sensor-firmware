#include "commands.h"
#include "helper.h"

void exec_observe(void) {
	// Memory Full!
	if (obs_count >= 127) return;

	unsigned int data;
	increment_obs_count();

	// Depth
	set_adc_channel(1);
	delay_us(50);
	data = read_adc();
	set_obs_depth(obs_count, data);

	// Temp
	set_adc_channel(0);
	delay_us(50);
	data = read_adc();
	set_obs_temp(obs_count, data);

	// printf("\r\n%u. Pressure:%u Temperature:%u", obs_count, depth, temp);
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
	// TODO: Why we don't use atof() here?
	latitude = str_to_float(lat);
	longitude = str_to_float(lon);
}

int1 toggle_obs_state(void) {
	if (is_observing) {
		start_obs();
		printf("\r\nObservation Started.");
	} else {
		stop_obs();
		printf("\r\nObservation Stopped.");
	}

	return is_observing;
}

void start_obs(void) {
	is_observing = TRUE;

	obs_count = 0;
	PORTC = 0x0B;
}

void stop_obs(void) {
	is_observing = FALSE;

	PORTC = 0x03;
}

void print_obs_results(void) {
	printf("\r\n[Time:%lu Lat:%.5f Lon:%.5f]", unixtime, latitude, longitude);

	for (unsigned int i = 0; i < obs_count; i++) {
		unsigned int p = get_obs_depth(i);
		unsigned int t = get_obs_temp(i);
		printf("\r\n%u. Pressure:%u Temperature:%u", i, p, t);
	}
}

void increment_obs_count(void) {
	obs_count++;
	set_obs_count(obs_count);
}

void print_obs_count(void) { printf("\r\n%u", obs_count); }
