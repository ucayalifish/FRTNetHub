#ifndef FRTNETHUB_HOST_UTILS_H
#define FRTNETHUB_HOST_UTILS_H

#include <stdint.h>

void init_mac_address(uint8_t *mac_addr);

char const * hostname(void);

#define HOSTNAME_LENGTH 18 // FRTNH-(12 байт MAC-адреса в hex)

#endif //FRTNETHUB_HOST_UTILS_H
