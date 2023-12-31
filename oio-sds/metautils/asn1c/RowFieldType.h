/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "AWL-MetaDirectory-Protocol"
 * 	found in "//oio-sds/metautils/lib/description.asn"
 * 	`asn1c -fwide-types -fcompound-names -fskeletons-copy`
 */

#ifndef	_RowFieldType_H_
#define	_RowFieldType_H_


#include <asn_application.h>

/* Including external dependencies */
#include <ENUMERATED.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RowFieldType {
	RowFieldType_typeInt	= 0,
	RowFieldType_typeBlob	= 1,
	RowFieldType_typeText	= 2,
	RowFieldType_typeFloat	= 3
} e_RowFieldType;

/* RowFieldType */
typedef ENUMERATED_t	 RowFieldType_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RowFieldType;
asn_struct_free_f RowFieldType_free;
asn_struct_print_f RowFieldType_print;
asn_constr_check_f RowFieldType_constraint;
ber_type_decoder_f RowFieldType_decode_ber;
der_type_encoder_f RowFieldType_encode_der;
xer_type_decoder_f RowFieldType_decode_xer;
xer_type_encoder_f RowFieldType_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _RowFieldType_H_ */
#include <asn_internal.h>
