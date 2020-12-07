package com.aliyun.teautil;

import com.aliyun.tea.TeaModel;
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
       
        InputStream listInputStream = new ByteArrayInputStream("[{\"test\":\"test\"}]".getBytes("UTF-8"));
        List<Object> list = (List<Object>) Common.readAsJSON(listInputStream);
        Assert.assertEquals("{test=test}", list.get(0).toString());
        
        try {
            is = new ByteArrayInputStream("<xml>test</xml>".getBytes("UTF-8"));
            Common.readAsJSON(is);
            Assert.fail();
        } catch (RuntimeException e) {
            Assert.assertEquals("Error: convert to JSON, response is:\n<xml>test</xml>", e.getMessage());
        }
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
    public void toStringTest() throws Exception {
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
        Assert.assertNull(result.get("testNull"));
        Assert.assertEquals("string", result.get("testString"));
        Assert.assertEquals("1", result.get("testNum"));
    }

    @Test
    public void anyifyMapValueTest() {
        Assert.assertNull(Common.anyifyMapValue(null));

        Map<String, String> map = new HashMap<>();
        map.put("testString", "string");
        map.put("testNum", "1");
        map.put("testBoo", "true");
        Map<String, Object> result = Common.anyifyMapValue(map);
        Assert.assertEquals("true", result.get("testBoo"));
        Assert.assertEquals("string", result.get("testString"));
        Assert.assertEquals("1", result.get("testNum"));
    }

    @Test
    public void assertAsMapTest() {
        try {
            Common.assertAsMap(new ArrayList<>());
            Assert.fail();
        } catch (Exception e) {
            Assert.assertEquals("The value is not a object", e.getMessage());
        }

        try {
            Common.assertAsMap(null);
            Assert.fail();
        } catch (Exception e) {
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
    public void is2xxTest() throws Exception {
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

    @Test
    public void validateModelTest() {
        try {
            Common.validateModel(new TeaModel());
            Common.validateModel(null);
            Assert.fail();
        } catch (Exception e) {
            Assert.assertEquals("parameter is not allowed as null", e.getMessage());
        }

    }

    @Test
    public void toMapTest() throws Exception {
        Map map = Common.toMap(new ToMapTest());
        Assert.assertEquals("test", map.get("test"));
    }

    @Test
    public void assertAsBytesTest() throws Exception {
        byte[] result = Common.assertAsBytes(new byte[]{1});
        Assert.assertNotNull(result);

        try {
            Common.assertAsBytes(1);
            Assert.fail();
        } catch (Exception e) {
            Assert.assertEquals("The value is not a byteArray", e.getMessage());
        }
    }

    @Test
    public void assertAsNumberTest() throws Exception {
        Number result = Common.assertAsNumber(1);
        Assert.assertEquals(1, result);

        try {
            Common.assertAsNumber("1");
            Assert.fail();
        } catch (Exception e) {
            Assert.assertEquals("The value is not a Number", e.getMessage());
        }
    }

    @Test
    public void assertAsStringTest() throws Exception {
        String result = Common.assertAsString("test");
        Assert.assertEquals("test", result);

        try {
            Common.assertAsString(1);
            Assert.fail();
        } catch (Exception e) {
            Assert.assertEquals("The value is not a String", e.getMessage());
        }
    }

    @Test
    public void assertAsBooleanTest() throws Exception {
        Boolean result = Common.assertAsBoolean(true);
        Assert.assertTrue(result);

        try {
            Common.assertAsBoolean(1);
            Assert.fail();
        } catch (Exception e) {
            Assert.assertEquals("The value is not a Boolean", e.getMessage());
        }
    }

    @Test
    public void sleepTest() throws InterruptedException {
        long start = System.currentTimeMillis();
        Common.sleep(10);
        long end = System.currentTimeMillis();
        Assert.assertTrue((end-start) >= 10);
    }

    @Test
    public void toArrayTest() {
        Assert.assertNull(Common.toArray(null));
        Assert.assertNull(Common.toArray("String"));

        List<ToMapTest> list = new ArrayList<>();
        ToMapTest toMapTest = new ToMapTest();
        list.add(toMapTest);
        list.add(null);
        List<Map<String, Object>> result = Common.toArray(list);
        Assert.assertEquals("test", result.get(0).get("ToArrayTest"));
    }

    @Test
    public void assertAsReadableTest() throws Exception {
        try {
            Common.assertAsReadable(new ArrayList<>());
            Assert.fail();
        } catch (Exception e) {
            Assert.assertEquals("The value is not a readable", e.getMessage());
        }

        try {
            Common.assertAsReadable(null);
            Assert.fail();
        } catch (Exception e) {
            Assert.assertEquals("The value is not a readable", e.getMessage());
        }

        InputStream inputStream = new ByteArrayInputStream("test".getBytes("UTF-8"));
        Assert.assertEquals(inputStream, Common.assertAsReadable(inputStream));
    }
}
