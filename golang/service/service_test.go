package service

import (
	"strings"
	"testing"

	"github.com/alibabacloud-go/tea/tea"
	"github.com/alibabacloud-go/tea/utils"
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
	utils.AssertEqual(t, "common", tea.StringValue(str))
}

func Test_ToJSONString(t *testing.T) {
	str := ToJSONString(map[string]interface{}{"test": "ok"})
	utils.AssertEqual(t, `{"test":"ok"}`, tea.StringValue(str))
}

func Test_ReadAsBytes(t *testing.T) {
	byt, err := ReadAsBytes(strings.NewReader("common"))
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "common", string(byt))
}

func Test_DefaultNumber(t *testing.T) {
	num := DefaultNumber(tea.Int(0), tea.Int(1))
	utils.AssertEqual(t, 0, tea.IntValue(num))

	num = DefaultNumber(tea.Int(2), tea.Int(1))
	utils.AssertEqual(t, 2, tea.IntValue(num))
}

func Test_DefaultString(t *testing.T) {
	str := DefaultString(nil, tea.String("1"))
	utils.AssertEqual(t, "1", tea.StringValue(str))

	str = DefaultString(tea.String("2"), tea.String("1"))
	utils.AssertEqual(t, "2", tea.StringValue(str))
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
	utils.AssertEqual(t, 32, len(tea.StringValue(nonce)))
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
	ok := Empty(tea.String(""))
	utils.AssertEqual(t, true, tea.BoolValue(ok))

	ok = Empty(tea.String("oss"))
	utils.AssertEqual(t, false, tea.BoolValue(ok))
}

func Test_EqualString(t *testing.T) {
	ok := EqualString(tea.String("v1"), tea.String("v1"))
	utils.AssertEqual(t, true, tea.BoolValue(ok))

	ok = EqualString(tea.String("v1"), tea.String("v2"))
	utils.AssertEqual(t, false, tea.BoolValue(ok))
}

func Test_EqualNumber(t *testing.T) {
	ok := EqualNumber(tea.Int(1), tea.Int(1))
	utils.AssertEqual(t, true, tea.BoolValue(ok))

	ok = EqualNumber(tea.Int(1), tea.Int(2))
	utils.AssertEqual(t, false, tea.BoolValue(ok))
}

func Test_ToBytes(t *testing.T) {
	byt := ToBytes(tea.String("test"))
	utils.AssertEqual(t, "test", string(byt))
}

func Test_ToMap(t *testing.T) {
	in := map[string]*string{
		"key": tea.String("value"),
	}
	res := ToMap(in)
	utils.AssertEqual(t, "value", res["key"].(string))

	res = ToMap(nil)
	utils.AssertNil(t, res)
}

func Test_ToString(t *testing.T) {
	str := ToString([]byte("test"))
	utils.AssertEqual(t, "test", tea.StringValue(str))
}

func Test_ParseJSON(t *testing.T) {
	obj := ParseJSON(tea.String(`{"test":"ok"}`)).(map[string]interface{})
	utils.AssertEqual(t, "ok", obj["test"])

	num := ParseJSON(tea.String(`10`)).(int)
	utils.AssertEqual(t, 10, num)

	boolVal := ParseJSON(tea.String(`true`)).(bool)
	utils.AssertEqual(t, true, boolVal)

	float64Val := ParseJSON(tea.String(`1.00`)).(float64)
	utils.AssertEqual(t, 1.00, float64Val)

	null := ParseJSON(tea.String(`[1.00]`))
	utils.AssertEqual(t, nil, null)
}

func Test_GetDateUTCString(t *testing.T) {
	time := GetDateUTCString()
	utils.AssertEqual(t, 29, len(tea.StringValue(time)))
}

func Test_ToFormString(t *testing.T) {
	str := ToFormString(nil)
	utils.AssertEqual(t, "", tea.StringValue(str))

	a := map[string]interface{}{
		"key1": "value1",
		"key2": "value2",
	}
	str = ToFormString(a)
	utils.AssertContains(t, tea.StringValue(str), "key1=value1")
}

func Test_IsUnset(t *testing.T) {
	ok := IsUnset(nil)
	utils.AssertEqual(t, true, tea.BoolValue(ok))

	ok = IsUnset("str")
	utils.AssertEqual(t, false, tea.BoolValue(ok))

	var a map[string]string
	ok = IsUnset(a)
	utils.AssertEqual(t, true, tea.BoolValue(ok))
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
	utils.AssertEqual(t, "10", tea.StringValue(out["num"]))
	utils.AssertEqual(t, `{"test":"ok"}`, tea.StringValue(out["json"]))
	utils.AssertEqual(t, "ok", tea.StringValue(out["str"]))
}

func Test_AnyifyMapValue(t *testing.T) {
	in := map[string]*string{
		"str": tea.String("ok"),
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
	out := AssertAsString(tea.String("ok"))
	utils.AssertEqual(t, "ok", tea.StringValue(out))

	defer func() {
		err := recover()
		utils.AssertEqual(t, "10 is not a string", err)
	}()
	AssertAsString(10)
}

func Test_AssertAsNumber(t *testing.T) {
	out := AssertAsNumber(tea.Int(10))
	utils.AssertEqual(t, 10, tea.IntValue(out))

	defer func() {
		err := recover()
		utils.AssertEqual(t, "false is not a int", err)
	}()
	AssertAsNumber(false)
}

func Test_AssertAsBoolean(t *testing.T) {
	out := AssertAsBoolean(tea.Bool(true))
	utils.AssertEqual(t, true, tea.BoolValue(out))

	defer func() {
		err := recover()
		utils.AssertEqual(t, "10 is not a bool", err)
	}()
	AssertAsBoolean(10)
}

func Test_UserAgent(t *testing.T) {
	utils.AssertEqual(t, len(tea.StringValue(GetUserAgent(tea.String("")))), 61)
	utils.AssertEqual(t, len(tea.StringValue(GetUserAgent(tea.String("tea")))), 65)
	utils.AssertContains(t, tea.StringValue(GetUserAgent(tea.String("tea"))), " tea")
}

func Test_Is2xx(t *testing.T) {
	utils.AssertEqual(t, tea.BoolValue(Is2xx(tea.Int(200))), true)
	utils.AssertEqual(t, tea.BoolValue(Is2xx(tea.Int(300))), false)
}

func Test_Is3xx(t *testing.T) {
	utils.AssertEqual(t, tea.BoolValue(Is3xx(tea.Int(300))), true)
	utils.AssertEqual(t, tea.BoolValue(Is3xx(tea.Int(400))), false)
}

func Test_Is4xx(t *testing.T) {
	utils.AssertEqual(t, tea.BoolValue(Is4xx(tea.Int(400))), true)
	utils.AssertEqual(t, tea.BoolValue(Is4xx(tea.Int(500))), false)
}

func Test_Is5xx(t *testing.T) {
	utils.AssertEqual(t, tea.BoolValue(Is5xx(tea.Int(500))), true)
	utils.AssertEqual(t, tea.BoolValue(Is5xx(tea.Int(600))), false)
}
