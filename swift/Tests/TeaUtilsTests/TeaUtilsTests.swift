import XCTest
import Tea
@testable import TeaUtils


class TestModel: TeaModel {
    var num: Int = 100
    var str: String = "string"
    
    public override init() {
        super.init()
    }

    public init(_ dict: [String: Any]) {
        super.init()
        self.fromMap(dict)
    }
    
    public override func validate() throws -> Void {
    }
    
    public override func toMap() -> [String : Any] {
        var map = super.toMap()
        if self.num != nil {
            map["num"] = self.num
        }
        if self.str != nil {
            map["str"] = self.str
        }
        return map
    }
    
    public override func fromMap(_ dict: [String: Any]) -> Void {
        if dict.keys.contains("num") {
            self.num = dict["num"] as! Int
        }
        if dict.keys.contains("str") {
            self.str = dict["str"] as! String
        }
    }
}

class TestModel2: TeaModel {
    var num: Int = 200
    var str: String = "model2"
    
    public override init() {
        super.init()
    }

    public init(_ dict: [String: Any]) {
        super.init()
        self.fromMap(dict)
    }
    
    public override func validate() throws -> Void {
    }
    
    public override func toMap() -> [String : Any] {
        var map = super.toMap()
        if self.num != nil {
            map["num"] = self.num
        }
        if self.str != nil {
            map["str"] = self.str
        }
        return map
    }
    
    public override func fromMap(_ dict: [String: Any]) -> Void {
        if dict.keys.contains("num") {
            self.num = dict["num"] as! Int
        }
        if dict.keys.contains("str") {
            self.str = dict["str"] as! String
        }
    }
}

final class ClientTests: XCTestCase {
    func testToBytes() {
        XCTAssertEqual([115, 116, 114, 105, 110, 103], Client.toBytes("string"))
    }

    func testToString() {
        XCTAssertEqual("string", Client.toString([115, 116, 114, 105, 110, 103]))
    }

    func testParseJSON() {
        let result: [String: Any] = Client.parseJSON("{\"foo\":\"bar\",\"num\":10,\"bool\":true,\"list\":[\"1\",\"2\"],\"map\":{\"key1\":\"value1\",\"key2\":\"value2\"},\"null\":null}") as! [String: Any]
        XCTAssertEqual("bar", result["foo"] as! String)
        XCTAssertEqual(10, result["num"] as! Int)
        XCTAssertEqual(true, result["bool"] as! Bool)
        XCTAssertEqual("1", (result["list"] as! [String])[0])
        XCTAssertEqual("2", (result["list"] as! [String])[1])
        XCTAssertEqual("value1", (result["map"] as! [String: String])["key1"])
    }

    func testReadAsBytes() async throws {
        let data: Data = "string".data(using: .utf8)!
        let result: [UInt8] = try await Client.readAsBytes(data)
        XCTAssertTrue(result == [115, 116, 114, 105, 110, 103])
    }

    func testReadAsString() async throws {
        let data: Data = "string".data(using: .utf8)!
        let result: String = try await Client.readAsString(data)
        XCTAssertEqual("string", result)
    }

    func testReadAsJSON() async throws {
        let data: Data = "{\"foo\":\"bar\"}".data(using: .utf8)!
        var target: [String: String] = [String: String]()
        target["foo"] = "bar"
        let result: [String: String] = try await Client.readAsJSON(data) as! [String: String]
        XCTAssertTrue(target["foo"] == result["foo"])
    }

    func testGetNonce() {
        XCTAssertEqual(32, (Client.getNonce().lengthOfBytes(using: .utf8)))
    }

    func testGetDateUTCString() {
        let date: String = Client.getDateUTCString()
        XCTAssertEqual(29, date.lengthOfBytes(using: .utf8))
    }

    func testDefaultString() {
        XCTAssertEqual("default", Client.defaultString(nil, "default"))
        XCTAssertEqual("default", Client.defaultString("", "default"))
        XCTAssertEqual("real", Client.defaultString("real", "default"))
    }

    func testDefaultNumber() {
        XCTAssertEqual(1, Client.defaultNumber(nil, 1))
        XCTAssertEqual(0, Client.defaultNumber(0, 1))
        XCTAssertEqual(200, Client.defaultNumber(200, 1))
    }

    func testToFormString() {
        var dict: [String: Any] = [String: Any]()
        dict["foo"] = "bar"
        dict["empty"] = ""
        dict["null"] = nil
        dict["withWhiteSpace"] = "a b"
        XCTAssertEqual("foo=bar&withWhiteSpace=a%20b", Client.toFormString(dict as [String: Any]))
    }

    func testToJSONString() {
        var dict: [String: Any] = [:]
        dict["foo"] = "bar"
        dict["num"] = 10
        dict["bool"] = true
        var list: [Any] = []
        list.append("1")
        list.append(2)
        list.append(false)
        dict["list"] = list
        var map: [String: Any] = [:]
        map["key1"] = "value1"
        map["key2"] = 2
        map["key3"] = true
        map["str"] = "test&<>://中文"
        dict["map"] = map
        
        XCTAssertTrue(Client.toJSONString(dict).contains("\"foo\":\"bar\""))
        XCTAssertTrue(Client.toJSONString(dict).contains("\"bool\":true"))
        XCTAssertTrue(Client.toJSONString(dict).contains("\"key1\":\"value1\""))
        XCTAssertTrue(Client.toJSONString(dict).contains("\"key2\":2"))
        XCTAssertTrue(Client.toJSONString(dict).contains("\"key3\":true"))
        XCTAssertTrue(Client.toJSONString(dict).contains("\"str\":\"test&<>:\\/\\/中文\""))
        XCTAssertTrue(Client.toJSONString(dict).contains("\"num\":10"))
        XCTAssertTrue(Client.toJSONString(dict).contains("\"list\":[\"1\",2,false]"))
        
        XCTAssertEqual("", Client.toJSONString(nil))
        XCTAssertEqual("", Client.toJSONString(""))
        XCTAssertEqual("test", Client.toJSONString("test"))
        let bytes: [UInt8] = [115, 116, 114, 105, 110, 103]
        XCTAssertEqual("string", Client.toJSONString(bytes))
    }

    func testEmpty() {
        XCTAssertTrue(Client.empty(""))
        XCTAssertFalse(Client.empty("not empty"))
    }

    func testEqualString() {
        XCTAssertTrue(Client.equalString("equal", "equal"))
        XCTAssertFalse(Client.equalString("a", "b"))
    }

    func testEqualNumber() {
        XCTAssertTrue(Client.equalNumber(1, 1))
        XCTAssertFalse(Client.equalNumber(1, 2))
    }

    func testIsUnset() {
        var a: Any? = nil
        XCTAssertTrue(Client.isUnset(a))

        a = "a"
        XCTAssertFalse(Client.isUnset(a))
    }

    func testStringifyMapValue() {
        var source: [String: Any] = [String: Any]()
        var target: [String: String] = [String: String]()

        source["true"] = true
        target["true"] = "true"
        source["123"] = 123
        target["123"] = "123"
        source["foo"] = "bar"
        target["foo"] = "bar"
        source["0"] = 0
        target["0"] = "0"

        let result = Client.stringifyMapValue(source)
        XCTAssertEqual(target["true"], result["true"])
        XCTAssertEqual(target["123"], result["123"])
        XCTAssertEqual(target["foo"], result["foo"])
        XCTAssertEqual(target["0"], result["0"])
    }

    func testAssertAsMap() throws {
        do {
            try Client.assertAsMap("map")
            assert(false)
        } catch {
            if (error is Tea.TeaError) {
                assert(true)
            } else {
                assertionFailure()
            }
        }

        let map = [String: String]()
        let res = try Client.assertAsMap(map)
        XCTAssertEqual(map, res as? [String: String])
    }

    func testGetUserAgent() {
        let userAgent: String = Client.getUserAgent("CustomizedUserAgent")
        XCTAssertTrue(userAgent.contains("CustomizedUserAgent"))
    }

    func testAnyifyMapValue() {
        var source: [String: Any] = [String: Any]()
        var target: [String: String] = [String: String]()

        source["true"] = true
        target["true"] = "true"
        source["123"] = 123
        target["123"] = "123"
        source["foo"] = "bar"
        target["foo"] = "bar"
        source["0"] = 0
        target["0"] = "0"

        let result = Client.anyifyMapValue(target)
        XCTAssertEqual(target["true"], result["true"] as? String)
        XCTAssertEqual(target["123"], result["123"] as? String)
        XCTAssertEqual(target["foo"], result["foo"] as? String)
        XCTAssertEqual(target["0"], result["0"] as? String)
    }

    func testAssertAsBoolean() throws {
        do {
            try Client.assertAsBoolean("string")
            assert(false)
        } catch {
            if (error is Tea.TeaError) {
                assert(true)
            } else {
                assertionFailure()
            }
        }

        let res = try Client.assertAsBoolean(false)
        XCTAssertFalse(res)
    }

    func testAssertAsString() throws {
        do {
            try Client.assertAsString(false)
            assert(false)
        } catch {
            if (error is Tea.TeaError) {
                assert(true)
            } else {
                assertionFailure()
            }
        }

        let res = try Client.assertAsString("string")
        XCTAssertEqual("string", res)
    }

    func testAssertAsBytes() throws {
        do {
            try Client.assertAsBytes("bytes")
            assert(false)
        } catch {
            if (error is Tea.TeaError) {
                assert(true)
            } else {
                assertionFailure()
            }
        }

        let bytes = [UInt8]()
        let res = try Client.assertAsBytes(bytes)
        XCTAssertEqual(bytes, res)
    }

    func testAssertAsNumber() throws {
        do {
            try Client.assertAsNumber("number")
            assert(false)
        } catch {
            if (error is Tea.TeaError) {
                assert(true)
            } else {
                assertionFailure()
            }
        }
        var num: Int = 1
        num = try Client.assertAsNumber(num)
        XCTAssertEqual(1, num)
        let res = try Client.assertAsNumber(101)
        XCTAssertEqual(101, res)
    }

    func testAssertAsInteger() throws {
        do {
            try Client.assertAsInteger("number")
            assert(false)
        } catch {
            if (error is Tea.TeaError) {
                assert(true)
            } else {
                assertionFailure()
            }
        }
        var num: Int = 1
        num = try Client.assertAsInteger(num)
        XCTAssertEqual(1, num)
        var num32: Int32 = 1
        num = try Client.assertAsInteger(num32)
        XCTAssertEqual(1, num)
        var num64: Int64 = 1
        num = try Client.assertAsInteger(num64)
        XCTAssertEqual(1, num)
        let res = try Client.assertAsInteger(101)
        XCTAssertEqual(101, res)
    }

    func testAssertAsArray() throws {
        do {
            try Client.assertAsArray("array")
            assert(false)
        } catch {
            if (error is Tea.TeaError) {
                assert(true)
            } else {
                assertionFailure()
            }
        }

        var array = [Any]()
        array.append(1)
        let res = try Client.assertAsArray(array)
        XCTAssertEqual(array[0] as! Int, res[0] as! Int)
    }

    func testis2xx() {
        let n1 = 200
        let n2 = 300
        XCTAssertTrue(Client.is2xx(n1))
        XCTAssertFalse(Client.is2xx(n2))
    }

    func testis3xx() {
        let n1 = 200
        let n2 = 300
        XCTAssertFalse(Client.is3xx(n1))
        XCTAssertTrue(Client.is3xx(n2))
    }

    func testis4xx() {
        let n1 = 300
        let n2 = 400
        XCTAssertFalse(Client.is4xx(n1))
        XCTAssertTrue(Client.is4xx(n2))
    }

    func testis5xx() {
        let n1 = 400
        let n2 = 500
        XCTAssertFalse(Client.is5xx(n1))
        XCTAssertTrue(Client.is5xx(n2))
    }

    func testValidateModel() throws {
        try Client.validateModel(TestModel())
    }

    func testToMap() throws {
        let model = TestModel()
        let map = Client.toMap(model)
        XCTAssertEqual(model.str, map["str"] as! String)
        XCTAssertEqual(model.num, map["num"] as! Int)
    }

    func testSleep() throws {
        let time1 = Date()
        let timeInterval1:TimeInterval = time1.timeIntervalSince1970

        Client.sleep(2000)

        let time2 = Date()
        let timeInterval2:TimeInterval = time2.timeIntervalSince1970
        let diff = Int(timeInterval2) - Int(timeInterval1)

        XCTAssertTrue(1 < diff && diff < 3)
    }

    func testToArray() throws {
        var array = [TeaModel]()
        array.append(TestModel())
        array.append(TestModel2())
        let res = Client.toArray(array)
        XCTAssertEqual(2, res.count)
        XCTAssertEqual(100, res[0]["num"] as! Int)
        XCTAssertEqual("string", res[0]["str"] as! String)
        XCTAssertEqual(200, res[1]["num"] as! Int)
        XCTAssertEqual("model2", res[1]["str"] as! String)
    }

    func testRuntimeOptions() throws {
        var opts = RuntimeOptions(
            [
                "autoretry": false,
                "ignoreSSL": false,
                "key": "key",
                "cert": "cert",
                "ca": "ca",
                "max_attempts": 3,
                "backoff_policy": "backoffPolicy",
                "backoff_period": 10,
                "readTimeout": 3000,
                "connectTimeout": 3000,
                "httpProxy": "httpProxy",
                "httpsProxy": "httpsProxy",
                "noProxy": "noProxy",
                "maxIdleConns": 300,
                "keepAlive": true,
            ]
        )
        XCTAssertEqual(false, opts.autoretry)
        XCTAssertEqual(false, opts.ignoreSSL)
        XCTAssertEqual("key", opts.key)
        XCTAssertEqual("cert", opts.cert)
        XCTAssertEqual("ca", opts.ca)
        XCTAssertEqual(3, opts.maxAttempts)
        XCTAssertEqual("backoffPolicy", opts.backoffPolicy)
        XCTAssertEqual(10, opts.backoffPeriod)
        XCTAssertEqual(3000, opts.readTimeout)
        XCTAssertEqual(3000, opts.connectTimeout)
        XCTAssertEqual("httpProxy", opts.httpProxy)
        XCTAssertEqual("httpsProxy", opts.httpsProxy)
        XCTAssertEqual("noProxy", opts.noProxy)
        XCTAssertEqual(300, opts.maxIdleConns)
        XCTAssertEqual(true, opts.keepAlive)
    }

    static var allTests = [
        ("testToBytes", testToBytes),
        ("testToString", testToString),
        ("testParseJSON", testParseJSON),
        ("testReadAsBytes", testReadAsBytes),
        ("testReadAsString", testReadAsString),
        ("testReadAsJSON", testReadAsJSON),
        ("testGetNonce", testGetNonce),
        ("testGetDateUTCString", testGetDateUTCString),
        ("testDefaultString", testDefaultString),
        ("testDefaultNumber", testDefaultNumber),
        ("testToFormString", testToFormString),
        ("testToJSONString", testToJSONString),
        ("testEqualString", testEqualString),
        ("testEqualNumber", testEqualNumber),
        ("testIsUnset", testIsUnset),
        ("testStringifyMapValue", testStringifyMapValue),
        ("testAssertAsMap", testAssertAsMap),
        ("testGetUserAgent", testGetUserAgent),
        ("testAnyifyMapValue", testAnyifyMapValue),
        ("testAssertAsBoolean", testAssertAsBoolean),
        ("testAssertAsString", testAssertAsString),
        ("testAssertAsBytes", testAssertAsBytes),
        ("testAssertAsNumber", testAssertAsNumber),
        ("testAssertAsArray", testAssertAsArray),
        ("testis2xx", testis2xx),
        ("testis3xx", testis3xx),
        ("testis4xx", testis4xx),
        ("testis5xx", testis5xx),
        ("testValidateModel", testValidateModel),
        ("testToMap", testToMap),
        ("testSleep", testSleep),
        ("testToArray", testToArray),
    ]
}
