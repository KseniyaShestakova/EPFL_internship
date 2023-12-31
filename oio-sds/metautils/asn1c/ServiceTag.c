/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "AWL-MetaDirectory-Protocol"
 * 	found in "//oio-sds/metautils/lib/description.asn"
 * 	`asn1c -fwide-types -fcompound-names -fskeletons-copy`
 */

#include "ServiceTag.h"

static asn_TYPE_member_t asn_MBR_value_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ServiceTag__value, choice.b),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"b"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ServiceTag__value, choice.i),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"i"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ServiceTag__value, choice.r),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_REAL,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"r"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ServiceTag__value, choice.s),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"s"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_value_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* b */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* i */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* r */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* s */
};
static asn_CHOICE_specifics_t asn_SPC_value_specs_3 = {
	sizeof(struct ServiceTag__value),
	offsetof(struct ServiceTag__value, _asn_ctx),
	offsetof(struct ServiceTag__value, present),
	sizeof(((struct ServiceTag__value *)0)->present),
	asn_MAP_value_tag2el_3,
	4,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_value_3 = {
	"value",
	"value",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	0,	/* No PER visible constraints */
	asn_MBR_value_3,
	4,	/* Elements count */
	&asn_SPC_value_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_ServiceTag_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ServiceTag, name),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PrintableString,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"name"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ServiceTag, value),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_value_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"value"
		},
};
static const ber_tlv_tag_t asn_DEF_ServiceTag_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ServiceTag_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* name */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* value */
};
static asn_SEQUENCE_specifics_t asn_SPC_ServiceTag_specs_1 = {
	sizeof(struct ServiceTag),
	offsetof(struct ServiceTag, _asn_ctx),
	asn_MAP_ServiceTag_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_ServiceTag = {
	"ServiceTag",
	"ServiceTag",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_ServiceTag_tags_1,
	sizeof(asn_DEF_ServiceTag_tags_1)
		/sizeof(asn_DEF_ServiceTag_tags_1[0]), /* 1 */
	asn_DEF_ServiceTag_tags_1,	/* Same as above */
	sizeof(asn_DEF_ServiceTag_tags_1)
		/sizeof(asn_DEF_ServiceTag_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_ServiceTag_1,
	2,	/* Elements count */
	&asn_SPC_ServiceTag_specs_1	/* Additional specs */
};

