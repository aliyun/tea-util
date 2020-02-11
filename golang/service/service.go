package service

import (
	"encoding/json"
	"fmt"
	"io"
	"io/ioutil"
	"net/http"
	"net/url"
	"strconv"
	"time"

	"github.com/aliyun/tea-util/golang/utils"
)

type RuntimeOptions struct {
	Autoretry      *bool   `json:"autoretry" xml:"autoretry"`
	IgnoreSSL      *bool   `json:"ignoreSSL" xml:"ignoreSSL"`
	MaxAttempts    *int    `json:"maxAttempts" xml:"maxAttempts"`
	BackoffPolicy  *string `json:"backoffPolicy" xml:"backoffPolicy"`
	BackoffPeriod  *int    `json:"backoffPeriod" xml:"backoffPeriod"`
	ReadTimeout    *int    `json:"readTimeout" xml:"readTimeout"`
	ConnectTimeout *int    `json:"connectTimeout" xml:"connectTimeout"`
	LocalAddr      *string `json:"localAddr" xml:"localAddr"`
	HttpProxy      *string `json:"httpProxy" xml:"httpProxy"`
	HttpsProxy     *string `json:"httpsProxy" xml:"httpsProxy"`
	NoProxy        *string `json:"noProxy" xml:"noProxy"`
	MaxIdleConns   *int    `json:"maxIdleConns" xml:"maxIdleConns"`
	Socks5Proxy    *string `json:"socks5Proxy" xml:"socks5Proxy"`
	Socks5NetWork  *string `json:"socks5NetWork" xml:"socks5NetWork"`
}

func ReadAsString(body io.Reader) (string, error) {
	byt, err := ioutil.ReadAll(body)
	if err != nil {
		return "", err
	}
	return string(byt), nil
}

func StringifyMapValue(a map[string]interface{}) map[string]string {
	res := make(map[string]string)
	for key, value := range a {
		byt, _ := json.Marshal(value)
		res[key] = string(byt)
	}
	return res
}

func ReadAsBytes(body io.Reader) ([]byte, error) {
	byt, err := ioutil.ReadAll(body)
	if err != nil {
		return nil, err
	}
	return byt, nil
}

func DefaultString(reaStr, defaultStr string) string {
	if reaStr == "" {
		return defaultStr
	}
	return reaStr
}

func ToJSONString(a map[string]interface{}) string {
	byt, _ := json.Marshal(a)
	return string(byt)
}

func DefaultNumber(reaNum, defaultNum int) int {
	if reaNum == 0 {
		return defaultNum
	}
	return reaNum
}

func ReadAsJSON(body io.Reader) (result map[string]interface{}, err error) {
	byt, err := ioutil.ReadAll(body)
	if err != nil {
		return
	}
	err = json.Unmarshal(byt, &result)
	return
}

func GetNonce() string {
	return utils.GetUUID()
}

func Empty(val string) bool {
	return val == ""
}

func EqualString(val1, val2 string) bool {
	return val1 == val2
}

func EqualNumber(val1, val2 int) bool {
	return val1 == val2
}

func IsUnset(val interface{}) bool {
	return val == nil
}

func ToBytes(a string) []byte {
	return []byte(a)
}

func AssertAsMap(a interface{}) map[string]interface{} {
	byt, _ := json.Marshal(a)
	res := make(map[string]interface{})
	err := json.Unmarshal(byt, &res)
	if err == nil {
		return res
	}
	return res
}

func ParseJSON(a string) interface{} {
	tmp := make(map[string]interface{})
	err := json.Unmarshal([]byte(a), &tmp)
	if err == nil {
		return tmp
	}

	if num, err := strconv.Atoi(a); err == nil {
		return num
	}

	if ok, err := strconv.ParseBool(a); err == nil {
		return ok
	}

	if floa64tVal, err := strconv.ParseFloat(a, 64); err == nil {
		return floa64tVal
	}
	return nil
}

func ToString(a []byte) string {
	return string(a)
}

func ToFormString(a map[string]interface{}) string {
	if a == nil {
		return ""
	}
	res := ""
	first := true
	for k, v := range a {
		if first {
			first = false
		} else {
			res += "&"
		}
		res += url.QueryEscape(k)
		res += "="
		res += url.QueryEscape(fmt.Sprintf("%v", v))
	}
	return res
}

func GetDateUTCString() string {
	return time.Now().UTC().Format(http.TimeFormat)
}
