// This file is auto-generated, don't edit it. Thanks.
package com.aliyun.teautil.models;

import com.aliyun.tea.*;

/**
 * The common runtime options model
 */
public class RuntimeOptions extends TeaModel {
    // whether to try again
    @NameInMap("autoretry")
    public Boolean autoretry = false;

    // ignore SSL validation
    @NameInMap("ignoreSSL")
    public Boolean ignoreSSL = true;

    // maximum number of retries
    @NameInMap("max_attempts")
    public Integer maxAttempts;

    // backoff policy
    @NameInMap("backoff_policy")
    public String backoffPolicy;

    // backoff period
    @NameInMap("backoff_period")
    public Integer backoffPeriod;

    // read timeout
    @NameInMap("readTimeout")
    public Integer readTimeout;

    // connect timeout
    @NameInMap("connectTimeout")
    public Integer connectTimeout;

    // http proxy url
    @NameInMap("httpProxy")
    public String httpProxy;

    // https Proxy url
    @NameInMap("httpsProxy")
    public String httpsProxy;

    // agent blacklist
    @NameInMap("noProxy")
    public String noProxy;

    // maximum number of connections
    @NameInMap("maxIdleConns")
    public Integer maxIdleConns;

    // local addr
    @NameInMap("localAddr")
    public String localAddr;

    // SOCKS5 proxy
    @NameInMap("socks5Proxy")
    public String socks5Proxy;

    // SOCKS5 netWork
    @NameInMap("socks5NetWork")
    public String socks5NetWork;

    // whether to enable keep-alive
    @NameInMap("keepAlive")
    public Boolean keepAlive;

    public static RuntimeOptions build(java.util.Map<String, ?> map) throws Exception {
        RuntimeOptions self = new RuntimeOptions();
        return TeaModel.build(map, self);
    }

}
