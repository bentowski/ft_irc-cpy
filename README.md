# ft_irc-cpy

//////////////WARNING //////////    
This repo is just a copy of a group project.
you can find the original repo at this address if the owner still switched it on public : https://github.com/ivloisy/ft_irc

////////////////////////////////


ft_irc is a project for the 42 School.

This project has for target to reproduce a little IRC Tchat, by the RFC2812

For run the project, you just need `make`, `c++`, `irssi` (or `netcat`) 

1) compile the project, you have this make commands:

`make` > Just make the project

`make clean` > Clean all objects files

`make fclean` > make clean and clean the executable

`make re` > make fclean and make

2) run the program:
`./ircserv <port> <password>` (the password is required)

3) Connect to the "server" with `irssi` of `netcat`
