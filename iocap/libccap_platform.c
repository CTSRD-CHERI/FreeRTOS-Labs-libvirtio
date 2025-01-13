#include <stdio.h>
#include <stdint.h>

#include "libccap.h"
#include "mbedtls/aes.h"

// THIS FILE CONTAINS FREERTOS-SPECIFIC FUNCTION DEFINITIONS AND IS NOT PART OF LIBCCAP PROPER.

/**
 * Define the function libccap uses to print debug information when it panics.
 */
uint64_t ccap_panic_write_utf8(const uint8_t *utf8, uint64_t utf_len) {
    for (uint64_t i = 0; i < utf_len; i++) {
        printf("%c", utf8[i]);
    }
    return utf_len;
}

/**
 * Define the function libccap uses to AES-encrypt data to generate signatures.
 */
void aes_encrypt_128_func(const CCapU128 *secret, const CCapU128 *data, CCapU128 *result) {
    mbedtls_aes_context ctx;
    mbedtls_aes_init(&ctx);
    if (mbedtls_aes_setkey_enc(&ctx, *secret, 128) == 0) {
        if (mbedtls_aes_crypt_ecb(&ctx, MBEDTLS_AES_ENCRYPT, *data, *result) == 0) {
            // TODO signal success/failure
        }
    }
    mbedtls_aes_free(&ctx);
}
