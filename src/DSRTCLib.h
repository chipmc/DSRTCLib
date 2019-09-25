/*
  DSRTCLib.h - library for Maxim Integrated's DS1337 and DS1339 RTCs
*/

// ensure this library description is only included once
#ifndef DSRTCLib_h
#define DSRTCLib_h

#include "Particle.h"

#define I2C_READ	Wire.read
#define I2C_WRITE	Wire.write

// include types & constants of Wire ic2 lib
#include <Wire.h>

// indices within the rtc_bcd[] buffer
#define DSRTCLib_SEC	        0
#define DSRTCLib_MIN	        1
#define DSRTCLib_HR	        2
#define DSRTCLib_DOW	        3
#define DSRTCLib_DATE           4
#define DSRTCLib_MTH	        5
#define DSRTCLib_YR	        6

#define DSRTCLib_BASE_YR        2000

#define DSRTCLib_CTRL_ID	0b1101000

 // Define register bit masks
#define DSRTCLib_CLOCKHALT	0b10000000

#define DSRTCLib_LO_BCD		0b00001111
#define DSRTCLib_HI_BCD		0b11110000

#define DSRTCLib_HI_SEC		0b01110000
#define DSRTCLib_HI_MIN		0b01110000
#define DSRTCLib_HI_HR		0b00110000
#define DSRTCLib_LO_DOW		0b00000111
#define DSRTCLib_HI_DATE	0b00110000
#define DSRTCLib_HI_MTH		0b00110000
#define DSRTCLib_HI_YR		0b11110000

#define DSRTCLib_ARLM1		0x07
#define DSRTCLib_ARLM1_LO_SEC	0b00001111
#define DSRTCLib_ARLM1_HI_SEC	0b01110000
#define DSRTCLib_ARLM1_LO_MIN	0b01110000
#define DSRTCLib_ARLM1_HI_MIN	0b00001111

#define DSRTCLib_SP		0x0E
#define	DSRTCLib_SP_EOSC	0b10000000
#define	DSRTCLib_SP_RS2		0b00010000
#define	DSRTCLib_SP_RS1		0b00001000
#define	DSRTCLib_SP_INTCN	0b00000100
#define	DSRTCLib_SP_A2IE	0b00000010
#define	DSRTCLib_SP_A1IE	0b00000001

#define DSRTCLib_STATUS		0x0F
#define DSRTCLib_STATUS_OSF	0b10000000
#define DSRTCLib_STATUS_A2F	0b00000010
#define DSRTCLib_STATUS_A1F	0b00000001

/* Definitions for alarm repeat */
/* The private variable alarm_repeat holds the user's alarm repeat preference. However, the DS1337 & DS1339 encode these in the topmost bit(s) of the 4 alarm registers. */
/* Splattering these bits across the alarm regs is handled in the writeAlarm() function. */
/* If DY/DT is set, the day field is interpreted as a DayOfWeek (1 ~ 7), else it is interpreted as a DayOfMonth.*/

/* user alarm_repeat bit mask:
       7   6   5    4       3      2       1     0
      [x   x   x   A1M4   DY/DT   A1M3   A1M2   A1M1]
*/

#define EVERY_SECOND            0b00010111
#define EVERY_MINUTE            0b00010110
#define EVERY_HOUR              0b00010100
#define EVERY_DAY               0b00010000
#define EVERY_WEEK              0b00001000
#define EVERY_MONTH             0b00000000


// library interface description : base class
class DSRTCLib
{
	// user-accessible "public" interface
	public:
		DSRTCLib();

                DSRTCLib(int int_pin);

		unsigned char time_is_set();
		unsigned char alarm_is_set();
		//unsigned char time_is_valid();

		void    enable_interrupt();
		void    disable_interrupt();
		void    clear_interrupt();

		void    readTime();
		void    readAlarm();
		void    writeTime();
                void    writeTime(unsigned long);
		void    writeAlarm();
                void    writeAlarm(unsigned long);
                void    setAlarmRepeat(byte repeat);

                unsigned char getSeconds();
                unsigned char getMinutes();
                unsigned char getHours();
                unsigned char getDays();
                unsigned char getDayOfWeek();
                unsigned char getMonths();
                unsigned int getYears();
                unsigned long date_to_epoch_seconds(unsigned int year, byte month, byte day, byte hour, byte minute, byte second);
                unsigned long date_to_epoch_seconds();
                void epoch_seconds_to_date(unsigned long);								
                void alarmSeconds(unsigned long secondsToSnooze);

                void setSeconds(unsigned char);
                void setMinutes(unsigned char);
                void setHours(unsigned char);
                void setDays(unsigned char);
                void setDayOfWeek(unsigned char);
                void setMonths(unsigned char);
                void setYears(unsigned int);

		void	start(void);
		void	stop(void);
		unsigned char getRegister(unsigned char registerNumber);
		void	setRegister(unsigned char registerNumber, unsigned char registerValue);


	// library-accessible "private" interface
	private:
                void init();
	        byte    time_set;
	        byte alarm_repeat;
		byte	rtc_bcd[7]; // used prior to read/set DS1337 & DS1339 registers;
		void	read(void);
		void	save(void);
		byte bcd2bin(byte);
		byte bin2bcd(byte);
                int _rtc_int_number;
                int _rtc_int_pin;
};

class DS1339 : public DSRTCLib
{
  // TO DO: Implement trickle charger for DS1339
  public:
                DS1339();
                DS1339(int int_pin);
  private:

};

class DS1337 : public DSRTCLib
{
  public:
                DS1337();
                DS1337(int int_pin);
  private:
  
};

#endif
