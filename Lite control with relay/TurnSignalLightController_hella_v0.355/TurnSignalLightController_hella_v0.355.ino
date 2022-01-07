// 2020-04-22 ~ v0.35

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

static uint8_t TurnSigBlinkModeStatFlag;

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

void ExecuteDaytimeRunningLampControlFunction(const uint8_t _In_CtrlFlag) //데이라이트
{
    //
    if (_In_CtrlFlag == 0U)
    {
        //
        digitalWrite(daylight, HIGH);
    }
    else
    {
        //
        digitalWrite(daylight, LOW);
    }
}
void ExecuteClearanceLampControlFunction(const uint8_t _In_CtrlFlag) //미등
{
    //
    if (_In_CtrlFlag == 0U)
    {
        //
        digitalWrite(stoplightN, HIGH);
    }
    else
    {
        //
        digitalWrite(stoplightN, LOW);
    }
}
void ExecuteTurnSignalBlinkControlFunction(const uint8_t _In_CtrlFlag)
{
    //
    const uint32_t CurrTickCnt = GetTickCount();
    static uint32_t TurnSigBlinkStartTimeTickCntMilliSec;

    //
    if (((_In_CtrlFlag >> 1U) & 1U) == 0U && ((_In_CtrlFlag >> 2U) & 1U) == 0U)
    {
        TurnSigBlinkStartTimeTickCntMilliSec = 0UL;
        TurnSigBlinkModeStatFlag = 0x00U;
    }
    else
    {
        //
        if (TurnSigBlinkStartTimeTickCntMilliSec == 0UL)
        {
            TurnSigBlinkStartTimeTickCntMilliSec = CurrTickCnt;
        }

        //
        if (CurrTickCnt >= (TurnSigBlinkStartTimeTickCntMilliSec + BLINK_DELAY_MILLISECONDS))
        {
            if (TurnSigBlinkModeStatFlag == 0x00U)
            {
                TurnSigBlinkModeStatFlag = 0xFFU;
            }
            else
            {
                TurnSigBlinkModeStatFlag = 0x00U;
            }

            //
            TurnSigBlinkStartTimeTickCntMilliSec = 0UL;
        }
    }
}
void ExecuteTurnSignalLampLeftControlFunction(const uint8_t _In_CtrlFlag) //좌 방향
{
    //
    if (_In_CtrlFlag == 0U)
    {
        //
        digitalWrite(left, HIGH); //방향등 끔
    }
    else
    {
        //
        if (TurnSigBlinkModeStatFlag == 0UL)
        {
            //
            digitalWrite(left, LOW); //방향등 끔
        }
        else
        {
            //
            digitalWrite(left, HIGH); //방향등 켬
        }
    }
}
void ExecuteTurnSignalLampRightControlFunction(const uint8_t _In_CtrlFlag) //우 방향
{
    //
    if (_In_CtrlFlag == 0U)
    {
        //
        digitalWrite(right, HIGH); //방향등 끔
    }
    else
    {
        //
        if (TurnSigBlinkModeStatFlag == 0UL)
        {
            //
            digitalWrite(right, LOW); //방향등 끔
        }
        else
        {
            //
            digitalWrite(right, HIGH); //방향등 켬
        }
    }
}
void ExecuteHeadLampControlFunction(const uint8_t _In_CtrlFlag) //상, 하향등
{
    //
    if (_In_CtrlFlag == 2U)
    {
        //
        digitalWrite(downlight, LOW);
        digitalWrite(uplight, HIGH);
    }
    else if (_In_CtrlFlag == 3U)
    {
        //
        digitalWrite(downlight, LOW);
        digitalWrite(uplight, LOW);
    }
    else
    {
        digitalWrite(downlight, HIGH);
        digitalWrite(uplight, HIGH);
    }
}
void ExecuteBrakeLampControlFunction(const uint8_t _In_CtrlFlag) //정지등
{
    //
    if (_In_CtrlFlag == 0U)
    {
        //
        digitalWrite(stoplight, HIGH);
    }
    else
    {
        //
        digitalWrite(stoplight, LOW);
    }
}
void doorchack() //문열림 확인
{
    if (analogRead(A0) > 10)
    {
        Serial.println(analogRead(A0));
    }
    else
    {
        Serial.println("0");
    }
}

void setup()
{
    //
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(daylight, INPUT);
    pinMode(uplight, INPUT);
    pinMode(downlight, INPUT);
    pinMode(right, INPUT);
    pinMode(left, INPUT);
    pinMode(stoplight, INPUT);
    pinMode(stoplightN, INPUT);

    pinMode(door, INPUT_PULLUP);
    Serial.begin(9600UL);

    // for (;;)
    // {
    // 	//
    // 	ExecuteWelcomeCelemonyFunction();
    // }
    Serial.println("chack_setup");
}
uint8_t doorchacktime = 0;
void loop()
{
    //
    static uint32_t LastFuncExecTickCnt;
    //
    const uint32_t CurrTickCnt = GetTickCount();

    //
    if (CurrTickCnt >= (LastFuncExecTickCnt + 22UL))
    {
        if (doorchacktime > 100)
        {
            doorchack();
            doorchacktime = 0;
        }
        else
        {
            doorchacktime++;
        }
        //
        const uint8_t LampCtrlCmd = ReadLampConrtolCommand();
        //
        if (CheckValidLampControlCommand(LampCtrlCmd) != 0U) //맨앞자리(|000 0000) 확인해서 램프컨트롤 모드인지 확인
        {
            //
            // 미등 램프 제어 부분
            //
            if (CheckEnabledHeadLamp(LampCtrlCmd) != 0U)
            {
                //
                ExecuteDaytimeRunningLampControlFunction(0U);
                ExecuteClearanceLampControlFunction(1U);
            }
            else
            {
                //
                ExecuteDaytimeRunningLampControlFunction(1U);
                ExecuteClearanceLampControlFunction(0U);
            }

            //
            // 턴 시그널 램프 제어 부분
            //
            //
            ExecuteTurnSignalBlinkControlFunction(LampCtrlCmd);
            //
            // if (CheckEnabledTurnSignalLamp(LampCtrlCmd) != 0U)
            {
                //왼쪽
                if (((LampCtrlCmd >> 1U) & 1U) != 0U)
                {
                    //
                    ExecuteTurnSignalLampLeftControlFunction(1U);
                }
                else
                {
                    //
                    ExecuteTurnSignalLampLeftControlFunction(0U);
                }

                // 오른쪽
                if (((LampCtrlCmd >> 2U) & 1U) != 0U)
                {
                    //
                    ExecuteTurnSignalLampRightControlFunction(1U);
                }
                else
                {
                    //
                    ExecuteTurnSignalLampRightControlFunction(0U);
                }
            }

            //
            // 전조등 램프 제어 부분
            //
            if (CheckEnabledHeadLamp(LampCtrlCmd) != 0U) // -11- ---- 인지 판단
            {
                //
                ExecuteHeadLampControlFunction((LampCtrlCmd >> 5U) & 3U);
            }
            else
            {
                //
                ExecuteHeadLampControlFunction(0U);
            }

            //
            // 브레이크 램프 제어 부분
            //
            if (CheckEnabledBrakeLamp(LampCtrlCmd) != 0U)
            {
                //
                ExecuteBrakeLampControlFunction(1U);
            }
            else
            {
                //
                ExecuteBrakeLampControlFunction(0U);
            }
        }

        //
        LastFuncExecTickCnt = CurrTickCnt;
    }
}
