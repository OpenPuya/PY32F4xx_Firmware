#include "usbd_core.h"
#include "usbd_msc.h"

#define MSC_IN_EP  0x81
#define MSC_OUT_EP 0x02

#define USBD_VID           0x36b7
#define USBD_PID           0xFFFF
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

#define USB_CONFIG_SIZE (9 + MSC_DESCRIPTOR_LEN)

const uint8_t msc_flash_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0200, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x01, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    MSC_DESCRIPTOR_INIT(0x00, MSC_OUT_EP, MSC_IN_EP, 0x02),
    ///////////////////////////////////////
    /// string0 descriptor
    ///////////////////////////////////////
    USB_LANGID_INIT(USBD_LANGID_STRING),
    ///////////////////////////////////////
    /// string1 descriptor
    ///////////////////////////////////////
    0x0A,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'P', 0x00,                  /* wcChar0 */
    'U', 0x00,                  /* wcChar1 */
    'Y', 0x00,                  /* wcChar2 */
    'A', 0x00,                  /* wcChar3 */
    ///////////////////////////////////////
    /// string2 descriptor
    ///////////////////////////////////////
    0x1C,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'P', 0x00,                  /* wcChar0 */
    'U', 0x00,                  /* wcChar1 */
    'Y', 0x00,                  /* wcChar2 */
    'A', 0x00,                  /* wcChar3 */
    ' ', 0x00,                  /* wcChar4 */
    'M', 0x00,                  /* wcChar5 */
    'S', 0x00,                  /* wcChar6 */
    'C', 0x00,                  /* wcChar7 */
    ' ', 0x00,                  /* wcChar8 */
    'D', 0x00,                  /* wcChar9 */
    'E', 0x00,                  /* wcChar10 */
    'M', 0x00,                  /* wcChar11 */
    'O', 0x00,                  /* wcChar12 */
    ///////////////////////////////////////
    /// string3 descriptor
    ///////////////////////////////////////
    0x16,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    '2', 0x00,                  /* wcChar0 */
    '0', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    '2', 0x00,                  /* wcChar3 */
    '1', 0x00,                  /* wcChar4 */
    '2', 0x00,                  /* wcChar5 */
    '3', 0x00,                  /* wcChar6 */
    '4', 0x00,                  /* wcChar7 */
    '5', 0x00,                  /* wcChar8 */
    '6', 0x00,                  /* wcChar9 */
#ifdef CONFIG_USB_HS
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x01,
    0x00,
#endif
    0x00
};

void usbd_configure_done_callback(void)
{
    /* do nothing */
}

#define P25Q128_WRITE_ENABLE             0x06
#define P25Q128_WRITE_DISABLE            0x04
#define P25Q128_PAGE_PROGRAM             0x02
#define P25Q128_SECTOR_ERASE             0x20
#define P25Q128_READ_DATA                0x03
#define P25Q128_READ_STATUS_REGISTER     0x05

#define DISK_BASE_ADDR 0
#define DISK_PAGE_SIZE 256

#define BLOCK_SIZE  4096
#define BLOCK_COUNT 32768
extern SPI_HandleTypeDef hSPI2;

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void ErrorHandler(void)
{
  
}

/**
  * @brief  This function transmit one byte.
  * @param  pTxData: pointer to transmission data buffer
  * @retval None
  */
static void APP_SPITransmit(uint8_t *pTxData)
{
  uint8_t temp = 0;
  if (HAL_SPI_TransmitReceive(&hSPI2, pTxData, &temp, 1, 100) != HAL_OK)
  {
    ErrorHandler();
  }
}

/**
  * @brief  This function receive one byte.
  * @param  pRxData: pointer to reception data buffer
  * @retval None
  */
static void APP_SPIReceive(uint8_t *pRxData)
{
  uint8_t temp = 0xFF;
  if (HAL_SPI_TransmitReceive(&hSPI2, &temp, pRxData, 1, 100) != HAL_OK)
  {
    ErrorHandler();
  }
}

/**
  * @brief  Read flash status reg.
  * @param  None
  * @retval Flash status reg value
  */
static uint8_t GetStatus(void)
{
  uint8_t cmd = 0;
  uint8_t status;
  
  /*Pull down NSS*/
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
  
  /*Send read status register instruction*/
  cmd = P25Q128_READ_STATUS_REGISTER;
  
  APP_SPITransmit(&cmd);
  
  /*Read flash status reg*/
  APP_SPIReceive(&status);
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
  
  return status;
}

/**
  * @brief  Send write enale instruction.
  * @param  None
  * @retval None
  */
static void WriteEnable(void)
{
  uint8_t cmd = 0;
  
  /*Pull down NSS*/
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
  
  /*Write enable*/
  cmd = P25Q128_WRITE_ENABLE;
  
  APP_SPITransmit(&cmd);
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
  
  /* Wait for the operation to complete. */
  while((GetStatus() & 0x01) != 0);
}

/**
  * @brief  Write an amount of data
  * @param  Address£ºpage address
  * @param  DataArray£ºData to be written
  * @param  Count£ºNumber of bytes
  * @retval None
  */
static void APP_P25Q128_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
  uint8_t cmd[3] = {0};
  uint8_t *pbuf = DataArray;
  uint32_t txcnt = Count;
  
  WriteEnable();
  
  /*Pull down NSS*/
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
  
  /*Send write instruction*/
  cmd[0] = P25Q128_PAGE_PROGRAM;
  
  APP_SPITransmit(&cmd[0]);
  
  /*Send address*/
  cmd[0] = (uint8_t)(Address >> 16);
  cmd[1] = (uint8_t)(Address >> 8);
  cmd[2] = (uint8_t)Address;
  APP_SPITransmit(&cmd[0]);
  APP_SPITransmit(&cmd[1]);
  APP_SPITransmit(&cmd[2]);
  
  /* Write data */
  while(txcnt > 0)
  {
    APP_SPITransmit(pbuf);
    pbuf++;
    txcnt--;
  }
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
  
  /* Wait for the operation to complete. */
  while((GetStatus() & 0x01) != 0);
}

/**
  * @brief  Erases data in the specified Sector
  * @param  Address£ºSector address
  * @retval None
  */
static void APP_P25Q128_SectorErase(uint32_t Address)
{
  uint8_t cmd[3] = {0};
  
  WriteEnable();

  /*Pull down NSS*/
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
  
  /*Send erase instruction*/
  cmd[0] = P25Q128_SECTOR_ERASE;
  
  APP_SPITransmit(&cmd[0]);
  
  /*Send address*/
  cmd[0] = (uint8_t)(Address >> 16);
  cmd[1] = (uint8_t)(Address >> 8);
  cmd[2] = (uint8_t)Address;
  APP_SPITransmit(&cmd[0]);
  APP_SPITransmit(&cmd[1]);
  APP_SPITransmit(&cmd[2]);
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
  
  /* Wait for the operation to complete. */
  while((GetStatus() & 0x01) != 0);
  
}
  
/**
  * @brief  Read an amount of data
  * @param  Address£ºstart address
  * @param  DataArray£ºData being read out
  * @param  Count£ºNumber of bytes
  * @retval None
  */
static void APP_P25Q128_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
  uint8_t cmd[3] = {0};
  uint8_t *pbuf = DataArray;
  uint32_t rxcnt = Count;
  
  WriteEnable();
  
  /*Pull down NSS*/
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
  
  /*Send read instruction*/
  cmd[0] = P25Q128_READ_DATA;
  APP_SPITransmit(&cmd[0]);
  
  /*Send address*/
  cmd[0] = (uint8_t)(Address >> 16);
  cmd[1] = (uint8_t)(Address >> 8);
  cmd[2] = (uint8_t)Address;
  APP_SPITransmit(&cmd[0]);
  APP_SPITransmit(&cmd[1]);
  APP_SPITransmit(&cmd[2]);
  
  /*read data*/
  while(rxcnt > 0)
  {
    APP_SPIReceive(pbuf);
    pbuf++;
    rxcnt--;
  }
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
}

void usbd_msc_get_cap(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
    *block_num = BLOCK_COUNT; 
    *block_size = BLOCK_SIZE;
}

int usbd_msc_sector_read(uint32_t sector, uint8_t *buffer, uint32_t length)
{
  APP_P25Q128_ReadData(sector * BLOCK_SIZE, buffer, length);

  return 0;
}

int usbd_msc_sector_write(uint32_t sector, uint8_t *buffer, uint32_t length)
{
    uint8_t *pbuf  = buffer;
    uint32_t tempadr = sector * BLOCK_SIZE;
    uint32_t writecnt = length;
    uint32_t nbsectors = (length+BLOCK_SIZE-1)/BLOCK_SIZE;

    for(uint32_t i = 0; i<nbsectors; i++)
    {
      APP_P25Q128_SectorErase(tempadr);
      tempadr += BLOCK_SIZE;
    }
  
    tempadr = sector * BLOCK_SIZE;
    while(writecnt > 0)
    {
      if(writecnt > DISK_PAGE_SIZE)
      {
        APP_P25Q128_PageProgram(tempadr, pbuf, DISK_PAGE_SIZE);
        writecnt -= DISK_PAGE_SIZE;
        tempadr += DISK_PAGE_SIZE;
        pbuf += DISK_PAGE_SIZE;
      }
      else
      {
        APP_P25Q128_PageProgram(tempadr, pbuf, writecnt);
        tempadr += writecnt;
        pbuf += writecnt;
        writecnt = 0;
        break;
      }
    }

    return 0;
}

struct usbd_interface intf0;

void msc_ram_init(void)
{
    usbd_desc_register(msc_flash_descriptor);
    usbd_add_interface(usbd_msc_init_intf(&intf0, MSC_OUT_EP, MSC_IN_EP));

    usbd_initialize();
}
