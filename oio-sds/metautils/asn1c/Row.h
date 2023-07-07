/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "AWL-MetaDirectory-Protocol"
 * 	found in "//oio-sds/metautils/lib/description.asn"
 * 	`asn1c -fwide-types -fcompound-names -fskeletons-copy`
 */

#ifndef	_Row_H_
#define	_Row_H_


#include <asn_application.h>

/* Including external dependencies */
#include <INTEGER.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RowFieldSequence;

/* Row */
typedef struct Row {
	INTEGER_t	 rowid;
	struct RowFieldSequence	*fields	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Row_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Row;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "RowFieldSequence.h"

#endif	/* _Row_H_ */
#include <asn_internal.h>
