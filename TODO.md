# dpGPG - Pendrive Generator

TODO:
- [x] Cut code into libraries (like mbr.cpp, highlevel.cpp, or something)
- [x] Make code *prettier*
- [x] Do something with these system() things, check if command goes right, and stuff
- [ ] Make protection questions ("Are you sure about that device" etc)
- [x] Don't kill another pendrive
- [ ] Maybe comment a bit more the code in dense places
- [ ] Make partition_table_gen() more dynamic (as in change the input arguments and function to calculate space for encryption buffer and secring)
- [x] Add dpGPG "Magic bytes" to let system daemon know that it is the dpGPG and it have to do stuff with it
- [x] Change /tmp/dpGPG folder to /tmp/dpGPG/pen-generator
- [ ] Make sure that md5/sha256/whatever hashes of secring on laptop and pendrive are the same
- [ ] Add option to ask if want to overwrite pendrive with 0x00's before dpGPG init key installation
- [x] Copy secring onto 1MB partition
- [ ] Ask if want to remove local secring

# dpGPG - System Daemon

TODO:
- [ ] ~~dmesg notification when "dpGPG" pendrive is connected~~ Syslog notification system
- [ ] Check every 10sec if new device is connected
- [ ] Add config file
  - [ ] Ask if want to push notifications to *notify-send*
- [ ] Automatically mount:
  - [ ] Secring partition in /tmp/dpGPG/secring as read-only
  - [ ] Encryption buffer in /tmp/dpGPG/buffer as read-write

# Misc

TODO:
- [ ] Add some things to readme
  - [ ] Compilation
  - [ ] Installation
  - [ ] Usage
