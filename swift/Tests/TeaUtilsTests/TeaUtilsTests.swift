import XCTest
import Tea
@testable import TeaUtils


class TestModel: TeaModel {
    var num: Int = 100
    var str: String = "string"
}

class TestModel2: TeaModel {
    var num: Int = 200
    var str: String = "model2"
}

final class TeaUtilsTests: XCTestCase {
    func testToBytes() {
        XCTAssertEqual([115, 116, 114, 105, 110, 103], TeaUtils.toBytes("string"))
    }

    func testToString() {
        XCTAssertEqual("string", TeaUtils.toString([115, 116, 114, 105, 110, 103]))
    }

    func testParseJSON() {
        var target: [String: String] = [String: String]()
        target["foo"] = "bar"

        let result: [String: String] = TeaUtils.parseJSON("{\"foo\":\"bar\"}") as! [String: String]
        XCTAssertTrue(target["foo"] == result["foo"])
    }

    func testReadAsBytes() {
        let data: Data = "string".data(using: .utf8)!
        XCTAssertEqual([115, 116, 114, 105, 110, 103], TeaUtils.readAsBytes(data))
    }

    func testReadAsString() {
        let data: Data = "string".data(using: .utf8)!
        XCTAssertEqual("string", TeaUtils.readAsString(data))
    }

    func testReadAsJSON() {
        let data: Data = "{\"foo\":\"bar\"}".data(using: .utf8)!

        var target: [String: String] = [String: String]()
        target["foo"] = "bar"

        let result: [String: String] = TeaUtils.readAsJSON(data) as! [String: String]
        XCTAssertTrue(target["foo"] == result["foo"])
    }

    func testGetNonce() {
        XCTAssertEqual(32, (TeaUtils.getNonce().lengthOfBytes(using: .utf8)))
    }

    func testGetDateUTCString() {
        let date: String = TeaUtils.getDateUTCString()
        XCTAssertEqual(20, date.lengthOfBytes(using: .utf8))
    }

    func testDefaultString() {
        XCTAssertEqual("default", TeaUtils.defaultString(nil, "default"))
        XCTAssertEqual("default", TeaUtils.defaultString("", "default"))
        XCTAssertEqual("real", TeaUtils.defaultString("real", "default"))
    }

    func testDefaultNumber() {
        XCTAssertEqual(1, TeaUtils.defaultNumber(nil, 1))
        XCTAssertEqual(1, TeaUtils.defaultNumber(0, 1))
        XCTAssertEqual(200, TeaUtils.defaultNumber(200, 1))
    }

    func testToFormString() {
        var dict: [String: Any] = [String: Any]()
        dict["foo"] = "bar"
        dict["empty"] = ""
        dict["null"] = nil
        dict["withWhiteSpace"] = "a b"
        XCTAssertEqual("foo=bar&withWhiteSpace=a%20b", TeaUtils.toFormString(query: dict as [String: Any]))
    }

    func testToJSONString() {
        var dict: [String: String] = [String: String]()
        dict["foo"] = "bar"
        XCTAssertEqual("{\"foo\":\"bar\"}", TeaUtils.toJSONString(dict))
    }

    func testEmpty() {
        XCTAssertTrue(TeaUtils.empty(""))
        XCTAssertFalse(TeaUtils.empty("not empty"))
    }

    func testEqualString() {
        XCTAssertTrue(TeaUtils.equalString("equal", "equal"))
        XCTAssertFalse(TeaUtils.equalString("a", "b"))
    }

    func testEqualNumber() {
        XCTAssertTrue(TeaUtils.equalNumber(1, 1))
        XCTAssertFalse(TeaUtils.equalNumber(1, 2))
    }

    func testIsUnset() {
        var a: Any? = nil
        XCTAssertTrue(TeaUtils.isUnset(&a))

        a = "a"
        XCTAssertFalse(TeaUtils.isUnset(&a))
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

        let result = TeaUtils.stringifyMapValue(source)
        XCTAssertEqual(target["true"], result["true"])
        XCTAssertEqual(target["123"], result["123"])
        XCTAssertEqual(target["foo"], result["foo"])
        XCTAssertEqual(target["0"], result["0"])
    }

    func testAssertAsMap() throws {
        do {
            try TeaUtils.assertAsMap("map")
            assert(false)
        } catch {
            switch error{
            case TeaException.Error:
                assert(true)
            default:
                throw error
            }
        }

        let map = [String: String]()
        let res = try TeaUtils.assertAsMap(map)
        XCTAssertEqual(map, res as? [String: String])
    }

    func testGetUserAgent() {
        let userAgent: String = TeaUtils.getUserAgent("CustomizedUserAgent")
        print(userAgent)
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

        let result = TeaUtils.anyifyMapValue(target)
        XCTAssertEqual(target["true"], result["true"] as? String)
        XCTAssertEqual(target["123"], result["123"] as? String)
        XCTAssertEqual(target["foo"], result["foo"] as? String)
        XCTAssertEqual(target["0"], result["0"] as? String)
    }

    func testAssertAsBoolean() throws {
        do {
            try TeaUtils.assertAsBoolean("string")
            assert(false)
        } catch {
            switch error{
            case TeaException.Error:
                assert(true)
            default:
                throw error
            }
        }

        let res = try TeaUtils.assertAsBoolean(false)
        XCTAssertFalse(res)
    }

    func testAssertAsString() throws {
        do {
            try TeaUtils.assertAsString(false)
            assert(false)
        } catch {
            switch error{
            case TeaException.Error:
                assert(true)
            default:
                throw error
            }
        }

        let res = try TeaUtils.assertAsString("string")
        XCTAssertEqual("string", res)
    }

    func testAssertAsBytes() throws {
        do {
            try TeaUtils.assertAsBytes("bytes")
            assert(false)
        } catch {
            switch error{
            case TeaException.Error:
                assert(true)
            default:
                throw error
            }
        }

        let bytes = [UInt8]()
        let res = try TeaUtils.assertAsBytes(bytes)
        XCTAssertEqual(bytes, res)
    }

    func testAssertAsNumber() throws {
        do {
            try TeaUtils.assertAsNumber("number")
            assert(false)
        } catch {
            switch error{
            case TeaException.Error:
                assert(true)
            default:
                throw error
            }
        }

        let res = try TeaUtils.assertAsNumber(101)
        XCTAssertEqual(101, res)
    }

    func testAssertAsArray() throws {
        do {
            try TeaUtils.assertAsArray("array")
            assert(false)
        } catch {
            switch error{
            case TeaException.Error:
                assert(true)
            default:
                throw error
            }
        }

        var array = [Any]()
        array.append(1)
        let res = try TeaUtils.assertAsArray(array)
        XCTAssertEqual(array[0] as! Int, res[0] as! Int)
    }

    func testis2xx() {
        let n1 = 200
        let n2 = 300
        XCTAssertTrue(TeaUtils.is2xx(n1))
        XCTAssertFalse(TeaUtils.is2xx(n2))
    }

    func testis3xx() {
        let n1 = 200
        let n2 = 300
        XCTAssertFalse(TeaUtils.is3xx(n1))
        XCTAssertTrue(TeaUtils.is3xx(n2))
    }

    func testis4xx() {
        let n1 = 300
        let n2 = 400
        XCTAssertFalse(TeaUtils.is4xx(n1))
        XCTAssertTrue(TeaUtils.is4xx(n2))
    }

    func testis5xx() {
        let n1 = 400
        let n2 = 500
        XCTAssertFalse(TeaUtils.is5xx(n1))
        XCTAssertTrue(TeaUtils.is5xx(n2))
    }

    func testValidateModel() throws {
        try TeaUtils.validateModel(TestModel())
    }

    func testToMap() throws {
        let model = TestModel()
        let map = TeaUtils.toMap(model)
        XCTAssertEqual(model.str, map["str"] as! String)
        XCTAssertEqual(model.num, map["num"] as! Int)
    }

    func testSleep() throws {
        let time1 = Date()
        let timeInterval1:TimeInterval = time1.timeIntervalSince1970

        TeaUtils.sleep(2000)

        let time2 = Date()
        let timeInterval2:TimeInterval = time2.timeIntervalSince1970
        let diff = Int(timeInterval2) - Int(timeInterval1)

        XCTAssertTrue(1 < diff && diff < 3)
    }

    func testToArray() throws {
        var array = [TeaModel]()
        array.append(TestModel())
        array.append(TestModel2())
        let res = TeaUtils.toArray(array)

        XCTAssertEqual(100, res[0]["num"] as! Int)
        XCTAssertEqual("string", res[0]["str"] as! String)
        XCTAssertEqual(200, res[1]["num"] as! Int)
        XCTAssertEqual("model2", res[1]["str"] as! String)
    }

    static var allTests = [
        ("testToBytes", testToBytes),
    ]
}
