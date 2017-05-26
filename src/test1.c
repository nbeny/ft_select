#ifdef unix
static char term_buffer[2048];
#else
#define term_buffer 0
#endif

init_terminal_data ()
{
  char *termtype = getenv ("TERM");
  int success;

  if (termtype == 0)
    fatal ("Specify a terminal type with `setenv TERM '.\n");

  success = tgetent (term_buffer, termtype);
  if (success < 0)
    fatal ("Could not access the termcap data base.\n");
  if (success == 0)
    fatal ("Terminal type `%s' is not defined.\n", termtype);
}
