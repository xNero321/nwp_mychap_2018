/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** ip_header.c
*/
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <stdint.h>
#include <netdb.h>
#include "packet.h"

int socket_init(packet_t *core, packet_ipv4_t *op4)
{
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    struct hostent *hostname = NULL;
    packet_ipv4_t *packet = malloc(sizeof(packet_ipv4_t));

    if (sock < 0)
        error(ERROR_RAWSOCKET);
    set_socket_opt(sock);
    get_info_socket_client(sock, core);
    hostname = gethostbyname(core->target);
    if (hostname == NULL) {
        printf("No such hostname: '%s'\n", core->target);
        exit(84);
    }
    send_first_phase(packet, core, sock);
    return (0);
}

int fill_info_socket_server(packet_t *core)
{
    core->sin.sin_family = AF_INET;
    core->sin.sin_port = htons(core->port);
    inet_aton(core->target, &core->sin.sin_addr);
}

int get_info_socket_client(int sock, packet_t *core)
{
    int sa_len = sizeof(core->cin);

    if (getsockname(sock, (struct sockaddr *)&core->cin, &sa_len) == -1)
        error(ERROR_GETSOCKNAME);
    return (1);
}

void set_socket_opt(int sock)
{
    int on = 1;

    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *) &on,
    sizeof(on)) < 0)
        error(ERROR_SOCKOPT);
    return;
}
