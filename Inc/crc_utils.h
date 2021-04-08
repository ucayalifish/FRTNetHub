#ifndef FRTNETHUB_CRC_UTILS_H
#define FRTNETHUB_CRC_UTILS_H

#include <stdint.h>
#include <stddef.h>

uint8_t crc8(const void * data, size_t len);

uint32_t crc32(const void * data, size_t len, uint32_t init);

#endif //FRTNETHUB_CRC_UTILS_H
