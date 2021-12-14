// 2020-04-22 ~

#include "FastLED.h"

#define GetTickCount millis

#define LED_CONTROL_MODULE_TOTAL_AMOUNT_COUNT 56U
#define LED_CONTROL_DATA_OUTPUT_PIN 6U

#define LED_COLOR_OFF_R (0x00U)
#define LED_COLOR_OFF_G (0x00U)
#define LED_COLOR_OFF_B (0x00U)
#define LED_COLOR_WELCOME_R (0x0DU)
#define LED_COLOR_WELCOME_G (0x4CU)
#define LED_COLOR_WELCOME_B (0xFFU)
#define LED_COLOR_DAYTIME_RUNNING_R (0x0DU)
#define LED_COLOR_DAYTIME_RUNNING_G (0x4CU)
#define LED_COLOR_DAYTIME_RUNNING_B (0xFFU)
#define LED_COLOR_CLEARANCE_FRONT_R (0x05U)
#define LED_COLOR_CLEARANCE_FRONT_G (0x07U)
#define LED_COLOR_CLEARANCE_FRONT_B (0x0DU)
#define LED_COLOR_CLEARANCE_REAR_R (0x09U)
#define LED_COLOR_CLEARANCE_REAR_G (0x00U)
#define LED_COLOR_CLEARANCE_REAR_B (0x00U)
#define LED_COLOR_TURN_SIGNAL_R (0xFFU)
#define LED_COLOR_TURN_SIGNAL_G (0x1CU)
#define LED_COLOR_TURN_SIGNAL_B (0x00U)
#define LED_COLOR_HEAD_R (0xFFU)
#define LED_COLOR_HEAD_G (0xA0U)
#define LED_COLOR_HEAD_B (0x30U)
#define LED_COLOR_BRAKE_R (0xFFU)
#define LED_COLOR_BRAKE_G (0x00U)
#define LED_COLOR_BRAKE_B (0x00U)

#define LED_WELCOME_PIXEL_COUNT (56U)
#define LED_WELCOME_START_INDEX (0U)
#define LED_WELCOME_INDEX_LENGTH LED_WELCOME_PIXEL_COUNT

#define LED_DAYTIME_PIXEL_COUNT (14U)
#define LED_DAYTIME_RUNNING_LEFT_START_INDEX (14U)
#define LED_DAYTIME_RUNNING_LEFT_INDEX_LENGTH LED_DAYTIME_PIXEL_COUNT
#define LED_DAYTIME_RUNNING_RIGHT_START_INDEX (0U)
#define LED_DAYTIME_RUNNING_RIGHT_INDEX_LENGTH LED_DAYTIME_PIXEL_COUNT

#define LED_DAYTIME_REAR_PIXEL_COUNT (5U)
#define LED_DAYTIME_REAR_RUNNING_LEFT_START_INDEX (29U)
#define LED_DAYTIME_REAR_RUNNING_LEFT_INDEX_LENGTH LED_DAYTIME_REAR_PIXEL_COUNT
#define LED_DAYTIME_REAR_RUNNING_RIGHT_START_INDEX (51U)
#define LED_DAYTIME_REAR_RUNNING_RIGHT_INDEX_LENGTH LED_DAYTIME_REAR_PIXEL_COUNT

#define LED_CLEARANCE_PIXEL_COUNT (14U)
#define LED_CLEARANCE_FRONT_LEFT_START_INDEX (14U)
#define LED_CLEARANCE_FRONT_LEFT_INDEX_LENGTH LED_CLEARANCE_PIXEL_COUNT
#define LED_CLEARANCE_FRONT_RIGHT_START_INDEX (0U)
#define LED_CLEARANCE_FRONT_RIGHT_INDEX_LENGTH LED_CLEARANCE_PIXEL_COUNT
#define LED_CLEARANCE_REAR_LEFT_START_INDEX (28U)
#define LED_CLEARANCE_REAR_LEFT_INDEX_LENGTH LED_CLEARANCE_PIXEL_COUNT
#define LED_CLEARANCE_REAR_RIGHT_START_INDEX (42U)
#define LED_CLEARANCE_REAR_RIGHT_INDEX_LENGTH LED_CLEARANCE_PIXEL_COUNT

#define LED_HEAD_PIXEL_COUNT (7U)
#define LED_HEAD_LEFT_START_INDEX (14U)
#define LED_HEAD_LEFT_INDEX_LENGTH LED_HEAD_PIXEL_COUNT
#define LED_HEAD_RIGHT_START_INDEX (7U)
#define LED_HEAD_RIGHT_INDEX_LENGTH LED_HEAD_PIXEL_COUNT

#define LED_TURN_SIGNAL_PIXEL_COUNT (14U)
#define LED_TURN_SIGNAL_FRONT_LEFT_START_INDEX (14U)
#define LED_TURN_SIGNAL_FRONT_LEFT_INDEX_LENGTH LED_TURN_SIGNAL_PIXEL_COUNT
#define LED_TURN_SIGNAL_FRONT_RIGHT_START_INDEX (0U)
#define LED_TURN_SIGNAL_FRONT_RIGHT_INDEX_LENGTH LED_TURN_SIGNAL_PIXEL_COUNT
#define LED_TURN_SIGNAL_REAR_LEFT_START_INDEX (28U)
#define LED_TURN_SIGNAL_REAR_LEFT_INDEX_LENGTH LED_TURN_SIGNAL_PIXEL_COUNT
#define LED_TURN_SIGNAL_REAR_RIGHT_START_INDEX (42U)
#define LED_TURN_SIGNAL_REAR_RIGHT_INDEX_LENGTH LED_TURN_SIGNAL_PIXEL_COUNT

#define LED_BRAKE_PIXEL_COUNT (5U)
#define LED_BRAKE_LEFT_START_INDEX (37U)
#define LED_BRAKE_LEFT_INDEX_LENGTH LED_BRAKE_PIXEL_COUNT
#define LED_BRAKE_RIGHT_START_INDEX (42U)
#define LED_BRAKE_RIGHT_INDEX_LENGTH LED_BRAKE_PIXEL_COUNT

#define LED_BACKUP_PIXEL_COUNT (1U)
#define LED_BACKUP_LEFT_START_INDEX (37U)
#define LED_BACKUP_LEFT_INDEX_LENGTH LED_BRAKE_PIXEL_COUNT
#define LED_BACKUP_RIGHT_START_INDEX (42U)
#define LED_BACKUP_RIGHT_INDEX_LENGTH LED_BRAKE_PIXEL_COUNT

static CRGB TotLEDPixList[LED_CONTROL_MODULE_TOTAL_AMOUNT_COUNT] = {0U};
static CRGB TurnSigLEDPixList[LED_TURN_SIGNAL_PIXEL_COUNT] = {0U};

uint8_t CheckValidLampControlCommand(const uint8_t _In_LampCtrlCmd)
{
	//
	//
	return ((_In_LampCtrlCmd >> 7U) & 1U);
}
uint8_t CheckEnabledTurnSignalLamp(const uint8_t _In_LampCtrlCmd)
{
	//
	//
	return ((_In_LampCtrlCmd >> 1U) & 3U);
}
uint8_t CheckEnabledHeadLamp(const uint8_t _In_LampCtrlCmd)
{
	//
	//
	return ((_In_LampCtrlCmd >> 5U) & 3U);
}
uint8_t CheckEnabledBrakeLamp(const uint8_t _In_LampCtrlCmd)
{
	//
	//
	return ((_In_LampCtrlCmd >> 3U) & 3U);
}
uint8_t CheckEnabledBackupLamp(const uint8_t _In_LampCtrlCmd)
{
	//
	//
	return ((_In_LampCtrlCmd >> 3U) & 3U);
}

uint8_t ReadLampConrtolCommand(void)
{
	//
	static uint8_t LampCtrlCmd;
	//
	if (Serial.available() > 0U)
	{
		//
		LampCtrlCmd = Serial.read();

		//
		Serial.flush();
	}

	//
	if (CheckValidLampControlCommand(LampCtrlCmd) == 0U)
	{
		//
		LampCtrlCmd = 0x8EU;
		// LampCtrlCmd = 0x80U;
	}

	//
	//
	return LampCtrlCmd;
}

uint8_t ExecuteWelcomeCelemonyFunction(void)
{
	//
	uint8_t Result = 0UL;

	// //
	// static uint8_t TotRefLEDPixIdxLenOffset;
	// //
	// const uint8_t LEDfPixIdxOffset = LED_WELCOME_START_INDEX;
	// const uint8_t TotRefLEDPixIdxLen = LED_WELCOME_INDEX_LENGTH;

	// //
	// for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
	// {
	// 	//
	// 	TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_WELCOME_R;
	// 	TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_WELCOME_G;
	// 	TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_WELCOME_B;
	// }

	// //
	// if (LastCnt >= LED_WELCOME_INDEX_LENGTH)
	// {
	// 	//
	// 	Result = 1U;
	// }
	// else
	// {
	// 	//
	// 	LastCnt++;

	// 	//
	// 	Result = 0U;;
	// }

	//
	//
	return Result;
}

void ExecuteTurnSignalLampFlowAnimationPixelation(const uint8_t _In_CtrlFlag)
{
	//
	static uint8_t TurnSigLEDPixFillCnt;
	static uint8_t TurnSigLEDPixFlowStag;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RemLEDPixCnt = LED_TURN_SIGNAL_PIXEL_COUNT; RemLEDPixCnt--;)
		{
			//
			const uint8_t RefLEDPixIdx = RemLEDPixCnt;
			//
			TurnSigLEDPixList[RefLEDPixIdx].r = LED_COLOR_OFF_R;
			TurnSigLEDPixList[RefLEDPixIdx].g = LED_COLOR_OFF_G;
			TurnSigLEDPixList[RefLEDPixIdx].b = LED_COLOR_OFF_B;
		}

		//
		TurnSigLEDPixFillCnt = 0U;
		TurnSigLEDPixFlowStag = 0U;
	}
	else
	{
		//
		if (TurnSigLEDPixFlowStag == 0U)
		{
			//
			for (uint8_t RefLEDPixIdx = TurnSigLEDPixFillCnt; RefLEDPixIdx--;)
			{
				//
				TurnSigLEDPixList[RefLEDPixIdx].r = LED_COLOR_TURN_SIGNAL_R;
				TurnSigLEDPixList[RefLEDPixIdx].g = LED_COLOR_TURN_SIGNAL_G;
				TurnSigLEDPixList[RefLEDPixIdx].b = LED_COLOR_TURN_SIGNAL_B;
			}
		}
		else
		{
			//
			for (uint8_t RefLEDPixIdx = TurnSigLEDPixFillCnt; RefLEDPixIdx--;)
			{
				//
				TurnSigLEDPixList[RefLEDPixIdx].r = LED_COLOR_OFF_R;
				TurnSigLEDPixList[RefLEDPixIdx].g = LED_COLOR_OFF_G;
				TurnSigLEDPixList[RefLEDPixIdx].b = LED_COLOR_OFF_B;
			}
		}

		//
		if (TurnSigLEDPixFillCnt >= LED_TURN_SIGNAL_PIXEL_COUNT)
		{
			//
			TurnSigLEDPixFillCnt = 0U;

			//
			if (TurnSigLEDPixFlowStag == 0U)
			{
				TurnSigLEDPixFlowStag = 1U;
			}
			else
			{
				TurnSigLEDPixFlowStag = 0U;
			}
		}
		else
		{
			TurnSigLEDPixFillCnt += 1U;
		}
	}
}

void ExecuteDaytimeRunningLampLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_DAYTIME_RUNNING_LEFT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_DAYTIME_RUNNING_LEFT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_DAYTIME_RUNNING_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_DAYTIME_RUNNING_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_DAYTIME_RUNNING_B;
		}
	}
}
void ExecuteDaytimeRunningLampRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_DAYTIME_RUNNING_RIGHT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_DAYTIME_RUNNING_RIGHT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_DAYTIME_RUNNING_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_DAYTIME_RUNNING_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_DAYTIME_RUNNING_B;
		}
	}
}
void ExecuteDaytimeRearRunningLampLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_DAYTIME_REAR_RUNNING_LEFT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_DAYTIME_REAR_RUNNING_LEFT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_DAYTIME_RUNNING_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_DAYTIME_RUNNING_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_DAYTIME_RUNNING_B;
		}
	}
}
void ExecuteDaytimeRearRunningLampRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_DAYTIME_REAR_RUNNING_RIGHT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_DAYTIME_REAR_RUNNING_RIGHT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_DAYTIME_RUNNING_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_DAYTIME_RUNNING_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_DAYTIME_RUNNING_B;
		}
	}
}

void ExecuteClearanceLampFrontLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_CLEARANCE_FRONT_LEFT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_CLEARANCE_FRONT_LEFT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_CLEARANCE_FRONT_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_CLEARANCE_FRONT_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_CLEARANCE_FRONT_B;
		}
	}
}
void ExecuteClearanceLampFrontRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_CLEARANCE_FRONT_RIGHT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_CLEARANCE_FRONT_RIGHT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_CLEARANCE_FRONT_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_CLEARANCE_FRONT_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_CLEARANCE_FRONT_B;
		}
	}
}
void ExecuteClearanceLampRearLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_CLEARANCE_REAR_LEFT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_CLEARANCE_REAR_LEFT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_CLEARANCE_REAR_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_CLEARANCE_REAR_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_CLEARANCE_REAR_B;
		}
	}
}
void ExecuteClearanceLampRearRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_CLEARANCE_REAR_RIGHT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_CLEARANCE_REAR_RIGHT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_CLEARANCE_REAR_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_CLEARANCE_REAR_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_CLEARANCE_REAR_B;
		}
	}
}

void ExecuteTurnSignalLampFrontLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_TURN_SIGNAL_FRONT_LEFT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_TURN_SIGNAL_FRONT_LEFT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = TurnSigLEDPixList[RefLEDPixIdx].r;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = TurnSigLEDPixList[RefLEDPixIdx].g;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = TurnSigLEDPixList[RefLEDPixIdx].b;
		}
	}
}
void ExecuteTurnSignalLampFrontRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_TURN_SIGNAL_FRONT_RIGHT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_TURN_SIGNAL_FRONT_RIGHT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + ((TotRefLEDPixIdxLen - 1U) - RefLEDPixIdx))].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + ((TotRefLEDPixIdxLen - 1U) - RefLEDPixIdx))].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + ((TotRefLEDPixIdxLen - 1U) - RefLEDPixIdx))].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + ((TotRefLEDPixIdxLen - 1U) - RefLEDPixIdx))].r = TurnSigLEDPixList[RefLEDPixIdx].r;
			TotLEDPixList[(LEDPixIdxOffset + ((TotRefLEDPixIdxLen - 1U) - RefLEDPixIdx))].g = TurnSigLEDPixList[RefLEDPixIdx].g;
			TotLEDPixList[(LEDPixIdxOffset + ((TotRefLEDPixIdxLen - 1U) - RefLEDPixIdx))].b = TurnSigLEDPixList[RefLEDPixIdx].b;
		}
	}
}
void ExecuteTurnSignalLampRearLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_TURN_SIGNAL_REAR_LEFT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_TURN_SIGNAL_REAR_LEFT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + ((TotRefLEDPixIdxLen - 1U) - RefLEDPixIdx))].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + ((TotRefLEDPixIdxLen - 1U) - RefLEDPixIdx))].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + ((TotRefLEDPixIdxLen - 1U) - RefLEDPixIdx))].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + ((TotRefLEDPixIdxLen - 1U) - RefLEDPixIdx))].r = TurnSigLEDPixList[RefLEDPixIdx].r;
			TotLEDPixList[(LEDPixIdxOffset + ((TotRefLEDPixIdxLen - 1U) - RefLEDPixIdx))].g = TurnSigLEDPixList[RefLEDPixIdx].g;
			TotLEDPixList[(LEDPixIdxOffset + ((TotRefLEDPixIdxLen - 1U) - RefLEDPixIdx))].b = TurnSigLEDPixList[RefLEDPixIdx].b;
		}
	}
}
void ExecuteTurnSignalLampRearRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_TURN_SIGNAL_REAR_RIGHT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_TURN_SIGNAL_REAR_RIGHT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = TurnSigLEDPixList[RefLEDPixIdx].r;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = TurnSigLEDPixList[RefLEDPixIdx].g;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = TurnSigLEDPixList[RefLEDPixIdx].b;
		}
	}
}

void ExecuteHeadLampLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_HEAD_LEFT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_HEAD_LEFT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_HEAD_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_HEAD_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_HEAD_B;
		}
	}
}
void ExecuteHeadLampRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_HEAD_RIGHT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_HEAD_RIGHT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_HEAD_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_HEAD_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_HEAD_B;
		}
	}
}
void ExecuteBrakeLampLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_BRAKE_LEFT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_BRAKE_LEFT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_BRAKE_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_BRAKE_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_BRAKE_B;
		}
	}
}
void ExecuteBrakeLampRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint8_t LEDPixIdxOffset = LED_BRAKE_RIGHT_START_INDEX;
	const uint8_t TotRefLEDPixIdxLen = LED_BRAKE_RIGHT_INDEX_LENGTH;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_OFF_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_OFF_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_OFF_B;
		}
	}
	else
	{
		//
		for (uint8_t RefLEDPixIdx = TotRefLEDPixIdxLen; RefLEDPixIdx--;)
		{
			//
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].r = LED_COLOR_BRAKE_R;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].g = LED_COLOR_BRAKE_G;
			TotLEDPixList[(LEDPixIdxOffset + RefLEDPixIdx)].b = LED_COLOR_BRAKE_B;
		}
	}
}

void setup()
{
	//
	Serial.begin(9600UL);

	//
	FastLED.addLeds<NEOPIXEL, LED_CONTROL_DATA_OUTPUT_PIN>(TotLEDPixList, LED_CONTROL_MODULE_TOTAL_AMOUNT_COUNT);

	// for (;;)
	// {
	// 	//
	// 	ExecuteWelcomeCelemonyFunction();
	// }
}

void loop()
{
	//
	static uint32_t LastFuncExecTickCnt;
	//
	const uint32_t CurrTickCnt = GetTickCount();

	//
	if (CurrTickCnt >= (LastFuncExecTickCnt + 22UL))
	{
		//
		const uint8_t LampCtrlCmd = ReadLampConrtolCommand();
		//
		if (CheckValidLampControlCommand(LampCtrlCmd) != 0U)
		{
			//
			// 미등 램프 제어 부분
			//
			if (CheckEnabledHeadLamp(LampCtrlCmd) != 0U)
			{
				//
				ExecuteClearanceLampFrontLeftControlFunction(1U);
				ExecuteClearanceLampFrontRightControlFunction(1U);
				ExecuteClearanceLampRearLeftControlFunction(1U);
				ExecuteClearanceLampRearRightControlFunction(1U);
			}
			else
			{
				//
				ExecuteClearanceLampFrontLeftControlFunction(0U);
				ExecuteClearanceLampFrontRightControlFunction(0U);
				ExecuteClearanceLampRearLeftControlFunction(0U);
				ExecuteClearanceLampRearRightControlFunction(0U);
				//
				ExecuteDaytimeRunningLampLeftControlFunction(1U);
				ExecuteDaytimeRunningLampRightControlFunction(1U);
				ExecuteDaytimeRearRunningLampLeftControlFunction(1U);
				ExecuteDaytimeRearRunningLampRightControlFunction(1U);
			}

			//
			// 턴 시그널 램프 제어 부분
			//
			if (CheckEnabledTurnSignalLamp(LampCtrlCmd) != 0U)
			{
				//
				ExecuteTurnSignalLampFlowAnimationPixelation(1U);

				//
				if (((LampCtrlCmd >> 1U) & 1U) != 0U)
				{
					//
					ExecuteTurnSignalLampFrontLeftControlFunction(1U);
					ExecuteTurnSignalLampRearLeftControlFunction(1U);
				}
				// else
				// {
				// 	// //
				// 	// if (CheckEnabledHeadLamp(LampCtrlCmd) == 0U)
				// 	// {
				// 	// 	//
				// 	// 	ExecuteTurnSignalLampFrontLeftControlFunction(0U);
				// 	// 	ExecuteTurnSignalLampRearLeftControlFunction(0U);
				// 	// }
				// }

				//
				if (((LampCtrlCmd >> 2U) & 1U) != 0U)
				{
					//
					ExecuteTurnSignalLampFrontRightControlFunction(1U);
					ExecuteTurnSignalLampRearRightControlFunction(1U);
				}
				// else
				// {
				// 	// //
				// 	// if (CheckEnabledHeadLamp(LampCtrlCmd) == 0U)
				// 	// {
				// 	// 	//
				// 	// 	ExecuteTurnSignalLampFrontRightControlFunction(0U);
				// 	// 	ExecuteTurnSignalLampRearRightControlFunction(0U);
				// 	// }
				// }
			}
			else
			{
				//
				ExecuteTurnSignalLampFlowAnimationPixelation(0U);
				// //
				// if (CheckEnabledHeadLamp(LampCtrlCmd) == 0U)
				// {
				// 	//
				// 	ExecuteTurnSignalLampFrontLeftControlFunction(0U);
				// 	ExecuteTurnSignalLampRearLeftControlFunction(0U);
				// 	//
				// 	ExecuteTurnSignalLampFrontRightControlFunction(0U);
				// 	ExecuteTurnSignalLampRearRightControlFunction(0U);
				// }
			}

			//
			// 전조등 램프 제어 부분
			//
			if (CheckEnabledHeadLamp(LampCtrlCmd) == 3U)
			{
				//
				ExecuteHeadLampLeftControlFunction(1U);
				ExecuteHeadLampRightControlFunction(1U);
			}
			// else
			// {
			// 	//
			// 	if (CheckEnabledTurnSignalLamp(LampCtrlCmd) == 0U)
			// 	{
			// 		// //
			// 		// if (CheckEnabledHeadLamp(LampCtrlCmd) == 0U)
			// 		// {
			// 		// 	//
			// 		// 	ExecuteHeadLampLeftControlFunction(0U);
			// 		// 	ExecuteHeadLampRightControlFunction(0U);
			// 		// }
			// 	}
			// }

			//
			// 브레이크 램프 제어 부분
			//
			if (CheckEnabledBrakeLamp(LampCtrlCmd) != 0U)
			{
				//
				ExecuteBrakeLampLeftControlFunction(1U);
				ExecuteBrakeLampRightControlFunction(1U);
			}
			// else
			// {
			// 	//
			// 	if (CheckEnabledTurnSignalLamp(LampCtrlCmd) == 0U)
			// 	{
			// 		// //
			// 		// if (CheckEnabledHeadLamp(LampCtrlCmd) == 0U)
			// 		// {
			// 		// 	//
			// 		// 	ExecuteBrakeLampLeftControlFunction(0U);
			// 		// 	ExecuteBrakeLampRightControlFunction(0U);
			// 		// }
			// 	}
			// }
		}

		//
		FastLED.show();

		//
		LastFuncExecTickCnt = CurrTickCnt;
	}
}
