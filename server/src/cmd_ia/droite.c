/*
** droite.c for droite.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue May 20 17:55:58 2014 Nicolas Bridoux
** Last update Thu May 29 23:23:11 2014 Nicolas Bridoux
*/

#include "server.h"

void		droite(t_server *serv, t_selfd *fd,
		       __attribute__((unused))char **args)
{
  t_client	*client;

  client = (t_client *)fd->data;
  if (client->orientation == UP)
    client->orientation = RIGHT;
  else if (client->orientation == DOWN)
    client->orientation = LEFT;
  else if (client->orientation == LEFT)
    client->orientation = UP;
  else if (client->orientation == RIGHT)
    client->orientation = DOWN;
  send_response(fd, "ok");
  ppo_event(serv, fd);
}
