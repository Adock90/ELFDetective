# ELFDetective
A Small ELF File Viewer written in C. It allows a user under user priviliges to view: ELF Header, Program Header, Section Headers of a ELF executable file.
Compatible on POSIX based Operating Systems including: Linux, MacOS, Andriod (via <a href="https://github.com/termux">termux</a>), ChromeOS and BSD.
This is not compatible on Windows. For Windows Users -> <a href="https://github.com/Adock90/PEADetective">PEADetective</a>


# Dependancies
ELFDetective does not depend on much. However, it does depend on: <a href="https://sourceware.org/git/glibc.git">glibc</a> (for core program), <a href="https://github.com/python/cpython">Python</a> (for building), <a href="https://www.gnu.org/software/bash/">bash</a> (for installing)


# NOTE

The ELFDetectiveInstall.sh file is for release downloades or Website Downloaders ONLY

# Building

# 1 Clone or Download as ZIP.

<code>git clone https://github.com/Adock90/ELFDetective</code>

# 2 Run build.py

<code>./build.py</code>

# 3 Run Executable

·/ELFDetective /bin/bash --Header
