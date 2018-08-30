/**
 * homework 12.26
 *
 * linux> man 3 gethostbyname, 可得以下信息: 
struct hostent *gethostbyname(const char *name);

struct hostent {
	char  *h_name;            // official name of host
	char **h_aliases;         // alias list
	int    h_addrtype;        // host address type
	int    h_length;          // length of address
	char **h_addr_list;       // list of addresses
};

The members of the hostent structure are:

       h_name The official name of the host.

       h_aliases An array of alternative names for the host, terminated by a null pointer.

       h_addrtype The type of address; always AF_INET or AF_INET6 at present.

       h_length The length of the address in bytes.

       h_addr_list
              An  array  of pointers to network addresses for the host (in network byte
              order), terminated by a null pointer.

       h_addr The first address in h_addr_list for backward compatibility.
*/

#include "csapp.h"

static sem_t mutex; /* Initially = 1 */

struct hostent *gethostbyname_ts(const char *name, struct hostent *buf)
{
	struct hostent *temp;
	
	P(&mutex);
	temp = gethostbyname(name);
	buf = (struct hostent *) Malloc(sizeof(struct hostent));
	
	/* copy: h_addrtype, h_length */
	buf->h_addrtype = temp->h_addrtype;
	buf->h_length = temp->h_length;
	
	/* copy: *h_name */
	buf->h_name = (char *) Malloc(strlen(temp->h_name)+1);
	strcpy(buf->h_name, temp->h_name);
	
	/* copy: **h_aliases */
	int len, i;
	for (i = 0, len = 0; temp->h_aliases[i] != NULL; i++)
		len++;
	buf->h_aliases = (char **) Malloc((len+1) * sizeof(char *));
	for (i = 0; i < len; i++) {
		buf->h_aliases[i] = (char *) Malloc(strlen(temp->h_aliases[i])+1);
		strcpy(buf->h_aliases[i], temp->h_aliases[i]);
	}
	buf->h_aliases[i] = NULL;
	
	/* copy: **h_addr_list */
	for (i = 0, len = 0; temp->h_addr_list[i] != NULL; i++)
		len++;
	buf->h_addr_list = (char **) Malloc((len+1) * sizeof(char *));
	for (i = 0; i < len; i++) {
		buf->h_addr_list[i] = (char *) Malloc(strlen(temp->h_addr_list[i])+1);
		strcpy(buf->h_addr_list[i], temp->h_addr_list[i]);
	}
	buf->h_addr_list[i] = NULL;
	
	V(&mutex);
	return buf;
}

/* test */
int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s <hostname>\n", argv[0]);
		exit(0);
	}
	
	Sem_init(&mutex, 0, 1);
	
	struct hostent *host;
	host = gethostbyname_ts(argv[1], host);
	printf("%s\n", host->h_name);
	printf("%d\n", host->h_addrtype);
	printf("%d\n", host->h_length);
	
	return 0;
}