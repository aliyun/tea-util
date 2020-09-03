English | [简体中文](/README-zh-CN.md)


# Darabonba Util SDK for C++

![](https://aliyunsdk-pages.alicdn.com/icons/AlibabaCloud.svg)


## Installation

### Linux

```bash
git clone https://github.com/alibabacloud-sdk-cpp/dara-util.git
cd dara-util
sh scripts/install.sh
```

### Windows

1. Run the following command to clone code from Github via git-bash:

  ```bash
  git clone https://github.com/alibabacloud-sdk-cpp/dara-util.git
  ```
2. Build Visual Studio solution
  * Change directory to source code and make directory `cmake_build`
  * Open CMake UI and
    * `Browse Source` to open source code directory.
    * `Browse build`  to open the created `cmake_build` directory
    * click `configure`
    * click `generate`, Generate VS solution

3. Build and Install C++ SDK
  * Go to the cmake_build directory and open darabonba_util.sln with Visual Studio Solutions
  * Select  `Release`
  * Check INSTALL option from Build -> Configuration Manager
  * Build->Build Solutions to build.


## Issue

[Submit Issue](https://github.com/alibabacloud-sdk-cpp/dara-util/issues/new/choose), Problems that do not meet the guidelines may close immediately.


## Release notes

Detailed changes for each version are recorded in the [Release Notes](/CHANGELOG.md).

## Related

* [OpenAPI Explorer][open-api]
* [Latest Release][latest-release]
* [Alibabacloud Console System][console]
* [Alibaba Cloud Home Page][aliyun]

## License

[Apache-2.0](/LICENSE.md)

Copyright (c) 2009-present, Alibaba Cloud All rights reserved.

[open-api]: https://api.aliyun.com
[latest-release]: https://github.com/alibabacloud-sdk-cpp/dara-util/releases
[console]: https://home.console.aliyun.com
[aliyun]: https://www.aliyun.com
