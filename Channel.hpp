#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>

class Channel
{

	public:

		Channel();
		Channel( Channel const & src );
		~Channel();

		Channel &		operator=( Channel const & rhs );

	private:

};

std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */