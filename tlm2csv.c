#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <string.h>

#define UINT64 unsigned long
#define UINT32 unsigned int
#define INT32  signed   int
#define UINT16 unsigned short
#define INT16  signed   short
#define UINT8  unsigned char
#define INT8   signed   char

//
// Correct any read UINT16 for proper byte order for this machine.
// May replace with nothing if this machine has proper byte order 
// matching TLM file format.
//
UINT16 REORDERUINT16(UINT16 in)
{
       UINT8 b1   = (in >> 8) & 0xff;
       UINT8 b2   = (in & 0xff);
       UINT16 out = (b2 << 8) | b1;
       return(out);
}

#include "spektrumTelemetrySensors.h"

/*
 * GIven the device id we will return its name. Note the macro trick using # to
 * replace the argument with its string name.
 */
const char *deviceName(int device)
{     switch(device) {
#define CASERETURN(__ids) case __ids: return(#__ids);
        CASERETURN(TELE_DEVICE_NODATA)
        CASERETURN(TELE_DEVICE_VOLTAGE)
        CASERETURN(TELE_DEVICE_TEMPERATURE)
        CASERETURN(TELE_DEVICE_AMPS)
        CASERETURN(TELE_DEVICE_RSV_04)
        CASERETURN(TELE_DEVICE_FLITECTRL)
        CASERETURN(TELE_DEVICE_RSV_06)
        CASERETURN(TELE_DEVICE_RSV_07)
        CASERETURN(TELE_DEVICE_RSV_08)
        CASERETURN(TELE_DEVICE_PBOX	)
        CASERETURN(TELE_DEVICE_LAPTIMER	)
        CASERETURN(TELE_DEVICE_TEXTGEN)
        CASERETURN(TELE_DEVICE_VTX	)
        CASERETURN(TELE_DEVICE_RSV_0E)
        CASERETURN(TELE_DEVICE_RSV_0F)
        CASERETURN(TELE_DEVICE_RSV_10)
        CASERETURN(TELE_DEVICE_AIRSPEED	)
        CASERETURN(TELE_DEVICE_ALTITUDE	)
        CASERETURN(TELE_DEVICE_RSV_13)
        CASERETURN(TELE_DEVICE_GMETER)
        CASERETURN(TELE_DEVICE_JETCAT)
        CASERETURN(TELE_DEVICE_GPS_LOC)
        CASERETURN(TELE_DEVICE_GPS_STATS)
        CASERETURN(TELE_DEVICE_RX_MAH	)
        CASERETURN(TELE_DEVICE_JETCAT_2)
        CASERETURN(TELE_DEVICE_GYRO)
        CASERETURN(TELE_DEVICE_ATTMAG	)
        CASERETURN(TELE_DEVICE_TILT)
        CASERETURN(TELE_DEVICE_RSV_1D	)
        CASERETURN(TELE_DEVICE_AS6X_GAIN)
        CASERETURN(TELE_DEVICE_AS3X_LEGACYGAIN	)
        CASERETURN(TELE_DEVICE_ESC	)
        CASERETURN(TELE_DEVICE_RSV_21		)
        CASERETURN(TELE_DEVICE_FUEL	)
        CASERETURN(TELE_DEVICE_RSV_23)
        CASERETURN(TELE_DEVICE_ALPHA6)
        CASERETURN(TELE_DEVICE_RSV_25)
        CASERETURN(TELE_DEVICE_GPS_BINARY	)
        CASERETURN(TELE_DEVICE_REMOTE_ID)
        CASERETURN(TELE_DEVICE_RSV_28)
        CASERETURN(TELE_DEVICE_RSV_29)
        CASERETURN(TELE_DEVICE_RSV_2A)
        CASERETURN(TELE_DEVICE_RSV_2B)
        CASERETURN(TELE_DEVICE_RSV_2C)
        CASERETURN(TELE_DEVICE_RSV_2D)
        CASERETURN(TELE_DEVICE_RSV_2E)
        CASERETURN(TELE_DEVICE_RSV_2F)
        CASERETURN(TELE_DEVICE_RSV_33	)
        CASERETURN(TELE_DEVICE_FP_MAH)
        CASERETURN(TELE_DEVICE_RSV_35)
        CASERETURN(TELE_DEVICE_DIGITAL_AIR	)
        CASERETURN(TELE_DEVICE_RSV_37)
        CASERETURN(TELE_DEVICE_STRAIN)
        CASERETURN(TELE_DEVICE_RSV_39)
        CASERETURN(TELE_DEVICE_LIPOMON)
        CASERETURN(TELE_DEVICE_RSV_3B	)
        CASERETURN(TELE_DEVICE_RSV_3C)
        CASERETURN(TELE_DEVICE_RSV_3D)
        CASERETURN(TELE_DEVICE_RSV_3E)
        CASERETURN(TELE_DEVICE_LIPOMON_14)
        CASERETURN(TELE_DEVICE_VARIO_S)
        CASERETURN(TELE_DEVICE_RSV_41)
        CASERETURN(TELE_DEVICE_SMARTBATT	)
        CASERETURN(TELE_DEVICE_RSV_43)
        CASERETURN(TELE_DEVICE_RSV_44)
        CASERETURN(TELE_DEVICE_RSV_45)
        CASERETURN(TELE_DEVICE_RSV_46)
        CASERETURN(TELE_DEVICE_RSV_47)
        CASERETURN(TELE_DEVICE_RSV_48)
        CASERETURN(TELE_DEVICE_RSV_49)
        CASERETURN(TELE_DEVICE_RSV_4A)
        CASERETURN(TELE_DEVICE_RSV_4B)
        CASERETURN(TELE_DEVICE_RSV_4C)
        CASERETURN(TELE_DEVICE_RSV_4D)
        CASERETURN(TELE_DEVICE_RSV_4E)
        CASERETURN(TELE_DEVICE_RSV_4F)
        CASERETURN(TELE_DEVICE_USER_16SU)
        CASERETURN(TELE_DEVICE_RSV_51	)
        CASERETURN(TELE_DEVICE_USER_16SU32U)
        CASERETURN(TELE_DEVICE_RSV_53)
        CASERETURN(TELE_DEVICE_USER_16SU32S)
        CASERETURN(TELE_DEVICE_RSV_55)
        CASERETURN(TELE_DEVICE_USER_16U32SU)
        CASERETURN(TELE_DEVICE_RSV_57	)
        CASERETURN(TELE_DEVICE_RSV_58)
        CASERETURN(TELE_DEVICE_MULTICYLINDER)
        CASERETURN(TELE_DEVICE_MULTIENGINE	)
        CASERETURN(TELE_DEVICE_RSV_5B)
        CASERETURN(TELE_DEVICE_RSV_5C)
        CASERETURN(TELE_DEVICE_RSV_5D)
        CASERETURN(TELE_DEVICE_RSV_5E)
        CASERETURN(TELE_DEVICE_RSV_5F)
        CASERETURN(TELE_DEVICE_VSPEAK)
        CASERETURN(TELE_DEVICE_SMOKE_EL	)
        CASERETURN(TELE_DEVICE_CROSSFIRE)
        CASERETURN(TELE_DEVICE_RSV_63)
        CASERETURN(TELE_DEVICE_RSV_64)
        CASERETURN(TELE_DEVICE_RSV_65)
        CASERETURN(TELE_DEVICE_EXTRF)
        CASERETURN(TELE_DEVICE_RSV_67)
        CASERETURN(TELE_DEVICE_RSV_68)
        CASERETURN(TELE_DEVICE_RSV_69)
        CASERETURN(TELE_DEVICE_RSV_6A)
        CASERETURN(TELE_DEVICE_RSV_6C)
        CASERETURN(TELE_DEVICE_RSV_6D)
        CASERETURN(TELE_DEVICE_RSV_6E)
        CASERETURN(TELE_DEVICE_RSV_6F)
        CASERETURN(TELE_DEVICE_RSV_70)
        CASERETURN(TELE_XRF_LINKSTATUS)
        CASERETURN(TELE_DEVICE_RSV_72)
        CASERETURN(TELE_DEVICE_RSV_73)
        CASERETURN(TELE_DEVICE_RSV_74)
        CASERETURN(TELE_DEVICE_RSV_75)
        CASERETURN(TELE_DEVICE_RSV_76)
        CASERETURN(TELE_DEVICE_RSV_77)
        CASERETURN(TELE_DEVICE_RSV_78)
        CASERETURN(TELE_DEVICE_RSV_79)
        CASERETURN(TELE_DEVICE_RSV_7A)
        CASERETURN(TELE_DEVICE_ALT_ZERO)
        CASERETURN(TELE_DEVICE_RTC		)
        CASERETURN(TELE_DEVICE_RPM	)
        CASERETURN(TELE_DEVICE_QOS	)
      }
      return("TELE_DEVICE_UNKNOWN");
}

/*
 * Format error of some kind. Exit and say what happened.
 */
void tlmerror(const char *s)
{    fprintf(stdout, "OOPS %s\n", s);
     exit(-1);
}

/*
 * Headers are 4 x 0xff bytes.
 */
int  isheader(unsigned char *b)
{    return((*b++ == 0xff) && (*b++ == 0xff) && (*b++ == 0xff) && (*b == 0xff));
}

/*
 * To monitor progress.
 */
void logit(char *s, unsigned aux)
{    fprintf(stdout, s, aux);
}

/*
 * To monitor progress.
 */
void logitf(char *s, float f)
{    fprintf(stdout, s, f);
}

/*
 * To monitor progress.
 */
void logits(char *s, const char *str)
{    fprintf(stdout, s, str);
}

/*
 * Dump the buffer in a readable format
 */
void dumpit(unsigned char b[], int len)
{    for(int i = 0; i < len; i++) 
         fprintf(stdout, "%02d|", i);
     fprintf(stdout,"\n");
     //
     for(int i = 0; i < len; i++) 
         fprintf(stdout, "%02x|", b[i]);
     fprintf(stdout,"\n");
}
 
/*
 * We are in either header or sensor processing state, we also trak how
 * many of each we have seen, useful because 0 is important.
 */
#define PROCESSING_SENSORS 0
#define PROCESSING_HEADERS 1
int state       = PROCESSING_SENSORS;
int num_headers = 0;
int num_sensors = 0;

//
// These are the things we decode.
//
unsigned char buffer[100];
char          model_name[11];

/*
 * Ensure sizes are correct for the included TLM files from SPEKTRUM. 
 */
void sanity()
{    UINT64 t64;
     if (sizeof(t64) != 64/8) tlmerror("sizeof t64 not 64/8 bytes\n");
     UINT32 t32;
     if (sizeof(t32) != 32/8) tlmerror("sizeof t32 not 32/8 bytes\n");
     UINT16 t16;
     if (sizeof(t16) != 16/8) tlmerror("sizeof t16 not 16/8 bytes\n");
     UINT8 t8;
     if (sizeof(t8)  != 1   ) tlmerror("sizeof t8 not 8/8 bytes\n");
     const char *vname = deviceName(TELE_DEVICE_VOLTAGE);
     if (strcmp(vname, "TELE_DEVICE_VOLTAGE") != 0) tlmerror(vname);
}

/*
 * Convert Spectrum binary .TLM file format to comma asci separated values .CSV
 */
int main(int argc, char* argv[])
{
  //
  sanity();

  /* Parse the command line arguments. */
  if (argc != 2) {
      fprintf(stdout, "Usage: %s <inptTLMfile> > outputCSVfile\n", argv[0]);
      return(-1);
  }

  FILE *fd = fopen(argv[1], "rb");
  if (fd == NULL) {
      fprintf(stdout,"%s cannot opent TLM file '%s'\n", argv[0], argv[1]);
      return(-2);
  }

  while(!feof(fd)) {
      if (fread(&buffer[0], 4, 1, fd) != 1) tlmerror("cant read header");
      if (isheader(buffer)) {
	  state = PROCESSING_HEADERS;
	  num_sensors  = 0;
	  num_headers += 1;
          if (fread(&buffer[4], 32, 1, fd) != 1) tlmerror("cant read TX 36 byte header block");
	  if (num_headers == 1) {
	      logit("got first header [", 0);
	      strncpy(model_name, (char *)&buffer[12], sizeof(model_name)-1);
              logit(model_name, 0);
	      logit("]\n", 0);
	  } else { 
	      unsigned short fivesix = ((unsigned)buffer[4] << 8) | (unsigned) buffer[5];
              switch(fivesix) {
		      case 0x0101 : logit("Volts Sensor Enabled\n", 0);
				    break;
                      case 0x0202 : logit("Temp Sensor Enabled\n", 0);
				    break;
                      case 0x0303 : logit("Amps Sensor Enabled\n", 0);
				    break;
                      case 0x0a0a : logit("PBox Enabled\n", 0);
				    break;
                      case 0x1111 : logit("Speed Sensor Enabled\n", 0);
				    break;
                      case 0x1212 : logit("Altimeter Sensor Enabled\n", 0);
				    break;
                      case 0x1414 : logit("GForce Sensor Enabled\n", 0);
				    break;
                      case 0x1515 : logit("Jetpac Enabled (option only on the DX18 and DX10t\n", 0);
				    break;
                      case 0x1616 : logit("GPS Sensor Enabled\n", 0);
				    break;
		      case 0x7e7e : logit("RPM Sensor Enabled\n", 0);
                                    break;
		      case 0x1717 : logit("end of headers\n", fivesix);
		  	            break;
	              default     : logit("unknown 5/6 bytes in header %x\n", fivesix);
			            break;
              }
	  }
      } else {
	  state = PROCESSING_SENSORS;
	  num_headers  = 0;
	  num_sensors += 1;
          if (fread(&buffer[4], 16, 1, fd) != 1) tlmerror("cant read sensor 20 byte block");
	  //dumpit(&buffer[0], 20);

	  //
	  // According to Spektrum header file 
	  //
          UINT8 identifier = buffer[4];
	  UINT8 sid        = buffer[5];
	  if (sid != 0) identifier = sid;

          logits("%s\n", deviceName(identifier));

	  UN_TELEMETRY *un = (UN_TELEMETRY *) &buffer[4];

	  switch(identifier) {
	          //
	          case TELE_DEVICE_VARIO_S:
			     logitf("  got u.varioSimple.altitude %f m\n", REORDERUINT16(un->varioSimple.altitude) * 0.1);
			     break;
	          //
	          case TELE_DEVICE_QOS:
			     logit( "  got u.rx_loss %u\n", REORDERUINT16(un->qos.F));
			     logit( "  got u.rx_hold %u\n", REORDERUINT16(un->qos.H));
			     logitf("  got u.rx_volt %f V\n", REORDERUINT16(un->qos.rxVoltage)*0.01);
			     break;
	          //
	          case TELE_DEVICE_RPM:
			     //logit("  got u.microsecods(rpm) %u\n", REORDERUINT16(un->rpm.microseconds));
			     //logit("  got u.volts %u\n", REORDERUINT16(un->rpm.volts));
			     //logit("  got u.volts %u\n", REORDERUINT16(un->rpm.temperature));
			     break;
	          //
	          case TELE_DEVICE_RSV_7A: // ??
			     break;
	          //
	          case TELE_DEVICE_VOLTAGE:
			     logitf("  got u.hv.volts %f v\n", REORDERUINT16(un->hv.volts) * 0.01);
			     break;
	          //
	          case TELE_DEVICE_SMARTBATT:
			     logit("  got u.smartbatt_header.typeChannel %x\n", un->smartBatt_header.typeChannel);

                             UINT8 channel = un->smartBatt_header.typeChannel & 0x0f;
                             UINT8 type    = un->smartBatt_header.typeChannel >> 4;

			     logit("     got u.smartBatt_header.channel %x v\n", channel);
			     logit("     got u.smartBatt_header.type %x v\n", type);
			     break;
	          //
	          case TELE_DEVICE_GYRO:
			     break;
	          //
	          case TELE_DEVICE_GMETER:
			     break;
	          //
	          case TELE_DEVICE_FLITECTRL:
			     break;
	          //
	          case TELE_DEVICE_TEXTGEN:
			     logits("  got u.textgen.text [%s]\n", un->textgen.text);
			     break;
	          //
	          case TELE_DEVICE_ESC:
			     logit( "  got u.esc.RPM  %u (elec)\n", REORDERUINT16(un->esc.RPM)*10);
			     logitf("  got u.esc.voltsInput %f v\n", REORDERUINT16(un->esc.voltsInput) * 0.01);
			     logitf("  got u.esc.tempFET %f C\n", REORDERUINT16(un->esc.tempFET) * 0.1);
			     logitf("  got u.esc.currentMotor %f A\n", REORDERUINT16(un->esc.currentMotor) * 0.01);
			     logitf("  got u.esc.tempBEC %f C\n", REORDERUINT16(un->esc.tempBEC) * 0.1);
			     logitf("  got u.esc.currentBEC %f A\n", un->esc.currentBEC * 0.1);
			     logitf("  got u.esc.voltsBEC %f \n", un->esc.voltsBEC *0.05);
			     logitf("  got u.esc.throttle %f %%\n", un->esc.throttle * 0.5);
			     logitf("  got u.esc.power %f %%\n", un->esc.powerOut * 0.5);
			     break;
          }
      }
  }
  return 0;
}

