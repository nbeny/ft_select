
char *tparam (char *ctlstring, char *buffer, int size, int parm1,...)

	int	main(void)
{
char *buf;
char buffer[40];

buf = tparam (command, buffer, 40, parm);
tputs (buf, 1, fputchar);
if (buf != buffer)
free (buf);
}
