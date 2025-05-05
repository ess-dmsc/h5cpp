FROM debian:bookworm

RUN apt-get update
RUN apt-get install -y base-passwd apt-utils dialog -y
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN apt-get -qq update && apt-get -qq install -y libterm-readline-gnu-perl software-properties-common coreutils gnupg2 procps curl apt-transport-https gnupg2 ca-certificates wget
RUN apt-get -qq update && apt-get -qq -y dist-upgrade
RUN apt-get -qq update && apt-get  -y install cmake g++ doxygen python3-sphinx git gfortran graphviz libcppunit-dev texlive doxygen pkg-config texlive-latex-extra texlive-latex-recommended texlive-pictures  python3-pygments libgtest-dev lsb-release  python3-breathe texlive-pictures python3-sphinx-rtd-theme libjs-mathjax fonts-mathjax fonts-mathjax-extras ghostscript cmake catch2 libboost-filesystem-dev

RUN apt-get clean

# add p00user
RUN useradd -rm -d /home/p00user -s /bin/bash p00user
USER p00user
RUN mkdir -p /home/p00user/src
WORKDIR /home/p00user/src
