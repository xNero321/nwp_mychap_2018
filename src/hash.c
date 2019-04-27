/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** hash256
*/

#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <openssl/sha.h>
#include "packet.h"

char *sha256(const char *str, packet_t *core)
{
	unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
	SHA256_CTX sha256;
	char *output_buffer;

	if (!(output_buffer = calloc(1, sizeof(char)
	* ((SHA256_DIGEST_LENGTH * 2) + 1))))
		return (NULL);
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str, 10 + strlen(core->password));
	SHA256_Final(hash, &sha256);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
		sprintf(output_buffer + (i * 2), "%02x", hash[i]);
	output_buffer[64] = 0;
	return (output_buffer);
}
