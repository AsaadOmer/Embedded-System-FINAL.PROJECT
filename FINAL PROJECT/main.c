#define F_CPU 8000000UL
#include <util/delay.h>

/* UTIL Layer */
#include "UTIL/STD_TYPES.h"
#include "UTIL/BIT_MATH.h"

/* MCAL Layer */
#include "MCAL/REGISTER.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "MCAL/TIMER0/TIMER0_interface.h"
#include "MCAL/TWI/TWI_interface.h"
#include "MCAL/GI/GI_interface.h"

/* HAL Layer */
#include "HAL/EEPROM/EEPROM_interface.h"
#include "HAL/SSD/SSD_interface.h"
#include "HAL/LM35/LM35_interface.h"
#include "HAL/ACTUATORS/ACTUATORS_interface.h"

/* Button Pins Definitions */
#ifndef ON_OFF_BTN_PIN
#define ON_OFF_BTN_PIN         DIO_PIN0
#endif

#ifndef UP_BTN_PIN
#define UP_BTN_PIN             DIO_PIN1
#endif

#ifndef DOWN_BTN_PIN
#define DOWN_BTN_PIN           DIO_PIN2
#endif

/* System States Definitions */
typedef enum {
	STATE_OFF,
	STATE_ON,
	STATE_SET_TEMP
} SystemState_t;

/* Global System Variables */
volatile SystemState_t CurrentState = STATE_OFF;
volatile u8 TempReadFlag = 0;
volatile u8 SetTempBlinkFlag = 0;
volatile u8 SettingTimeoutCounter = 0;

u8 TargetTemp = 60;
u8 ActualTemp = 0;
u8 TempReadings[10] = {0};
u8 ReadingIndex = 0;
u8 AverageTemp = 0;

/* Function Prototypes */
void Timer0_ISR_Callback(void);
u8   Calculate_Average_Temp(u8 NewTemp);

int main(void) {
	/* 1. Hardware Drivers Initialization */
	ADC_voidInit();          // *** ????? ???: ????? ??? ADC ***
	ACTUATORS_voidInit();
	SSD_voidInit();
	LM35_voidInit();
	EEPROM_voidInit();
	
	/* 2. Read Desired Temperature from EEPROM */
	u8 SavedTemp = EEPROM_u8ReadByte(0x0000);
	if (SavedTemp >= 35 && SavedTemp <= 75 && (SavedTemp % 5 == 0)) {
		TargetTemp = SavedTemp;
		} else {
		TargetTemp = 60;
		EEPROM_voidWriteByte(0x0000, TargetTemp);
	}

	/* 3. Timer0 & Interrupt Setup */
	TIMER0_voidSetCallBack(Timer0_ISR_Callback);
	TIMER0_voidInit();
	GI_voidEnable();

	/* 4. Local Button States */
	u8 Prev_ON_OFF_Btn = DIO_PIN_HIGH;
	u8 Prev_UP_Btn     = DIO_PIN_HIGH;
	u8 Prev_DOWN_Btn   = DIO_PIN_HIGH;

	while (1) {
		/* Read Current Button States */
		u8 Curr_ON_OFF_Btn = BUTTON_u8GetState(ON_OFF_BTN_PIN);
		u8 Curr_UP_Btn     = BUTTON_u8GetState(UP_BTN_PIN);
		u8 Curr_DOWN_Btn   = BUTTON_u8GetState(DOWN_BTN_PIN);

		/* Handle 100ms ADC Reading Request from ISR */
		if (TempReadFlag && CurrentState != STATE_OFF) {
			TempReadFlag = 0;
			ActualTemp = LM35_u8GetTemp();
			AverageTemp = Calculate_Average_Temp(ActualTemp);
		}

		/* ================= ON/OFF BUTTON ================= */
		if (Prev_ON_OFF_Btn == DIO_PIN_LOW && Curr_ON_OFF_Btn == DIO_PIN_HIGH) {
			_delay_ms(30);
			if (BUTTON_u8GetState(ON_OFF_BTN_PIN) == DIO_PIN_HIGH)  {
				if (CurrentState == STATE_OFF) {
					CurrentState = STATE_ON;
					ActualTemp = LM35_u8GetTemp();
					for (u8 i = 0; i < 10; i++) {
						TempReadings[i] = ActualTemp;
					}
					AverageTemp = ActualTemp;
					} else {
					CurrentState = STATE_OFF;
					HEATER_voidTurnOff();
					COOLER_voidTurnOff();
					HEATER_LED_voidTurnOff();
					SSD_voidDisable();
				}
			}
		}
		Prev_ON_OFF_Btn = Curr_ON_OFF_Btn;

		/* ================= STATE MACHINE LOGIC ================= */
		switch (CurrentState) {
			case STATE_OFF:
			SSD_voidDisable();
			HEATER_voidTurnOff();
			COOLER_voidTurnOff();
			HEATER_LED_voidTurnOff();
			break;

			case STATE_ON:
			SSD_voidDisplayNumber(AverageTemp);

			/* Enter SET_TEMP Mode on UP or DOWN Press */
			if ((Prev_UP_Btn == DIO_PIN_HIGH && Curr_UP_Btn == DIO_PIN_LOW) ||
			(Prev_DOWN_Btn == DIO_PIN_HIGH && Curr_DOWN_Btn == DIO_PIN_LOW)) {
				CurrentState = STATE_SET_TEMP;
				SettingTimeoutCounter = 0;
			}

			/* Heater & Cooler Control Logic */
			if (AverageTemp < (TargetTemp - 5)) {
				HEATER_voidTurnOn();
				COOLER_voidTurnOff();
				} else if (AverageTemp > (TargetTemp + 5)) {
				HEATER_voidTurnOff();
				COOLER_voidTurnOn();
				HEATER_LED_voidTurnOff();   //  HEATER_LED_voidTurnOn(), Off
			   } else {
				HEATER_voidTurnOff();
				COOLER_voidTurnOff();
				HEATER_LED_voidTurnOff();
			}
			break;

			case STATE_SET_TEMP:
			if (SetTempBlinkFlag) {
				SSD_voidDisplayNumber(TargetTemp);
				} else {
				SSD_voidDisable();
			}

			/* UP Button Logic (+5) */
			if (Prev_UP_Btn == DIO_PIN_HIGH && Curr_UP_Btn == DIO_PIN_LOW) {
				_delay_ms(30);
				if (BUTTON_u8GetState(UP_BTN_PIN) == DIO_PIN_LOW) {
					if (TargetTemp < 75) {
						TargetTemp += 5;
					}
					SettingTimeoutCounter = 0;
				}
			}

			/* DOWN Button Logic (-5) */
			if (Prev_DOWN_Btn == DIO_PIN_HIGH && Curr_DOWN_Btn == DIO_PIN_LOW) {
				_delay_ms(30);
				if (BUTTON_u8GetState(DOWN_BTN_PIN) == DIO_PIN_LOW) {
					if (TargetTemp > 35) {
						TargetTemp -= 5;
					}
					SettingTimeoutCounter = 0;
				}
			}

			/* Timeout 5 Seconds Check */
			if (SettingTimeoutCounter >= 5) {
				EEPROM_voidWriteByte(0x0000, TargetTemp);
				CurrentState = STATE_ON;
			}
			break;
		}

		Prev_UP_Btn   = Curr_UP_Btn;
		Prev_DOWN_Btn = Curr_DOWN_Btn;
	}

	return 0;
}

/* ================= TIMER0 ISR CALLBACK (10ms) ================= */
void Timer0_ISR_Callback(void) {
	static u8  TempCounter = 0;
	static u16 OneSecCounter = 0;

	if (CurrentState != STATE_OFF) {
		/* Trigger Temp Read every 100ms (10 Ticks) */
		TempCounter++;
		if (TempCounter >= 10) {
			TempCounter = 0;
			TempReadFlag = 1;
		}

		/* 1 Second Counter (100 Ticks) */
		OneSecCounter++;
		if (OneSecCounter >= 100) {
			OneSecCounter = 0;

			SetTempBlinkFlag ^= 1;

			if (CurrentState == STATE_SET_TEMP) {
				SettingTimeoutCounter++;
			}

			if (CurrentState == STATE_ON && AverageTemp < (TargetTemp - 5)) {
				HEATER_LED_voidToggle();
			}
		}
	}
}

u8 Calculate_Average_Temp(u8 NewTemp) {
	u16 Sum = 0;
	TempReadings[ReadingIndex] = NewTemp;
	ReadingIndex = (ReadingIndex + 1) % 10;

	for (u8 i = 0; i < 10; i++) {
		Sum += TempReadings[i];
	}
	return (u8)(Sum / 10);
}