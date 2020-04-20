#pragma once
#include "cyhal.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*

How do you handle?
	DMA
	Handle multiple devices per BUS
	what about non-uniform sectors?
	advanced sector protection

	fast read
	rtos wait? - seamaphore - busyWait?

	There is no efficent way to implement isBusy because you cant keep clocking..

Todo:
	device signature
	manufactuere signature
	quad enable (need to read about dual/octa)
	sfdp
*/

// Additions to the Cypress HAL //

typedef enum cyhal_qspi_datarate {
	CYHAL_QSPI_CFG_DATARATE_UNKNOWN,
	CYHAL_QSPI_CFG_DATARATE_SDR,
	CYHAL_QSPI_CFG_DATARATE_DDR
} cyhal_qspi_datarate_t;

/******************************************************************************************************
 * 
 * General
 *  
 * ****************************************************************************************************/


typedef enum {
    IOTEXPERT_NOR_ERASE_SECTOR,
    IOTEXPERT_NOR_ERASE_BLOCK,
    IOTEXPERT_NOR_ERASE_CHIP,
} iotexpert_nor_erase_commands_t;

typedef struct {
	cyhal_qspi_t *qspi;
	uint32_t chipSize; 
	uint32_t numSectors;
	uint32_t sectorSize;

	uint32_t pageSize;
	uint32_t numPages;

	uint32_t blockSize;
	uint32_t numBlocks;

	cyhal_qspi_command_t *cmdRead;
	cyhal_qspi_command_t *cmdPageProgram;
	cyhal_qspi_command_t *cmdReadSr1;
	cyhal_qspi_command_t *cmdWren;
	cyhal_qspi_command_t *cmdEraseSector;
	cyhal_qspi_command_t *cmdEraseBlock;
	cyhal_qspi_command_t *cmdEraseChip;
	
} iotexpert_nor_t;

typedef struct {

} iot_nor_commands_t;


cy_rslt_t iotexpert_nor_init(iotexpert_nor_t *nor,cyhal_qspi_t *qspi);

// ARH Not Done
cy_rslt_t iotexpert_nor_sfdp(iotexpert_nor_t *nor);

bool iotexpert_nor_isBusy(iotexpert_nor_t *nor);

cy_rslt_t iotexpert_nor_busyWait(iotexpert_nor_t *nor);

// ARH Not Done
// setAddressWidth(24,32)
cy_rslt_t iotexpert_nor_setAddressWidth(iotexpert_nor_t *nor,cyhal_qspi_size_t size);

// ARH Not Done
cy_rslt_t iotexpert_nor_setIOMode(iotexpert_nor_t *nor,cyhal_qspi_bus_width_t ioMode);
cyhal_qspi_bus_width_t iotexpert_nor_getIOMode(iotexpert_nor_t *nor);

// ARH Not Done
cy_rslt_t iotexpert_nor_setDataRate(iotexpert_nor_t *nor,cyhal_qspi_datarate_t dataRate);
cyhal_qspi_datarate_t iotexpert_nor_getDataRate(iotexpert_nor_t *nor);


// Information About the Flash
uint32_t iotexpert_nor_getSizeBytes(iotexpert_nor_t *nor);

uint32_t iotexpert_nor_getSectorSizeBytes(iotexpert_nor_t *nor);
uint32_t iotexpert_nor_getNumSectors(iotexpert_nor_t *nor);

uint32_t iotexpert_nor_getPageSizeBytes(iotexpert_nor_t *nor);
uint32_t iotexpert_nor_getNumPages(iotexpert_nor_t *nor);

uint32_t iotexpert_nor_getBlockSizeBytes(iotexpert_nor_t *nor);
uint32_t iotexpert_nor_getNumBlocks(iotexpert_nor_t *nor);

// setWriteEnable - must do this before erase or page
cy_rslt_t iotexpert_nor_writeEnable(iotexpert_nor_t *nor);

// ARH Not Done
// 3-return 3 bytes MFG ID << 16 + device id 16-bits ... use command 9Fh
uint32_t iotexpert_nor_readMfgId(iotexpert_nor_t *nor);

// ARH Not Done
// sleep - deepSleep
cy_rslt_t iotexpert_nor_deepSleep(iotexpert_nor_t *nor);


// S=SDR D=DDR (P6 SMIF cant do D) ... what about >1 commands?
typedef enum {
    iotexpert_nor_1S1S1S,
	iotexpert_nor_1S1S2S,
 	iotexpert_nor_1S1S4S,
    iotexpert_nor_1S1S8S,
	iotexpert_nor_1S2S2S,
    iotexpert_nor_1S4S4S,
    iotexpert_nor_1S8S8S,

} iotexpert_nor_mode_t;

/******************************************************************************************************
 * 
 * Read
 *  
 *****************************************************************************************************/


// Use best known method to read
cy_rslt_t iotexpert_nor_readSync(iotexpert_nor_t *nor,uint32_t address,uint8_t *buffer,size_t *length);

// ARH Not Done
cy_rslt_t iotexpert_nor_readASync(iotexpert_nor_t *nor,uint32_t address,uint8_t *buffer,uint32_t *length);

// ARH Not Done
cy_rslt_t iotexpert_nor_readModeSync(iotexpert_nor_t *nor,iotexpert_nor_mode_t mode,uint8_t *buffer,uint32_t *length);
// ARH Not Done
cy_rslt_t iotexpert_nor_readModeAync(iotexpert_nor_t *nor,iotexpert_nor_mode_t mode,uint8_t *buffer,uint32_t *length);


// ARH Not Done
cy_rslt_t iotexpert_nor_selectBank(iotexpert_nor_t *nor,uint32_t bank);

/******************************************************************************************************
 * 
 * Erase
 *  
 *****************************************************************************************************/


cy_rslt_t iotexpert_nor_eraseSync(iotexpert_nor_t *nor,iotexpert_nor_erase_commands_t type,uint32_t area);

/******************************************************************************************************
 * 
 * Write
 *  
 * ****************************************************************************************************/

cy_rslt_t iotexpert_nor_programPageSync(iotexpert_nor_t *nor,uint32_t address,uint8_t *buffer,size_t* length);

#if defined(__cplusplus)
}
#endif