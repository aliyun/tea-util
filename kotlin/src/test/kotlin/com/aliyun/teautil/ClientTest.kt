package com.aliyun.teautil

import com.aliyun.teautil.Client.Companion.empty
import org.junit.Assert
import org.junit.Test
import java.io.ByteArrayInputStream
import java.io.IOException
import java.io.InputStream
import java.io.UnsupportedEncodingException
import java.text.SimpleDateFormat
import java.util.*

class ClientTest {
    @Test
    @Throws(Exception::class)
    fun emptyTest() {
        var `object`: String? = null
        Assert.assertTrue(empty(`object`))
        `object` = "12"
        Assert.assertFalse(Client.empty(`object`))
    }

    @Throws(Exception::class)
    @Test
    fun dateUTCStringTest() {
        val df = SimpleDateFormat("EEE, dd MMM yyyy HH:mm:ss z", Locale.US)
        df.timeZone = SimpleTimeZone(0, "GMT")
        val date = df.parse(Client.getDateUTCString())
        Assert.assertNotNull(date)
    }

    @Test
    fun defaultTest() {
        var result: String = Client.defaultString("test", "default")
        Assert.assertEquals("test", result)
        result = Client.defaultString(null, "default")
        Assert.assertEquals("default", result)
        var number: Number = Client.defaultNumber(3, 4L)
        Assert.assertEquals(3, number)
        number = Client.defaultNumber(null, 4L)
        Assert.assertEquals(4L, number)
        number = Client.defaultNumber(-1, 4L)
        Assert.assertEquals(4L, number)
    }

    @Test
    fun equalStringTest() {
        Assert.assertFalse(Client.equalString(null, "2"))
        Assert.assertFalse(Client.equalString("1", null))
        Assert.assertFalse(Client.equalString("1", "2"))
    }

    @Test
    fun equalNumberTest() {
        Assert.assertFalse(Client.equalNumber(null, 2))
        Assert.assertFalse(Client.equalNumber(1, null))
        Assert.assertFalse(Client.equalNumber(1, 2))
        Assert.assertTrue(Client.equalNumber(6, 6))
    }

    @Test
    @Throws(IOException::class)
    fun readAsJSONTest() {
        Client()
        Assert.assertEquals(null, Client.readAsBytes(null))
        val `is`: InputStream = ByteArrayInputStream("{\"test\":\"test\"}".toByteArray(charset("UTF-8")))
        val map = Client.readAsJSON(`is`) as Map<String, Any>
        Assert.assertEquals("test", map["test"])
    }

    @Test
    @Throws(UnsupportedEncodingException::class)
    fun toFormStringTest() {
        val map: MutableMap<String, Any?> = HashMap()
        var result: String = Client.toFormString(null)
        Assert.assertEquals("", result)
        result = Client.toFormString(map)
        Assert.assertEquals("", result)
        map["form"] = "test"
        map["param"] = "test"
        map["nullTest"] = null
        result = Client.toFormString(map)
        Assert.assertEquals("form=test&param=test", result)
    }

    @Test
    fun toJSONStringTest() {
        val map = HashMap<Any?, Any?>()
        map["test"] = "test"
        Assert.assertEquals("{\"test\":\"test\"}", Client.toJSONString(map))
    }

    @Test
    fun nonceTest() {
        Assert.assertFalse(Client.getNonce() == Client.getNonce())
    }

    @Test
    fun isUnsetTes() {
        Assert.assertTrue(Client.isUnset(null))
        Assert.assertFalse(Client.isUnset("test"))
    }

    @Test
    @Throws(Exception::class)
    fun toStringTest() {
        val bytes: ByteArray = Client.toBytes("test")
        Assert.assertEquals("test", Client.toString(bytes))
    }

    @Test
    fun stringifyMapValueTest() {
        Assert.assertNull(Client.stringifyMapValue(null))
        val map: MutableMap<String, Any?> = HashMap()
        map["testNull"] = null
        map["testString"] = "string"
        map["testNum"] = 1
        map["testBoo"] = true
        val result = Client.stringifyMapValue(map)
        Assert.assertEquals("true", result?.get("testBoo"))
        Assert.assertEquals("null", result?.get("testNull"))
        Assert.assertEquals("string", result?.get("testString"))
        Assert.assertEquals("1", result?.get("testNum"))
    }

    @Test
    fun anyifyMapValueTest() {
        Assert.assertNull(Client.anyifyMapValue(null))
        val map: MutableMap<String, String> = HashMap()
        map["testString"] = "string"
        map["testNum"] = "1"
        map["testBoo"] = "true"
        val result: Map<String, Any>? = Client.anyifyMapValue(map)
        Assert.assertEquals("true", result?.get("testBoo"))
        Assert.assertEquals("string", result?.get("testString"))
        Assert.assertEquals("1", result?.get("testNum"))
    }

    @Test
    fun assertAsMapTest() {
        try {
            Client.assertAsMap(ArrayList<Any>())
            Assert.fail()
        } catch (e: Exception) {
            Assert.assertEquals("The value is not a MutableMap type", e.message)
        }
        try {
            Client.assertAsMap(null)
            Assert.fail()
        } catch (e: Exception) {
            Assert.assertEquals("The value is not a MutableMap type", e.message)
        }
        val map: MutableMap<String, String> = HashMap()
        map["test"] = "test"
        Assert.assertEquals("test", Client.assertAsMap(map)["test"])
    }

    @Throws(Exception::class)
    @Test
    fun userAgentTest() {
        Assert.assertTrue(Client.getUserAgent(null).contains("tea-util"))
        Assert.assertTrue(Client.getUserAgent("test").contains("test"))
    }

    @Test
    @Throws(Exception::class)
    fun is2xxTest() {
        Assert.assertFalse(Client.is2xx(null))
        Assert.assertFalse(Client.is2xx(66))
        Assert.assertFalse(Client.is2xx(400))
        Assert.assertTrue(Client.is2xx(200))
    }

    @Test
    @Throws(Exception::class)
    fun is3xxTest() {
        Assert.assertFalse(Client.is3xx(null))
        Assert.assertFalse(Client.is3xx(66))
        Assert.assertFalse(Client.is3xx(500))
        Assert.assertTrue(Client.is3xx(300))
    }

    @Test
    @Throws(Exception::class)
    fun is4xxTest() {
        Assert.assertFalse(Client.is4xx(null))
        Assert.assertFalse(Client.is4xx(66))
        Assert.assertFalse(Client.is4xx(600))
        Assert.assertTrue(Client.is4xx(400))
    }

    @Test
    @Throws(Exception::class)
    fun is5xxTest() {
        Assert.assertFalse(Client.is5xx(null))
        Assert.assertFalse(Client.is5xx(66))
        Assert.assertFalse(Client.is5xx(700))
        Assert.assertTrue(Client.is5xx(500))
    }

//    @Test
//    @Throws(Exception::class)
//    fun toMapTest() {
//        val map: Map<*, *> = Client.toMap(ToMapTest())
//        Assert.assertEquals("test", map["test"])
//    }
}

