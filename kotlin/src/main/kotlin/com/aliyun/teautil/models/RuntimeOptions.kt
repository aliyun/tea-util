// This file is auto-generated, don't edit it
package com.aliyun.teautil.models

import com.aliyun.tea.*;

open class RuntimeOptions : TeaModel() {
    @NameInMap("autoretry")
    open var autoretry: Boolean? = null

    @NameInMap("ignoreSSL")
    open var ignoreSSL: Boolean? = null

    @NameInMap("max_attempts")
    open var maxAttempts: Number? = null

    @NameInMap("backoff_policy")
    open var backoffPolicy: String? = null

    @NameInMap("backoff_period")
    open var backoffPeriod: Number? = null

    @NameInMap("readTimeout")
    open var readTimeout: Number? = null

    @NameInMap("connectTimeout")
    open var connectTimeout: Number? = null

    @NameInMap("httpProxy")
    open var httpProxy: String? = null

    @NameInMap("httpsProxy")
    open var httpsProxy: String? = null

    @NameInMap("noProxy")
    open var noProxy: String? = null

    @NameInMap("maxIdleConns")
    open var maxIdleConns: Number? = null

    @NameInMap("localAddr")
    open var localAddr: String? = null

    @NameInMap("socks5Proxy")
    open var socks5Proxy: String? = null

    @NameInMap("socks5NetWork")
    open var socks5NetWork: String? = null

    companion object {
        open fun build(map : Map<String, Any>): RuntimeOptions {
            var self = RuntimeOptions()
            return build(map, self)
        }
    }
}
