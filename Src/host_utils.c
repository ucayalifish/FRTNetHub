#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "crc_utils.h"
#include "host_utils.h"

static char const * host_name_template_ = "FRTNH-%02X%02X%02X%02X%02X%02X";

static char host_name_[] = "FRTNH-XXXXXXXXXXXX"; // terminating zero

#define CPU_ID_ ((const uint32_t *) 0x1FFF7A10)

#define CPU_ID_LEN_ 12

void init_mac_address(uint8_t * mac_addr)
{
  assert(mac_addr);
  assert(mac_addr[2] != 0);

// MAC-address should be initialized by generated code
  uint8_t const  element = mac_addr[2];
  uint32_t const tmp     = crc32(CPU_ID_, CPU_ID_LEN_, 0xffffffffU);
  memcpy(&mac_addr[2], &tmp, sizeof(tmp));
  *(mac_addr + 3) = crc8((mac_addr + 2), 2);
  mac_addr[2] = element;

  sprintf(host_name_, host_name_template_, mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  host_name_[HOSTNAME_LENGTH] = '\0';
}

char const * hostname(void)
{
  return host_name_;
}
