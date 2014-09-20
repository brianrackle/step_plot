
## Initialize Environment
sudo apt-get update -y
sudo apt-get upgrade -y
sudo apt-get install g++ subversion cmake emacs git xdg-utils htop ncurses-dev ruby ruby-dev nodejs make -y
sudo mkdir repos

## Pull Clang and LLVM
cd ~/repos/
sudo mkdir clang
cd clang
sudo svn co http://llvm.org/svn/llvm-project/llvm/branches/release_35/ llvm
cd llvm/tools
sudo svn co http://llvm.org/svn/llvm-project/cfe/branches/release_35/ clang

## Build Clang and LLVM
cd ~/repos/clang
sudo mkdir build
cd build
sudo ../llvm/configure --enable-optimized --enable-targets=host --disable-compiler-version-checks
sudo make -j 8
sudo make install

## Pull and Make libc++
cd ~/repos/clang
sudo svn co http://llvm.org/svn/llvm-project/libcxx/trunk libcxx
sudo mkdir build_libcxx
cd build_libcxx
sudo CC=clang CXX=clang++ cmake -G "Unix Makefiles" -DLIBCXX_CXX_ABI=libsupc++ -DLIBCXX_LIBSUPCXX_INCLUDE_PATHS="/usr/include/c++/4.8;/usr/include/x86_64-linux-gnu/c++/4.8" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr $HOME/repos/clang/libcxx
sudo make -j 8
sudo make install

## Setup Emacs
xdg-mime default emacs.desktop text/plain

## Clone BSB
cd ~/repos/
sudo git clone https://github.com/brianrackle/brainstem_breakfast.git
cd brainstem_breakfast/source
sudo clang++ --std=c++14 --stdlib=libc++ main.cpp

## Install Jekyll
sudo gem install jekyll --no-rdoc --no-ri

## All
