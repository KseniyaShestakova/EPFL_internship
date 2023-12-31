/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "AWL-MetaDirectory-Protocol"
 * 	found in "//oio-sds/metautils/lib/description.asn"
 * 	`asn1c -fwide-types -fcompound-names -fskeletons-copy`
 */

#include "NamespaceInfo.h"

static asn_TYPE_member_t asn_MBR_NamespaceInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct NamespaceInfo, name),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PrintableString,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"name"
		},
	{ ATF_POINTER, 2, offsetof(struct NamespaceInfo, chunkSize),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"chunkSize"
		},
	{ ATF_POINTER, 1, offsetof(struct NamespaceInfo, options),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ParameterSequence,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"options"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NamespaceInfo, storagePolicy),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ParameterSequence,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"storagePolicy"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NamespaceInfo, dataSecurity),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ParameterSequence,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"dataSecurity"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NamespaceInfo, servicePools),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ParameterSequence,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"servicePools"
		},
};
static const ber_tlv_tag_t asn_DEF_NamespaceInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_NamespaceInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* name */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 1, 0, 0 }, /* chunkSize */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 2, 0, 0 }, /* options */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 3, 0, 0 }, /* storagePolicy */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 4, 0, 0 }, /* dataSecurity */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 5, 0, 0 } /* servicePools */
};
static asn_SEQUENCE_specifics_t asn_SPC_NamespaceInfo_specs_1 = {
	sizeof(struct NamespaceInfo),
	offsetof(struct NamespaceInfo, _asn_ctx),
	asn_MAP_NamespaceInfo_tag2el_1,
	6,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_NamespaceInfo = {
	"NamespaceInfo",
	"NamespaceInfo",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_NamespaceInfo_tags_1,
	sizeof(asn_DEF_NamespaceInfo_tags_1)
		/sizeof(asn_DEF_NamespaceInfo_tags_1[0]), /* 1 */
	asn_DEF_NamespaceInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_NamespaceInfo_tags_1)
		/sizeof(asn_DEF_NamespaceInfo_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_NamespaceInfo_1,
	6,	/* Elements count */
	&asn_SPC_NamespaceInfo_specs_1	/* Additional specs */
};

