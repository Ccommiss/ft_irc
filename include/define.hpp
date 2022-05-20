/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:31:45 by csejault          #+#    #+#             */
/*   Updated: 2022/05/19 17:55:48 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_HPP
# define DEFINE_HPP

//Flag used to print debug message
#ifndef DEBUG
# define DEBUG 0
#endif

//Flag used to disable printing carriage return
# define NOCR false

//Flag used for throwin (or not) exception
# define THROW true
# define NO_THROW false

//Buffer size for RECV message
#define RECV_BUFF_SIZE 512

//Max client nbr
# define MAX_EVENTS                10

//timeout for epoll wait in ms
//-1 for infinity
# define TIMEOUT                -1

//socket's queue size after what ECONNREFUSED ist return
# define BACKLOG                   10


#endif
