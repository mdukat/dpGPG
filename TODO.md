# dpGPG - Pendrive Generator

TODO:
- Cut code into libraries (like mbr.cpp, highlevel.cpp, or something)
- Make code *prettier*
- Do something with these system() things, check if command goes right, and stuff
- Make protection questions ("Are you sure about that device" etc)
- Don't kill another pendrive
- Maybe comment a bit more the code in dense places
- Make partition_table_gen() more dynamic (as in change the input arguments and function to calculate space for encryption buffer and secring)
- Add dpGPG "Magic bytes" to let system daemon know that it is the dpGPG and it have to do stuff with it
- Change /tmp/dpGPG folder to /tmp/dpGPG/pen-generator

# dpGPG - System Daemon

TODO:
- dmenu notification when "dpGPG" pendrive is connected
- automatically mount:
  - secring partition in /tmp/dpGPG/secring as read-only
  - encryption buffer in /tmp/dpGPG/buffer as read-write
