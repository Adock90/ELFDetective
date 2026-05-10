# ELFDetective
A Small ELF File Viewer written in C. It allows a user under user priviliges to view: ELF Header, Program Header, Section Headers of a ELF executable file.
Compatible on POSIX based Operating Systems including: Linux, MacOS, Andriod (via <a href="https://github.com/termux">termux</a>), ChromeOS and BSD.
This is not compatible on Windows. For Windows Users -> <a href="https://github.com/Adock90/PEADetective">PEADetective</a>


# Dependancies
ELFDetective does not depend on much. However, it does depend on: <a href="https://sourceware.org/git/glibc.git">glibc</a> (for core program), <a href="https://github.com/python/cpython">Python</a> (for building), <a href="https://www.gnu.org/software/bash/">bash</a> (for installing)


# NOTE

The ELFDetectiveInstall.sh file is for release downloades or Website Downloaders ONLY

# Building from source

<h2>1 Clone or Download as ZIP</h2>

<code>git clone https://github.com/Adock90/ELFDetective</code>

<h2>2 Run build.py</h2>

<code>./build.py</code>

<h2>3 Run Executable</h2>

·/ELFDetective /bin/bash --Header


# Using it

<h2>Help/Manual</h2>
For help with the program, Just run <code>./ELFDetective</code> in the terminal.
This will provide an output that will guide you.

<h2>Check if ELF is 32 bit or 64 bit</h2>
For checking the arch of the CPU it has been compiled for, Just run <code>./ELFDetective [Program Path]</code>
This should output either: <code>ELF64</code> or <code>ELF32</code>.

<h2>Inspect File Header</h2>
For checking the File Header of a ELF File, Run <code>./ELFDetective [Program Path] --Header</code>
This should output the header contents.

<h2>Inspect Program Header</h2>
For checking the Program Header of a ELF File, Run <code>./ELFDetective [Program Path] --Program-Header</code>
This should output the program header contents.

<h2>Inspect Section Headers</h2>
For checking the Program Header of a ELF File, Run <code>./ELFDetective [Program Path] --Section-Headers</code>
This should output the section headers contents.
