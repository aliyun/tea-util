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

    // privite key for client certificate
    @NameInMap("key")
    public String key;

    // client certificate
    @NameInMap("cert")
    public String cert;

    // server certificate
    @NameInMap("ca")
    public String ca;

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

    public RuntimeOptions setAutoretry(Boolean autoretry) {
        this.autoretry = autoretry;
        return this;
    }
    public Boolean getAutoretry() {
        return this.autoretry;
    }

    public RuntimeOptions setIgnoreSSL(Boolean ignoreSSL) {
        this.ignoreSSL = ignoreSSL;
        return this;
    }
    public Boolean getIgnoreSSL() {
        return this.ignoreSSL;
    }

    public RuntimeOptions setKey(String key) {
        this.key = key;
        return this;
    }
    public String getKey() {
        return this.key;
    }

    public RuntimeOptions setCert(String cert) {
        this.cert = cert;
        return this;
    }
    public String getCert() {
        return this.cert;
    }

    public RuntimeOptions setCa(String ca) {
        this.ca = ca;
        return this;
    }
    public String getCa() {
        return this.ca;
    }

    public RuntimeOptions setMaxAttempts(Integer maxAttempts) {
        this.maxAttempts = maxAttempts;
        return this;
    }
    public Number getMaxAttempts() {
        return this.maxAttempts;
    }

    public RuntimeOptions setBackoffPolicy(String backoffPolicy) {
        this.backoffPolicy = backoffPolicy;
        return this;
    }
    public String getBackoffPolicy() {
        return this.backoffPolicy;
    }

    public RuntimeOptions setBackoffPeriod(Integer backoffPeriod) {
        this.backoffPeriod = backoffPeriod;
        return this;
    }
    public Number getBackoffPeriod() {
        return this.backoffPeriod;
    }

    public RuntimeOptions setReadTimeout(Integer readTimeout) {
        this.readTimeout = readTimeout;
        return this;
    }
    public Number getReadTimeout() {
        return this.readTimeout;
    }

    public RuntimeOptions setConnectTimeout(Integer connectTimeout) {
        this.connectTimeout = connectTimeout;
        return this;
    }
    public Number getConnectTimeout() {
        return this.connectTimeout;
    }

    public RuntimeOptions setHttpProxy(String httpProxy) {
        this.httpProxy = httpProxy;
        return this;
    }
    public String getHttpProxy() {
        return this.httpProxy;
    }

    public RuntimeOptions setHttpsProxy(String httpsProxy) {
        this.httpsProxy = httpsProxy;
        return this;
    }
    public String getHttpsProxy() {
        return this.httpsProxy;
    }

    public RuntimeOptions setNoProxy(String noProxy) {
        this.noProxy = noProxy;
        return this;
    }
    public String getNoProxy() {
        return this.noProxy;
    }

    public RuntimeOptions setMaxIdleConns(Integer maxIdleConns) {
        this.maxIdleConns = maxIdleConns;
        return this;
    }
    public Number getMaxIdleConns() {
        return this.maxIdleConns;
    }

    public RuntimeOptions setLocalAddr(String localAddr) {
        this.localAddr = localAddr;
        return this;
    }
    public String getLocalAddr() {
        return this.localAddr;
    }

    public RuntimeOptions setSocks5Proxy(String socks5Proxy) {
        this.socks5Proxy = socks5Proxy;
        return this;
    }
    public String getSocks5Proxy() {
        return this.socks5Proxy;
    }

    public RuntimeOptions setSocks5NetWork(String socks5NetWork) {
        this.socks5NetWork = socks5NetWork;
        return this;
    }
    public String getSocks5NetWork() {
        return this.socks5NetWork;
    }

    public RuntimeOptions setKeepAlive(Boolean keepAlive) {
        this.keepAlive = keepAlive;
        return this;
    }
    public Boolean getKeepAlive() {
        return this.keepAlive;
    }

}
