# Beaglebone-Black-Setup
This repository contains the complete procedure for setting up a BeagleBone Black (BBB), including image flashing, network configuration, dependency installation, and kernel header installation.
# Introduction
This document provides a step-by-step guide for setting up the BeagleBone Black (BBB) development board. It covers the complete process of flashing the operating system image, configuring network connectivity through a host Ubuntu machine or virtual machine, enabling internet access on the BBB, and installing the required software dependencies.

The guide also includes instructions for configuring IP forwarding, Network Address Translation (NAT), DNS settings, and persistent network routing to ensure reliable connectivity between the BeagleBone Black and the host system. Additionally, it describes the installation of essential packages and Linux kernel headers required for embedded Linux development, driver development, and kernel module compilation.

By following this document, users can quickly prepare a BeagleBone Black development environment suitable for application development, kernel programming, device driver development, and other embedded Linux projects.
# Table of Contents
- [Prerequisites](#prerequisites)
- [Flashing Image in BBB](#Flashing-Image-in-BBB)
- [Insert SD Card in BBB and connect BBB to PC](Insert-SD-Card-in-BBB-and-connect-BBB-to-PC)
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
# Insert SD Card in BBB and connect BBB to PC
