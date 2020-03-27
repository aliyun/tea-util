package service

import (
	"strings"
	"testing"

	"github.com/alibabacloud-go/tea/tea"
	"github.com/aliyun/tea-util/golang/utils"
)

func Test_SetFunc(t *testing.T) {
	runtime := new(RuntimeOptions).SetAutoretry(true).
		SetBackoffPeriod(10).
		SetBackoffPolicy("no").
		SetConnectTimeout(100).
		SetHttpProxy("httpproxy").
		SetHttpsProxy("httpsproxy").
		SetIgnoreSSL(true).
		SetLocalAddr("localaddr").
		SetMaxAttempts(3).
		SetMaxIdleConns(5).
		SetNoProxy("noproxy").
		SetReadTimeout(50).
		SetSocks5NetWork("tcp").
		SetSocks5Proxy("sock5proxy")
	utils.AssertEqual(t, true, tea.BoolValue(runtime.Autoretry))
	utils.AssertEqual(t, true, tea.BoolValue(runtime.IgnoreSSL))
	utils.AssertEqual(t, 10, tea.IntValue(runtime.BackoffPeriod))
	utils.AssertEqual(t, 100, tea.IntValue(runtime.ConnectTimeout))
	utils.AssertEqual(t, 50, tea.IntValue(runtime.ReadTimeout))
	utils.AssertEqual(t, 3, tea.IntValue(runtime.MaxAttempts))
	utils.AssertEqual(t, 5, tea.IntValue(runtime.MaxIdleConns))
	utils.AssertEqual(t, "no", tea.StringValue(runtime.BackoffPolicy))
	utils.AssertEqual(t, "httpproxy", tea.StringValue(runtime.HttpProxy))
	utils.AssertEqual(t, "httpsproxy", tea.StringValue(runtime.HttpsProxy))
	utils.AssertEqual(t, "localaddr", tea.StringValue(runtime.LocalAddr))
	utils.AssertEqual(t, "noproxy", tea.StringValue(runtime.NoProxy))
	utils.AssertEqual(t, "tcp", tea.StringValue(runtime.Socks5NetWork))
	utils.AssertEqual(t, "sock5proxy", tea.StringValue(runtime.Socks5Proxy))
	runtime.GoString()
}

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
	res := AssertAsMap(result)
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "test", res["cleint"])

	result, err = ReadAsJSON(strings.NewReader(""))
	utils.AssertNil(t, err)
	utils.AssertNil(t, result)
}

func Test_GetNonce(t *testing.T) {
	nonce := GetNonce()
	utils.AssertEqual(t, 32, len(nonce))
}

type validateTest struct {
	Num *int `json:"num" require:"true"`
}

func Test_ValidateModel(t *testing.T) {
	a := new(validateTest)
	err := ValidateModel(a)
	utils.AssertEqual(t, err.Error(), "num should be setted")

	a.Num = tea.Int(1)
	err = ValidateModel(a)
	utils.AssertNil(t, err)

	err = ValidateModel(nil)
	utils.AssertNil(t, err)
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
		"str": "ok",
	}
	out := StringifyMapValue(in)
	utils.AssertEqual(t, "10", out["num"])
	utils.AssertEqual(t, `{"test":"ok"}`, out["json"])
	utils.AssertEqual(t, "ok", out["str"])
}

func Test_AnyifyMapValue(t *testing.T) {
	in := map[string]string{
		"str": "ok",
	}
	out := AnyifyMapValue(in)
	utils.AssertEqual(t, "ok", out["str"].(string))
}

func Test_AssertAsMap(t *testing.T) {
	in := map[string]interface{}{
		"num": "10",
	}
	out := AssertAsMap(in)
	utils.AssertEqual(t, "10", out["num"].(string))

	defer func() {
		err := recover()
		utils.AssertEqual(t, "10 is not a map[string]interface{}", err)
	}()
	AssertAsMap(10)
}

func Test_AssertAsString(t *testing.T) {
	out := AssertAsString("ok")
	utils.AssertEqual(t, "ok", out)

	defer func() {
		err := recover()
		utils.AssertEqual(t, "10 is not a string", err)
	}()
	AssertAsString(10)
}

func Test_AssertAsNumber(t *testing.T) {
	out := AssertAsNumber(10)
	utils.AssertEqual(t, 10, out)

	defer func() {
		err := recover()
		utils.AssertEqual(t, "false is not a int", err)
	}()
	AssertAsNumber(false)
}

func Test_AssertAsBoolean(t *testing.T) {
	out := AssertAsBoolean(true)
	utils.AssertEqual(t, true, out)

	defer func() {
		err := recover()
		utils.AssertEqual(t, "10 is not a bool", err)
	}()
	AssertAsBoolean(10)
}

func Test_UserAgent(t *testing.T) {
	utils.AssertEqual(t, len(GetUserAgent("")), 61)
	utils.AssertEqual(t, len(GetUserAgent("ccp")), 65)
	utils.AssertContains(t, GetUserAgent("ccp"), " ccp")
}

func Test_Is2xx(t *testing.T) {
	utils.AssertEqual(t, Is2xx(200), true)
	utils.AssertEqual(t, Is2xx(300), false)
}

func Test_Is3xx(t *testing.T) {
	utils.AssertEqual(t, Is3xx(300), true)
	utils.AssertEqual(t, Is3xx(400), false)
}

func Test_Is4xx(t *testing.T) {
	utils.AssertEqual(t, Is4xx(400), true)
	utils.AssertEqual(t, Is4xx(500), false)
}

func Test_Is5xx(t *testing.T) {
	utils.AssertEqual(t, Is5xx(500), true)
	utils.AssertEqual(t, Is5xx(600), false)
}
