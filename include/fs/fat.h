#ifndef __FAT__
#define __FAT__

#include <drivers/hdd.h>
#include <drivers/screen.h>
#include <lib/string.h>
#include <ports.h>
#include <types.h>

#define NULL 0

typedef struct {
    uint8_t bdb_short_jump[3];
    uint8_t     bdb_oem[8];
    uint16_t    bdb_bytes_per_sector;
    uint8_t     bdb_sectors_per_cluster;
    uint16_t    bdb_reserved_sector;
    uint8_t     bdb_fat_count;
    uint16_t    bdb_dir_entries_count;    
    uint16_t    bdb_total_sectors;     
    uint8_t     bdb_media_descriptor_type;
    uint16_t    bdb_sectors_per_fat;      
    uint16_t    bdb_sectors_per_track;
    uint16_t    bdb_heads;      
    uint32_t    bdb_hidden_sectors;
    uint32_t    bdb_large_sector_count;

    // Extended Boot Record
    uint8_t drive_number;
    uint8_t reserved;
    uint8_t signature;
    uint8_t volume_id[4];
    uint8_t volume_label[11];
    uint8_t system_id[8];
}__attribute__((packed)) BootSector;

typedef struct {
    uint8_t file_name[11];
    uint8_t attributes;
    uint8_t windowsNT;
    uint8_t creationTime;
    uint16_t creationTimeInSeconds;
    uint16_t date;
    uint16_t lastAccessedDate;
    uint16_t high16;
    uint16_t lastModifiedTime;
    uint16_t lastModifiedDate;
    uint16_t lower16;
    uint32_t sizeOfFile;
}__attribute__((packed)) RootDirectory;

typedef struct {
    uint32_t fatBlock:24;
}__attribute__((packed)) FatTableEntry;

bool readBootSector();
void initGlobalVariables();
void readFat();


void findFile(char* filename);
RootDirectory* searchInRoot(char* filename);

void printBootSector();
void printGlobalVariables();
#endif