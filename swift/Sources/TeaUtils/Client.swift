import Foundation
import CryptoSwift
import Tea


public class Client {
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
        return (timestampStr + UUID().uuidString).md5()
    }

    public static func getDateUTCString() -> String {
        let formatter = DateFormatter()
        formatter.locale = Locale(identifier: "en_US")
        formatter.timeZone = TimeZone(identifier: "GMT")
        formatter.dateFormat = "EEE, dd MMM yyyy HH:mm:ss z"
        return formatter.string(from: Date())
    }

    public static func defaultString(_ real: String?, _ default: String?) -> String {
        if real != nil {
            return !real!.isEmpty ? real! : `default` ?? ""
        }
        return `default` ?? ""
    }
    
    public static func defaultNumber(_ real: Int?, _ default: Int?) -> Int {
        if real != nil {
            return real!
        }
        return `default` ?? 0
    }
    
    public static func defaultNumber(_ real: Int32?, _ default: Int32?) -> Int32 {
        if real != nil {
            return real!
        }
        return `default` ?? 0
    }
    
    public static func defaultNumber(_ real: Int64?, _ default: Int64?) -> Int64 {
        if real != nil {
            return real!
        }
        return `default` ?? 0
    }

    public static func toFormString(_ query: [String: Any]?) -> String {
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
        if obj == nil {
            return ""
        }
        if obj is [UInt8] {
            return String(bytes: obj as! [UInt8], encoding: .utf8) ?? ""
        }
        if (!JSONSerialization.isValidJSONObject(obj)) {
            return "\(obj!)"
        }
        let data : Data = try! JSONSerialization.data(withJSONObject: obj, options: [])
        let JSONString = NSString(data: data, encoding: String.Encoding.utf8.rawValue)
        return JSONString! as String
    }

    public static func empty(_ val: String?) -> Bool {
        val == nil || val!.isEmpty
    }

    public static func equalString(_ left: String?, _ right: String?) -> Bool {
        left == right
    }
    
    public static func equalNumber(_ left: Int?, _ right: Int?) -> Bool {
        left == right
    }
    
    public static func equalNumber(_ left: Int32?, _ right: Int32?) -> Bool {
        left == right
    }
    
    public static func equalNumber(_ left: Int64?, _ right: Int64?) -> Bool {
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
                    if val is [UInt8]{
                        map[key] = String(bytes: val as! [UInt8], encoding: .utf8) ?? ""
                    } else {
                        map[key] = "\(val)"
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

    public static func assertAsNumber(_ any: Any?) throws -> Int {
        if any is Int {
            return any as! Int
        }
        if any is Int32 {
            return Int(any as! Int32)
        }
        if any is Int64 {
            return Int(any as! Int64)
        }
        throw TeaError("\(any ?? "") is not a Int")
    }

    public static func assertAsInteger(_ value: Any?) throws -> Int {
        if value is Int {
            return value as! Int
        }
        if value is Int32 {
            return Int(value as! Int32)
        }
        if value is Int64 {
            return Int(value as! Int64)
        }
        throw TeaError("\(value ?? "") is not a Int")
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
    
    public static func is2xx(_ code: Int32?) -> Bool {
        code != nil && 200 <= code! && code! < 300
    }

    public static func is3xx(_ code: Int32?) -> Bool {
        code != nil && 300 <= code! && code! < 400
    }

    public static func is4xx(_ code: Int32?) -> Bool {
        code != nil && 400 <= code! && code! < 500
    }

    public static func is5xx(_ code: Int32?) -> Bool {
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
