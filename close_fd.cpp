/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:04:15 by csejault          #+#    #+#             */
/*   Updated: 2022/05/19 16:39:07 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <unistd.h>
#include "cs_utils.hpp"

void	close_fd(int &fd, bool exception)
{
	if (fd >= 0)
	{
		if (0 > close(fd))
		{
			std::stringstream ss;
			ss << "Failed to close fd nb[" << fd << "]";
			fd = -1;
			if (exception)
				throw std::runtime_error(ss.str());
		}
		std::stringstream ss;
		ss << "Succesfully closed fd nb[" << fd << "]";
		debug(ss.str());
		fd = -1;
	}
	else
		debug("WARN - try to close fd -1");
}
