package service

import (
	"testing"

	"github.com/alibabacloud-go/tea/utils"
)

func Test_GetUUID(t *testing.T) {
	uuid := getUUID()
	utils.AssertEqual(t, len(uuid), 32)
}
