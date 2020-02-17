// swift-tools-version:5.1
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "TeaUtils",
    products: [
        .library(
            name: "TeaUtils",
            targets: ["TeaUtils"])
    ],
    dependencies: [
        .package(url: "https://github.com/krzyzanowskim/CryptoSwift.git", from: "1.3.0"),
        .package(url: "https://github.com/SwiftyJSON/SwiftyJSON.git", from: "5.0.0"),
    ],
    targets: [
        .target(
            name: "TeaUtils",
            dependencies: ["CryptoSwift", "SwiftyJSON"]),
        .testTarget(
            name: "TeaUtilsTests",
            dependencies: ["TeaUtils", "CryptoSwift", "SwiftyJSON"]),
    ]
)
