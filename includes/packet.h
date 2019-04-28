/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** packet.h
*/

#ifndef __PACKET__
#define __PACKET__
//---------------- INCLUDES ---------------
    #include <stdio.h>
    #include <stdlib.h>
    #include <getopt.h>
    #include <stdint.h>
    #include <netinet/udp.h>
    #include <netinet/ip.h>
//-------------- ERRORS MESSAGES ---------------
    #define ERROR_SOCK "Error: getsockname() failed.\n"
    #define ERROR_SOCKOPT "Cannot set IP_HDRINCL.\n"
    #define ERROR_ARGS "Error: Arguments are not valid.\n"
    #define ERROR_ARG "Error: Arguments are missing.\n"
    #define ERROR_FLAG "Error: Unrecognized flag.\n"
    #define ERROR_RAWSOCKET "Error: Failed to create raw socket.\n"
    #define ERROR_GETSOCKNAME "Error: getsockname() failed.\n"
    #define PAYLOAD_SIZE 256
//---------------- STRUCTURES --------------------
    typedef struct packet_s
    {
        char *target;
        int port;
        char *password;
        struct sockaddr_in sin;
        struct sockaddr_in cin;
    }packet_t;

    typedef struct packet_ipv4
    {
        struct iphdr ip;
        struct udphdr udp;
        char payload[PAYLOAD_SIZE];
    }packet_ipv4_t;

//---------------- FUNCTION PROTOTYPES ------------------
//---------------- error_handling.c ---------------------
    void error(char *str);
//------------------- hash256.c -----------------------
    char *sha256(const char *str, packet_t *core);
//------------------- headers.c ------------------------
    void set_udp_header(struct udphdr *udph, uint16_t s_port, uint16_t d_port,
        unsigned short size);
    void set_ip_header(struct iphdr *iph, unsigned short size,
        uint32_t d_addr, uint32_t s_addr);
    void send_first_phase(packet_ipv4_t *packet, packet_t *core,
        int sock);
    void send_next_phase(packet_ipv4_t *packet, packet_t *core, int sock);
    void check_last_phase(packet_ipv4_t *packet, packet_t *core, int sock);
//-------------------- main.c ---------------------
    void init_packet(packet_t *core);
    int check_args(packet_t *core);
    int get_option(struct option op[], char **av, packet_t *core, int ac);
    int get_flags_from_switch(packet_t *core, int f);
//---------------- socket_init.c ---------------------
    int socket_init(packet_t *core, packet_ipv4_t *op4);
    int fill_info_socket_server(packet_t *core);
    int get_info_socket_client(int sock, packet_t *core);
    void set_socket_opt(int sock);
#endif
