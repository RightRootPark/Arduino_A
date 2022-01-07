// 2020-04-22 ~

#define GetTickCount millis

#define BLINK_DELAY_MILLISECONDS 450UL

#define daylight 11
#define uplight 2
#define downlight 3
#define right 4
#define left 5
#define stoplight 6
#define stoplightN 7
#define inside 8

#define door 9

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

	//
	//
	return Result;
}

void ExecuteDaytimeRunningLampLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	if (_In_CtrlFlag == 0U)
	{
		//
	}
	else
	{
		//
	}
}
void ExecuteDaytimeRunningLampRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	if (_In_CtrlFlag == 0U)
	{
		//
	}
	else
	{
		//
	}
}
void ExecuteDaytimeRearRunningLampLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	if (_In_CtrlFlag == 0U)
	{
		//
	}
	else
	{
		//
	}
}
void ExecuteDaytimeRearRunningLampRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	if (_In_CtrlFlag == 0U)
	{
		//
	}
	else
	{
		//
	}
}
void ExecuteClearanceLampFrontLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	if (_In_CtrlFlag == 0U)
	{
		//
	}
	else
	{
		//
	}
}
void ExecuteClearanceLampFrontRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	if (_In_CtrlFlag == 0U)
	{
		//
	}
	else
	{
		//
	}
}
void ExecuteClearanceLampRearLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	if (_In_CtrlFlag == 0U)
	{
		//
	}
	else
	{
		//
	}
}
void ExecuteClearanceLampRearRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	if (_In_CtrlFlag == 0U)
	{
		//
	}
	else
	{
		//
	}
}
void ExecuteTurnSignalLampFrontLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	const uint32_t CurrTickCnt = GetTickCount();
	static uint32_t EvtStartTimeTickCntMilliSec;
	static uint8_t BlinkModeStat;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		EvtStartTimeTickCntMilliSec = 0UL;
	}
	else
	{
		//
		if (EvtStartTimeTickCntMilliSec == 0UL)
		{
			EvtStartTimeTickCntMilliSec = CurrTickCnt;

			//
			if (BlinkModeStat == 0UL)
			{
				BlinkModeStat = 1UL;
			}
			else
			{
				BlinkModeStat = 0UL;
			}
		}

		//
		if (CurrTickCnt >= (EvtStartTimeTickCntMilliSec + BLINK_DELAY_MILLISECONDS))
		{
			//
			if (BlinkModeStat == 0UL)
			{
				//
				digitalWrite(left, HIGH);
			}
			else
			{
				//
				digitalWrite(left, LOW);
			}

			//
			EvtStartTimeTickCntMilliSec = 0UL;
		}
	}
}
void ExecuteTurnSignalLampFrontRightControlFunction(const uint8_t _In_CtrlFlag)
{ //
	const uint32_t CurrTickCnt = GetTickCount();
	static uint32_t EvtStartTimeTickCntMilliSec;
	static uint8_t BlinkModeStat;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		EvtStartTimeTickCntMilliSec = 0UL;
	}
	else
	{
		//
		if (EvtStartTimeTickCntMilliSec == 0UL)
		{
			EvtStartTimeTickCntMilliSec = CurrTickCnt;

			//
			if (BlinkModeStat == 0UL)
			{
				BlinkModeStat = 1UL;
			}
			else
			{
				BlinkModeStat = 0UL;
			}
		}

		//
		if (CurrTickCnt >= (EvtStartTimeTickCntMilliSec + BLINK_DELAY_MILLISECONDS))
		{
			//
			if (BlinkModeStat == 0UL)
			{
				//
				digitalWrite(right, HIGH);
			}
			else
			{
				//
				digitalWrite(right, LOW);
			}

			//
			EvtStartTimeTickCntMilliSec = 0UL;
		}
	}
}
void ExecuteTurnSignalLampRearLeftControlFunction(const uint8_t _In_CtrlFlag)
{ //
	const uint32_t CurrTickCnt = GetTickCount();
	static uint32_t EvtStartTimeTickCntMilliSec;
	static uint8_t BlinkModeStat;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		EvtStartTimeTickCntMilliSec = 0UL;
	}
	else
	{
		//
		if (EvtStartTimeTickCntMilliSec == 0UL)
		{
			EvtStartTimeTickCntMilliSec = CurrTickCnt;

			//
			if (BlinkModeStat == 0UL)
			{
				BlinkModeStat = 1UL;
			}
			else
			{
				BlinkModeStat = 0UL;
			}
		}

		//
		if (CurrTickCnt >= (EvtStartTimeTickCntMilliSec + BLINK_DELAY_MILLISECONDS))
		{
			//
			if (BlinkModeStat == 0UL)
			{
				//
			}
			else
			{
				//
			}

			//
			EvtStartTimeTickCntMilliSec = 0UL;
		}
	}
}
void ExecuteTurnSignalLampRearRightControlFunction(const uint8_t _In_CtrlFlag)
{ //
	const uint32_t CurrTickCnt = GetTickCount();
	static uint32_t EvtStartTimeTickCntMilliSec;
	static uint8_t BlinkModeStat;

	//
	if (_In_CtrlFlag == 0U)
	{
		//
		EvtStartTimeTickCntMilliSec = 0UL;
	}
	else
	{
		//
		if (EvtStartTimeTickCntMilliSec == 0UL)
		{
			EvtStartTimeTickCntMilliSec = CurrTickCnt;

			//
			if (BlinkModeStat == 0UL)
			{
				BlinkModeStat = 1UL;
			}
			else
			{
				BlinkModeStat = 0UL;
			}
		}

		//
		if (CurrTickCnt >= (EvtStartTimeTickCntMilliSec + BLINK_DELAY_MILLISECONDS))
		{
			//
			if (BlinkModeStat == 0UL)
			{
				//
			}
			else
			{
				//
			}

			//
			EvtStartTimeTickCntMilliSec = 0UL;
		}
	}
}
void ExecuteHeadLampLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	if (_In_CtrlFlag == 0U)
	{
		//
	}
	else
	{
		//
	}
}
void ExecuteHeadLampRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	if (_In_CtrlFlag == 0U)
	{
		//
	}
	else
	{
		//
	}
}
void ExecuteBrakeLampLeftControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	if (_In_CtrlFlag == 0U)
	{
		//
	}
	else
	{
		//
	}
}
void ExecuteBrakeLampRightControlFunction(const uint8_t _In_CtrlFlag)
{
	//
	if (_In_CtrlFlag == 0U)
	{
		//
	}
	else
	{
		//
	}
}

void setup()
{
	//
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(daylight, OUTPUT);
	pinMode(uplight, OUTPUT);
	pinMode(downlight, OUTPUT);
	pinMode(right, OUTPUT);
	pinMode(left, OUTPUT);
	pinMode(stoplight, OUTPUT);
	pinMode(stoplightN, OUTPUT);

	pinMode(door, INPUT_PULLUP);
	Serial.begin(9600UL);

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
				if (((LampCtrlCmd >> 1U) & 1U) != 0U)
				{
					//
					ExecuteTurnSignalLampFrontLeftControlFunction(1U);
					ExecuteTurnSignalLampRearLeftControlFunction(1U);
				}

				//
				if (((LampCtrlCmd >> 2U) & 1U) != 0U)
				{
					//
					ExecuteTurnSignalLampFrontRightControlFunction(1U);
					ExecuteTurnSignalLampRearRightControlFunction(1U);
				}
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

			//
			// 브레이크 램프 제어 부분
			//
			if (CheckEnabledBrakeLamp(LampCtrlCmd) != 0U)
			{
				//
				ExecuteBrakeLampLeftControlFunction(1U);
				ExecuteBrakeLampRightControlFunction(1U);
			}
		}

		//
		LastFuncExecTickCnt = CurrTickCnt;
	}
}
