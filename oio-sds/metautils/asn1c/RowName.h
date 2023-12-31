/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "AWL-MetaDirectory-Protocol"
 * 	found in "//oio-sds/metautils/lib/description.asn"
 * 	`asn1c -fwide-types -fcompound-names -fskeletons-copy`
 */

#ifndef	_RowName_H_
#define	_RowName_H_


#include <asn_application.h>

/* Including external dependencies */
#include <INTEGER.h>
#include <OCTET_STRING.h>
#include "RowFieldType.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RowName */
typedef struct RowName {
	INTEGER_t	 pos;
	OCTET_STRING_t	 name;
	RowFieldType_t	*type	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RowName_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RowName;

#ifdef __cplusplus
}
#endif

#endif	/* _RowName_H_ */
#include <asn_internal.h>
