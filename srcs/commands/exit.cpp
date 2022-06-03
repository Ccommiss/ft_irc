/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:46:46 by ccommiss          #+#    #+#             */
/*   Updated: 2022/06/03 14:55:23 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"
#include "Answers.hpp"

void Commands::quit_s(Server &s, User *u, std::vector<std::string> cmd) // exit ou quit
{
    (void)cmd;
	s.delete_user(u);
}
