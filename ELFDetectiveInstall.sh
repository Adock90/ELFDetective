#!/bin/bash

DEB=0
RED=0
ARCH=0

ls "/etc/debian_version" 2> /dev/null
if [ $? -eq 0 ];
then
	echo "Debian based distro detected"
	DEB=1
else
	echo "Debian based distro not detected"
fi

ls "/etc/redhat-release" 2> /dev/null
if [ $? -eq 0 ];
then
        echo "Red-Hat/Fedora based distro detected"
        RED=1
else

        echo "Red-Hat/Fedora based distro not detected"
fi

ls "/etc/arch-release" 2> /dev/null
if [ $? -eq 0 ];
then
        echo "Arch based distro detected"
        ARCH=1
else
        echo "Arch based distro not detected"
fi


echo "Checking for git"

if [ $DEB -eq 1 ];
then
	dpkg -s git 2> /dev/null
	if [ $? -eq 1 ];
	then
		printf "git is not installed. Want to install.(Y/n)"
		read input
		if [ $input == "y" ] || [ $input == "Y" ];
		then
			sudo apt install git -y
		else
		
			echo -e "Cannot continue without required program git"
		fi
	else
	
		echo  -e "git is installed"
	fi

elif [ $RED -eq 1 ];
then
	rpm -qa git 2> /dev/null
    if [ $? -eq 1 ];
    then
        printf "git is not installed. Want to install.(Y/n)"
		read input
        if [ $input == "y" ] || [ $input == "Y" ];
        then
            sudo dnf install git -y
        else
               
            echo -e "Cannot continue without required program git"
		    exit
        fi
        else
            echo -e "git is installed"
        fi

elif [ $ARCH -eq 1 ];
then
	pacman -Qi git 2> /dev/null
    if [ $? -eq 1 ];
    then
        printf "git is not installed. Want to install.(Y/n)"
        read input
        if [ $input == "y" ] || [ $input == "Y" ];
        then
            yes | sudo pacman -S git
        else
               
            echo -e "Cannot continue without required program git"
			exit
        fi
    else
        echo -e "git is installed"
    fi

else

	echo -e "Unsupported distro"
    echo -e "Install it manually with 'sudo <package manager> install git -y"
	echo -e "Then rerun script"
    exit
fi

cd /home/$USER/

git clone https://github.com/Adock90/ELFDetective

cd ELFDetective/

build.py
