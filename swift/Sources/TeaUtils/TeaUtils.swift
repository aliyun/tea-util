import Foundation
import CryptoSwift
import SwiftyJSON
import Tea


public class TeaUtils {
    public static func toBytes(_ str: String) -> [UInt8] {
        str.toBytes()
    }

    public static func toString(_ bytes: [UInt8]) -> String {
        String(bytes: bytes, encoding: .utf8) ?? ""
    }

    public static func parseJSON(_ str: String) -> [String: AnyObject] {
        str.jsonDecode()
    }

    public static func readAsBytes(_ data: Data) -> [UInt8] {
        [UInt8](data)
    }

    public static func readAsString(_ data: Data) -> String {
        String(data: data, encoding: .utf8) ?? ""
    }

    public static func readAsJSON(_ data: Data) -> [String: AnyObject] {
        let str: String = TeaUtils.readAsString(data)
        return TeaUtils.parseJSON(str)
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

    public static func defaultString(_ real: String?, _ default: String = "") -> String {
        if real == nil {
            return `default`
        }
        let r: String = real!
        return r.isEmpty ? `default` : r
    }

    public static func defaultNumber(_ real: Int?, _ default: Int) -> Int {
        real == nil || real == 0 ? `default` : real ?? 0
    }

    public static func toFormString(query: [String: Any]) -> String {
        var url: String = ""
        if query.count > 0 {
            let keys = Array(query.keys).sorted()
            var arr: [String] = [String]()
            for key in keys {
                let value: String = "\(query[key] ?? "")"
                if value.isEmpty {
                    continue
                }
                arr.append(key + "=" + "\(value)".urlEncode())
            }
            arr = arr.sorted()
            if arr.count > 0 {
                url = arr.joined(separator: "&")
            }
        }
        return url
    }

    public static func toJSONString(_ obj: Any) -> String {
        let json = JSON(obj)
        let r: String = json.rawString(.utf8, options: .fragmentsAllowed) ?? ""
        return r
    }

    public static func empty(_ val: String) -> Bool {
        val.isEmpty
    }

    public static func equalString(_ left: String, _ right: String) -> Bool {
        left == right
    }

    public static func equalNumber(_ left: Int, _ right: Int) -> Bool {
        left == right
    }

    public static func isUnset(_ value: inout Any?) -> Bool {
        value == nil
    }

    public static func stringifyMapValue(_ dict: [String: Any?]) -> [String: String] {
        var map = [String: String]()
        for (key, val) in dict {
            if val != nil {
                if isBool(val) {
                    map[key] = val as! Bool == true ? "true" : "false"
                } else if val as? Int == 0 {
                    map[key] = "0"
                } else if !(val is String) {
                    map[key] = "\(val ?? "")"
                } else {
                    map[key] = val as! String
                }
            }
        }
        return map
    }

    public static func anyifyMapValue(_ dict: [String: String]) -> [String: Any] {
        dict as [String: Any]
    }

    public static func assertAsBoolean(_ any: Any?) throws -> Bool {
        if any is Bool {
            return any as! Bool
        }
        throw TeaException.Error("\(any ?? "") is not a Bool")
    }

    public static func assertAsString(_ any: Any?) throws -> String {
        if any is String {
            return any as! String
        }
        throw TeaException.Error("\(any ?? "") is not a String")
    }

    public static func assertAsBytes(_ any: Any?) throws -> [UInt8] {
        if any is [UInt8] {
            return any as! [UInt8]
        }
        throw TeaException.Error("\(any ?? "") is not a Bytes")
    }

    public static func assertAsNumber(_ any: Any?) throws -> Int {
        if any is Int {
            return any as! Int
        }
        throw TeaException.Error("\(any ?? "") is not a Int")
    }

    public static func assertAsMap(_ any: Any?) throws -> [String: Any?] {
        if any is [String: Any?] {
            return any as! [String: Any?]
        }
        throw TeaException.Error("\(any ?? "") is not a map")
    }

    public static func assertAsArray(_ any: Any?) throws -> [Any?] {
        if any is [Any?] {
            return any as! [Any?]
        }
        throw TeaException.Error("\(any ?? "") is not a array")
    }

    public static func getUserAgent(_ userAgent: String) -> String {
        getDefaultUserAgent() + " " + userAgent
    }

    public static func is2xx(_ code: Int) -> Bool {
        200 <= code && code < 300
    }

    public static func is3xx(_ code: Int) -> Bool {
        300 <= code && code < 400
    }

    public static func is4xx(_ code: Int) -> Bool {
        400 <= code && code < 500
    }

    public static func is5xx(_ code: Int) -> Bool {
        500 <= code && code < 600
    }

    public static func validateModel(_ model: TeaModel) throws -> Void {
        try model.validate()
    }

    public static func toMap(_ model: TeaModel) -> [String: Any] {
        model.toMap()
    }

    public static func sleep(_ millisecond: Int) -> Void {
        Foundation.sleep(UInt32(millisecond / 1000))
    }

    public static func toArray(_ input: Any) -> [[String: Any]] {
        var array = [[String: Any]]()
        for i in input as! [Any?] {
            let model = i as! TeaModel
            array.append(model.toMap())
        }
        return array
    }

//    public static func assertAsReadable(_ value: Any) throws -> Void {
//
//    }
}