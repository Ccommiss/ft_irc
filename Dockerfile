
FROM ubuntu:latest
ARG my_project=ft_irc
RUN mkdir ${my_project}
ENV TZ=Europe/Minsk
RUN apt-get update -y
RUN apt-get autoclean
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get install -y  build-essential valgrind clang curl zsh git
RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
COPY ./* /${my_project}/
