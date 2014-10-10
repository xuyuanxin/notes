#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

const char *hstrerror(int err)
{
	if (err == 0)
		return("no error");

	if (err == HOST_NOT_FOUND)
		return("Unknown host");

	if (err == TRY_AGAIN)
		return("Hostname lookup failure");

	if (err == NO_RECOVERY)
		return("Unknown server error");

	if (err == NO_DATA)
        return("No address associated with name");

	return("unknown error");
}

int main(int argc, char **argv)
{
	char			*ptr, **pptr;
	char			str[INET_ADDRSTRLEN];
	struct hostent	*hptr;

	while (--argc > 0) 
	{
		ptr = *++argv;
		if ( (hptr = gethostbyname(ptr)) == NULL) 
		{
			printf("gethostbyname error for host: %s: %s",ptr, hstrerror(h_errno));
			continue;
		}
		
		printf("official hostname: %s\n", hptr->h_name);

		for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
		{
			printf("\talias: %s\n", *pptr);
		}

		switch (hptr->h_addrtype) 
		{
		case AF_INET:
			pptr = hptr->h_addr_list;
			for ( ; *pptr != NULL; pptr++)
			{
				printf("\taddress: %s\n",inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
			}
			break;

		default:
			printf("unknown address type");
			break;
		}
	}
	exit(0);
}


