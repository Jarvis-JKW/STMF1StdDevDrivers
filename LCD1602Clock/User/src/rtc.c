/**
  ******************************************************************************
  * @file    /User/src/rtc.c 
  * @author  Jarvis-JKW
  * @version V0.0.3
  * @date    2022年2月9日
  * @brief   RTC Clock
  ******************************************************************************
  */

#include "rtc.h"
#include "buzzer.h"
  
CAL_TypeDef CAL_Structure;
const uint8_t mon_table[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/**
  * @brief  RTC Clock Init and Check
  * @param  None
  * @retval SUCCESS | ERROR
  */
uint8_t RTC_Config(void)
{
    uint8_t temp=0;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);

    /* Check BKP->DR1 to determine if it is the first configuration, 0x5050 is a flag */
    if(BKP_ReadBackupRegister(BKP_DR1) != 0x5050)       //First configuration
    {
        BKP_DeInit();                                   //Reset backup register
        RCC_LSEConfig(RCC_LSE_ON);                      //Enable LSE(32768Hz)

        /* Wait for LSE Ready */
        while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
        {
            if(temp++>250)
                return ERROR;
            delay_ms(10);
        }

        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);  
        RCC_RTCCLKCmd(ENABLE);
        RTC_WaitForLastTask();
        RTC_WaitForSynchro();

        RTC_ITConfig(RTC_IT_SEC, ENABLE);               //Interrupts occur every second
        RTC_WaitForLastTask();

        RTC_EnterConfigMode();
        RTC_SetPrescaler(32767);
        RTC_WaitForLastTask();
        RTC_Set(2022, 1, 31, 17, 39, 25);
        RTC_ExitConfigMode();

        BKP_WriteBackupRegister(BKP_DR1, 0X5050);       //Mark to determine it is configurated
    }
    else                                                //Not the first configuration
    {
        RTC_WaitForSynchro();
        RTC_ITConfig(RTC_IT_SEC, ENABLE);
        RTC_WaitForLastTask();
    }

    RTC_UpdateTime();  //Update time

    return SUCCESS;
}

/**
  * @brief  Check whether it is a leap year
  * @param  A 4-digit year
  * @retval 0: No | 1: Yes
  */
uint8_t isLeapYear(uint16_t year)
{
    return (year%4==0 && year%100) || (year%400==0);
}

/**
  * @brief  RTC set clock
  * @param  calendar & time
  * @retval 0: success | 1: invalid param(s)
  */
uint8_t RTC_Set(uint16_t yyyy, uint8_t MM, uint8_t dd, uint8_t HH, uint8_t mm, uint8_t ss)
{
    uint16_t t;
    uint32_t secCount=0;

    if(yyyy<1970 || yyyy>2099)
        return 1;

    /* Accumulate the passed years' seconds */
    for(t=1970; t<yyyy; t++)
        secCount += isLeapYear(t) ? 366*24*60*60:365*24*60*60;

    /* Accumulate the passed months' seconds of the current year */
    for(t=0; t<MM-1; t++)
    {
        secCount += (uint32_t)mon_table[t] * 86400;
        /* February has an extra day in leap years  */
        if(isLeapYear(yyyy) && t==1)
            secCount += 86400;
    }
    /* Accumulate the passed seconds of the current month */
    secCount += (uint32_t)(dd - 1) * 86400;
    secCount += (uint32_t)HH * 3600;
    secCount += (uint32_t)mm * 60;
    secCount += ss;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);

    RTC_SetCounter(secCount);
    RTC_WaitForLastTask();
    
    return 0;        
}

/**
  * @brief  RTC Set alarm
  * @param  calendar & time
  * @retval 0: success | 1: invalid param(s)
  */
uint8_t RTC_Alarm_Set(uint16_t yyyy, uint8_t MM, uint8_t dd, uint8_t HH, uint8_t mm, uint8_t ss)
{
    uint16_t t;
    uint32_t secCount=0;

    if(yyyy<1970 || yyyy>2099)
        return 1;

    /* Accumulate the passed years' seconds */
    for(t=1970; t<yyyy; t++)
        secCount += isLeapYear(t) ? 366*24*60*60:365*24*60*60;

    /* Accumulate the passed months' seconds of the current year */
    for(t=0; t<MM-1; t++)
    {
        secCount += (uint32_t)mon_table[t] * 24*60*60;
        /* February has an extra day in leap years  */
        if(isLeapYear(yyyy) && t==1)
            secCount += 24*60*60;
    }
    /* Accumulate the passed seconds of the current month */
    secCount += (uint32_t)(dd - 1) * 24*60*60;
    secCount += (uint32_t)HH * 60*60;
    secCount += (uint32_t)mm * 60;
    secCount += ss;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);

    RTC_SetAlarm(secCount);
    RTC_WaitForLastTask();
    
    return 0;
}

/**
  * @brief  RTC update time
  * @param  None
  * @retval 0: success | 1: fail
  */
uint8_t RTC_UpdateTime(void)
{
    uint32_t secCount = RTC_GetCounter();   /* from 1970-1-1 */
    uint32_t dayCount = secCount / (24*60*60);
    uint16_t temp = 1970;                   /* temp->yyyy */

    /* calculate the passed days of the current year */ 
    while(dayCount>=365)
    {
        if(isLeapYear(temp))
        {
            if(dayCount>=366)
                dayCount -= 366;
            else
                break;
        }
        else
            dayCount -= 365;
        temp++;
    }
    CAL_Structure.yyyy = temp;

    temp = 0;                               /* temp->MM_idx */
    /* when accumulate day counts is more than 28 days */
    while(dayCount>=28)
    {
        /* Check if it is leap year & it is in febrary */
        if(isLeapYear(CAL_Structure.yyyy) && temp==1)
        {
            if(dayCount>=29)
                dayCount -= 29;
            else
                break; /* Leap year and it is in the febrary */
        }
        else
        {
            if(dayCount>=mon_table[temp])
                dayCount -= mon_table[temp];
            else
                break;
        }
        temp++;  
    }
    CAL_Structure.MM = temp + 1; /* idx = MM - 1 */
    CAL_Structure.dd = dayCount + 1;

    dayCount = secCount % 86400;
    CAL_Structure.HH = dayCount / 3600;
    CAL_Structure.mm = (dayCount % 3600) / 60;  
    CAL_Structure.ss = (dayCount % 3600) % 60;
    CAL_Structure.week = CalcWeek(CAL_Structure.yyyy, CAL_Structure.MM, CAL_Structure.dd);
    
    return 0;
}     

/**
  * @brief  RTC get week
  * @param  year, month, day
  * @retval 0 ~ 6: Sunday, Monday, Tuesday, Wednsday, Thursday, Friday, Saturday
  * @note   Compute accord to Zeller Formula
  */
uint8_t CalcWeek(uint16_t year,uint8_t month,uint8_t day)
{    
    uint8_t century;
    int16_t week;
    
    if(month<3)
    {
        month += 12;
        year--;
    }
    century = year / 100;
    year %= 100;
    
    week = year + year/4 + century/4 - 2*century + ((uint16_t)26*(month+1))/10 + day - 1;
    
    if(week<0)
        week = 7 - (-week)%7;
    else
        week = week%7;
    
    return week;
}

/**
  * @brief  RTC Clock Test
  * @param  second remain
  */
void COM_RTC_Clock(uint8_t sec)
{
    uint8_t time=0;

    printf("STM32F103ZET6 RTC Clock Test will end in %ds\r\n", sec);
    if(CAL_Structure.ss+sec<60)
        sec += CAL_Structure.ss;
    else
        sec += CAL_Structure.ss-60;

    while(time!=sec)
    {
        if(time!=CAL_Structure.ss)
        {
            time = CAL_Structure.ss;
            printf("%d-%d-%d %d:%d:%d\r\n",
            CAL_Structure.yyyy, CAL_Structure.MM, CAL_Structure.dd,
            CAL_Structure.HH,   CAL_Structure.mm, CAL_Structure.ss);
        }
    }
}

/* RTC Interruption ----------------------------------------------------------*/
/**
  * @brief  This function handles RTC Interruption.
  */
void RTC_IRQHandler(void)
{
    /* Triggerd per second */
    if(RTC_GetITStatus(RTC_IT_SEC) != RESET)
        RTC_UpdateTime();

    /* Alarm interruption */
    if(RTC_GetITStatus(RTC_IT_ALR) != RESET)
    {
        RTC_ClearITPendingBit(RTC_IT_ALR);
        RTC_UpdateTime();
        beep(3);
    }

    RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);//清闹钟中断
    RTC_WaitForLastTask();
}

/******************************** END OF FILE *********************************/
