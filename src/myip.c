#include <string.h> /* for strncpy */
#include <unistd.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>



void myip(char s[]) {
  int fd;
  struct ifreq ifr;
  fd = socket(AF_INET, SOCK_DGRAM, 0);

  /* I want to get an IPv4 IP address */
  ifr.ifr_addr.sa_family = AF_INET;

  /* I want IP address attached to "eth0","wlan0","wlp3s0" */
  strncpy(ifr.ifr_name, "wlp3s0", IFNAMSIZ - 1);
  ioctl(fd, SIOCGIFADDR, &ifr);
  close(fd);
  /* return result */
  strcpy(s,inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
}

