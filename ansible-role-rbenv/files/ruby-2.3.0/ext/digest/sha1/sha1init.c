/* $RoughId: sha1init.c,v 1.2 2001/07/13 19:49:10 knu Exp $ */
/* $Id: sha1init.c 52694 2015-11-21 04:35:57Z naruse $ */

#include <ruby/ruby.h>
#include "../digest.h"
#if defined(SHA1_USE_OPENSSL)
#include "sha1ossl.h"
#elif defined(SHA1_USE_COMMONDIGEST)
#include "sha1cc.h"
#else
#include "sha1.h"
#endif

static const rb_digest_metadata_t sha1 = {
    RUBY_DIGEST_API_VERSION,
    SHA1_DIGEST_LENGTH,
    SHA1_BLOCK_LENGTH,
    sizeof(SHA1_CTX),
    (rb_digest_hash_init_func_t)SHA1_Init,
    (rb_digest_hash_update_func_t)SHA1_Update,
    (rb_digest_hash_finish_func_t)SHA1_Finish,
};

/*
 * A class for calculating message digests using the SHA-1 Secure Hash
 * Algorithm by NIST (the US' National Institute of Standards and
 * Technology), described in FIPS PUB 180-1.
 */
void
Init_sha1(void)
{
    VALUE mDigest, cDigest_Base, cDigest_SHA1;

    rb_require("digest");

#if 0
    mDigest = rb_define_module("Digest"); /* let rdoc know */
#endif
    mDigest = rb_path2class("Digest");
    cDigest_Base = rb_path2class("Digest::Base");

    cDigest_SHA1 = rb_define_class_under(mDigest, "SHA1", cDigest_Base);

#undef RUBY_UNTYPED_DATA_WARNING
#define RUBY_UNTYPED_DATA_WARNING 0
    rb_iv_set(cDigest_SHA1, "metadata",
	      Data_Wrap_Struct(0, 0, 0, (void *)&sha1));
}
