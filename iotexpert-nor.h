#ifndef IOTEXPERT_NOR_H
#define IOTEXPERT_NOR_H

#include "cyhal.h"

/*
SFDP

Read
	Fast/Regular (different clock rate)
	In the modes of:
		1-1-1
		1-1-2
		1-1-4
		1-2-2
		1-4-4

		24-bit address
		32-bit address
	callback & blocking modes

Page Program	
	single/dual/Quad Mode
	callback/blocking

Erase sector, block, chip
	callback/blocking

Set Quad Mode

Check if Busy

How do you handle?
	Switch to Quad mode
	Read busy flag
	DMA
	Handle multiple devices per BUS
	How do you handle banks for large memories
	what about non-uniform sectors?
	advanced sector protection

*/

// Ryan we need double datarate
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

cy_rslt_t iotexpert_nor_sfdp(cyhal_qspi_t *qspi);

// isBusy
cy_rslt_t iotexpert_nor_isBusy(cyhal_qspi_t *qspi);

// setAddressWidth(24,32)
cy_rslt_t iotexpert_nor_setAddressWidth(cyhal_qspi_t *qspi,cyhal_qspi_size_t size);

// setMode(single,dual,quad,octal)
cy_rslt_t iotexpert_nor_setIOMode(cyhal_qspi_t *qspi,cyhal_qspi_bus_width_t ioMode);
cyhal_qspi_bus_width_t iotexpert_nor_getIOMode(cyhal_qspi_t *qspi);

cy_rslt_t iotexpert_nor_setDataRate(cyhal_qspi_t *qspi,cyhal_qspi_datarate_t dataRate);
cyhal_qspi_datarate_t iotexpert_nor_getDataRate(cyhal_qspi_t *qspi);


// Information About the Flash
uint32_t iotexpert_nor_getSizeBytes(cyhal_qspi_t *qspi);

// getNumSectors
uint32_t iotexpert_nor_getSectorSizeBytes(cyhal_qspi_t *qspi);
uint32_t iotexpert_nor_getNumSectors(cyhal_qspi_t *qspi);


// getPageSize
uint32_t iotexpert_nor_getPageSizeBytes(cyhal_qspi_t *qspi);
uint32_t iotexpert_nor_getNumPages(cyhal_qspi_t *qspi);

// getNumBlocks
uint32_t iotexpert_nor_getBlockSizeBytes(cyhal_qspi_t *qspi);
uint32_t iotexpert_nor_getNumBlocks(cyhal_qspi_t *qspi);

// setWriteEnable - must do this before erase or page
cy_rslt_t iotexpert_nor_writeEnable(cyhal_qspi_t *qspi);

/******************************************************************************************************
 * 
 * Erase
 *  
 *****************************************************************************************************/

typedef enum {
    IOTEXPERT_NOR_SECTOR,
    IOTEXPERT_NOR_BLOCK,
    IOTEXPERT_NOR_CHIP

} iotexpert_nor_eraseSize_t;

cy_rslt_t iotexpert_nor_erase(cyhal_qspi_t *qspi,iotexpert_nor_eraseSize_t type,uint32_t area);


/******************************************************************************************************
 * 
 * Read
 *  
 *****************************************************************************************************/

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


// Use best known method to read
cy_rslt_t iotexpert_nor_readSync(cyhal_qspi_t *qspi,uint8_t *buffer,uint32_t *length);
cy_rslt_t iotexpert_nor_readASync(cyhal_qspi_t *qspi,uint8_t *buffer,uint32_t *length);

cy_rslt_t iotexpert_nor_readModeSync(cyhal_qspi_t *qspi,iotexpert_nor_mode_t mode,uint8_t *buffer,uint32_t *length);
cy_rslt_t iotexpert_nor_readModeAync(cyhal_qspi_t *qspi,iotexpert_nor_mode_t mode,uint8_t *buffer,uint32_t *length);


// selectBank()
cy_rslt_t iotexpert_nor_selectBank(cyhal_qspi_t *qspi,uint32_t bank);

/******************************************************************************************************
 * 
 * Write
 *  
 * ****************************************************************************************************/



#endif
