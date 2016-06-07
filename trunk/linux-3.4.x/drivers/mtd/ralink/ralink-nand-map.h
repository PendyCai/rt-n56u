#ifndef __RALINK_NAND_MAP_H__
#define __RALINK_NAND_MAP_H__

#define NAND_MTD_BOOT_PART_SIZE		CONFIG_MTD_BOOTLOADER_PART_SIZ
#define NAND_MTD_BOOTENV_PART_SIZE	CONFIG_MTD_BOOTENV_PART_SIZ
#define NAND_MTD_FACTORY_PART_SIZE	CONFIG_MTD_FACTORY_PART_SIZ
#define NAND_MTD_KERNEL_PART_SIZE	CONFIG_MTD_FIRMWARE_PART_SIZ
#define NAND_MTD_CONFIG_PART_SIZE	CONFIG_MTD_CONFIG_PART_SIZ
#define NAND_MTD_STORE_PART_SIZE	CONFIG_MTD_STORE_PART_SIZ

#if defined (CONFIG_MTD_CONFIG_PART_BELOW)
#define NAND_MTD_KERNEL_PART_IDX	3
#define NAND_MTD_KERNEL_PART_OFFSET	(NAND_MTD_BOOT_PART_SIZE + NAND_MTD_BOOTENV_PART_SIZE + NAND_MTD_FACTORY_PART_SIZE)
#define NAND_MTD_RWFS_PART_OFFSET	(NAND_MTD_KERNEL_PART_OFFSET + NAND_MTD_KERNEL_PART_SIZE + NAND_MTD_CONFIG_PART_SIZE + NAND_MTD_STORE_PART_SIZE)
#else
#define NAND_MTD_KERNEL_PART_IDX	4
#define NAND_MTD_KERNEL_PART_OFFSET	(NAND_MTD_BOOT_PART_SIZE + NAND_MTD_BOOTENV_PART_SIZE + NAND_MTD_CONFIG_PART_SIZE + NAND_MTD_FACTORY_PART_SIZE)
#define NAND_MTD_RWFS_PART_OFFSET	(NAND_MTD_KERNEL_PART_OFFSET + NAND_MTD_KERNEL_PART_SIZE + NAND_MTD_STORE_PART_SIZE)
#endif

#if defined (CONFIG_RT2880_ROOTFS_IN_FLASH)
#define NAND_MTD_ROOTFS_PART_IDX	(NAND_MTD_KERNEL_PART_IDX + 1)
#define NAND_MTD_RWFS_PART_IDX		7
#else
#define NAND_MTD_RWFS_PART_IDX		6
#endif




#ifdef BOARD_SKYRN1

#undef  NAND_MTD_RWFS_PART_IDX   
#define NAND_MTD_RWFS_PART_IDX      6

#undef  NAND_MTD_KERNEL_PART_IDX
#define NAND_MTD_KERNEL_PART_IDX    3
static struct mtd_partition rt2880_partitions[] = {

    /* mtd0 */
    {
        name    :   "Bootloader",
        size    :   0x100000,
        offset  :   0,
    },
    /* mtd1 */
    {
        name    :   "Config",
        size    :   0x80000,
        offset  :   0x200000,
    },
    /* mtd2 */
    {
        name    :   "Factory",
        size    :   0x80000,
        offset  :   0x300000,
    },
    /* mtd3 */
    {
        name    :   "Linux",
        size    :   0xA00000,
        offset  :   0x400000,
    },
    /* mtd4 */
    {
        name    :   "RootFS",
        size    :   0xF00000,
        offset  :   0x1000000,
    },
    /* mtd5 */
    {
        name    :   "Storage",
        size    :   0x400000,
        offset  :   0x2000000,
    },
    /* mtd6 */
    {
        name    :   "RWFS",
        size    :   0x800000,
        offset  :   0x2600000,
    },
    /* mtd7 */
    {
        name    :   "Firmware_Stub",
        size    :   0xC00000,
        offset  :   0x3000000,
    },

};

#else
static struct mtd_partition rt2880_partitions[] = {
	{
		name:   "Bootloader",			/* mtdblock0 */
		size:   NAND_MTD_BOOT_PART_SIZE,	/* 512K */
		offset: 0,
	}, {
		name:   "BootEnv",			/* mtdblock1 */
		size:   NAND_MTD_BOOTENV_PART_SIZE,	/* 256K */
		offset: MTDPART_OFS_APPEND,
#if !defined (CONFIG_MTD_CONFIG_PART_BELOW)
	}, {
		name:   "Config",			/* mtdblock2 */
		size:   NAND_MTD_CONFIG_PART_SIZE,	/* 1024K */
		offset: MTDPART_OFS_APPEND,
#endif
	}, {
		name:   "Factory",			/* mtdblock3 */
		size:   NAND_MTD_FACTORY_PART_SIZE,	/* 256K */
		offset: MTDPART_OFS_APPEND,
	}, {
		name:   "Kernel",			/* mtdblock4 */
		size:   NAND_MTD_KERNEL_PART_SIZE,	/* 16M */
		offset: NAND_MTD_KERNEL_PART_OFFSET,
#if defined (CONFIG_RT2880_ROOTFS_IN_FLASH)
	}, {
		name:   "RootFS",			/* mtdblock5 */
		size:   0,				/* calc */
		offset: MTDPART_OFS_APPEND,
#endif
#if defined (CONFIG_MTD_CONFIG_PART_BELOW)
	}, {
		name:   "Config",			/* mtdblockX */
		size:   NAND_MTD_CONFIG_PART_SIZE,	/* 1024K */
		offset: MTDPART_OFS_APPEND,
#endif
	}, {
		name:   "Storage",			/* mtdblock6 */
		size:   NAND_MTD_STORE_PART_SIZE,	/* 2M */
		offset: MTDPART_OFS_APPEND,
	}, {
		name:   "RWFS",				/* mtdblock7 */
		size:   0,				/* calc */
		offset: MTDPART_OFS_APPEND,
	}, {
		name:   "Firmware_Stub",		/* mtdblock8 */
		size:   NAND_MTD_KERNEL_PART_SIZE,	/* Kernel+RootFS */
		offset: NAND_MTD_KERNEL_PART_OFFSET,
	}
};


#endif

inline void recalc_partitions(uint64_t flash_size, uint32_t kernel_size)
{
#ifndef BOARD_SKYRN1

	/* calc "Kernel" size */
  #if defined (CONFIG_RT2880_ROOTFS_IN_FLASH)
    #if defined (CONFIG_ROOTFS_IN_FLASH_NO_PADDING)
	  rt2880_partitions[NAND_MTD_KERNEL_PART_IDX].size = kernel_size;
    #else
	  rt2880_partitions[NAND_MTD_KERNEL_PART_IDX].size = CONFIG_MTD_KERNEL_PART_SIZ;
    #endif
    /* calc "RootFS" size */
	rt2880_partitions[NAND_MTD_ROOTFS_PART_IDX].size = NAND_MTD_KERNEL_PART_SIZE - rt2880_partitions[NAND_MTD_KERNEL_PART_IDX].size;
  #endif

	/* calc "RWFS" size (UBIFS or JFFS2) */
	rt2880_partitions[NAND_MTD_RWFS_PART_IDX].size = flash_size - NAND_MTD_RWFS_PART_OFFSET;

#endif
}

#endif
