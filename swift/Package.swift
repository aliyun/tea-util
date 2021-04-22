// swift-tools-version:5.1
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "TeaUtils",
    platforms: [
        .iOS(.v12),
        .tvOS(.v12),
        .watchOS(.v5),
        .macOS(.v10_15)
    ],
    products: [
        .library(
            name: "TeaUtils",
            targets: ["TeaUtils"])
    ],
    dependencies: [
        .package(url: "https://github.com/krzyzanowskim/CryptoSwift.git", from: "1.3.0"),
        .package(url: "https://github.com/SwiftyJSON/SwiftyJSON.git", from: "5.0.0"),
        .package(url: "https://github.com/aliyun/tea-swift.git", from: "0.3.0"),
    ],
    targets: [
        .target(
            name: "TeaUtils",
            dependencies: ["CryptoSwift", "SwiftyJSON", "Tea"]),
        .testTarget(
            name: "TeaUtilsTests",
            dependencies: ["TeaUtils", "CryptoSwift", "SwiftyJSON", "Tea"]),
    ]
)
