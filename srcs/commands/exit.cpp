#include "Server.hpp"
#include "Answers.hpp"

void Commands::quit_s(Server &s, User *u, std::vector<std::string> arg) // exit ou quit
{
    out("QUIT CMD" << *arg.begin())
    s.quit_server(u);
}