## Installation
```bash
git clone https://github.com/ISOnRM/readbytes
pushd readbytes
make
make install
make clean
popd
```

## Usage
```plaintext
[mark@mk-laptop readbytes_showcase] $ mkdir i_am_a_directory
[mark@mk-laptop readbytes_showcase] $ touch i_am_an_empty_file
[mark@mk-laptop readbytes_showcase] $ echo "123" > i_am_not_an_empty_file
[mark@mk-laptop readbytes_showcase] $ readbytes -h
Usage: readbytes <filenames>
-h/--help Show this help
npc in ascii output is non-printable-character
[mark@mk-laptop readbytes_showcase] $ readbytes i_am_a_directory i_am_an_empty_file i_am_not_an_empty_file 
file "i_am_a_directory" is not a regular file.
File "i_am_an_empty_file" is empty.
Reading file "i_am_not_an_empty_file":
off=0x00000000 dec=49 hex=0x31 ascii='1'
off=0x00000001 dec=50 hex=0x32 ascii='2'
off=0x00000002 dec=51 hex=0x33 ascii='3'
off=0x00000003 dec=10 hex=0x0a ascii=npc
```
