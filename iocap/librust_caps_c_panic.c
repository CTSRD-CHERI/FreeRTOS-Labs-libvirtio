#include <stdio.h>
#include <stdint.h>

/**
 * Define the function librust_caps_c uses to print debug information when it panics.
 */
uint64_t ccap_panic_write_utf8(const uint8_t *utf8, uint64_t utf_len) {
    for (uint64_t i = 0; i < utf_len; i++) {
        printf("%c", utf8[i]);
    }
    return utf_len;
}