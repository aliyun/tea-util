//
// Created by Axios on 2020/2/17.
//

import Foundation

func isBool(_ val: Any?) -> Bool {
    if val == nil {
        return false
    }
    if val is Bool {
        return true
    }
    return false
}

func osName() -> String {
    let osNameVersion: String = {
        let version = ProcessInfo.processInfo.operatingSystemVersion
        let versionString = "\(version.majorVersion).\(version.minorVersion).\(version.patchVersion)"

        let osName: String = {
            #if os(iOS)
            return "iOS"
            #elseif os(watchOS)
            return "watchOS"
            #elseif os(tvOS)
            return "tvOS"
            #elseif os(macOS)
            return "OSX"
            #elseif os(Linux)
            return "Linux"
            #else
            return "Unknown"
            #endif
        }()

        return "\(osName)/\(versionString)"
    }()
    return osNameVersion
}

func version() -> String {
    let package: String = {
        guard
                let afInfo = Bundle(for: AlibabaCloudCommons.self).infoDictionary,
                let build = afInfo["CFBundleShortVersionString"],
                let name = afInfo["CFBundleName"]
                else {
            return "Unknown"
        }

        return "\(name)/\(build)"
    }()
    return package
}

var defaultUserAgent:String = ""

func getDefaultUserAgent() -> String {
    if defaultUserAgent.isEmpty {
        defaultUserAgent += osName() + " " + version() + " TeaDSL/1"
    }
    return defaultUserAgent
}
