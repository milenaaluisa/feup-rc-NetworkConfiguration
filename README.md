# RC_T04 - Network Configuration

> **2022/2023** - 3rd Year, 1st Semester
> 
> **Course** - RC (Redes de Computadores | Computer Networks)
> 
> **Project developed by**
> - Anete Pereira (up202008856)
> - Isabel Amaral (up202006677)
> - Milena Gouveia (up202008862)

### Project description
The goal of this project was to develop a download application using an FTP client and configure a network based on experimental results.

### Part 1 - Development of a Download Application
This application can be used by compiling the code in the [download](/download/) folder using the provided Makefile.

Some **execution examples**:

host `netlab1.fe.up.pt` (requires being inside FEUP's network or being connected with the VPN):

without login:

- ./download [ftp://netlab1.fe.up.pt/pub.txt](ftp://netlab1.fe.up.pt/pub.txt)

with login:

- ./download [ftp://rcom:rcom@netlab1.fe.up.pt/pipe.txt](ftp://rcom:rcom@netlab1.fe.up.pt/pipe.txt)
- ./download [ftp://rcom:rcom@netlab1.fe.up.pt/files/pic1.jpg](ftp://rcom:rcom@netlab1.fe.up.pt/files/pic1.jpg)
- ./download [ftp://rcom:rcom@netlab1.fe.up.pt/files/pic2.jpg](ftp://rcom:rcom@netlab1.fe.up.pt/files/pic1.jpg)
- ./download [ftp://rcom:rcom@netlab1.fe.up.pt/files/crab.mp4](ftp://rcom:rcom@netlab1.fe.up.pt/files/crab.mp4)

host `ftp.up.pt` (doesn't require being inside FEUP's network):

- ./download [ftp://ftp.up.pt/pub/debian/README](ftp://ftp.up.pt/pub/debian/README)
- ./download [ftp://ftp.up.pt/pub/apache/README.html](ftp://ftp.up.pt/pub/apache/README.html)

<br>

### Part 2 - Configuration and Study of a Network
The commands used for the configuration in each experience ***x*** are listed inside the respective exp\<x\> folder. The complete configuration is reached in experience 4, therefore, there aren't any new commands for experience 5 and experience 6.

The full configuration for this project can be checked [here](/exp4/).
