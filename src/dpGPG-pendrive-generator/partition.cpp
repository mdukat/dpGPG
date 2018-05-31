void partition_table_gen(
    char* partition_table, // pointer to partition table char array
    bool boot_indicator = false, // Active = True, Inactive = False
    char partition_id = '\x0c') // Partition type (0x0C == FAT32)
{
    switch(boot_indicator)
    {
        case true:
            partition_table[0] = '\x80';
        case false:
            partition_table[0] = '\x00';
    }
    partition_table[1] = '\x21';
    partition_table[2] = '\x03';
    partition_table[3] = '\x00';
    partition_table[4] = partition_id;
    partition_table[5] = '\x42';
    partition_table[6] = '\x04';
    partition_table[7] = '\x00';

    partition_table[8] = '\x00';
    partition_table[9] = '\x08';
    partition_table[10] = '\x00';
    partition_table[11] = '\x00';

    partition_table[12] = '\x00';
    partition_table[13] = '\x08';
    partition_table[14] = '\x00';
    partition_table[15] = '\x00';

    for(int i = 16; i<=63; i++)
    {
        partition_table[i] = '\x00';
    }
}
