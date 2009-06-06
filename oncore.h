/*
 * oncore.h
 *
 *  Created on: May 30, 2009
 *      Author: Andrew Hills <ahills@ecs.umass.edu>
 *
 *  Supports Motorola Oncore M12+ commands.
 */

#ifndef ONCORE_H_
#define ONCORE_H_

/* Unsigned conversion operations */
/* WARNING: _getintN(x) assumes the following:						*
 * 1)	x is a pointer to a char array with at least N elements		*
 * 2)	x is an expression including some sort of increasing index	*
 * 3)	characters are eight bits wide								*/
#define _getint4(x)			((*(x) << 24) + (*(x) << 16) + (*(x) << 8) + *(x))
#define _getint3(x)			((*(x) << 16) + (*(x) << 8) + *(x))
#define _getint2(x)			((*(x) << 8) + *(x))

/* ONCORE constants */
#define ONCORE_CHANNELS		12	/* Oncore M12+ has twelve channels */
#define ONCORE_TAG_SIZE		6	/* Number of bytes in ID tag */
enum { ONCORE_MSG_INVALID, ONCORE_MSG_VALID };	/* For the valid field of structs */

/* Length of messages, in bytes (including first four) */
	/* Minimum length of any message */
#define ONCORE_LENGTH_MIN		7
	/* Mask angle */
#define ONCORE_LENGTH_CMD_Ag	8
#define ONCORE_LENGTH_RSP_Ag	8
	/* Ignore list */
#define ONCORE_LENGTH_CMD_Am	12
#define ONCORE_LENGTH_RSP_Am	12
	/* Position lock parameters */
#define ONCORE_LENGTH_CMD_AM	11
#define ONCORE_LENGTH_RSP_AM	11
	/* Marine filter select */
#define ONCORE_LENGTH_CMD_AN	8
#define ONCORE_LENGTH_RSP_AN	8
	/* Datum select */
#define ONCORE_LENGTH_CMD_Ao	8
#define ONCORE_LENGTH_RSP_Ao	25
	/* RTCM port baud rate select */
#define ONCORE_LENGTH_CMD_AO	8
#define ONCORE_LENGTH_RSP_AO	8
	/* Define user datum message */
#define ONCORE_LENGTH_CMD_Ap	25
#define ONCORE_LENGTH_RSP_Ap	25
	/* Pulse mode select */
#define ONCORE_LENGTH_CMD_AP	8
#define ONCORE_LENGTH_RSP_AP	8
	/* Ionospheric correction select */
#define ONCORE_LENGTH_CMD_Aq	8
#define ONCORE_LENGTH_RSP_Aq	8
	/* Position filter select */
#define ONCORE_LENGTH_CMD_AQ	8
#define ONCORE_LENGTH_RSP_AQ	8
	/* Position hold parameters */
#define ONCORE_LENGTH_CMD_As	20
#define ONCORE_LENGTH_RSP_As	20
	/* Position lock select */
#define ONCORE_LENGTH_CMD_AS	8
#define ONCORE_LENGTH_RSP_AS	8
	/* Time correction select */
#define ONCORE_LENGTH_CMD_Aw	8
#define ONCORE_LENGTH_RSP_Aw	8
	/* 1PPS time offset */
#define ONCORE_LENGTH_CMD_Ay	11
#define ONCORE_LENGTH_RSP_Ay	11
	/* 1PPS cable delay correction */
#define ONCORE_LENGTH_CMD_Az	11
#define ONCORE_LENGTH_RSP_Az	11
	/* Visible satellite data */
#define ONCORE_LENGTH_CMD_Bb	8
#define ONCORE_LENGTH_RSP_Bb	92
	/* Almanac status */
#define ONCORE_LENGTH_CMD_Bd	8
#define ONCORE_LENGTH_RSP_Bd	23
	/* Almanac data request */
#define ONCORE_LENGTH_CMD_Be	8
#define ONCORE_LENGTH_RSP_Cb	33
	/* Ephemeris data input */
#define ONCORE_LENGTH_CMD_Bf	80
#define ONCORE_LENGTH_RSP_Cc	80
	/* Pseudo-range correction output request */
#define ONCORE_LENGTH_CMD_Bh	8
#define ONCORE_LENGTH_RSP_Ce	52
	/* Leap second status */
#define ONCORE_LENGTH_CMD_Bj	8
#define ONCORE_LENGTH_RSP_Bj	8
	/* UTC offset output */
#define ONCORE_LENGTH_CMD_Bo	8
#define ONCORE_LENGTH_RSP_Bo	8
	/* UTC/ionospheric data */
#define ONCORE_LENGTH_CMD_Bp	8
#define ONCORE_LENGTH_CMD_Co	29
#define ONCORE_LENGTH_RSP_Co	29
	/* Almanac data input */
#define ONCORE_LENGTH_CMD_Cb	33
#define ONCORE_LENGTH_RSP_Ch	9
	/* Pseudo-range correction data input */
#define ONCORE_LENGTH_CMD_Ce	52
#define ONCORE_LENGTH_RSP_Ck	7
	/* Set to defaults */
#define ONCORE_LENGTH_CMD_Cf	7
#define ONCORE_LENGTH_RSP_Cf	7
	/* Switch I/O format (to NMEA) */
#define ONCORE_LENGTH_CMD_Ci	8
	/* Receiver ID */
#define ONCORE_LENGTH_CMD_Cj	7
#define ONCORE_LENGTH_RSP_Cj	294
	/* ASCII position */
#define ONCORE_LENGTH_CMD_Eq	8
#define ONCORE_LENGTH_RSP_Eq	96
	/* Combined position */
#define ONCORE_LENGTH_CMD_Ga	20
#define ONCORE_LENGTH_RSP_Ga	20
	/* Combined time */
#define ONCORE_LENGTH_CMD_Gb	17
#define ONCORE_LENGTH_RSP_Gb	17
	/* 1PPS control */
#define ONCORE_LENGTH_CMD_Gc	8
#define ONCORE_LENGTH_RSP_Gc	8
	/* Position control */
#define ONCORE_LENGTH_CMD_Gd	8
#define ONCORE_LENGTH_RSP_Gd	8
	/* Time RAIM select */
#define ONCORE_LENGTH_CMD_Ge	8
#define ONCORE_LENGTH_RSP_Ge	8
	/* Time RAIM alarm */
#define ONCORE_LENGTH_CMD_Gf	9
#define ONCORE_LENGTH_RSP_Gf	9
	/* Leap second pending */
#define ONCORE_LENGTH_CMD_Gj	7
#define ONCORE_LENGTH_RSP_Gj	21
	/* Vehicle ID */
#define ONCORE_LENGTH_CMD_Gk	13
#define ONCORE_LENGTH_RSP_Gk	13
	/* 12-channel position/status/data */
#define ONCORE_LENGTH_CMD_Ha	8
#define ONCORE_LENGTH_RSP_Ha	154
	/* 12-channel short position */
#define ONCORE_LENGTH_CMD_Hb	8
#define ONCORE_LENGTH_RSP_Hb	54
	/* 12-channel Time RAIM status */
#define ONCORE_LENGTH_CMD_Hn	8
#define ONCORE_LENGTH_RSP_Hn	78
	/* Inverse differential with pseudo-range */
#define ONCORE_LENGTH_CMD_Hr	14
#define ONCORE_LENGTH_RSP_Hr	170
	/* 12-channel self-test */
#define ONCORE_LENGTH_CMD_Ia	7
#define ONCORE_LENGTH_RSP_Ia	10
	/* System power-on failure */
#define ONCORE_LENGTH_RSP_Sz	8

/* Enumerate all codes */
typedef enum oncore_msg_e {
	MSG_INVALID = 0,	/* Invalid command is 0/false */
	MSG_IS_CMD,			/* Indicates that a message is a command */
	MSG_IS_RSP,			/* Indicates that a message is a response */
	/* Mask angle */
	CMD_Ag, RSP_Ag,
	/* Ignore list */
	CMD_Am, RSP_Am,
	/* Position lock parameters */
	CMD_AM, RSP_AM,
	/* Marine filter select */
	CMD_AN, RSP_AN,
	/* Datum select */
	CMD_Ao, RSP_Ao,
	/* RTCM port baud rate select */
	CMD_AO, RSP_AO,
	/* Define user datum message */
	CMD_Ap, RSP_Ap,
	/* Pulse mode select */
	CMD_AP, RSP_AP,
	/* Ionospheric correction select */
	CMD_Aq, RSP_Aq,
	/* Position filter select */
	CMD_AQ, RSP_AQ,
	/* Position hold parameters */
	CMD_As, RSP_As,
	/* Position lock select */
	CMD_AS, RSP_AS,
	/* Time correction select */
	CMD_Aw, RSP_Aw,
	/* 1PPS time offset */
	CMD_Ay, RSP_Ay,
	/* 1PPS cable delay correction */
	CMD_Az, RSP_Az,
	/* Visible satellite data */
	CMD_Bb, RSP_Bb,
	/* Almanac status */
	CMD_Bd, RSP_Bd,
	/* Almanac data request */
	CMD_Be, RSP_Cb,
	/* Ephemeris data input */
	CMD_Bf, RSP_Cc,
	/* Pseudo-range correction output request */
	CMD_Bh, RSP_Ce,
	/* Leap second status */
	CMD_Bj, RSP_Bj,
	/* UTC offset output */
	CMD_Bo,RSP_Bo,
	/* UTC/ionospheric data */
	CMD_Bp, CMD_Co, RSP_Co,
	/* Almanac data input */
	CMD_Cb, RSP_Ch,
	/* Pseudo-range correction data input */
	CMD_Ce, RSP_Ck,
	/* Set to defaults */
	CMD_Cf, RSP_Cf,
	/* Switch I/O format (to NMEA) */
	CMD_Ci,
	/* Receiver ID */
	CMD_Cj, RSP_Cj,
	/* ASCII position */
	CMD_Eq, RSP_Eq,
	/* Combined position */
	CMD_Ga, RSP_Ga,
	/* Combined time */
	CMD_Gb, RSP_Gb,
	/* 1PPS control */
	CMD_Gc, RSP_Gc,
	/* Position control */
	CMD_Gd, RSP_Gd,
	/* Time RAIM select */
	CMD_Ge, RSP_Ge,
	/* Time RAIM alarm */
	CMD_Gf, RSP_Gf,
	/* Leap second pending */
	CMD_Gj, RSP_Gj,
	/* Vehicle ID */
	CMD_Gk, RSP_Gk,
	/* 12-channel position/status/data */
	CMD_Ha, RSP_Ha,
	/* 12-channel short position */
	CMD_Hb, RSP_Hb,
	/* 12-channel Time RAIM status */
	CMD_Hn, RSP_Hn,
	/* Inverse differential with pseudo-range */
	CMD_Hr, RSP_Hr,
	/* 12-channel self-test */
	CMD_Ia, RSP_Ia,
	/* System power-on failure */
	RSP_Sz,
} oncore_msg;

/* Type definitions (structs) for message response parsing */
/* NOTE: types are named oncore_rsp_XX, where @@XX is the command being parsed */
/* WARNING: assumes char=8b, short=16b, int=32b */
typedef struct oncore_rsp_Ha {
	unsigned char	valid;		/* Boolean: whether structure contains valid data */
	unsigned char	dt_mon;		/* Month (0-11) */
	unsigned char	dt_day;		/* Day (0-30) */
	unsigned short	dt_year;	/* Year (1900-2010) */
	unsigned char	dt_hour;	/* Hour (0-23) */
	unsigned char	dt_min;		/* Minute (0-59) */
	unsigned char	dt_sec;		/* Second (0-59) */
	unsigned int	dt_frac;	/* Nanosecond (0-999,999,999) */

	unsigned int	posf_lat;	/* Filtered latitude (-324,000,000-324,000,000) */
	unsigned int	posf_lon;	/* Filtered longitude (-324,000,000-324,000,000) */
	unsigned int	posf_gps;	/* Filtered GPS height (-100,000-1,800,000) */
	unsigned int	posf_msl;	/* Filtered MSL height (0) */
	unsigned int	pos_lat;	/* Unfiltered latitude (-324,000,000-324,000,000) */
	unsigned int	pos_lon;	/* Unfiltered longitude (-324,000,000-324,000,000) */
	unsigned int	pos_gps;	/* Unfiltered GPS height (-100,000-1,800,000) */
	unsigned int	pos_msl;	/* Unfiltered MSL height (0) */

	unsigned short	vel_3d;		/* 3D speed (0-51,400) */
	unsigned short	vel_2d;		/* 2D speed (0-51,400) */
	unsigned short	vel_hd;		/* Heading (0-3599) */
	unsigned short	dop;		/* Geometry/DOP (0-999) */

	unsigned char	sat_vis;	/* Visible satellites (0-12) */
	unsigned char	sat_trk;	/* Tracked satellites (0-12) */

	unsigned char	c_svid[ONCORE_CHANNELS];	/* SVID (0-37) */
	unsigned char	c_mode[ONCORE_CHANNELS];	/* Mode */
	unsigned char	c_ss[ONCORE_CHANNELS];		/* Signal strength (0-255) */
	unsigned char	c_iode[ONCORE_CHANNELS];	/* IODE (0-255) */
	unsigned short	c_status[ONCORE_CHANNELS];	/* Channel status */

	unsigned short	recv_status;/* Receiver status */
	unsigned short	oc_bias;	/* Clock bias (-32768-32767) */
	unsigned int	oc_offset;	/* Oscillator offset (0-250,000) */
	unsigned short	oc_temp;	/* Oscillator temperature (-110-250) */

	unsigned char	utc_param;	/* UTC parameters */
	unsigned char	gmt_sign;	/* GMT offset sign (0-1) */
	unsigned char	gmt_hour;	/* GMT offset hours (0-23) */
	unsigned char	gmt_min;	/* GMT offset min (0-59) */

	unsigned char	tag[ONCORE_TAG_SIZE];		/* ID tag (0x20-0x7e) */
	unsigned char	checksum;	/* One-byte checksum */
} oncore_rsp_Ha;

typedef struct oncore_rsp_Bb {
	unsigned char valid;
} oncore_rsp_Bb;

oncore_msg oncore_get_type(unsigned char * message, unsigned int message_length);
void * oncore_parse(unsigned char * message, unsigned int message_length, oncore_msg message_type);
unsigned int oncore_build(void * message, oncore_msg message_type, unsigned char * output);

#endif /* ONCORE_H_ */
