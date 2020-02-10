﻿using AlibabaCloud.TeaUtil.Models;

using Xunit;

namespace tests.Models
{
    public class RuntimeObjectTest
    {
        [Fact]
        public void Test_RuntimeObject()
        {
            RuntimeOptions runtime = new RuntimeOptions();
            runtime.Autoretry = true;
            runtime.BackoffPeriod = 1;
            runtime.BackoffPolicy = "backoff";
            runtime.ConnectTimeout = 1000;
            runtime.HttpProxy = "proxy";
            runtime.HttpsProxy = "httpsProxy";
            runtime.IgnoreSSL = false;
            runtime.LocalAddr = "localAddr";
            runtime.MaxAttempts = 3;
            runtime.MaxIdleConns = 4;
            runtime.NoProxy = "no";
            runtime.ReadTimeout = 2000;
            runtime.Socks5NetWork = "socks5";
            runtime.Socks5Proxy = "socks5Proxy";

            Assert.NotNull(runtime);
            Assert.True(runtime.Autoretry);
            Assert.Equal(1, runtime.BackoffPeriod);
            Assert.Equal("backoff", runtime.BackoffPolicy);
            Assert.Equal(1000, runtime.ConnectTimeout);
            Assert.Equal("proxy", runtime.HttpProxy);
            Assert.Equal("httpsProxy", runtime.HttpsProxy);
            Assert.False(runtime.IgnoreSSL);
            Assert.Equal("localAddr", runtime.LocalAddr);
            Assert.Equal(3, runtime.MaxAttempts);
            Assert.Equal(4, runtime.MaxIdleConns);
            Assert.Equal("no", runtime.NoProxy);
            Assert.Equal(2000, runtime.ReadTimeout);
            Assert.Equal("socks5", runtime.Socks5NetWork);
            Assert.Equal("socks5Proxy", runtime.Socks5Proxy);
        }
    }
}
