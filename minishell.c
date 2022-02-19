/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/02/19 15:25:34 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool valid(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  return (TRUE);
}

void free_app(t_app *self) { (void)self; }

int main(int argc, char *argv[]) {
  t_app self;

  // Load app setup
  self = (t_app){0};
  if (valid(argc - 1, &argv[1])) {
    // Do stuff
    free_app(&self);
  } else
    ft_putendl("Error");
  return (0);
}
