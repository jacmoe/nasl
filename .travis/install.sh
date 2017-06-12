#!/bin/bash

set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    brew update || brew update
    brew outdated pyenv || brew upgrade pyenv
    brew install pyenv-virtualenv
    brew install cmake || true

    if which pyenv > /dev/null; then
        eval "$(pyenv init -)"
    fi

    pyenv install 2.7.10
    pyenv virtualenv 2.7.10 conan
    pyenv rehash
    pyenv activate conan
fi

pip install conan_package_tools # It install conan too
pip install conan --upgrade
conan remote list
conan remote remove conan-center
conan remote add dimi https://api.bintray.com/conan/dimi309/conan-packages
conan remote add conan-center https://api.bintray.com/conan/dimi309/conan-packages
conan remote list
conan user
