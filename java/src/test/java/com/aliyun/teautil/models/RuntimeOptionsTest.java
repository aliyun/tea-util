package com.aliyun.teautil.models;

import org.junit.Assert;
import org.junit.Test;

import java.util.HashMap;
import java.util.Map;

public class RuntimeOptionsTest {
    @Test
    public void setAndGetTest() throws Exception {
        Map<String, Object> map = new HashMap<String, Object>();
        map.put("autoretry", false);
        map.put("ignoreSSL", false);
        map.put("key", "key");
        map.put("cert", "cert");
        map.put("ca", "ca");
        map.put("max_attempts", 3);
        map.put("backoff_policy", "backoffPolicy");
        map.put("backoff_period", 10);
        map.put("readTimeout", 3000);
        map.put("connectTimeout", 3000);
        map.put("httpProxy", "httpProxy");
        map.put("httpsProxy", "httpsProxy");
        map.put("noProxy", "noProxy");
        map.put("maxIdleConns", 300);
        map.put("keepAlive", true);

        RuntimeOptions opts = RuntimeOptions.build(map);
        Assert.assertEquals(false, opts.autoretry);
        Assert.assertEquals(false, opts.ignoreSSL);
        Assert.assertEquals("key", opts.key);
        Assert.assertEquals("cert", opts.cert);
        Assert.assertEquals("ca", opts.ca);
        Assert.assertEquals(3, (int) opts.maxAttempts);
        Assert.assertEquals("backoffPolicy", opts.backoffPolicy);
        Assert.assertEquals(10, (int) opts.backoffPeriod);
        Assert.assertEquals(3000, (int) opts.readTimeout);
        Assert.assertEquals(3000, (int) opts.connectTimeout);
        Assert.assertEquals("httpProxy", opts.httpProxy);
        Assert.assertEquals("httpsProxy", opts.httpsProxy);
        Assert.assertEquals("noProxy", opts.noProxy);
        Assert.assertEquals(300, (int) opts.maxIdleConns);
        Assert.assertEquals(true, opts.keepAlive);
    }
}
