/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_convert.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:04:46 by msousa            #+#    #+#             */
/*   Updated: 2022/02/10 23:22:27 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CONVERT_H
# define LIBFT_CONVERT_H

# include "libft.h"

double	ft_atof(char *str);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
char	*ft_itoa(int n);
char	*ft_uitoa(unsigned int n);
char	*ft_ultoa_base(unsigned long n, char *radix);

#endif
