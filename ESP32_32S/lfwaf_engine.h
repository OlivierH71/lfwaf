/*
 *  Engine Processor class  FOR LFWAF on ESP32-32S
 *  This class manage motors as well as events coming from buttons and
 *  and communication channels (Wifi)
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
*/
#ifndef lfwaf_engine_h
#define lfwaf_engine_h

#include <Ticker.h>    // We use Ticker rather than Timer. Ticker is easier to program
#include "lfwaf_logger.h"
#include "lfwaf_settings.h"
// #include "cntBtn.h"
#include "HW-354.h"
#include "DirectMotor.h""

/*************************************************************
  Motor Definitions
*************************************************************/
#define motW_L_pin  26
#define motW_R_pin  27
#define motF_L_pin  32
#define motF_R_pin  33

#define motorMinValue 80
#define motorMaxValue 255

#define CHANNEL_W 0
#define CHANNEL_F 1

/*************************************************************
  Manual Buttons Definitions
*************************************************************/
#define btnW_L_pin  19
#define btnW_R_pin  21
#define btnF_L_pin  22
#define btnF_R_pin  23
#define btnEOC_up_pin 5
#define btnEOC_dn_pin 18

class lfwaf_engine {
public:
    int speedW = motorMinValue;
    int speedF = motorMinValue;
    int currentFilter = 1;
    // int wheelMove = 0;
    lfwaf_logger *_log;
    lfwaf_settings *_settings;
    // cntBtn *btnW_L,*btnW_R, *btnF_L, *btnF_R, *btnEOC_up, *btnEOC_dn;
    void focuserMove(boolean toUp);
    void focuserStop();
    void filterWheelMoveTo(int wheelMove);
    void filterWheelStop();
    void checkManualBtns();
    HW354 *motorWheel = new HW354(motW_L_pin, motW_R_pin, CHANNEL_W);
    HW354 *motorFocus = new HW354(motF_L_pin, motF_R_pin, CHANNEL_F);
    //DirectMotor *motorFocus = new DirectMotor(motF_L_pin, motF_R_pin, CHANNEL_F);
    lfwaf_engine(lfwaf_logger *log, lfwaf_settings *settings);
private:
    bool focuser_moving = false;
    bool filterw_moving = false;
    Ticker  wheelMovedTicker;
};

 /*  void btnPressedHandler(cntBtn *btn);
   void btnReleasedHandler(cntBtn *btn); */

#endif
