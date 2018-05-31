#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "highlevel.hpp"
#include "partition.hpp"

int main(int argc, char *argv[])
{
    if(!argv[2] || !argv[1]){
        std::cout << "dpGPG pendrive generator by Mateusz d3s Dukat\n./dpGPG <pendrive_device> <full_path_to_secring.gpg>" << std::endl;
        return 1;
    }

    std::ifstream permission_test (argv[1]);
    if(permission_test.fail()){
        std::cout << "Failed to open device!" << std::endl;
        return 1;
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

    //dpGPG magic bytes (first byte stay 0x00)
    MBR_array[1] = 'd';
    MBR_array[2] = 'p';
    MBR_array[3] = 'g';
    MBR_array[4] = 'p';
    MBR_array[5] = 'g';

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
    int format_state = format_and_mount(quick_stream_buffer.str());
    quick_stream_buffer.str("");

    if(format_state == 1)
    {
        std::cout << "[ERROR] mkfs.fat error! Clearing stuff and exiting...\n";
        clear_folders();
        return 1;
    } else if(format_state == 2)
    {
        std::cout << "[ERROR] mkdir /tmp/dpGPG error! Clearing stuff and exiting...\n";
        clear_folders();
        return 1;
    } else if(format_state == 3)
    {
        std::cout << "[ERROR] mount error! Clearing stuff and exiting...\n";
        clear_folders();
        return 1;
    }

    //Put secring.gpg on pendrive
    std::cout << "Putting secring.gpg on pendrive...\n";
    int copy_state = copy_secring(argv[2]);
    if(copy_state == 1)
    {
        std::cout << "[ERROR] secring copy failed! Clearing stuff and exiting...\n";
        clear_folders();
        return 1;
    }

    //Clear folders etc
    std::cout << "Clearing stuff...\n";
    clear_folders();

    std::cout << "Work done. Have a nice day :P" << std::endl;
    return 0;
}
