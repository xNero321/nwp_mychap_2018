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
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>
#include "packet.h"

void set_udp_header(struct udphdr *udph, uint16_t s_port, uint16_t d_port,
	unsigned short size)
{
	udph->uh_sport = htons(s_port);
	udph->uh_dport = htons(d_port);
	udph->uh_sum = 0;
	udph->uh_ulen = htons(sizeof(struct udphdr) + size);
}

void set_ip_header(struct iphdr *iph, unsigned short size,
	uint32_t d_addr, uint32_t s_addr)
{
	iph->version = IPVERSION;
	iph->ihl = 5;
	iph->tos = IPTOS_LOWDELAY;
	iph->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr)
	+ PAYLOAD_SIZE);
	iph->id = rand();
	iph->frag_off = 0x40;
	iph->ttl = IPDEFTTL;
	iph->protocol = 17;
	iph->check = 0;
	iph->daddr = d_addr;
	iph->saddr = s_addr;
}

int prepare_packet_sending(packet_ipv4_t *packet, packet_t *core, int sock)
{
	int fromlen = sizeof(core->cin);

	fill_info_socket_server(core);
	set_udp_header(&packet->udp, core->cin.sin_port, core->port,
	PAYLOAD_SIZE);
	set_ip_header(&packet->ip, PAYLOAD_SIZE, core->sin.sin_addr.s_addr,
	core->cin.sin_addr.s_addr);
	memmove(packet->payload, "client hello", strlen("client hello"));
	if (sendto(sock, packet, sizeof(*packet), 0,
		(struct sockaddr *)&(core->sin), sizeof(core->sin)) < 0)
		perror("dommage");
	memset(packet->payload, 0, strlen(packet->payload));
	// if (recvfrom(sock, packet, sizeof(*packet), 0,
	// 	(struct sockaddr *)&(core->cin), &fromlen) < 0)
	// 	perror("dommage");
	// printf("%s", packet->payload);
}
