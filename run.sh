#/bin/bash
gcc -w -Wall App/PackReader/PackReader.c App/Container/Container.c main.c -o container
chmod +x container
./container
