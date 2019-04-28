/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** send_phase.c
*/
/** \file send_phase.c
  * \brief packet sending and receive file
  * \author Janote J.
*/
#include <string.h>
#include "packet.h"

/*
** PURPOSE : Fills udp and ip header and send the first phase
   with "client hello" then receive the server packet
** PARAMS  : packet_ipv4_t *packet, packet_t *core, int sock
** RETURNS : void
*/
void send_first_phase(packet_ipv4_t *packet, packet_t *core, int sock)
{
    fill_info_socket_server(core);
    set_udp_header(&packet->udp, core->cin.sin_port, core->port,
    PAYLOAD_SIZE);
    set_ip_header(&packet->ip, PAYLOAD_SIZE, core->sin.sin_addr.s_addr,
    core->cin.sin_addr.s_addr);
    memmove(packet->payload, "client hello", strlen("client hello"));
    if (sendto(sock, packet, sizeof(*packet), 0,
    (struct sockaddr *)&(core->sin), sizeof(core->sin)) < 0)
        perror("dommage");
    while (packet->udp.uh_dport == core->sin.sin_port) {
        memset(packet, 0, sizeof(*packet));
        if (recvfrom(sock, packet, sizeof(*packet),
        MSG_WAITALL, NULL, NULL) < 0)
            perror("dommage");
    }
    send_next_phase(packet, core, sock);
}

/*
** PURPOSE : After receveing the server packet, concat the server payload with
  the password given in argument then send it back hashed to the server
** PARAMS  : packet_ipv4_t *packet, packet_t *core, int sock
** RETURNS : void
*/
void send_next_phase(packet_ipv4_t *packet, packet_t *core, int sock)
{
    char *tmp = strdup(packet->payload);

    strncpy(tmp + 10, core->password, strlen(core->password) + 1);
    memset(packet, 0, sizeof(*packet));
    set_udp_header(&packet->udp, core->cin.sin_port, core->port,
    PAYLOAD_SIZE);
    set_ip_header(&packet->ip, PAYLOAD_SIZE, core->sin.sin_addr.s_addr,
    core->cin.sin_addr.s_addr);
    memmove(packet->payload, sha256(tmp, core), strlen(sha256(tmp, core)));
    if (sendto(sock, packet, sizeof(*packet), 0,
    (struct sockaddr *)&(core->sin), sizeof(core->sin)) < 0)
        perror("dommage");
    check_last_phase(packet, core, sock);
}

/*
** PURPOSE : After receiving the last server packet just checks if the server
   acknoledge the handshake thus prints the secret
** PARAMS  : packet_ipv4_t *packet, packet_t *core, int sock
** RETURNS : void
*/
void check_last_phase(packet_ipv4_t *packet, packet_t *core, int sock)
{
    while (packet->udp.uh_dport == core->sin.sin_port) {
        memset(packet, 0, sizeof(*packet));
        if (recvfrom(sock, packet, sizeof(*packet),
        MSG_WAITALL, NULL, NULL) < 0)
        perror("dommage");
    }
    if (strcmp(packet->payload, "KO") == 0)
        printf("%s\n", packet->payload);
    else
        printf("Secret: '%s'\n", packet->payload);
}
