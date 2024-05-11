// This file is auto-generated, don't edit it. Thanks.
package com.aliyun.teautil.models;

import com.aliyun.tea.*;

public class ExtendsParameters extends TeaModel {
    @NameInMap("headers")
    public java.util.Map<String, String> headers;

    public static ExtendsParameters build(java.util.Map<String, ?> map) throws Exception {
        ExtendsParameters self = new ExtendsParameters();
        return TeaModel.build(map, self);
    }

    public ExtendsParameters setHeaders(java.util.Map<String, String> headers) {
        this.headers = headers;
        return this;
    }
    public java.util.Map<String, String> getHeaders() {
        return this.headers;
    }

}
