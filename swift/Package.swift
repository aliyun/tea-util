// swift-tools-version:5.6
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "TeaUtils",
    platforms: [.macOS(.v10_15),
                .iOS(.v13),
                .tvOS(.v13),
                .watchOS(.v6)],
    products: [
        .library(
            name: "TeaUtils",
            targets: ["TeaUtils"])
    ],
    dependencies: [
        .package(url: "https://github.com/krzyzanowskim/CryptoSwift.git", from: "1.5.1"),
        .package(url: "https://github.com/aliyun/tea-swift.git", from: "1.0.0"),
    ],
    targets: [
        .target(
            name: "TeaUtils",
            dependencies: [
                .product(name: "CryptoSwift", package: "CryptoSwift"),
                .product(name: "Tea", package: "tea-swift")
            ]),
        .testTarget(
            name: "TeaUtilsTests",
            dependencies: [
                "TeaUtils",
                .product(name: "Tea", package: "tea-swift")
            ]),
    ],
    swiftLanguageVersions: [.v5]
)
