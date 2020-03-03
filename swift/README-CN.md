[English](README.md) | 简体中文

![](https://aliyunsdk-pages.alicdn.com/icons/AlibabaCloud.svg)

## Alibaba Cloud Tea Util for Swift

## 依赖

- iOS 13.3+ / macOS 10.15+
- Xcode 11.3+
- Swift 5.1

## 安装

### CocoaPods

[CocoaPods](https://cocoapods.org) 是 Cocoa 项目管理工具。请访问其官方网站获取关于 CocoaPods 的使用和安装说明。要使用 CocoaPods 将 `TeaUtils` 集成到你的 Xcode 项目中，需要在 `Podfile` 中定义以下内容:

```ruby
pod 'TeaUtils', '~> 0.1.0'
```

### Carthage

要使用 [Carthage](https://github.com/Carthage/Carthage) 将 Tea 集成到你的 Xcode 项目中，需要在 `Cartfile` 中定义以下内容:

```ogdl
github "alibabacloud-sdk-swift/tea-utils" "0.1.0"
```

### Swift 包管理工具

要使用 [Swift Package Manager](https://swift.org/package-manager/) 将 Tea 集成到你的 Xcode 项目中，请将 Tea 添加至你的 `Package.swift` 文件的 dependencies 数组内容中:

```swift
dependencies: [
    .package(url: "https://github.com/alibabacloud-sdk-swift/tea-utils.git", from: "0.1.0")
]
```

另外，还需要在 `target` 的 `dependencies` 中添加 `"TeaUtils"`，如下：

```swift
.target(
    name: "<your-project-name>",
    dependencies: [
        "TeaUtils",
    ]),
```

## 问题

[提交 Issue](https://github.com/alibabacloud-sdk-swift/tea-utils/issues/new)，不符合指南的问题可能会立即关闭。

## 发行说明

每个版本的详细更改记录在[发行说明](./ChangeLog.txt)中。

## 相关

* [最新源码](https://github.com/alibabacloud-sdk-swift/tea-utils/tree/master/swift)

## 许可证

[Apache-2.0](http://www.apache.org/licenses/LICENSE-2.0)

Copyright (c) 2009-present, Alibaba Cloud All rights reserved.
