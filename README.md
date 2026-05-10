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
This will provide an output like this:

<code>[ELFDetective] No file specified</code>
<code>Usage: ELFDetective [<file>] [<options>]</code>
<code>      [<file>]: The path to the file you want to inspect.</code>
<code>      		Example: ELFDetective /bin/bash --Header</code> 
<code>      [<options>]: The different headers and sections of the elf to inspect.</code>
<code>          Examples: 'ELFDetective --Header' 'ELFDetective --Sections'. Even have multiple 'ELFDetective --Header --Program-Header'</code>
<code>          Options: Include '--Header', '--Program-Header', '--Section-Headers'</code>
