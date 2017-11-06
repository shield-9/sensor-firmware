#ifndef COMMANDS_H
#define COMMANDS_H

void observe(void);
void set_datetime(char *date, char *time);
unsigned long long calc_unixtime(long int year, int month, int day, int hour,
								int min, int sec);
void set_obs_position(char *lat, char *lon);
void start_obs(void);
void print_obs_result(void);
void print_obs_count(void);

#endif
