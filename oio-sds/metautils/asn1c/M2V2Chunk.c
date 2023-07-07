/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "AWL-MetaDirectory-Protocol"
 * 	found in "//oio-sds/metautils/lib/description.asn"
 * 	`asn1c -fwide-types -fcompound-names -fskeletons-copy`
 */

#include "M2V2Chunk.h"

static asn_TYPE_member_t asn_MBR_M2V2Chunk_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct M2V2Chunk, id),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PrintableString,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"id"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct M2V2Chunk, hash),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"hash"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct M2V2Chunk, size),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"size"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct M2V2Chunk, ctime),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ctime"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct M2V2Chunk, content),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"content"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct M2V2Chunk, position),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PrintableString,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"position"
		},
};
static const ber_tlv_tag_t asn_DEF_M2V2Chunk_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_M2V2Chunk_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* id */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* hash */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* size */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* ctime */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* content */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 } /* position */
};
static asn_SEQUENCE_specifics_t asn_SPC_M2V2Chunk_specs_1 = {
	sizeof(struct M2V2Chunk),
	offsetof(struct M2V2Chunk, _asn_ctx),
	asn_MAP_M2V2Chunk_tag2el_1,
	6,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_M2V2Chunk = {
	"M2V2Chunk",
	"M2V2Chunk",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_M2V2Chunk_tags_1,
	sizeof(asn_DEF_M2V2Chunk_tags_1)
		/sizeof(asn_DEF_M2V2Chunk_tags_1[0]), /* 1 */
	asn_DEF_M2V2Chunk_tags_1,	/* Same as above */
	sizeof(asn_DEF_M2V2Chunk_tags_1)
		/sizeof(asn_DEF_M2V2Chunk_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_M2V2Chunk_1,
	6,	/* Elements count */
	&asn_SPC_M2V2Chunk_specs_1	/* Additional specs */
};

