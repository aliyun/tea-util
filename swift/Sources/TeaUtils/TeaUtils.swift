import Foundation
import CryptoSwift
import SwiftyJSON
import Tea


public class TeaUtils {
    public static func toBytes(_ str: String?) -> [UInt8] {
        str?.toBytes() ?? []
    }

    public static func toString(_ bytes: [UInt8]?) -> String {
        if bytes != nil {
            return String(bytes: bytes!, encoding: .utf8) ?? ""
        }
        return ""
    }

    public static func parseJSON(_ str: String?) -> Any {
        str?.jsonDecode() ?? [String: Any]()
    }

    @available(macOS 10.15, iOS 13, tvOS 13, watchOS 6, *)
    public static func readAsBytes(_ data: Data?) async throws -> [UInt8] {
        if data != nil {
            return [UInt8](data!)
        }
        return []
    }
    
    @available(macOS 10.15, iOS 13, tvOS 13, watchOS 6, *)
    public static func readAsBytes(_ stream: InputStream?) async throws -> [UInt8] {
        var buff : [UInt8] = []
        stream?.read(&buff, maxLength: 1024)
        return buff
    }

    @available(macOS 10.15, iOS 13, tvOS 13, watchOS 6, *)
    public static func readAsString(_ data: Data?) async throws -> String {
        if data != nil {
            return String(data: data!, encoding: .utf8) ?? ""
        }
        return ""
    }
    
    @available(macOS 10.15, iOS 13, tvOS 13, watchOS 6, *)
    public static func readAsString(_ stream: InputStream?) async throws -> String {
        var buff : [UInt8] = []
        stream?.read(&buff, maxLength: 1024)
        return toString(buff)
    }

    @available(macOS 10.15, iOS 13, tvOS 13, watchOS 6, *)
    public static func readAsJSON(_ data: Data?) async throws -> Any {
        let str: String = try await readAsString(data)
        return parseJSON(str)
    }
    
    @available(macOS 10.15, iOS 13, tvOS 13, watchOS 6, *)
    public static func readAsJSON(_ stream: InputStream?) async throws -> Any {
        let str: String = try await readAsString(stream)
        return parseJSON(str)
    }

    public static func getNonce() -> String {
        let timestamp: TimeInterval = Date().toTimestamp()
        let timestampStr: String = String(timestamp)
        return (String.randomString(len: 10) + timestampStr + UUID().uuidString).md5()
    }

    public static func getDateUTCString() -> String {
        let formatter = DateFormatter()
        formatter.locale = Locale(identifier: "en_US")
        formatter.timeZone = TimeZone(identifier: "GMT")
        formatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss'Z'"
        return formatter.string(from: Date())
    }

    public static func defaultString(_ real: String?, _ default: String?) -> String {
        if real != nil {
            return !real!.isEmpty ? real! : `default` ?? ""
        }
        return `default` ?? ""
    }

    public static func defaultNumber(_ real: NSNumber?, _ default: NSNumber?) -> NSNumber {
        if real != nil {
            return real!
        }
        return `default` ?? 0
    }

    public static func toFormString(query: [String: Any]?) -> String {
        var url: String = ""
        if query != nil && query!.count > 0 {
            let keys = Array(query!.keys).sorted()
            var arr: [String] = []
            for key in keys {
                let value: String = "\(query![key] ?? "")"
                if value.isEmpty {
                    continue
                }
                arr.append(key + "=" + "\(value)".urlEncode())
            }
            if arr.count > 0 {
                url = arr.joined(separator: "&")
            }
        }
        return url
    }

    public static func toJSONString(_ obj: Any?) -> String {
        var r: String = ""
        if obj != nil {
            let json = JSON(obj!)
            r = json.rawString(.utf8, options: .fragmentsAllowed) ?? ""
        }
        return r
    }

    public static func empty(_ val: String?) -> Bool {
        val == nil || val!.isEmpty
    }

    public static func equalString(_ left: String?, _ right: String?) -> Bool {
        left == right
    }

    public static func equalNumber(_ left: NSNumber?, _ right: NSNumber?) -> Bool {
        left == right
    }

    public static func isUnset(_ value: Any?) -> Bool {
        value == nil
    }

    public static func stringifyMapValue(_ dict: [String: Any]?) -> [String: String] {
        var map: [String: String] = [:]
        if dict != nil {
            for (key, val) in dict! {
                if val != nil {
                    if isBool(val) {
                        map[key] = val as! Bool == true ? "true" : "false"
                    } else if val as? Int == 0 {
                        map[key] = "0"
                    } else if val is [UInt8]{
                        map[key] = String(bytes: val as! [UInt8], encoding: .utf8) ?? ""
                    } else if !(val is String) {
                        map[key] = "\(val ?? "")"
                    } else {
                        map[key] = val as! String
                    }
                }
            }
        }
        return map
    }

    public static func anyifyMapValue(_ dict: [String: String]?) -> [String: Any] {
        if dict != nil {
            return dict! as [String: Any]
        }
        return [:]
    }

    public static func assertAsBoolean(_ any: Any?) throws -> Bool {
        if any is Bool {
            return any as! Bool
        }
        throw TeaError("\(any ?? "") is not a Bool")
    }

    public static func assertAsString(_ any: Any?) throws -> String {
        if any is String {
            return any as! String
        }
        throw TeaError("\(any ?? "") is not a String")
    }

    public static func assertAsBytes(_ any: Any?) throws -> [UInt8] {
        if any is [UInt8] {
            return any as! [UInt8]
        }
        throw TeaError("\(any ?? "") is not a Bytes")
    }

    public static func assertAsNumber(_ any: Any?) throws -> NSNumber {
        if any is NSNumber {
            return any as! NSNumber
        }
        if any is String || any is Bool {
            throw TeaError("\(any ?? "") is not a NSNumber")
        }
        return NSNumber(nonretainedObject: any)
    }

    public static func assertAsMap(_ any: Any?) throws -> [String: Any] {
        if any is Dictionary<String, Any> {
            return any as! Dictionary<String, Any>
        }
        throw TeaError("\(any ?? "") is not a map")
    }

    public static func assertAsArray(_ any: Any?) throws -> [Any?] {
        if any is Array<Any?> {
            return any as! Array<Any?>
        }
        throw TeaError("\(any ?? "") is not a array")
    }

    public static func getUserAgent(_ userAgent: String?) -> String {
        getDefaultUserAgent() + " " + (userAgent ?? "")
    }

    public static func is2xx(_ code: Int?) -> Bool {
        code != nil && 200 <= code! && code! < 300
    }

    public static func is3xx(_ code: Int?) -> Bool {
        code != nil && 300 <= code! && code! < 400
    }

    public static func is4xx(_ code: Int?) -> Bool {
        code != nil && 400 <= code! && code! < 500
    }

    public static func is5xx(_ code: Int?) -> Bool {
        code != nil && 500 <= code! && code! < 600
    }

    public static func validateModel(_ model: Tea.TeaModel?) throws -> Void {
        try model?.validate()
    }

    public static func toMap(_ model: Tea.TeaModel?) -> [String: Any] {
        model?.toMap() ?? [:]
    }

    public static func sleep(_ millisecond: Int?) -> Void {
        if millisecond != nil {
            Foundation.sleep(UInt32(millisecond! / 1000))
        }
    }

    public static func toArray(_ input: Any?) -> [[String: Any]] {
        var array: [[String: Any]] = []
        if input != nil {
            for model in input! as! [TeaModel?] {
                if model != nil {
                    array.append(model!.toMap())
                }
            }
        }
        return array
    }

    public static func assertAsReadable(_ value: Any?) throws -> InputStream {
        if value is InputStream {
            return value as! InputStream
        }
        throw TeaError("value is not a InputStream")
    }
}
