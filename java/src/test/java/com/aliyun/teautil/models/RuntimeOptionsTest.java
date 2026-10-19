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
        map.put("domain", "xx.xx.xx.xx");
        map.put("returnErrorResponse", true);

        Map<String, String> headers = new HashMap<String, String>();
        headers.put("key", "value");
        Map<String, String> queries = new HashMap<String, String>();
        queries.put("key", "value");
        Map<String, Object> extendsParameters = new HashMap<String, Object>();
        extendsParameters.put("headers", headers);
        extendsParameters.put("queries", queries);
        map.put("extendsParameters", extendsParameters);

        RuntimeOptions opts = RuntimeOptions.build(map);
        Assert.assertEquals(false, opts.autoretry);
        Assert.assertEquals(false, opts.ignoreSSL);
        Assert.assertEquals("xx.xx.xx.xx", opts.domain);
        Assert.assertTrue(opts.returnErrorResponse);
        
        opts.setDomain("test.domain.com");
        Assert.assertEquals("test.domain.com", opts.getDomain());
        opts.setReturnErrorResponse(false);
        Assert.assertEquals(false, opts.getReturnErrorResponse());
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
        Assert.assertEquals("value", opts.extendsParameters.headers.get("key"));
        Assert.assertEquals("value", opts.extendsParameters.queries.get("key"));
    }

    @Test
    public void setterGetterTest() throws Exception {
        Map<String, String> headers = new HashMap<String, String>();
        headers.put("h", "v");
        Map<String, String> queries = new HashMap<String, String>();
        queries.put("q", "1");

        ExtendsParameters ext = new ExtendsParameters();
        Assert.assertSame(ext, ext.setHeaders(headers));
        Assert.assertSame(ext, ext.setQueries(queries));
        Assert.assertEquals("v", ext.getHeaders().get("h"));
        Assert.assertEquals("1", ext.getQueries().get("q"));

        Map<String, Object> extMap = new HashMap<String, Object>();
        extMap.put("headers", headers);
        extMap.put("queries", queries);
        ExtendsParameters built = ExtendsParameters.build(extMap);
        Assert.assertEquals("v", built.getHeaders().get("h"));
        Assert.assertEquals("1", built.getQueries().get("q"));

        RuntimeOptions opts = new RuntimeOptions();
        Assert.assertSame(opts, opts.setAutoretry(true));
        Assert.assertEquals(Boolean.TRUE, opts.getAutoretry());
        Assert.assertSame(opts, opts.setIgnoreSSL(true));
        Assert.assertEquals(Boolean.TRUE, opts.getIgnoreSSL());
        Assert.assertSame(opts, opts.setKey("key"));
        Assert.assertEquals("key", opts.getKey());
        Assert.assertSame(opts, opts.setCert("cert"));
        Assert.assertEquals("cert", opts.getCert());
        Assert.assertSame(opts, opts.setCa("ca"));
        Assert.assertEquals("ca", opts.getCa());
        Assert.assertSame(opts, opts.setMaxAttempts(3));
        Assert.assertEquals(3, opts.getMaxAttempts());
        Assert.assertSame(opts, opts.setBackoffPolicy("policy"));
        Assert.assertEquals("policy", opts.getBackoffPolicy());
        Assert.assertSame(opts, opts.setBackoffPeriod(10));
        Assert.assertEquals(10, opts.getBackoffPeriod());
        Assert.assertSame(opts, opts.setReadTimeout(3000));
        Assert.assertEquals(3000, opts.getReadTimeout());
        Assert.assertSame(opts, opts.setConnectTimeout(1000));
        Assert.assertEquals(1000, opts.getConnectTimeout());
        Assert.assertSame(opts, opts.setHttpProxy("http://proxy"));
        Assert.assertEquals("http://proxy", opts.getHttpProxy());
        Assert.assertSame(opts, opts.setHttpsProxy("https://proxy"));
        Assert.assertEquals("https://proxy", opts.getHttpsProxy());
        Assert.assertSame(opts, opts.setNoProxy("localhost"));
        Assert.assertEquals("localhost", opts.getNoProxy());
        Assert.assertSame(opts, opts.setMaxIdleConns(5));
        Assert.assertEquals(5, opts.getMaxIdleConns());
        Assert.assertSame(opts, opts.setLocalAddr("127.0.0.1"));
        Assert.assertEquals("127.0.0.1", opts.getLocalAddr());
        Assert.assertSame(opts, opts.setSocks5Proxy("socks5://127.0.0.1"));
        Assert.assertEquals("socks5://127.0.0.1", opts.getSocks5Proxy());
        Assert.assertSame(opts, opts.setSocks5NetWork("tcp"));
        Assert.assertEquals("tcp", opts.getSocks5NetWork());
        Assert.assertSame(opts, opts.setKeepAlive(true));
        Assert.assertEquals(Boolean.TRUE, opts.getKeepAlive());
        Assert.assertSame(opts, opts.setExtendsParameters(ext));
        Assert.assertSame(ext, opts.getExtendsParameters());
    }
}
