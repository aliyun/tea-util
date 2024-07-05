package service

import (
	"io/ioutil"
	"strings"
	"testing"
	"time"

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
		SetKey("key").
		SetCert("cert").
		SetCa("ca").
		SetLocalAddr("localaddr").
		SetMaxAttempts(3).
		SetMaxIdleConns(5).
		SetNoProxy("noproxy").
		SetReadTimeout(50).
		SetSocks5NetWork("tcp").
		SetSocks5Proxy("sock5proxy").
		SetKeepAlive(false).
		SetExtendsParameters(new(ExtendsParameters).SetHeaders(map[string]*string{
			"key": tea.String("value")}).SetQueries(map[string]*string{
			"key": tea.String("value"),
		}))
	utils.AssertEqual(t, true, tea.BoolValue(runtime.Autoretry))
	utils.AssertEqual(t, true, tea.BoolValue(runtime.IgnoreSSL))
	utils.AssertEqual(t, "key", tea.StringValue(runtime.Key))
	utils.AssertEqual(t, "cert", tea.StringValue(runtime.Cert))
	utils.AssertEqual(t, "ca", tea.StringValue(runtime.Ca))
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
	utils.AssertEqual(t, false, tea.BoolValue(runtime.KeepAlive))
	utils.AssertEqual(t, "value", tea.StringValue(runtime.ExtendsParameters.Headers["key"]))
	utils.AssertEqual(t, "value", tea.StringValue(runtime.ExtendsParameters.Queries["key"]))
	runtime.GoString()
}

func Test_ReadAsString(t *testing.T) {
	str, err := ReadAsString(strings.NewReader("common"))
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "common", tea.StringValue(str))

	str, err = ReadAsString(ioutil.NopCloser(strings.NewReader("common")))
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "common", tea.StringValue(str))
}

func Test_ToJSONString(t *testing.T) {
	// interface
	str := ToJSONString(map[string]interface{}{"test": "ok"})
	utils.AssertEqual(t, `{"test":"ok"}`, tea.StringValue(str))
	// string
	str = ToJSONString("test")
	utils.AssertEqual(t, "test", tea.StringValue(str))
	// []byte
	str = ToJSONString([]byte("test"))
	utils.AssertEqual(t, "test", tea.StringValue(str))
	// io.Reader
	str = ToJSONString(strings.NewReader("test"))
	utils.AssertEqual(t, "test", tea.StringValue(str))

	str = ToJSONString(tea.String("test"))
	utils.AssertEqual(t, "test", tea.StringValue(str))
}

func Test_ReadAsBytes(t *testing.T) {
	byt, err := ReadAsBytes(strings.NewReader("common"))
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "common", string(byt))

	byt, err = ReadAsBytes(ioutil.NopCloser(strings.NewReader("common")))
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "common", string(byt))
}

func Test_DefaultNumber(t *testing.T) {
	num := DefaultNumber(tea.Int(0), tea.Int(1))
	utils.AssertEqual(t, 0, tea.IntValue(num))

	num = DefaultNumber(nil, tea.Int(1))
	utils.AssertEqual(t, 1, tea.IntValue(num))
}

func Test_DefaultString(t *testing.T) {
	str := DefaultString(nil, tea.String("1"))
	utils.AssertEqual(t, "1", tea.StringValue(str))

	str = DefaultString(tea.String("2"), tea.String("1"))
	utils.AssertEqual(t, "2", tea.StringValue(str))
}

func Test_ReadAsJSON(t *testing.T) {
	result, err := ReadAsJSON(strings.NewReader(`{"cleint":"test"}`))
	res, err := AssertAsMap(result)
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "test", res["cleint"])

	result, err = ReadAsJSON(strings.NewReader(""))
	utils.AssertNil(t, err)
	utils.AssertNil(t, result)

	result, err = ReadAsJSON(ioutil.NopCloser(strings.NewReader(`{"cleint":"test"}`)))
	res, err = AssertAsMap(result)
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "test", res["cleint"])
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

	obj1 := ParseJSON(tea.String(`["test1", "test2", "test3"]`)).([]interface{})
	utils.AssertEqual(t, "test2", obj1[1])

	num := ParseJSON(tea.String(`10`)).(int)
	utils.AssertEqual(t, 10, num)

	boolVal := ParseJSON(tea.String(`true`)).(bool)
	utils.AssertEqual(t, true, boolVal)

	float64Val := ParseJSON(tea.String(`1.00`)).(float64)
	utils.AssertEqual(t, 1.00, float64Val)

	null := ParseJSON(tea.String(`}}}}`))
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
	utils.AssertEqual(t, tea.StringValue(str), "key1=value1&key2=value2")
}

func Test_IsUnset(t *testing.T) {
	ok := IsUnset(nil)
	utils.AssertEqual(t, true, tea.BoolValue(ok))

	ok = IsUnset(tea.String(""))
	utils.AssertEqual(t, false, tea.BoolValue(ok))

	ok = IsUnset("")
	utils.AssertEqual(t, false, tea.BoolValue(ok))

	var a map[string]string
	ok = IsUnset(a)
	utils.AssertEqual(t, true, tea.BoolValue(ok))

	var b []string
	ok = IsUnset(b)
	utils.AssertEqual(t, true, tea.BoolValue(ok))
}

func Test_StringifyMapValue(t *testing.T) {
	in := map[string]interface{}{
		"num": 10,
		"json": map[string]string{
			"test": "ok",
		},
		"str":  "ok",
		"*str": tea.String("ok"),
	}
	out := StringifyMapValue(in)
	utils.AssertEqual(t, "10", tea.StringValue(out["num"]))
	utils.AssertEqual(t, `{"test":"ok"}`, tea.StringValue(out["json"]))
	utils.AssertEqual(t, "ok", tea.StringValue(out["str"]))
	utils.AssertEqual(t, "ok", tea.StringValue(out["*str"]))
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
	out, err := AssertAsMap(in)
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "10", out["num"].(string))

	out, err = AssertAsMap(map[string]string{"key": "value"})
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "value", out["key"].(string))

	out, err = AssertAsMap(map[string]int{"key": 10})
	utils.AssertNil(t, err)
	utils.AssertEqual(t, 10, out["key"].(int))

	out, err = AssertAsMap(10)
	utils.AssertEqual(t, "10 is not a map[string]interface{}", err.Error())
	utils.AssertNil(t, out)
}

func Test_AssertAsString(t *testing.T) {
	out, err := AssertAsString("ok")
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "ok", tea.StringValue(out))

	out, err = AssertAsString(tea.String("ok"))
	utils.AssertNil(t, err)
	utils.AssertEqual(t, "ok", tea.StringValue(out))

	out, err = AssertAsString(10)
	utils.AssertEqual(t, "10 is not a string", err.Error())
	utils.AssertNil(t, out)
}

func Test_AssertAsBytes(t *testing.T) {
	out, err := AssertAsBytes([]byte("ok"))
	utils.AssertNil(t, err)
	utils.AssertEqual(t, []byte("ok"), out)

	out, err = AssertAsBytes(10)
	utils.AssertEqual(t, "10 is not a []byte", err.Error())
	utils.AssertNil(t, out)
}

func Test_AssertAsReadable(t *testing.T) {
	out, err := AssertAsReadable(strings.NewReader("test"))
	utils.AssertNil(t, err)
	byt, _ := ioutil.ReadAll(out)
	utils.AssertEqual(t, []byte("test"), byt)

	out, err = AssertAsReadable(10)
	utils.AssertEqual(t, "10 is not a reader", err.Error())
	utils.AssertNil(t, out)
}

func Test_AssertAsNumber(t *testing.T) {
	out, err := AssertAsNumber(10)
	utils.AssertNil(t, err)
	utils.AssertEqual(t, 10, tea.IntValue(out))

	out, err = AssertAsNumber(tea.Int(10))
	utils.AssertNil(t, err)
	utils.AssertEqual(t, 10, tea.IntValue(out))

	out, err = AssertAsNumber(false)
	utils.AssertEqual(t, "false is not a int", err.Error())
	utils.AssertNil(t, out)
}

func Test_AssertAsInteger(t *testing.T) {
	out, err := AssertAsInteger(10)
	utils.AssertNil(t, err)
	utils.AssertEqual(t, 10, tea.IntValue(out))

	out, err = AssertAsInteger(tea.Int(10))
	utils.AssertNil(t, err)
	utils.AssertEqual(t, 10, tea.IntValue(out))

	out, err = AssertAsInteger(false)
	utils.AssertEqual(t, "false is not a int", err.Error())
	utils.AssertNil(t, out)
}

func Test_AssertAsBoolean(t *testing.T) {
	out, err := AssertAsBoolean(true)
	utils.AssertNil(t, err)
	utils.AssertEqual(t, true, tea.BoolValue(out))

	out, err = AssertAsBoolean(tea.Bool(true))
	utils.AssertNil(t, err)
	utils.AssertEqual(t, true, tea.BoolValue(out))

	out, err = AssertAsBoolean(10)
	utils.AssertEqual(t, "10 is not a bool", err.Error())
	utils.AssertNil(t, out)
}

func Test_UserAgent(t *testing.T) {
	utils.AssertEqual(t, tea.StringValue(GetUserAgent(tea.String(""))), defaultUserAgent)
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

func Test_Sleep(t *testing.T) {
	start := time.Now()
	Sleep(tea.Int(1001))
	cost := time.Since(start)
	utils.AssertEqual(t, cost.Seconds() >= 1, true)
}

type Str struct {
	Key string `json:"key"`
}

func Test_ToArray(t *testing.T) {
	in := []*Str{
		&Str{
			Key: "value",
		},
	}
	res := ToArray(in)
	utils.AssertEqual(t, res[0]["key"], "value")

	res = ToArray(nil)
	utils.AssertNil(t, res)
}

func Test_AssertAsArray(t *testing.T) {
	str := []string{"one", "two", "three"}
	defer func() {
		err := recover()
		if err != nil {
			utils.AssertEqual(t, "[one two three] is not a [x]interface{}", err)
		}
	}()
	array, err := AssertAsArray(str)
	utils.AssertNil(t, err)
	for i := 0; i < len(str); i++ {
		if i == 0 {
			utils.AssertEqual(t, "one", array[i])
		}
		if i == 1 {
			utils.AssertEqual(t, "two", array[i])
		}
		if i == 2 {
			utils.AssertEqual(t, "three", array[i])
		}
	}
}

func TestToJSONString(t *testing.T) {
	tests := []interface{}{"hello", strings.NewReader("abcd"), []byte("hello")}
	str := ToJSONString(tests[0])
	utils.AssertEqual(t, "hello", tea.StringValue(str))
	str = ToJSONString(tests[1])
	utils.AssertEqual(t, "abcd", tea.StringValue(str))
	str = ToJSONString(tests[2])
	utils.AssertEqual(t, "hello", tea.StringValue(str))

	testMap := map[string]interface{}{"key": "value", "map": map[string]string{"str": "test&<>://中文"}, "num": 1}
	str = ToJSONString(testMap)
	utils.AssertEqual(t, "{\"key\":\"value\",\"map\":{\"str\":\"test&<>://中文\"},\"num\":1}", tea.StringValue(str))
}
