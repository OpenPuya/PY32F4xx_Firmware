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

#define DISK_BASE_ADDR 0x08008000
#define DISK_PAGE_SIZE 256

#define BLOCK_SIZE  512
#define BLOCK_COUNT 704

void usbd_msc_get_cap(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
    *block_num = BLOCK_COUNT; 
    *block_size = BLOCK_SIZE;
}

int usbd_msc_sector_read(uint32_t sector, uint8_t *buffer, uint32_t length)
{
    uint32_t *pSrc,*pDst;
    uint32_t index = 0;
    pSrc = (uint32_t *)(DISK_BASE_ADDR+sector*BLOCK_SIZE);
    pDst = (uint32_t *)buffer;
    
    for(index=0; index<(length/4); index++)
    {
        pDst[index] = pSrc[index];
    }

    return 0;
}

int usbd_msc_sector_write(uint32_t sector, uint8_t *buffer, uint32_t length)
{
    uint32_t index, PAGEError = 0;
    uint32_t *ptr;
    FLASH_EraseInitTypeDef EraseInitStruct;
  
    /* FLASH unlock */
    HAL_FLASH_Unlock();
  
    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGEERASE;              /* Select Page erase */
    EraseInitStruct.PageAddress = DISK_BASE_ADDR+sector*BLOCK_SIZE;       /* Erase start address */
    EraseInitStruct.NbPages  = (length+DISK_PAGE_SIZE-1)/DISK_PAGE_SIZE;  /* The number of pages to be erased */
    HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);                      /* Execute page erase,PAGEError indicate 
                                                                             the erase error page, 0xFFFFFFFF means that erase successfully*/

    for (index=0; index<EraseInitStruct.NbPages; index++)
    {
        ptr = (uint32_t *)(buffer+DISK_PAGE_SIZE*index);
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, (EraseInitStruct.PageAddress + DISK_PAGE_SIZE*index), ptr);
    }
    
    /* FLASH lock */
    HAL_FLASH_Lock();

    return 0;
}

struct usbd_interface intf0;

void msc_ram_init(void)
{
    usbd_desc_register(msc_flash_descriptor);
    usbd_add_interface(usbd_msc_init_intf(&intf0, MSC_OUT_EP, MSC_IN_EP));

    usbd_initialize();
}
