package service

import (
	"strings"
	"testing"

	"github.com/aliyun/tea-util/golang/utils"
)

func Test_ReadAsString(t *testing.T) {
	str, err := ReadAsString(strings.NewReader("common"))
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "common", str)
}

func Test_ToJSONString(t *testing.T) {
	str := ToJSONString(map[string]interface{}{"test": "ok"})
	utils.AssertEqual(t, `{"test":"ok"}`, str)
}

func Test_ReadAsBytes(t *testing.T) {
	byt, err := ReadAsBytes(strings.NewReader("common"))
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "common", string(byt))
}

func Test_DefaultNumber(t *testing.T) {
	num := DefaultNumber(0, 1)
	utils.AssertEqual(t, 1, num)

	num = DefaultNumber(2, 1)
	utils.AssertEqual(t, 2, num)
}

func Test_DefaultString(t *testing.T) {
	str := DefaultString("", "1")
	utils.AssertEqual(t, "1", str)

	str = DefaultString("2", "1")
	utils.AssertEqual(t, "2", str)
}

func Test_ReadAsJSON(t *testing.T) {
	result, err := ReadAsJSON(strings.NewReader(`{"cleint":"test"}`))
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "test", result["cleint"])
}

func Test_GetNonce(t *testing.T) {
	nonce := GetNonce()
	utils.AssertEqual(t, 32, len(nonce))
}

func Test_Empty(t *testing.T) {
	ok := Empty("")
	utils.AssertEqual(t, true, ok)

	ok = Empty("oss")
	utils.AssertEqual(t, false, ok)
}

func Test_EqualString(t *testing.T) {
	ok := EqualString("v1", "v1")
	utils.AssertEqual(t, true, ok)

	ok = EqualString("v1", "v2")
	utils.AssertEqual(t, false, ok)
}

func Test_EqualNumber(t *testing.T) {
	ok := EqualNumber(1, 1)
	utils.AssertEqual(t, true, ok)

	ok = EqualNumber(1, 2)
	utils.AssertEqual(t, false, ok)
}

func Test_ToBytes(t *testing.T) {
	byt := ToBytes("test")
	utils.AssertEqual(t, "test", string(byt))
}

func Test_ToString(t *testing.T) {
	str := ToString([]byte("test"))
	utils.AssertEqual(t, "test", str)
}

func Test_ParseJSON(t *testing.T) {
	obj := ParseJSON(`{"test":"ok"}`).(map[string]interface{})
	utils.AssertEqual(t, "ok", obj["test"])

	num := ParseJSON(`10`).(int)
	utils.AssertEqual(t, 10, num)

	boolVal := ParseJSON(`true`).(bool)
	utils.AssertEqual(t, true, boolVal)

	float64Val := ParseJSON(`1.00`).(float64)
	utils.AssertEqual(t, 1.00, float64Val)

	null := ParseJSON(`[1.00]`)
	utils.AssertEqual(t, nil, null)
}

func Test_GetDateUTCString(t *testing.T) {
	time := GetDateUTCString()
	utils.AssertEqual(t, 29, len(time))
}

func Test_ToFormString(t *testing.T) {
	str := ToFormString(nil)
	utils.AssertEqual(t, "", str)

	a := map[string]interface{}{
		"key1": "value1",
		"key2": "value2",
	}
	str = ToFormString(a)
	utils.AssertContains(t, str, "key1=value1")
}

func Test_IsUnset(t *testing.T) {
	ok := IsUnset(nil)
	utils.AssertEqual(t, true, ok)

	ok = IsUnset("str")
	utils.AssertEqual(t, false, ok)
}

func Test_StringifyMapValue(t *testing.T) {
	in := map[string]interface{}{
		"num": 10,
		"json": map[string]string{
			"test": "ok",
		},
	}
	out := StringifyMapValue(in)
	utils.AssertEqual(t, "10", out["num"])
	utils.AssertEqual(t, `{"test":"ok"}`, out["json"])
}
