/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:08:56 by msousa            #+#    #+#             */
/*   Updated: 2022/02/10 23:17:11 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_H
# define LIBFT_MATH_H

# include "libft.h"

int		ft_abs(int n);
size_t	ft_ullen(unsigned long nbr);
size_t	ft_ullen_base(unsigned long nbr, int base);
char	*ft_ultoa_base(unsigned long n, char *radix);
long	ft_pow(int nb, int power);
double	ft_fabs(double n);

#endif
