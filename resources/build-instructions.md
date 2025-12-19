# Build your dreams!
Here is how to build "Modern SL" and enjoy its free content!

### First step

You have to compile the project using CMake
For this step you need
```
ncurses
CMake ver>=3.0
Make
GCC 14 or higher
```
#### How to build

First you need to download the repo

`
git clone https://github.com/ProgrammEverything/ModernSL.git
`

You can use git here but curl and other methods to download it works too. To continute you must be in the root directory of the project.

If you have downloaded it as a compressed file you must extract it and open the 
terminal in the project directory. (The option "Open Terminal Here from dolphin")

Now that you are in the root directory of the project you can generate your build files from CMake (Depending on what build system you want you can configure it. Here we go with make)

Do:

```
cmake . -B build
```
then do
```
cd build
make
```

Now you have compiled the project
You can execute it by using
```
./ModernSL
```
It is the executable binary and you can use it. Try it without any options and try to add some options to customize its behaviour!