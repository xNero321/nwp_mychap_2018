/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** packet.h
*/

#ifndef __PACKET__
#define __PACKET__
    #include <stdio.h>
    #include <stdlib.h>
    #include <getopt.h>
    #include <stdint.h>
    #include <netinet/udp.h>
    #include <netinet/ip.h>
    #define ERROR_SOCK "Error: getsockname() failed.\n"
    #define ERROR_SOCKOPT "Cannot set IP_HDRINCL.\n"
    #define ERROR_ARGS "Error: Arguments not right.\n"
    #define ERROR_ARG "Error: Arguments are not valid.\n"
    #define ERROR_FLAG "Error: Flag non approprié.\n"
    #define ERROR_RAWSOCKET "Error: Failed to create raw socket.\n"
    #define ERROR_GETSOCKNAME "Error: getsockname() failed.\n"
    #define PAYLOAD_SIZE 256
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

    void error(char *str);
    void init_packet(packet_t *core);
    int check_args(packet_t *core);
    int get_option(struct option op[], char **av, packet_t *core, int ac);
    int get_flags_from_switch(packet_t *core, int f);
    int socket_init(packet_t *core, packet_ipv4_t *op4);
    void set_socket_opt(int sock);
    int fill_info_socket_server(packet_t *core);
    int get_info_socket_client(int sock, packet_t *core);
    void set_udp_header(struct udphdr *udph, uint16_t s_port, uint16_t d_port,
        unsigned short size);
    void set_ip_header(struct iphdr *iph, unsigned short size,
        uint32_t d_addr, uint32_t s_addr);
    int prepare_packet_sending(packet_ipv4_t *packet, packet_t *core,
        int sock);
    int send_next_phase(packet_ipv4_t *packet, packet_t *core, int sock);
    int check_last_phase(packet_ipv4_t *packet, packet_t *core, int sock);
    char *sha256(const char *str, packet_t *core);
#endif
