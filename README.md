# nwp_mychap_2018

**A simple Handshake UDP protocol**

![forthebadge](https://forthebadge.com/images/badges/built-with-grammas-recipe.svg)![forthebadge](https://forthebadge.com/images/badges/60-percent-of-the-time-works-every-time.svg)

![shields.io](https://img.shields.io/badge/docker-v18.06.1-blue.svg?style=for-the-badge)![shields.io](https://img.shields.io/badge/docker--compose-v1.22.0-blue.svg?style=for-the-badge)

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/dd835695f2204829995675cb9a38e645)](https://www.codacy.com?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=xNero321/nwp_mychap_2018&amp;utm_campaign=Badge_Grade)

[![CircleCI](https://circleci.com/gh/xNero321/nwp_mychap_2018.svg?style=svg)](https://circleci.com/gh/xNero321/nwp_mychap_2018)

## Requirement

- GNU Make 4.2.1

________________________________

## Purpose

This project is based on an authentification using a handshake by UDP protocol.
The socket used for this project is a raw socket which means that the headers are manually filled.
This is how this project work :

### Step 1

- Create the socket
- Fill the IP and UDP header manually.
- Send the packet with "client hello"

### Step 2

- The server send back 10 random bytes of the same IP adress, port.

### Step 3

- Receiving the server packet and refill the IP and UDP headers.
- Use SHA256 to hash the response + the password authentification.
- Send the last packet with the hash from the last iteration.

### Step 4

- The server will send the password if the hash given is correct otherwise
it will send 'KO'.

________________________________

## Usage
	USAGE: sudo ./client -t <target> -p <port> -P <password>
        target      server hostname or ip address
        port        server port used to send packet
        password    waited password to authetificate to the server

________________________________

## Codacy analysis

This project use Codacy analysis, to see the project analysis

________________________________

## CI/CD Implementation [:WIP]

This project use CircleCI as integration software, every stages is located
in the `.circleci/config.yml` file composed of 1 stages/jobs.

PIPELINE:

- Build of the source code using EPITECH docker image

________________________________

## Doxygen

Doxygen is used as a documentation for this program.
