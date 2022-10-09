#include "lm35_sensor.h"
#include "lcd.h"
#include "adc.h"
#include "dc_motor.h"
#include "pwm.h"

typedef enum {
	stoped=0,precent25=25,precent50=50,precent75=75,precent100=100,nothing=-1
}motorState;
int main(){
	/*declaring needed variables*/
	uint8 currentTemp;
	motorState lastState=nothing,currentState=nothing;
	/*
	 * initialize ADC at frequency equal to 1/8 of CPU frequency and
	 * with internal V reference
	 */
	{
		ADC_ConfigType adc_config;
		adc_config.ref_volt=FCPUOver_8;
		adc_config.ref_volt=AVCC;
		ADC_init(&adc_config);
	}
	/*initializing LCD*/
	LCD_init();
	/*initializing PWM*/
	PWM_init();
	/*initializing DC MOTOR*/
	DcMotor_init();
	while(1){
		currentTemp = LM35_getTemperature();
		if(currentTemp<30){
			currentState=stoped;
			if(currentState!=lastState)
			{
				LCD_clearScreen();
				LCD_moveCursor(0, 3);
				LCD_displayString("fan is off");
			}
			LCD_moveCursor(1, 6);
			LCD_intgerToString(currentTemp);
			LCD_displayString(" C ");
			DcMotor_Rotate(stoped, 0);
			lastState=currentState;
		}else if(currentTemp<50){
			currentState=precent50;
			if(currentState!=lastState)
			{
				LCD_clearScreen();
				LCD_moveCursor(0, 2 );
				LCD_displayString("fan is on 25%");
			}
			LCD_moveCursor(1, 6);
			LCD_intgerToString(currentTemp);
			LCD_displayString(" C ");
			DcMotor_Rotate(clockwise,precent50);
			lastState=currentState;
		} else if(currentTemp<60){
			currentState=precent50;
			if(currentState!=lastState)
			{
				LCD_clearScreen();
				LCD_moveCursor(0, 2 );
				LCD_displayString("fan is on 50%");
			}
			LCD_moveCursor(1, 6);
			LCD_intgerToString(currentTemp);
			LCD_displayString(" C ");
			DcMotor_Rotate(clockwise,precent50);
			lastState=currentState;
		} else if(currentTemp<90){
			currentState=precent75;
			if(currentState!=lastState)
			{
				LCD_clearScreen();
				LCD_moveCursor(0, 2 );
				LCD_displayString("fan is on 75%");
			}
			LCD_moveCursor(1, 6);
			LCD_intgerToString(currentTemp);
			LCD_displayString(" C ");
			DcMotor_Rotate(clockwise,precent75);
			lastState=currentState;
		} else {
			currentState=precent100;
			if(currentState!=lastState)
			{
				LCD_clearScreen();
				LCD_moveCursor(0, 2 );
				LCD_displayString("fan is on 100%");

			}
			LCD_moveCursor(1, 6);
			LCD_intgerToString(currentTemp);
			LCD_displayString(" C ");
			DcMotor_Rotate(clockwise,precent100);
			lastState=currentState;
		}
	}
}
