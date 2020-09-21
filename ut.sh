#!/bin/bash

function upload_codecov_report {
  # upload_codecov_report <dir> <flag>
  cd "$1" || return 126
  wget --no-check-certificate https://codecov.io/bash -O codecov.sh
  pwd
  bash codecov.sh -cF "$2"
}

function run_swift {
  cd swift/ || rerturn 126
  swift package generate-xcodeproj --enable-code-coverage
  xcodebuild clean build -project TeaUtils.xcodeproj -scheme "TeaUtils-Package" -sdk "macosx" -destination "platform=OS X,arch=x86_64" -configuration Debug ONLY_ACTIVE_ARCH=NO test
  xcodebuild test -project TeaUtils.xcodeproj -scheme "TeaUtils-Package" -sdk "macosx" -destination "platform=OS X,arch=x86_64" -configuration Debug ONLY_ACTIVE_ARCH=NO test
  cd ../
  upload_codecov_report swift swift
}

function run_php {
  cd php/ || return 126
  composer --version
  composer install -vvv
  composer test || return 126
  cd ../
  upload_codecov_report php php
}

function run_go {
  cd golang/ || return 126
  export GO111MODULE=on
  go mod tidy
  go test -race -coverprofile=coverage.txt -covermode=atomic ./service/... || return 126
  cd ../
  upload_codecov_report golang go
}

function run_csharp {
  # before_install
  wget https://download.visualstudio.microsoft.com/download/pr/42f39f2f-3f24-4340-8c57-0a3133620c21/0a353696275b00cbddc9f60069867cfc/dotnet-sdk-2.2.110-linux-x64.tar.gz
  mkdir -p ~/dotnet/ && tar zxf dotnet-sdk-2.2.110-linux-x64.tar.gz -C ~/dotnet/
  sudo ln -sf ~/dotnet/dotnet /usr/bin/dotnet
  dotnet --info

  # install
  cd csharp/tests/ || return 126
  dotnet tool install --global altcover.visualizer
  dotnet restore
  dotnet build
  cd ../

  # run tests
  dotnet test tests/ /p:AltCover=true || return 126
  cd ../

  # upload code coverage report
  upload_codecov_report csharp csharp
}

function run_java {
  cd java/ || return 126
  mvn test -B || return 126
  cd ../
  upload_codecov_report java java
}

function run_ts {
  cd ts/ || return 126
  npm install
  npm run test-cov || return 126
  cd ../
  upload_codecov_report ts node_js
}

function run_python {
  #env
  export PYTHONPATH=$PYTHONPATH:`pwd`/python
  echo $PYTHONPATH 
  # install
  cd python || return 126
  pip install coverage
  pip install alibabacloud-tea

  coverage run --source="./alibabacloud_tea_util" -m pytest tests/test_* || return 126
  cd ../
  upload_codecov_report python python
}

function run_cpp {
  #env
  export CPLUS_INCLUDE_PATH="/usr/local/include/:/usr/include/jsoncpp/:/usr/lib/"
  sudo add-apt-repository ppa:mhier/libboost-latest -y
  sudo apt-get update
  aptitude search boost
  sudo apt-get install libboost-all-dev
  sudo apt-get install lcov libcpprest-dev libcurl4-openssl-dev libssl-dev uuid-dev libjson-c-dev libjsoncpp-dev
  cd cpp/
  sh scripts/codecov.sh
  cd ../
  upload_codecov_report cpp/cmake_build cpp
}

lang=$1

if [ "$lang" == "php" ]
then
  echo "run php"
  run_php
elif [ "$lang" == "go" ]
then
  echo "run golang"
  run_go
elif [ "$lang" == "csharp" ]
then
  echo "run csharp"
  run_csharp
elif [ "$lang" == "java" ]
then
  echo "run java"
  run_java
elif [ "$lang" == "python" ] 
then
  echo "run python"
  run_python
elif [ "$lang" == "ts" ]
then
  echo "run ts"
  run_ts
elif [ "$lang" == "swift" ]
then
  echo "run swift"
  run_swift
elif [ "$lang" == "cpp" ]
then
  echo "run_cpp"
  run_cpp
fi

exit $?