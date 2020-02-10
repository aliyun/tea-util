package com.aliyun.teautil;

import com.aliyun.tea.TeaRequest;
import org.junit.Assert;
import org.junit.Test;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.SimpleTimeZone;

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
        SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss'Z'");
        df.setTimeZone(new SimpleTimeZone(0, "UTC"));
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
}
