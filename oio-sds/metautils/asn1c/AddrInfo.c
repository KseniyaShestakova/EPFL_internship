/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "AWL-MetaDirectory-Protocol"
 * 	found in "//oio-sds/metautils/lib/description.asn"
 * 	`asn1c -fwide-types -fcompound-names -fskeletons-copy`
 */

#include "AddrInfo.h"

static int
memb_ipv4_constraint_2(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const OCTET_STRING_t *st = (const OCTET_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size == 4)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_ipv6_constraint_2(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const OCTET_STRING_t *st = (const OCTET_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size == 16)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_TYPE_member_t asn_MBR_ip_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct AddrInfo__ip, choice.ipv4),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		memb_ipv4_constraint_2,
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipv4"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AddrInfo__ip, choice.ipv6),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		memb_ipv6_constraint_2,
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipv6"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_ip_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ipv4 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* ipv6 */
};
static asn_CHOICE_specifics_t asn_SPC_ip_specs_2 = {
	sizeof(struct AddrInfo__ip),
	offsetof(struct AddrInfo__ip, _asn_ctx),
	offsetof(struct AddrInfo__ip, present),
	sizeof(((struct AddrInfo__ip *)0)->present),
	asn_MAP_ip_tag2el_2,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_ip_2 = {
	"ip",
	"ip",
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
	asn_MBR_ip_2,
	2,	/* Elements count */
	&asn_SPC_ip_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_AddrInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct AddrInfo, ip),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_ip_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ip"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AddrInfo, port),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"port"
		},
};
static const ber_tlv_tag_t asn_DEF_AddrInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_AddrInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ip */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* port */
};
static asn_SEQUENCE_specifics_t asn_SPC_AddrInfo_specs_1 = {
	sizeof(struct AddrInfo),
	offsetof(struct AddrInfo, _asn_ctx),
	asn_MAP_AddrInfo_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_AddrInfo = {
	"AddrInfo",
	"AddrInfo",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_AddrInfo_tags_1,
	sizeof(asn_DEF_AddrInfo_tags_1)
		/sizeof(asn_DEF_AddrInfo_tags_1[0]), /* 1 */
	asn_DEF_AddrInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_AddrInfo_tags_1)
		/sizeof(asn_DEF_AddrInfo_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_AddrInfo_1,
	2,	/* Elements count */
	&asn_SPC_AddrInfo_specs_1	/* Additional specs */
};

