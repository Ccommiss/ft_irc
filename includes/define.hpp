/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:31:45 by csejault          #+#    #+#             */
/*   Updated: 2022/05/24 18:47:54 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_HPP
# define DEFINE_HPP

//Flag used to print debug message
#ifndef DEBUG
# define DEBUG 0
#endif

#ifndef DEBUG_SV
# define DEBUG_SV 0
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
# define TIMEOUT                10000

//socket's queue size after what ECONNREFUSED ist return
# define BACKLOG                   10


#define SV  1
#endif
