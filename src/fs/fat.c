#include <fs/fat.h>

#define OFFSET 2048

BootSector bootSector;
uint32_t reservedSectorCount, fatTableSectorCount, rootSectorCount, dataBlockBegin, rootBegin;
RootDirectory rootDirectory[896];           // (0xA000 - 0x3000) / 0x20
FatTableEntry fat[170];                     // 4096 / 24 = 170
uint8_t Textfile[512 * 8];
int *fatBlocks;

bool readBootSector()
{
    read_sectors(&bootSector, OFFSET + 0, 1);
}

void initGlobalVariables()
{
    reservedSectorCount = bootSector.bdb_reserved_sector;
    fatTableSectorCount = bootSector.bdb_fat_count * bootSector.bdb_sectors_per_fat;
    rootSectorCount = (bootSector.bdb_dir_entries_count * 32)/ bootSector.bdb_bytes_per_sector;
    dataBlockBegin = OFFSET + reservedSectorCount + fatTableSectorCount + rootSectorCount;
    rootBegin = OFFSET + reservedSectorCount + fatTableSectorCount;
}

void readFat()
{
    read_sectors(fat, OFFSET + reservedSectorCount, 8);
    // for(int i = 0; i < 10; i++)
    // {
    //     print_hex(fat[i].fatBlock);
    //     printf(" ");
    // }
}

// int strcmp1(char* str1, char* str2)
// {
//     int i = 0;
//     while(str1[i] == str2[i])
//     {
//         if(str2[i+1]=='\0') return 1;
//         i++;
//     }
//     return 0;
// }

RootDirectory* searchInRoot(char* filename)
{
    read_sectors(rootDirectory, rootBegin, 0x38);
    // printf(rootDirectory[3].file_name);
    for(int i = 0; i < bootSector.bdb_dir_entries_count; i++)
    {
        if(strcmp(filename, rootDirectory[i].file_name) == 1)
        {
            printf("Found File!!!\n");
            return &rootDirectory[i];
        }
    }
    printf("File Not Found!!!\n");
    return NULL;
}

uint16_t findLBA(uint16_t cluster)
{
    uint16_t lba = dataBlockBegin + (cluster - 2) * bootSector.bdb_sectors_per_cluster;
    return lba;
}

void readFile(uint16_t lba)
{
    read_sectors(Textfile, lba, 1);
}

uint16_t getNextCluster(uint16_t cluster)
{
    int index = cluster / 2;
    if(cluster % 2 == 0)
        return fat[index].fatBlock & 0x000FFF;
    return (fat[index].fatBlock & 0xFFF000) >> 12;
}

void findFile(char* filename)
{
    RootDirectory* fileroot = searchInRoot(filename);
    int numBlocks = fileroot->sizeOfFile / (bootSector.bdb_bytes_per_sector * bootSector.bdb_sectors_per_cluster) + 1;

    uint16_t cluster = fileroot->lower16;

    char a[2];

    for(int i = 0; i < numBlocks; i++)
    {
        uint16_t lba = findLBA(cluster);
        readFile(lba);
        for(int j = 0; j < bootSector.bdb_bytes_per_sector * bootSector.bdb_sectors_per_cluster; j++)
        {
            a[1] = '\0';
            a[0] = Textfile[j];
            printf(a);
        }

        // printf("\n END OF FILE \n");
        cluster = getNextCluster(cluster);
    }

}

void printBootSector()
{
    // printf("Bytes per Sector: %x", bootSector.bdb_bytes_per_sector);
    // printf("\nDir Entries :%x", bootSector.bdb_dir_entries_count);
    // print_hex();
    // printf("\nReserved Sector Count: ");
    // print_hex(bootSector.bdb_reserved_sector);
    // printf("\nFat table count: ");
    // print_hex(bootSector.bdb_fat_count);
    // printf("\nSectors per Cluster: ");
    // print_hex(bootSector.bdb_sectors_per_cluster);
    // printf("\nTotal Sectors:  ");
    // print_hex(bootSector.bdb_total_sectors);
    // printf("\nSectors per fat:  ");
    // print_hex(bootSector.bdb_sectors_per_fat);
}

void printGlobalVariables()
{
    // printf("\nReserved Sector Count: ");
    // print_hex(reservedSectorCount);
    // printf("\nFatTableSectorCount:  ");
    // print_hex(fatTableSectorCount);
    // printf("\nRootSectorCount:  ");
    // print_hex(rootSectorCount);
    // printf("\nFat Table Begin:  ");
    // print_hex(0x01);
    // printf("\nRootBegin:  ");
    // print_hex(rootBegin);
    // printf("\nDataBegin:  ");
    // print_hex(dataBlockBegin);
}