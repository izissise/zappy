/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "select.h"

static int	max_fd_plusone(t_list *fds)
{
  int		max;
  t_list		*tmp;
  t_selfd		*fd;

  max = -1;
  tmp = fds;
  while (tmp)
    {
      fd = (t_selfd*)tmp->data;
      max = fd->fd > max ? fd->fd : max;
      tmp = tmp->next;
    }
  return (max + 1);
}

static void	set_fdset(t_list *fds, fd_set *setr, fd_set *setw)
{
  t_list		*tmp;
  t_selfd		*fd;

  FD_ZERO(setr);
  FD_ZERO(setw);
  tmp = fds;
  while (tmp)
    {
      fd = (t_selfd*)tmp->data;
      if ((fd->checktype & FDREAD) == FDREAD)
        FD_SET(fd->fd, setr);
      if ((fd->checktype & FDWRITE) == FDWRITE)
        FD_SET(fd->fd, setw);
      tmp = tmp->next;
    }
}

t_selfd	*create_fd(int fd, void *data, void (*call)())
{
  t_selfd	*res;

  if ((res = malloc(1 * sizeof(t_selfd))) == NULL)
    return (NULL);
  res->fd = fd;
  res->checktype = FDREAD;
  res->data = data;
  res->callback = call;
  return (res);
}

/*
** Return a list of t_selfd wich changed state
*/

t_selfd	*do_select(t_list *fds)
{
  fd_set		setr;
  fd_set		setw;
  t_list		*tmp;
  t_selfd		*fd;

  set_fdset(fds, &setr, &setw);
  if ((select(max_fd_plusone(fds), &setr, &setw, NULL, NULL) == -1))
    {
      if (errno != EINTR)
        perror("Select");
      return (NULL);
    }
  tmp = fds;
  while (tmp)
    {
      fd = (t_selfd*)tmp->data;
      if (FD_ISSET(fd->fd, &setr) || (FD_ISSET(fd->fd, &setw)))
        {
          fd->etype = (FD_ISSET(fd->fd, &setr)) | (FD_ISSET(fd->fd, &setw));
          fd->checktype = 0;
          return (fd);
        }
      tmp = tmp->next;
    }
  return (NULL);
}