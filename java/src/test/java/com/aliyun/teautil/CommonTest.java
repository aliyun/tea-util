package com.aliyun.teautil;

import com.aliyun.tea.TeaRequest;
import org.junit.Assert;
import org.junit.Test;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.text.SimpleDateFormat;
import java.util.*;

public class CommonTest {
    @Test
    public void emptyTest() {
        String object = null;
        Assert.assertTrue(Common.empty(object));

        object = "12";
        Assert.assertFalse(Common.empty(object));
    }

    @Test
    public void getDateUTCStringTest() throws Exception {
        SimpleDateFormat df = new SimpleDateFormat("EEE, dd MMM yyyy HH:mm:ss z", Locale.US);
        df.setTimeZone(new SimpleTimeZone(0, "GMT"));
        Date date = df.parse(Common.getDateUTCString());
        Assert.assertNotNull(date);
    }

    @Test
    public void _defaultTest() {
        String result = Common.defaultString("test", "default");
        Assert.assertEquals("test", result);

        result = Common.defaultString(null, "default");
        Assert.assertEquals("default", result);

        Number number = Common.defaultNumber(3, 4L);
        Assert.assertEquals(3, number);

        number = Common.defaultNumber(null, 4L);
        Assert.assertEquals(4L, number);

        number = Common.defaultNumber(-1, 4L);
        Assert.assertEquals(4L, number);
    }

    public static String getSignature(TeaRequest request, String secret) {
        return null;
    }

    @Test
    public void equalStringTest() {
        Assert.assertFalse(Common.equalString(null, "2"));
        Assert.assertFalse(Common.equalString("1", null));
        Assert.assertFalse(Common.equalString("1", "2"));
    }

    @Test
    public void equalNumberTest() {
        Assert.assertFalse(Common.equalNumber(null, 2));
        Assert.assertFalse(Common.equalNumber(1, null));
        Assert.assertFalse(Common.equalNumber(1, 2));
        Assert.assertTrue(Common.equalNumber(6, 6));
    }

    @Test
    public void readAsJSONTest() throws IOException {
        new Common();
        Assert.assertEquals(0, Common.readAsBytes(null).length);

        InputStream is = new ByteArrayInputStream("{\"test\":\"test\"}".getBytes("UTF-8"));
        Map<String, Object> map = (Map<String, Object>) Common.readAsJSON(is);
        Assert.assertEquals("test", map.get("test"));
    }

    @Test
    public void toFormStringTest() throws UnsupportedEncodingException {
        Map<String, Object> map = new HashMap<>();
        String result = Common.toFormString(null);
        Assert.assertEquals("", result);

        result = Common.toFormString(map);
        Assert.assertEquals("", result);

        map.put("form", "test");
        map.put("param", "test");
        map.put("nullTest", null);
        result = Common.toFormString(map);
        Assert.assertEquals("form=test&param=test", result);
    }

    @Test
    public void toJSONStringTest() {
        Map map = new HashMap();
        map.put("test", "test");
        Assert.assertEquals("{\"test\":\"test\"}", Common.toJSONString(map));
    }

    @Test
    public void getNonceTest() {
        Assert.assertFalse(Common.getNonce().equals(Common.getNonce()));
    }

    @Test
    public void isUnsetTes() {
        Assert.assertTrue(Common.isUnset(null));
        Assert.assertFalse(Common.isUnset("test"));
    }

    @Test
    public void toStringTest() throws Exception{
        byte[] bytes = Common.toBytes("test");
        Assert.assertEquals("test", Common.toString(bytes));
    }

    @Test
    public void stringifyMapValueTest() {
        Assert.assertNull(Common.stringifyMapValue(null));

        Map<String, Object> map = new HashMap<>();
        map.put("testNull", null);
        map.put("testString", "string");
        map.put("testNum", 1);
        map.put("testBoo", true);
        Map<String, String> result = Common.stringifyMapValue(map);
        Assert.assertEquals("true", result.get("testBoo"));
        Assert.assertEquals("null", result.get("testNull"));
        Assert.assertEquals("string", result.get("testString"));
        Assert.assertEquals("1", result.get("testNum"));
    }

    @Test
    public void assertAsMapTest() {
        try {
            Common.assertAsMap(new ArrayList<>());
            Assert.fail();
        }catch (Exception e) {
            Assert.assertEquals("The value is not a object", e.getMessage());
        }

        try {
            Common.assertAsMap(null);
            Assert.fail();
        }catch (Exception e) {
            Assert.assertEquals("The value is not a object", e.getMessage());
        }

        Map<String, String> map = new HashMap<>();
        map.put("test", "test");
        Assert.assertEquals("test", Common.assertAsMap(map).get("test"));
    }

    @Test
    public void getUserAgentTest() throws Exception {
        Assert.assertTrue(Common.getUserAgent(null).contains("tea-util"));
        Assert.assertTrue(Common.getUserAgent("test").contains("test"));
    }

    @Test
    public void is2xxTest() throws Exception{
        Assert.assertFalse(Common.is2xx(null));
        Assert.assertFalse(Common.is2xx(66));
        Assert.assertFalse(Common.is2xx(400));
        Assert.assertTrue(Common.is2xx(200));
    }

    @Test
    public void is3xxTest() throws Exception {
        Assert.assertFalse(Common.is3xx(null));
        Assert.assertFalse(Common.is3xx(66));
        Assert.assertFalse(Common.is3xx(500));
        Assert.assertTrue(Common.is3xx(300));
    }

    @Test
    public void is4xxTest() throws Exception {
        Assert.assertFalse(Common.is4xx(null));
        Assert.assertFalse(Common.is4xx(66));
        Assert.assertFalse(Common.is4xx(600));
        Assert.assertTrue(Common.is4xx(400));
    }

    @Test
    public void is5xxTest() throws Exception {
        Assert.assertFalse(Common.is5xx(null));
        Assert.assertFalse(Common.is5xx(66));
        Assert.assertFalse(Common.is5xx(700));
        Assert.assertTrue(Common.is5xx(500));
    }
}
