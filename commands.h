#ifndef COMMANDS_H
#define COMMANDS_H

void observe(void);
void set_datetime(char *date, char *time);
unsigned long long calc_unixtime(long int year, int month, int day, int hour,
								int min, int sec);
void set_observation_position(char *lat, char *lon);
void start_observation(void);
void print_observation_result(void);
void print_observation_count(void);

#endif
