#include <stm32f429xx.h>
#include <stm32f4xx_hal.h>

#include "crc_utils.h"

#define CRC8_POLY_      0x7u
#define CRC8_INIT_      0x00u
#define CRC8_FINAL_XOR_ 0x00u

uint8_t crc8(void const * data, size_t len)
{
  uint8_t     crc  = CRC8_INIT_;
  for (size_t byte = 0; byte < len; ++byte)
    {
      crc ^= (((uint8_t *) data)[byte]);
      for (uint8_t bit = 8; bit > 0; --bit)
        {
          if (crc & 0x80u)
            {
              crc = (uint8_t) ((crc << 1u) ^ CRC8_POLY_);
            }
          else
            {
              crc = (crc << 1u);
            }
        }
    }

  return (uint8_t) (crc ^ CRC8_FINAL_XOR_);
}

uint32_t crc32(void const * data, size_t len, uint32_t init)
{
  if (init)
    {
      __HAL_RCC_CRC_CLK_ENABLE();
    }

  if (!data)
    {
      return 0xffffffffU;
    }

  uint32_t * p32 = (uint32_t *) data;
  size_t count32 = len >> 2u;

  while (count32--)
    {
      CRC->DR = __RBIT(*p32);
      ++p32;
    }
  uint32_t crc = __RBIT(CRC->DR);

  len = len % 4;
  if (len)
    {
      CRC->DR = __RBIT(crc);
      switch (len)
        {
          case 1:
            {
              CRC->DR = __RBIT((*p32 & 0x000000FFu) ^ crc) >> 24u;
              crc = (crc >> 8u) ^ __RBIT(CRC->DR);
            }
          break;
          case 2:
            {
              CRC->DR = __RBIT((*p32 & 0x0000FFFFu) ^ crc) >> 16u;
              crc = (crc >> 16u) ^ __RBIT(CRC->DR);
            }
          break;
          case 3:
            {
              CRC->DR = __RBIT((*p32 & 0x00FFFFFFu) ^ crc) >> 8u;
              crc = (crc >> 24u) ^ __RBIT(CRC->DR);
            }
          break;
          default:;
        }
    }

  return ~crc;
}
