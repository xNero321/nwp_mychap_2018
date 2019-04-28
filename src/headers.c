/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** ip_header.c
*/
#include <string.h>
#include "packet.h"

/*
** PURPOSE : Autogenerates function contract comments
** PARAMS  : struct udphdr *udph, uint16_t s_port,
   uint16_t d_port, unsigned short size
** RETURNS : void
*/
void set_udp_header(struct udphdr *udph, uint16_t s_port, uint16_t d_port,
    unsigned short size)
{
    udph->uh_sport = htons(s_port);
    udph->uh_dport = htons(d_port);
    udph->uh_sum = 0;
    udph->uh_ulen = htons(sizeof(struct udphdr) + size);
}

/*
** PURPOSE : Fills the IP header using the parameters given to the function
** PARAMS  : struct iphdr *iph, unsigned short size,
   uint32_t d_addr, uint32_t s_addr -
** RETURNS : void
*/
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
