#/bin/bash
gcc -w -Wall App/PackReader/PackReader.c main.c -o container
chmod +x container
./container
