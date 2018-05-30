#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

void sync_drives()
{
    system("sync");
}

void format_and_mount(std::string drive)
{
    std::stringstream buffer;
    //format
    buffer << "mkfs.fat " << drive;
    std::string string_buffer = buffer.str();
    system(string_buffer.c_str());
    buffer.str("");
    //mount
    system("mkdir /tmp/dpGPG");
    buffer << "mount " << drive << " /tmp/dpGPG";
    string_buffer = buffer.str();
    system(string_buffer.c_str());
    buffer.str("");
}

void clear_folders()
{
    system("umount /tmp/dpGPG");
    system("rm -r /tmp/dpGPG");
}

std::string usage_info()
{
    return "dpGPG pendrive generator by Mateusz d3s Dukat\n./dpGPG <pendrive_device> <full_path_to_secring.gpg>";
}

std::string permission_test_failed()
{
    return "Failed to open device!";
}

std::string int_to_hex(unsigned int input_int)
{
    std::stringstream buffer;
    std::string returned;
    buffer << std::hex << input_int;
    buffer >> returned;
    return returned;
}

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

int main(int argc, char *argv[])
{
    if(!argv[2]){
        std::cout << usage_info() << std::endl;
        return -1;
    }

    std::ifstream permission_test (argv[1]);
    if(permission_test.fail()){
        std::cout << permission_test_failed() << std::endl;
        return -1;
    }
    permission_test.close();

    //Generation of first block
    std::cout << "Generating MBR and partition table...\n";
    char MBR_array[512];
    char partition_table[64];
    partition_table_gen(partition_table);
    for(int i = 0; i <= 511; i++)
    {
        MBR_array[i] = '\x00';
    }
    for(int i = 0; i <= 63; i++)
    {
        MBR_array[446+i] = partition_table[i];
    }
    MBR_array[510] = '\x55';
    MBR_array[511] = '\xaa';

    //Putting new MBR on drive
    std::cout << "Putting generated MBR on drive...\n";
    std::ofstream MBR_file (argv[1]);
    for(int i = 0; i <= 511; i++)
    {
        MBR_file.put(MBR_array[i]);
    }
    MBR_file.close();

    //Syncing drives
    std::cout << "Syncing drives...\n";
    sync_drives();

    //Format new partition and mount it
    std::cout << "Formatting and mounting 1MB partition...\n";
    std::stringstream quick_stream_buffer;
    quick_stream_buffer << argv[1] << "1";
    format_and_mount(quick_stream_buffer.str());
    quick_stream_buffer.str("");

    //Put secring.gpg on pendrive
    std::cout << "Putting secring.gpg on pendrive...\n";
    // see todo

    //Clear folders etc
    std::cout << "Clearing stuff...\n";
    clear_folders();

    std::cout << "Work done. Have a nice day :P" << std::endl;
    return 0;
}
