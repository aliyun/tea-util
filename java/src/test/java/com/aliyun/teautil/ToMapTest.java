package com.aliyun.teautil;

import com.aliyun.tea.NameInMap;
import com.aliyun.tea.TeaModel;

public class ToMapTest extends TeaModel {
    public String test = "test";

    @NameInMap("ToArrayTest")
    public String toArray = "test";
}
