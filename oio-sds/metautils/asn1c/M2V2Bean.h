/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "AWL-MetaDirectory-Protocol"
 * 	found in "//oio-sds/metautils/lib/description.asn"
 * 	`asn1c -fwide-types -fcompound-names -fskeletons-copy`
 */

#ifndef	_M2V2Bean_H_
#define	_M2V2Bean_H_


#include <asn_application.h>

/* Including external dependencies */
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct M2V2Alias;
struct M2V2ContentHeader;
struct M2V2Chunk;
struct M2V2Property;

/* M2V2Bean */
typedef struct M2V2Bean {
	struct M2V2Alias	*alias	/* OPTIONAL */;
	struct M2V2ContentHeader	*header	/* OPTIONAL */;
	struct M2V2Chunk	*chunk	/* OPTIONAL */;
	struct M2V2Property	*prop	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} M2V2Bean_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_M2V2Bean;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "M2V2Alias.h"
#include "M2V2ContentHeader.h"
#include "M2V2Chunk.h"
#include "M2V2Property.h"

#endif	/* _M2V2Bean_H_ */
#include <asn_internal.h>