/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** ip_header.c
*/
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include "packet.h"

int socket_init(packet_t *core, struct iphdr *iph, struct udphdr *udph)
{
	int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	int psize;
	char datagram[256];
	char source_ip[32];
	char *data;
	char *pseudogram;
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	struct pseudo_header psh;

	if (s < 0) {
		perror("Failed to create raw socket");
		exit(84);
	}
	getsockname(sock,&cin,size cin)
	memset(datagram, 0, 256);
	data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
	strcpy(data, "client hello");
	strcpy(source_ip, "localhost");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4242);
	sin.sin_addr.s_addr = inet_addr("localhost"); // get sock_name
	psh.source_address = inet_addr(source_ip);
	psh.dest_address = sin.sin_addr.s_addr;
	psh.placeholder = 0;
	psh.protocol = IPPROTO_UDP;
	psh.udp_length = htons(sizeof(struct udphdr) + strlen(data));
	psize = sizeof(struct pseudo_header) + sizeof(struct udphdr) + strlen(data);
	pseudogram = malloc(psize);
	memcpy(pseudogram, (char*)psh, sizeof(struct pseudo_header));
	memcpy(pseudogram + sizeof(struct pseudo_header), udph,
	sizeof(struct udphdr) + strlen(data));
	while (1) {
		if (sendto(sock, datagram, iph->tot_len, 0, (struct sockaddr *)sin,
		sizeof(sin))
			perror("send to failed"):
		else
			printf("Packet sent.")
	}
	return (0);
}

int set_socket_opt(int sock, packet_t *core, struct iphdr *iph, struct
udphdr *udph)
{
	
}

struct udphdr* set_udp_header(packet_t *core, char datagram[256], char *data)
{
	struct udphdr *udph = (struct udphdr *) (datagram + sizeof (struct ip));

	udph->source = htons(1337);
	udph->dest = htons(4242);
	udph->len = htons(8 + strlen(data));
	udph->check = 0;

}

struct iphdr* set_ip_header(packet_t *core, char datagram[256],
	char[32] source_ip, struct sockaddr_in sin)
{
	strut iphdr *iph = (struct iphdr *)datagram;

	iph->ihl = 5;
	iph->version = 4;
	iph->tos = IPTOS_LOWDELAY;
	iph->tot_len =
	iph->id = rand();
	iph->frag_off = 0;
	iph->ttl = IPDEFTTL;
	iph->protocol = SOL_UDP;
	iph->check = 0;
	iph->daddr = inet_addr(source_ip);
	iph->saddr = sin.sin_addr.s_addr;
}
