/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "AWL-MetaDirectory-Protocol"
 * 	found in "//oio-sds/metautils/lib/description.asn"
 * 	`asn1c -fwide-types -fcompound-names -fskeletons-copy`
 */

#ifndef	_M2V2Chunk_H_
#define	_M2V2Chunk_H_


#include <asn_application.h>

/* Including external dependencies */
#include <PrintableString.h>
#include <OCTET_STRING.h>
#include <INTEGER.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* M2V2Chunk */
typedef struct M2V2Chunk {
	PrintableString_t	 id;
	OCTET_STRING_t	 hash;
	INTEGER_t	 size;
	INTEGER_t	 ctime;
	OCTET_STRING_t	 content;
	PrintableString_t	 position;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} M2V2Chunk_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_M2V2Chunk;

#ifdef __cplusplus
}
#endif

#endif	/* _M2V2Chunk_H_ */
#include <asn_internal.h>
