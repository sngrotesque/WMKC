/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "Sm2derSimplfied"
 * 	found in "module.asn1"
 */

#ifndef	_ObjID_H_
#define	_ObjID_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OBJECT_IDENTIFIER.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ObjID */
typedef OBJECT_IDENTIFIER_t	 ObjID_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ObjID;
asn_struct_free_f ObjID_free;
asn_struct_print_f ObjID_print;
asn_constr_check_f ObjID_constraint;
ber_type_decoder_f ObjID_decode_ber;
der_type_encoder_f ObjID_encode_der;
xer_type_decoder_f ObjID_decode_xer;
xer_type_encoder_f ObjID_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _ObjID_H_ */
