
#ifndef AGNETAOS_CONFIG_H
#define AGNETAOS_CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

#define AGNETAOS_TOTAL_INTERRUPTS 512
// 100MB heap size
#define AGNETAOS_HEAP_SIZE_BYTES 104857600
#define AGNETAOS_HEAP_BLOCK_SIZE 4096

#define AGNETAOS_HEAP_ADDRESS 0x01000000
#define AGNETAOS_HEAP_TABLE_ADDRESS 0x00007E00

#define AGNETAOS_SECTOR_SIZE 512

#define AGNETAOS_MAX_FILESYSTEMS 12
#define AGNETAOS_MAX_FILE_DESCRIPTORS 512

#define AGNETAOS_MAX_PATH 108

#endif //AGNETAOS_CONFIG_H
