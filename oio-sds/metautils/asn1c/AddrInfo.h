/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "AWL-MetaDirectory-Protocol"
 * 	found in "//oio-sds/metautils/lib/description.asn"
 * 	`asn1c -fwide-types -fcompound-names -fskeletons-copy`
 */

#ifndef	_AddrInfo_H_
#define	_AddrInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include <INTEGER.h>
#include <OCTET_STRING.h>
#include <constr_CHOICE.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum AddrInfo__ip_PR {
	AddrInfo__ip_PR_NOTHING,	/* No components present */
	AddrInfo__ip_PR_ipv4,
	AddrInfo__ip_PR_ipv6
} AddrInfo__ip_PR;

/* AddrInfo */
typedef struct AddrInfo {
	struct AddrInfo__ip {
		AddrInfo__ip_PR present;
		union AddrInfo__ip_u {
			OCTET_STRING_t	 ipv4;
			OCTET_STRING_t	 ipv6;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} ip;
	INTEGER_t	 port;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AddrInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AddrInfo;

#ifdef __cplusplus
}
#endif

#endif	/* _AddrInfo_H_ */
#include <asn_internal.h>