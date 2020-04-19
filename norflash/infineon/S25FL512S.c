#include "cyhal.h"
#include "iotexpert-nor.h"
#if 0

typedef struct cyhal_qspi_command {
    struct {
        cyhal_qspi_bus_width_t bus_width;               /**< Bus width for the instruction */
        uint8_t value;                                  /**< Instruction value */
        bool disabled;                                  /**< Instruction phase skipped if disabled is set to true */
    } instruction;                                      /**< Instruction structure */
    struct {
        cyhal_qspi_bus_width_t bus_width;               /**< Bus width for the address */
        cyhal_qspi_size_t size;                         /**< Address size */
        uint32_t value;                                 /**< Address value */
        bool disabled;                                  /**< Address phase skipped if disabled is set to true */
    } address;                                          /**< Address structure */
    struct {
        cyhal_qspi_bus_width_t bus_width;               /**< Bus width for mode bits  */
        cyhal_qspi_size_t size;                         /**< Mode bits size */
        uint32_t value;                                 /**< Mode bits value */
        bool disabled;                                  /**< Mode bits phase skipped if disabled is set to true */
    } mode_bits;                                        /**< Mode bits structure */
    uint8_t dummy_count;                                /**< Dummy cycles count */
    struct {
        cyhal_qspi_bus_width_t bus_width;               /**< Bus width for data */
    } data;                                             /**< Data structure */
} cyhal_qspi_command_t;

#endif

cyhal_qspi_command_t S25FL512_cmdRdSr1 = {
    .instruction = {
        .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .value = 0x05,
        .disabled = false,
    },
    .address = {
        .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .size = 0,
        .value = 0,
        .disabled = true,
    },
    .mode_bits =     {
         .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .size = 0,
        .value = 0,
        .disabled = true,
    },
    .dummy_count = 0,
    .data = { .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE },
};



cyhal_qspi_command_t S25FL512_cmdWren = {
    .instruction = {
        .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .value = 0x06,
        .disabled = false,
    },
    .address = {
        .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .size = 0,
        .value = 0,
        .disabled = true,
    },
    .mode_bits =     {
         .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .size = 0,
        .value = 0,
        .disabled = true,
    },
    .dummy_count = 0,
    .data = { .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE },
};


 cyhal_qspi_command_t S25FL512_cmdEraseSector = {
    .instruction = {
        .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .value = 0xdc,
        .disabled = false,
    },
    .address = {
        .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .size = CYHAL_QSPI_CFG_SIZE_32,
        .value = 0,
        .disabled = false,
    },
    .mode_bits =     {
         .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .size = 0,
        .value = 0,
        .disabled = true,
    },
    .dummy_count = 0,
    .data = { .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE },
};

// Bulk Erase
cyhal_qspi_command_t S25FL512_cmdEraseChip = {
    .instruction = {
        .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .value = 0x60,
        .disabled = false,
    },
    .address = {
        .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .size = 0,
        .value = 0,
        .disabled = true,
    },
    .mode_bits =     {
         .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .size = 0,
        .value = 0,
        .disabled = true,
    },
    .dummy_count = 0,
    .data = { .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE },
};


// Read
cyhal_qspi_command_t S25FL512_cmdRead = {
    .instruction = {
        .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .value = 0x13,
        .disabled = false,
    },
    .address = {
        .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .size = CYHAL_QSPI_CFG_SIZE_32,
        .value = 0,
        .disabled = false,
    },
    .mode_bits =     {
         .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .size = 0,
        .value = 0,
        .disabled = true,
    },
    .dummy_count = 0,
    .data = { .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE },
};



cyhal_qspi_command_t S25FL512_cmdProgramPage = {
    .instruction = {
        .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .value = 0x12,
        .disabled = false,
    },
    .address = {
        .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .size = CYHAL_QSPI_CFG_SIZE_32,
        .value = 0,
        .disabled = false,
    },
    .mode_bits =     {
         .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE,
        .size = 0,
        .value = 0,
        .disabled = true,
    },
    .dummy_count = 0,
    .data = { .bus_width = CYHAL_QSPI_CFG_BUS_SINGLE },
};


// Read SFDP (RSFDP 5ah)
// Read Status Register (RDSR1 05h) - you can keep clocking and it will re-read
// Write Registers (WRR 01h)
// Write Enable (WREN 06h)
// Write Disable (WRDI 04h)
// Clear Status Register (CLSR 30h)

// Configuration register
// B1 = Quad enable 1, quad disable 0
// Read Configuration Register (RDCR 35h), 
// Write Registers (WRR 01h).

/////// legacy command
// Bank Register Access (BRAC B9h)
// Write Register (WRR 01h)
// Bank Register Read (BRRD 16h)
// Bank Register Write (BRWR 17h).
// B7 = 1 is 4 byte address B7=0 is 3 byte address
// Bits 0:1 are A24 and A25

// 16h Bank Register Read
// 17h Bank Register Write 



#if 0

#endif

cy_rslt_t S25FL512S_init(iotexpert_nor_t *nor)
{
    nor->chipSize = 512 / 8 * 1024 * 1024; 
    nor->numSectors = 256;
    nor->sectorSize = 256*1024;

    nor->pageSize = 512;
    nor->numPages = nor->chipSize/nor->pageSize;

	nor->cmdRead = &S25FL512_cmdRead;
	nor->cmdPageProgram = &S25FL512_cmdProgramPage;
	nor->cmdReadSr1 = &S25FL512_cmdRdSr1;
	nor->cmdWren = &S25FL512_cmdWren;
	nor->cmdEraseSector = &S25FL512_cmdEraseSector;
	nor->cmdEraseBlock = 0;
	nor->cmdEraseChip = &S25FL512_cmdEraseChip;

    return CY_RSLT_SUCCESS;
}

