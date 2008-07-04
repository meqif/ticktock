/* See LICENSE file for copyright and license details.
 *
 * ticktock -- a small, secure and light time daemon
 * Uses the Time protocol (port 37), instead of NTP
 *
 * TODO:
 *   Add DNS resolution
 *   Add loop for checking and setting the clock
 */

/* Socket stuff */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define NTP_SERVER "158.152.1.76"
#define PORT 37
#define BASE_1970 2208988800UL

int ticktock(const char *hostname, time_t *time_new) {
    int sockfd, nbytes;
    unsigned char buf[4];
    struct sockaddr_in dest_addr;

    /* Create socket */
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    /* Set socket's properties */
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    dest_addr.sin_addr.s_addr = inet_addr(hostname);
    memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

    /* Initiate connection */
    if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof dest_addr) == -1) {
        perror("connect");
        exit(1);
    }

    /* Get the time */
    nbytes = recv(sockfd, buf, sizeof buf, 0);
    buf[nbytes] = 0;
    *time_new = (time_t)(ntohl(*(uint32_t *)buf) - BASE_1970);

    /* Close socket */
    close(sockfd);

    return 0;
}

int main(int argc, char **argv) {
    struct timeval tv;
    time_t time_new;
    char *hostname = NULL;

    if (argc == 2)        hostname = argv[1];

    if (hostname == NULL) hostname = NTP_SERVER;

    ticktock(hostname, &time_new);
    tv.tv_sec  = time_new;
    tv.tv_usec = 0;

    if (settimeofday(&tv, NULL) == -1) {
        perror("Could not set system time");
        exit(1);
    }

    return 0;
}

// vim: et ts=4 sw=4 sts=4
