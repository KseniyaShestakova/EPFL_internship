/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "AWL-MetaDirectory-Protocol"
 * 	found in "//oio-sds/metautils/lib/description.asn"
 * 	`asn1c -fwide-types -fcompound-names -fskeletons-copy`
 */

#ifndef	_BaseVersion_H_
#define	_BaseVersion_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct TableVersion;

/* BaseVersion */
typedef struct BaseVersion {
	A_SEQUENCE_OF(struct TableVersion) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} BaseVersion_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_BaseVersion;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "TableVersion.h"

#endif	/* _BaseVersion_H_ */
#include <asn_internal.h>
