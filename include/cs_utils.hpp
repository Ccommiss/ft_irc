/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cs_utils.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:35:44 by csejault          #+#    #+#             */
/*   Updated: 2022/05/19 16:34:56 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CS_UTILS
# define CS_UTILS

#include <iostream>
#include <sstream>
#include "define.hpp"

void	close_fd(int &fd, bool exception);

	template <class T>
void debug( T message, bool cr = true)
{
	if (DEBUG)
	{
		std::cout << message;
		if (cr)
			std::cout << std::endl;
	}
}

	template <class T>
std::string	to_str( T to_convert)
{
	std::stringstream ss;
	ss << to_convert;
	return(ss.str());
}
#endif