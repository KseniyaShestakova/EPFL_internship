/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "AWL-MetaDirectory-Protocol"
 * 	found in "//oio-sds/metautils/lib/description.asn"
 * 	`asn1c -fwide-types -fcompound-names -fskeletons-copy`
 */

#ifndef	_ServiceInfo_H_
#define	_ServiceInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include <PrintableString.h>
#include "AddrInfo.h"
#include "Score.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ServiceTag;

/* ServiceInfo */
typedef struct ServiceInfo {
	PrintableString_t	 nsName;
	PrintableString_t	 type;
	AddrInfo_t	 addr;
	Score_t	 score;
	struct ServiceInfo__tags {
		A_SEQUENCE_OF(struct ServiceTag) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *tags;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ServiceInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ServiceInfo;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "ServiceTag.h"

#endif	/* _ServiceInfo_H_ */
#include <asn_internal.h>
