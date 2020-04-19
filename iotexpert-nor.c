
#include "cyhal.h"
#include <stdio.h>
#include "iotexpert-nor.h"
#include "S25FL512S.h"

cy_rslt_t iotexpert_nor_init(iotexpert_nor_t *nor,cyhal_qspi_t *qspi)
{
    memset(nor,0,sizeof(iotexpert_nor_t));
    nor->qspi = qspi;
    return CY_RSLT_SUCCESS;
}

cy_rslt_t iotexpert_nor_sfdp(iotexpert_nor_t *nor)
{

    printf("Started SFDP\n");
    return CY_RSLT_SUCCESS;
}


bool iotexpert_nor_isBusy(iotexpert_nor_t *nor)
{
    uint8_t sr1;
    size_t length = 1;
    cy_rslt_t rslt = cyhal_qspi_read(nor->qspi, nor->cmdReadSr1, &sr1, &length);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS);
    return (sr1 & 0x01);
}

cy_rslt_t iotexpert_nor_busyWait(iotexpert_nor_t *nor)
{
    while(iotexpert_nor_isBusy(nor));
    printf("done\n");
    return CY_RSLT_SUCCESS;
}


cy_rslt_t iotexpert_nor_writeEnable(iotexpert_nor_t *nor)
{
    cy_rslt_t result = cyhal_qspi_transfer(nor->qspi, nor->cmdWren, NULL, 0, NULL, 0);
    return result;

}

cy_rslt_t iotexpert_nor_erase(iotexpert_nor_t *nor,iotexpert_nor_erase_commands_t type,uint32_t area)
{
    cy_rslt_t result;
    result = iotexpert_nor_writeEnable(nor);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    switch(type)
    {
        case IOTEXPERT_NOR_ERASE_SECTOR:
            nor->cmdEraseSector->address.value=area;
            result = cyhal_qspi_transfer(nor->qspi, nor->cmdEraseSector, NULL, 0, NULL, 0);
        break;
        case IOTEXPERT_NOR_ERASE_BLOCK:
            CY_ASSERT(0); // ARH THIS IS BAD
        break;
        case IOTEXPERT_NOR_ERASE_CHIP:
            result = cyhal_qspi_transfer(nor->qspi,nor->cmdEraseChip, NULL, 0, NULL, 0);
        break;

    }

    return result;
}


// Information About the Flash
uint32_t iotexpert_nor_getSizeBytes(iotexpert_nor_t *nor)
{
    return nor->chipSize;
}

uint32_t iotexpert_nor_getSectorSizeBytes(iotexpert_nor_t *nor)
{
    return nor->sectorSize;
}

uint32_t iotexpert_nor_getNumSectors(iotexpert_nor_t *nor)
{
    return nor->numSectors;
}

uint32_t iotexpert_nor_getPageSizeBytes(iotexpert_nor_t *nor)
{
    return nor->pageSize;
}

uint32_t iotexpert_nor_getNumPages(iotexpert_nor_t *nor)
{
    return nor->numPages;
}

uint32_t iotexpert_nor_getBlockSizeBytes(iotexpert_nor_t *nor)
{
    return nor->blockSize;
}

uint32_t iotexpert_nor_getNumBlocks(iotexpert_nor_t *nor)
{
    return nor->numBlocks;
}


cy_rslt_t iotexpert_nor_readSync(iotexpert_nor_t *nor,uint32_t address,uint8_t *buffer,size_t *length)
{
    nor->cmdRead->address.value = address;
    cy_rslt_t result = cyhal_qspi_read(nor->qspi, nor->cmdRead, buffer, length);
    return result;
}

cy_rslt_t iotexpert_nor_programPageSync(iotexpert_nor_t *nor,uint32_t address,uint8_t *buffer,size_t* length)
{
    cy_rslt_t result;
    
    iotexpert_nor_writeEnable(nor);

    nor->cmdPageProgram->address.value = address;
    result = cyhal_qspi_write(nor->qspi, nor->cmdPageProgram, buffer, length);
    iotexpert_nor_busyWait(nor);
    return result;

}
