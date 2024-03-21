/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoinsep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:54:57 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/21 08:10:10 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"

char	*strjoinsep(char *s1, char *s2, unsigned int sep)
{
	char	*new;
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	new = (char *) malloc((size1 + size2 + 2) * sizeof(char));
	if (!new)
		return (0);
	ft_strlcpy(new, s1, size1 + 1);
	new[size1] = sep;
	new[size1 + 1] = '\0';
	ft_strlcat(new, s2, size1 + size2 + 3);
	return (new);
}
