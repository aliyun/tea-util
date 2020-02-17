import XCTest
@testable import TeaUtils

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
        dict["a"] = "b"
        XCTAssertEqual("{\"foo\":\"bar\",\"a\":\"b\"}", TeaUtils.toJSONString(dict))
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

        let result: [String: Any] = TeaUtils.stringifyMapValue(source)
        XCTAssertEqual(target["true"], result["true"] as? String)
        XCTAssertEqual(target["123"], result["123"] as? String)
        XCTAssertEqual(target["foo"], result["foo"] as? String)
        XCTAssertEqual(target["0"], result["0"] as? String)
    }

    func testAssertAsMap() {
        XCTAssertFalse(TeaUtils.assertAsMap(nil))
        XCTAssertFalse(TeaUtils.assertAsMap("string"))

        let map: [String: String] = [String: String]()
        XCTAssertTrue(TeaUtils.assertAsMap(map))
    }

    static var allTests = [
        ("testToBytes", testToBytes),
    ]
}
