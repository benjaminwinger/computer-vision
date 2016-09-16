FROM nfnty/arch-mini 

MAINTAINER UWARG

RUN printf '[archlinuxfr]\n\
SigLevel = Never\n\
Server = http://repo.archlinux.fr/$arch' >> /etc/pacman.conf

RUN pacman -Sy --noconfirm
RUN pacman -S util-linux gawk yaourt --noconfirm

RUN yaourt -Syua --noconfirm 
RUN useradd warg
RUN su warg
RUN yaourt -S boost opencv opencv-contrib cmake --noconfirm
