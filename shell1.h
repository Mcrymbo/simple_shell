#ifndef SHELL1_H
#define SHELL1_H

#include "shell.h"
/** aux_cd.c **/

void _dot(shell_d *data);
void cd_dot_dot(shell_d *data);
void cd_to(shell_d *data);
void cd_home(shell_d *data);
int _cd(shell_d *data);

/** cd.c **/
void str_rev(char *str);

#endif
