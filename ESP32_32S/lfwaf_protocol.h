/*
 *  Protocol COMMAND WORDS FOR LFAWF
 *
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
*/

#define lfwaf_tick_duration 5

#define cmdSETHOSTNAME  "SETHOSTNAME"       //* Set Name of LFWAF for wifi network
#define cmdGETHOSTNAME  "GETHOSTNAME"       //* returns Host Name recorded

#define cmdGOTOFILTNUM  "GOTOFILTNUM"       //* Goto Filter num   GOTOFNUM    {Filter Num}

#define cmdSETFILTNAME  "SETFILTNAME"       //* Set Filter name   SETFWNAME   {Filter Num} {Filter Name}

#define cmdSETFWSPEED   "SETFWSPEED"        //* Set Filter Speed  SETFWSPEED  {Speed(0-255)}

#define cmdSETFOSPEED   "SETFOSPEED"        //* Set Focuser Speed SETFOSPEED  {Speed(0-255)}
#define cmdGETFOSPEED   "GETFOSPEED"        //* Gets Focuser Speed 

#define cmdFOCUSER_IN   "FOCUSER_IN"        //* Focuser In        FOCUSER_IN  {number of ticks}
#define cmdFOCUSER_OUT  "FOCUSER_OUT"       //* Focuser Out       FOCUSER_OUT {number of ticks}
#define cmdISFOCUSER_M  "ISFOCUSER_M"       //* Check if Focuser is moving, answer can be "YES" or "NO"
#define cmdSTOPFOCUSER  "STOPFOCUSER"       //* Abort Focuser move

#define cmdSETWIFISSID  "SETWIFISSID"       //* Set Wifi SSIDs and Pwds
#define cmdGETWIFISSID  "GETWIFISSID"       //* gets Wifi SSIDs from device

#define cmdSETWIFIPREF  "SETWIFIPREF"       //* Set Wifi selection preference
#define cmdGETWIFIPREF  "GETWIFIPREF"       //* gets Wifi selection preference

#define cmdGETFOMAXPOS  "GETFOMAXPOS"       //- gets the device max position capability
#define cmdSETFOMAXPOS  "SETFOMAXPOS"       //- sets the device max position capability

#define cmdGETFOCUSPOS  "GETFOCUSPOS"       //- gets device current position
#define cmdSETFOCUSPOS  "SETFOCUSPOS"       //- sets device current position

#define cmdACKNOWLEDGE  "ACKNOWLEDGE\n"     // Start communication