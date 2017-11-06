#ifndef COMMANDS_H
#define COMMANDS_H

#define get_total_obs() read_eeprom(0)
#define set_total_obs(x) write_eeprom(0, x)
#define get_obs_temp(x) read_eeprom((x + 1) * 2)
#define set_obs_temp(x, y) write_eeprom((x + 1) * 2, y)
#define get_obs_depth(x) read_eeprom((x)*2 + 1)
#define set_obs_depth(x, y) write_eeprom((x)*2 + 1, y)

void exec_observe(void);
void set_datetime(char *date, char *time);
unsigned long long calc_unixtime(long int year, int month, int day, int hour,
								 int min, int sec);
void set_obs_position(char *lat, char *lon);
int1 toggle_obs_state(void);
void start_obs(void);
void stop_obs(void);
void print_obs_results(void);
void increment_obs_count(void);
void print_obs_count(void);

#endif
