#include "../include/ft_select.h"
#define READ_SIZE 512
int    main()
{
	char *buffer;
	int   nb_read;

/* ON ECRIT LE PREMIER TEXTE */
	write(1, "texte1\n", 7);
/* ON MALLOC LE BUFFER */
	buffer = malloc((READ_SIZE + 1) * sizeof(*buffer));
/* ON LIT SUR L'ENTREE STANDART (LE CLAVIER) */
	nb_read = read(0, buffer, READ_SIZE);
/* ON EVITE QUE IL NOUS METTE LE RETOUR A LA LIGNE DANS LA CHAINE */
	buffer[nb_read - 1] = 0;
/* ON ECRIT LE DEUXIEME TEXTE */
	write(1, buffer, strlen(buffer));
	return (0);
}
