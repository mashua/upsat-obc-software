#ifndef __TC_TM_H
#define __TC_TM_H

#include <stdint.h>

/* TM TC services*/
#define ECSS_VER_NUMBER				0
#define ECSS_DATA_FIELD_HDR_FLG		1
#define TC_TM_SER_TC_VER			1

#define ECSS_PUS_VER			1
#define ECSS_SEC_HDR_FIELD_FLG  0
/* Minimal */
#define TC_TM_SER_TC_VER_ACC_SUCC			1
#define TC_TM_SER_TC_VER_ACC_FAIL			2
/* Additional */
#define TC_TM_SER_TC_VER_EXEC_START_SUCC	3
#define TC_TM_SER_TC_VER_EXEC_START_FAIL	4
#define TC_TM_SER_TC_VER_EXEC_PROG_SUCC		5
#define TC_TM_SER_TC_VER_EXEC_PROG_FAIL		6
#define TC_TM_SER_TC_VER_EXEC_COMP_SUCC		7
#define TC_TM_SER_TC_VER_EXEC_COMP_FAIL		8

#define TC_TM_SER_DIST		2
#define TC_TM_SER_HK		3

/* Minimal */
#define TC_TM_SER_HK_PAR	25
/* Additional */

#define TC_TM_SER_STAT		4
#define TC_TM_SER_EVENT		5
#define TC_TM_SER_MEM		6
#define TC_TM_SER_NC1		7
#define TC_TM_SER_FMAG		8
#define TC_TM_SER_TMAG		9
#define TC_TM_SER_NC2		10

#define TC_TM_SER_SCH		11
#define TC_TM_SER_MON		12
#define TC_TM_SER_LDATA		13
#define TC_TM_SER_PCKT_FWD	14
#define TC_TM_SER_STORAGE	15
#define TC_TM_SER_NC3		16
#define TC_TM_SER_TEST		17
#define TC_TM_SER_PROC		18
#define TC_TM_SER_EV_ACT	19

/*sequence definitions*/
#define TC_TM_SEQ_FPACKET 0x01
#define TC_TM_SEQ_CPACKET 0x00
#define TC_TM_SEQ_LPACKET 0x02
#define TC_TM_SEQ_SPACKET 0x03

/*services ack req*/
/*should confirm endianess*/
#define TC_ACK_NO			0x00
#define TC_ACK_ACC			0x01
#define TC_ACK_EXE_START	0x02
#define TC_ACK_EXE_PROG		0x04
#define TC_ACK_EXE_COMP		0x08
#define TC_ACK_ALL			0x0F

#define TC_TM_SER_LDATA_MAX_DATA_PKT	512

#define VER_NUMBER 
#define TC_TM_TYPE
#define DATA_FIELD_HDR_FLG
#define APP_ID
#define SEQ_FLG

#define MAX_PKT_DATA	20
#define MAX_APP_ID		20
#define MAX_SERVICES	20
#define MAX_SUBTYPES	26

#define TC 1
#define TM 0

typedef enum {
#define R_PKT_ILLEGAL_APPID 	= 0,
#define R_PKT_INV_LEN			= 1,
#define R_PKT_INC_CRC			= 2,
#define R_PKT_ILLEGAL_PKT_TP	= 3,
#define R_PKT_ILLEGAL_PKT_STP	= 4,
#define R_PKT_ILLEGAL_APP_DATA  = 5,
#define R_OK                    = 6,
#define R_ERROR                 = 7,
#define R_EOT                   = 8
}OBC_returnStateTypedef;

#define TC_VERIFICATION_SERVICE			1
#define TC_HOUSEKEEPING_SERVICE			3
#define TC_FUNCTION_MANAGEMENT_SERVICE	8

#define OBC		1
#define EPS		2
#define ADCS	3
#define COMMS	4
#define IAC		5
#define GND		6

#define SD1		1

#define TURN_OFF	0
#define TURN_ON		1
#define RESET		2

extern const uint8_t services_verification_TC_TM[MAX_SERVICES][MAX_SUBTYPES][2];
extern const uint8_t app_id_verification[MAX_APP_ID];
extern const uint8_t services_verification_OBC_TC[MAX_SERVICES][MAX_SUBTYPES];

union _cnv {
	uint32_t cnv32;
	uint16_t cnv16[2];
	uint8_t cnv8[4];
};

struct tc_tm_pkt {
	/* packet id */
	//uint8_t ver; /* 3 bits, should be equal to 0 */
	
	//uint8_t data_field_hdr; /* 1 bit, data_field_hdr exists in data = 1 */
	uint16_t app_id; /* TM: app id = 0 for time packets, = 0xff for idle packets. */
	uint8_t type; /* 1 bit, tm = 0, tc = 1 */
	
	/* packet sequence control */
	uint8_t seq_flags; /* 3 bits, definition in TC_SEQ_xPACKET */
	uint16_t seq_count; /* 14 bits, packet counter, should be unique for each app id */

	uint16_t len; /* 16 bits, C = (Number of octets in packet data field) - 1 */

	uint8_t ack; /* 4 bits, definition in TC_ACK_xxxx 0 if its a TM */
	uint8_t ser_type; /* 8 bit, service type */
	uint8_t ser_subtype; /* 8 bit, service subtype */

	/*optional*/
	//uint8_t pckt_sub_cnt; /* 8 bits*/
	uint16_t dest_id;

	uint8_t data[MAX_PKT_DATA]; /* variable data, this should be fixed array */
/*	uint8_t padding;  x bits, padding for word alligment */

//	uint16_t crc; /* CRC or checksum, mission specific*/
};


//struct tc_tm_ser_ver_hdr {
//	uint16_t tc_pckt_id; /* 16 bits, copy of originating tc's, packet id */
//	uint8_t tc_pckt_seq; /* 16 bits, copy of originating tc's, packet seq */
//};

//struct tc_tm_ser_ver_header_suc {
//	struct tc_tm_ser_ver_hdr _tc_tm_ser_ver_hdr;
//};


/* Service 1, Verification */
//struct tc_tm_ser_ver_header_fail {
//	struct tc_tm_ser_ver_hdr _tc_tm_ser_ver_hdr;
//	uintx_t error; /* x bits */

	/*optional*/
//	uintx_t params; /* x bits*/
//};

/*I dont think that we will have steps in this mission, so no need for those*/
//struct tc_tm_ser_ver_header_step_suc {
//	struct tc_tm_ser_ver_header_suc _tc_tm_ser_ver_header_suc;
//	uintx_t step; /* x bits*/
//};


//struct tc_tm_ser_ver_header_step_fail {
//	struct tc_tm_ser_ver_hdr _tc_tm_ser_ver_hdr;
//	uintx_t step; /* x bits */
//	uintx_t error; /* x bits */

	/*optional*/
//	uintx_t params; /* x bits*/
//};

/* Service 3, Housekeeping and diagnostics */


/* Service 13, Verification */


OBC_returnStateTypedef checkSum(const uint8_t *data, uint16_t size);

OBC_returnStateTypedef unpack_pkt(const uint8_t *buf, struct tc_tm_pkt *pkt, const uint16_t size);

OBC_returnStateTypedef pack_pkt(uint8_t *buf, struct tc_tm_pkt *pkt, uint16_t *size);

#endif