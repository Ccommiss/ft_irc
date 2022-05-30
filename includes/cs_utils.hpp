/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cs_utils.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:35:44 by csejault          #+#    #+#             */
/*   Updated: 2022/05/25 14:40:21 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CS_UTILS
# define CS_UTILS

#include <iostream>
#include <sstream>
#include "define.hpp"

void	close_fd(int &fd, bool exception);

	template <class T>
void debug( int debug_flag, T message, bool cr = true)
{
	if (DEBUG && (debug_flag == US || debug_flag == SV))
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
