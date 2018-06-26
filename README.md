# Pack

[![N|Solid](http://i68.tinypic.com/2wcmluw.png)](https://drive.google.com/drive/folders/1g9kvVnblG2zZKaklLtMA5IDC51vtb72r?usp=sharing)
## [Pack ready container](http://www.packcontainer.tk/)

The LIGHTWEIGHTEST containers ever

  - Isolated environment
  - Host-container LAN
  - HDD to file

# Quick Start

cd to the directory with unzipped Pack source code and start container with
```sh
sudo bash run.sh
```

## Packfile
Your container is specified in a *_Packfile_* which has some rules and syntax.
The file is separated in several sections each of which has its own functionality.
The table below lists all of them implemented so far:


| Mode | After this line you specify... |
| ------ | ------ |
| #NAME |  your container name, which is also name of your image (*.img) file name. If you write several lines with names, the last non-blank line will be accepted as name. If not specified, by default it is "container"|
| #ISO | one line, the (full) location of where you mount your Pack.container. e.g. `/home/anna/Pack`|
| #NET | two lines, each of which is IP address. *first* - *host* vnet0 device, *second* - *guest* vnet1 device. |
| #RUN | Any amount of lines which are bash commands will be executes inside your Pack.container. e.g. `apt -y install net-tools && ifconfig` |
| #CGROUP | TBD |
| #ENV | TBD |
| #USR | TBD |

This is example of Packfile that is recommended 
```sh
#NAME
my-pack

#NET
10.1.1.1
10.1.1.2

#ISO
/home/user/Pack

#RUN
# this is a usual comment, like in command shell
# basically, this is bash part until next Mode swithing comment
echo THIS IS DONE IN PACKFILE :

apt-get update
apt-get install sysbench
sysbench --test=cpu --cpu-max-prime=20000 run
ifconfig
ps aux

echo finish

#CGROUP
50000
100000
/sys/fs/cgroup/cpu/demo

#ENV
EULA=true

#USR
user

```
After saving this as `Packfile` and run using Pack. you will get your container and automatically attach to it. to exit from Pack., run `exit` or press ctrl+d, as you usually exit from containers.

This order of modes is recommended, but you can change them on your risk.

# Sources

The list of papers that were used to write Pack.

* [M.Ridwan] - Separation Anxiety: A Tutorial for Isolating Your System with Linux Namespaces
* [Bootlin] - CGroups documentation
* [StackExchange] - info about mount and umount
* [Colorlib] - Some web layout materials for site


[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)
   [M.Ridwan]: https://www.toptal.com/linux/separation-anxiety-isolating-your-system-with-linux-namespaces
   [Bootlin]: https://elixir.bootlin.com/linux/v4.4/source/Documentation/cgroups/cgroups.txt
   [StackExchange]: https://unix.stackexchange.com/questions/246312/why-is-my-bind-mount-visible-outside-its-mount-namespace
   [Colorlib]: https://colorlib.com/wp/free-html-website-templates/