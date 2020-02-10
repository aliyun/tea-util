package utils

import "testing"

func Test_GetUUID(t *testing.T) {
	uuid := GetUUID()
	AssertEqual(t, len(uuid), 32)
}
