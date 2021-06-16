/*
 *  Protocol COMMAND WORDS FOR LFAWF
 *
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
*/

#define lfwaf_tick_duration 5

#define cmdSETHNAME    "SETHNAME"       // Set Name of LFWAF for wifi network

#define cmdGOTOFNUM    "GOTOFNUM"       // Goto Filter num   GOTOFNUM    {Filter Num}

#define cmdSETFNAME    "SETFNAME"       // Set Filter name   SETFWNAME   {Filter Num} {Filter Name}

#define cmdSETFWSPEED  "SETFWSPEED"     // Set Filter Speed  SETFWSPEED  {Speed(0-255)}

#define cmdSETFOSPEED  "SETFOSPEED"     // Set Focuser Speed SETFOSPEED  {Speed(0-255)} 

#define cmdFOCUSER_IN  "FOCUSER_IN"     // Focuser In        FOCUSER_IN  {number of ticks}

#define cmdFOCUSER_OUT "FOCUSER_OUT"    // Focuser Out       FOCUSER_OUT {number of ticks}

#define cmdSTOPFOCUSER  "STOPFOCUS"     // Abort Focuser move

#define cmdSETWIFISSID "SETWIFISSID"    // Set Wifi SSIDs and Pwds
#define cmdSETWIFIPREF "SETWIFIPREF"    // Set Wifi selection preference