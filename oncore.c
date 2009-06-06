/*
 * oncore.c
 *
 *  Created on: May 30, 2009
 *      Author: Andrew Hills <ahills@ecs.umass.edu>
 */

/* Standard library includes */
#include <stdlib.h>
#include <string.h>

/* Custom library includes */
#include "oncore.h"

/* Build a message from a struct */

unsigned int _build_Ha(oncore_rsp_Ha * message, unsigned char * output) {
	return 0;
}

/* Some functions need advanced parsing */

oncore_rsp_Ha _parse_Ha(unsigned char * message, unsigned int message_length) {
	oncore_rsp_Ha output;
	output.valid = ONCORE_MSG_INVALID;

	/* If message is not correct length, our output cannot possibly be valid. */
	if(message_length != ONCORE_LENGTH_RSP_Ha)
		return output;

	/* Format of @@Ha response:
		 * @@Ha					Command
		 * mdyy					Month, day, year
		 * hmsffff				Hour, minute, second, fraction (ns)
		 * aaaaoooohhhhmmmm		(Filtered) latitude (mas), longitude (mas), GPS height (cm), MSL height (cm)
		 * aaaaoooohhhhmmmm		(Unfiltered) latitude (mas), longitude (mas), GPS height (cm), MSL height (cm)
		 * VVvvhh				3D speed (cm/s), 2D speed (cm/s), heading (cm/s)
		 * dd					Geometry (DOP)
		 * nt					Visible satellite count, tracked satellite count
		 * imsIdd (repeat)		SVID, mode, signal strength, IODE, status (each channel)
		 * ssrr					Receiver status
		 * ccooooTT				Clock bias (ns), oscillator offset (Hz), oscillator temperature (0.5 C)
		 * u					UTC parameters
		 * shm					Sign, hours, minutes (GMT offset)
		 * vvvvvv				ID tag (0x20-0x7e)
		 * C<CR><LF>			Checksum and EOL
		 */

	unsigned char pos = 4;		/* Position of current byte */
	output.dt_mon =		message[pos++];
	output.dt_day =		message[pos++];
	output.dt_year =	_getint2(message + pos++);
	output.dt_hour =	message[pos++];
	output.dt_min =		message[pos++];
	output.dt_sec =		message[pos++];
	output.dt_frac =	_getint4(message + pos++);

	output.posf_lat =	_getint4(message + pos++);
	output.posf_lon =	_getint4(message + pos++);
	output.posf_gps =	_getint4(message + pos++);
	output.posf_msl =	_getint4(message + pos++);
	output.pos_lat =	_getint4(message + pos++);
	output.pos_lon =	_getint4(message + pos++);
	output.pos_gps =	_getint4(message + pos++);
	output.pos_msl =	_getint4(message + pos++);
	output.vel_3d =		_getint2(message + pos++);
	output.vel_2d =		_getint2(message + pos++);
	output.vel_hd =		_getint2(message + pos++);
	output.dop =		_getint2(message + pos++);
	output.sat_vis =	message[pos++];
	output.sat_trk =	message[pos++];

	unsigned int i;		/* Generic loop counter */
	for(i = 0; i < ONCORE_CHANNELS; i++) {
		output.c_svid[i] =		message[pos++];
		output.c_mode[i] =		message[pos++];
		output.c_ss[i] =		message[pos++];
		output.c_iode[i] =		message[pos++];
		output.c_status[i] =	_getint2(message + pos++);
	}

	output.recv_status =_getint2(message + pos++);
	pos += 2;			/* Ignore two reserved bytes */
	output.oc_bias =	_getint2(message + pos++);
	output.oc_offset =	_getint4(message + pos++);
	output.oc_temp =	_getint2(message + pos++);

	output.utc_param =	message[pos++];
	output.gmt_sign =	message[pos++];
	output.gmt_hour =	message[pos++];
	output.gmt_min =	message[pos++];

	for(i = 0; i < ONCORE_TAG_SIZE; i++)
		output.tag[i] =	message[pos++];
	output.checksum =	message[pos++];

	output.valid = ONCORE_MSG_VALID;

	return output;
}

oncore_rsp_Bb _parse_Bb(unsigned char * message, unsigned int message_length) {
	oncore_rsp_Bb output;
	output.valid = ONCORE_MSG_INVALID;

	/* If message is not correct length, our output cannot possibly be valid. */
	if(message_length != ONCORE_LENGTH_RSP_Bb)
		return output;

	/* Format of @@Bb response:
	 * @@Bb					Command
	 */

	return output;
}

oncore_msg oncore_get_type(unsigned char * message, unsigned int message_length) {
	/* Message must have minimum message length */
	if(message_length < ONCORE_LENGTH_MIN)
			return MSG_INVALID;

	/* Message MUST begin with @@ */
	if(message[0] != '@' || message[1] != '@')
		return MSG_INVALID;

	/* Create null-terminated string for strcmp */
	unsigned char code[3];
	code[0] = message[2];
	code[1] = message[3];
	code[2] = 0;

#define _gt_return(str)	if(!strcmp(code,#str)) return (message_length == ONCORE_LENGTH_RSP_##str) ? RSP_##str : MSG_INVALID	/* Make my life easier */

	/* Return a type for any RESPONSE-type codes. It's meaningless to test COMMAND-type codes. */

	_gt_return(Ag);
	_gt_return(Am);
	_gt_return(AM);
	_gt_return(AN);
	_gt_return(Ao);
	_gt_return(AO);
	_gt_return(Ap);
	_gt_return(AP);
	_gt_return(Aq);
	_gt_return(AQ);
	_gt_return(As);
	_gt_return(AS);
	_gt_return(Aw);
	_gt_return(Ay);
	_gt_return(Az);
	_gt_return(Bb);
	_gt_return(Bd);
	_gt_return(Cb);
	_gt_return(Cc);
	_gt_return(Ce);
	_gt_return(Bj);
	_gt_return(Bo);
	_gt_return(Co);
	_gt_return(Ch);
	_gt_return(Ck);
	_gt_return(Cf);
	_gt_return(Cj);
	_gt_return(Eq);
	_gt_return(Ga);
	_gt_return(Gb);
	_gt_return(Gc);
	_gt_return(Gd);
	_gt_return(Ge);
	_gt_return(Gf);
	_gt_return(Gj);
	_gt_return(Gk);
	_gt_return(Ha);
	_gt_return(Hb);
	_gt_return(Hn);
	_gt_return(Hr);
	_gt_return(Ia);
	_gt_return(Sz);
	return MSG_INVALID;
}

/* Given a message, length, type, oncore_parse() points parameter parsed to an appropriate struct. */
void * oncore_parse(unsigned char * message, unsigned int message_length, oncore_msg message_type) {
	if(message_type == RSP_Ha) {		/* Call @@Ha parser */
		oncore_rsp_Ha * output = malloc(sizeof(oncore_rsp_Ha));
		*output = _parse_Ha(message, message_length);
//		if(!parsed)
//			parsed = malloc(sizeof(output));
//		*parsed = output;
		return output;
	}
	else if (message_type == RSP_Bb) {	/* Call @@Bb parser */
		oncore_rsp_Bb * output = malloc(sizeof(oncore_rsp_Bb));
		*output = _parse_Bb(message, message_length);
//		if(!parsed)
//			parsed = malloc(sizeof(output));
//		*parsed = output;
		return output;
	}
	return NULL;						/* All other types do not get parsed. */
}

/* Given a pointer to a message struct and the message type, build a message in a character array and return its length. */
unsigned int oncore_build(void * message, oncore_msg message_type, unsigned char * output) {
	return 0;
}
