# Beaglebone-Black-Setup-Guide
This repository contains the complete procedure for setting up a BeagleBone Black (BBB), including image flashing, network configuration, dependency installation, and kernel header installation.
# Introduction
This document provides a step-by-step guide for setting up the BeagleBone Black (BBB) development board. It covers the complete process of flashing the operating system image, configuring network connectivity through a host Ubuntu machine or virtual machine, enabling internet access on the BBB, and installing the required software dependencies.

The guide also includes instructions for configuring IP forwarding, Network Address Translation (NAT), DNS settings, and persistent network routing to ensure reliable connectivity between the BeagleBone Black and the host system. Additionally, it describes the installation of essential packages and Linux kernel headers required for embedded Linux development, driver development, and kernel module compilation.

By following this document, users can quickly prepare a BeagleBone Black development environment suitable for application development, kernel programming, device driver development, and other embedded Linux projects.

### Note : This guide has been tested using Ubuntu 22.04 LTS as the host operating system. The target hardware platform used is the BeagleBone Black (BBB)

# Table of Contents
- [Prerequisites](#prerequisites)
- [Flashing Image in BBB](#Flashing-Image-in-BBB)
- [Network Setup](#Network-Setup)
- [Make settings permanent](Make-settings-permanent)
- [Dependency Installation](#Dependency-Installation)
- [Header Installation](#Header-Installation)

# Prerequisites
Hardware Requirements :
  - BeagleBone Black (BBB).
  - MicroSD Card (8GB or higher recommended).
  - USB Cable.
  - Host PC/Laptop.
  - Internet Connection.
  - USB SD Card-reader.
    
Software Requirements :
  - Ubuntu Host Machine or Ubuntu Virtual Machine.
  - Balena Etcher.
  - BBB Image File.
  - Administrative (sudo) privileges.
  
# Flashing Image in BBB
## Steps
1. Download image from [drive link](https://drive.google.com/drive/folders/1OXFgz5Sl-nOoM_cIQU6NIXMJJJ__GY0C?usp=sharing).
2. Download balenaEtcher [Application](https://etcher.balena.io/).
3. Insert Micro-card in SD card-reader.
4. Open BalenaEtcher and connect USB SD card-reader to Host device.
5. Select the Image file.
6. Select target (USB device).
7. Flash.
Insert SD Card in BBB and connect BBB to PC
# Network Setup
## Enable IP forwarding on Linux (Ubuntu)
Open Terminal on Linux and run following command.
```bash
$ sudo sysctl -w net.ipv4.ip_forward=1
```
Verify
```bash
$ cat /proc/sys/net/ipv4/ip_forward
```
Expected output :
```txt
1
```
## Configure NAT on (Ubuntu) VM/linux
Check the network interface name
```bash
$ ip route
```
or
```bash
$ ip addr
```
The network interface name used in this guide is enp0s3. On your system, the interface name may be different. Please identify your active network interface using the ip route command and replace enp0s3 with the appropriate interface name wherever applicable..
```bash
$ sudo iptables -t nat -A POSTROUTING -o enp0s3 -j MASQUERADE
```
```bash
$ sudo iptables -A FORWARD -i enp0s3 -o enxe0928f265edf -m state --state RELATED,ESTABLISHED -j ACCEPT
```
```bash
$ sudo iptables -A FORWARD -i enxe0928f265edf -o enp0s3 -j ACCEPT 
```
## Login to Beaglebone from Terminal
```bash
$ ssh debian@192.168.7.2
```
or 
```bash
$ ssh debian@192.168.7.1 
```
Enter “YES” and password – ``temppw``
##  Add Default Route on Beaglebone
On Beaglebone Terminal
```bash
$ sudo ip route add default via 192.168.7.1 dev usb0
```
Verify:
```bash
$ ip route
```
Expected output:
```txt
default via 192.168.7.1 dev usb0 
192.168.7.0/24 dev usb0 ... 
192.168.6.0/24 dev usb1 ...
```
##  Configure DNS on Beaglebone
```bash
$ sudo sh -c 'echo "nameserver 8.8.8.8" > /etc/resolv.conf'
```
```bash
$ sudo sh -c 'echo "nameserver 8.8.4.4" >> /etc/resolv.conf'
```
Verify:
```bash
$ cat /etc/resolv.conf
```
## Test
```bash
$ ping 8.8.8.8
```
```bash
ping google.com
```
Check if packets are getting transmitted. 
# Make settings permanent
If everything works, add the route automatically at boot on Beaglebone
```bash
$ sudo nano /etc/network/interfaces
```
Add :
```txt
up ip route add default via 192.168.7.1 dev usb0
```
And on the Linux/VM make IP forwarding permanent
```bash
$ sudo nano /etc/sysctl.conf
```
Uncomment or add : ``net.ipv4.ip_forward=1``.
Then
```bash
$ sudo sysctl -p
```
# Dependency Installation
On Beaglebone
```bash
$ mkdir iptables-armhf
```
```bash
$ cd iptables-armhf
```
iptables + dependencies for armhf from Debian 11 (Bullseye) 
```bash
$ wget http://ftp.us.debian.org/debian/pool/main/i/iptables/iptables_1.8.7-1_armhf.deb
```
```bash
$ wget http://ftp.us.debian.org/debian/pool/main/i/iptables/libip4tc2_1.8.7-1_armhf.deb 
```
```bash
$ wget http://ftp.us.debian.org/debian/pool/main/i/iptables/libip6tc2_1.8.7-1_armhf.deb
```
```bash
$ wget http://ftp.us.debian.org/debian/pool/main/libn/libnfnetlink/libnfnetlink0_1.0.1-3+b1_armhf.deb 
```
```bash
$ wget http://ftp.us.debian.org/debian/pool/main/libn/libnetfilter-conntrack/libnetfilter-conntrack3_1.0.8-3_armhf.deb 
```
```bash
$ wget http://ftp.us.debian.org/debian/pool/main/libm/libmnl/libmnl0_1.1.4-2_armhf.deb
```
```bash
$ wget http://ftp.us.debian.org/debian/pool/main/libn/libnftnl/libnftnl11_1.1.9-1_armhf.deb
```
```bash
$ sudo dpkg -i *.deb
```
If you still get dependency issues
```bash
$ sudo apt --fix-broken install
```
```bash
$ sudo iptables --version
```
Expected output : ``iptables v1.8.7 (nf_tables)``
# Header Installation
On Beaglebone Terminal
```bash
$ sudo apt update
```
```bash
$ sudo apt install linux-headers-5.10.168-ti-r71
```
