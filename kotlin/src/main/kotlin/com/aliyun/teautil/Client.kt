// This file is auto-generated, don't edit it
package com.aliyun.teautil

import com.aliyun.tea.TeaModel
import com.aliyun.tea.utils.StringUtils
import com.google.gson.Gson
import java.io.ByteArrayOutputStream
import java.io.InputStream
import java.net.URLEncoder
import java.text.SimpleDateFormat
import java.util.*

open class Client {

    companion object {
        private val defaultUserAgent: String = String.format("AlibabaCloud (%s; %s) Java/%s %s/%s TeaDSL/1",
                com.aliyun.teautil.KotlinProject.sysProps.getProperty("os.name"),
                com.aliyun.teautil.KotlinProject.sysProps.getProperty("os.arch"),
                com.aliyun.teautil.KotlinProject.sysProps.getProperty("java.runtime.version"),
                "tea-util",
                com.aliyun.teautil.KotlinProject.teaUtilVersion)


        /**
         * Convert a string(utf8) to bytes
         * @return the return bytes
         */
        @Throws(Exception::class)
        open fun toBytes(_val: String): ByteArray {
            return _val.toByteArray(charset("UTF-8"))
        }

        /**
         * Convert a bytes to string(utf8)
         * @return the return string
         */
        @Throws(Exception::class)
        open fun toString(_val: ByteArray): String {
            return String(_val)
        }

        /**
         * Parse it by JSON format
         * @return the parsed result
         */
        @Throws(Exception::class)
        open fun parseJSON(_val: String?): Any {
            return Gson().fromJson(_val, Map::class.java)
        }

        /**
         * Read data from a readable stream, and compose it to a bytes
         * @param stream the readable stream
         * @return the bytes result
         */
        @Throws(Exception::class)
        open fun readAsBytes(stream: InputStream?): ByteArray? {
            if (null == stream) {
                return stream
            } else {
                val os = ByteArrayOutputStream()
                val buff = ByteArray(4096)
                while (true) {
                    val read = stream.read(buff)
                    if (read == -1) {
                        return os.toByteArray()
                    }
                    os.write(buff, 0, read)
                }
            }
        }

        /**
         * Read data from a readable stream, and compose it to a string
         * @param stream the readable stream
         * @return the string result
         */
        @Throws(Exception::class)
        open fun readAsString(stream: InputStream): String? {
            return readAsBytes(stream)?.toString(Charsets.UTF_8)
        }

        /**
         * Read data from a readable stream, and parse it by JSON format
         * @param stream the readable stream
         * @return the parsed result
         */
        @Throws(Exception::class)
        open fun readAsJSON(stream: InputStream): Any? {
            return parseJSON(readAsString(stream));
        }

        /**
         * Generate a nonce string
         * @return the nonce string
         */
        @Throws(Exception::class)
        open fun getNonce(): String {
            val uniqueNonce = StringBuffer()
            val uuid = UUID.randomUUID()
            uniqueNonce.append(uuid.toString())
            uniqueNonce.append(System.currentTimeMillis())
            uniqueNonce.append(Thread.currentThread().id)
            return uniqueNonce.toString()
        }

        /**
         * Get an UTC format string by current date, e.g. 'Thu, 06 Feb 2020 07:32:54 GMT'
         * @return the UTC format string
         */
        @Throws(Exception::class)
        open fun getDateUTCString(): String {
            val df = SimpleDateFormat("EEE, dd MMM yyyy HH:mm:ss z", Locale.US)
            df.timeZone = SimpleTimeZone(0, "GMT")
            return df.format(Date())
        }

        /**
         * If not set the real, use default value
         * @return the return string
         */
        @Throws(Exception::class)
        open fun defaultString(real: String?, _default: String): String {
            return (if (!StringUtils.isEmpty(real)) {
                real
            } else _default) as String
        }

        /**
         * If not set the real, use default value
         * @return the return number
         */
        @Throws(Exception::class)
        open fun defaultNumber(real: Number?, _default: Number): Number {
            return if (real != null && real.toDouble() >= 0) {
                real
            } else _default
        }

        /**
         * Format a map to form string, like a=a%20b%20c
         * @return the form string
         */
        @Throws(Exception::class)
        open fun toFormString(_val: MutableMap<String, Any?>?): String {
            if (null == _val) {
                return ""
            }
            val result = StringBuilder()
            var first = true
            for ((key, value) in _val.entries) {
                if (StringUtils.isEmpty(value)) {
                    continue
                }
                if (first) {
                    first = false
                } else {
                    result.append("&")
                }
                result.append(URLEncoder.encode(key, "UTF-8"))
                result.append("=")
                result.append(URLEncoder.encode(value.toString(), "UTF-8"))
            }
            return result.toString()
        }

        /**
         * Stringify a value by JSON format
         * @return the JSON format string
         */
        @Throws(Exception::class)
        open fun toJSONString(_val: Any): String {
            return Gson().toJson(_val)
        }

        /**
         * Check the string is empty?
         * @return if string is null or zero length, return true
         */
        @Throws(Exception::class)
        open fun empty(_val: String?): Boolean {
            return if (null == _val) true else StringUtils.isEmpty(_val)
        }

        /**
         * Check one string equals another one?
         * @return if equals, return true
         */
        @Throws(Exception::class)
        open fun equalString(val1: String?, val2: String?): Boolean {
            return if (val1 == null || val2 == null) {
                false
            } else val1 === val2
        }

        /**
         * Check one number equals another one?
         * @return if equals, return true
         */
        @Throws(Exception::class)
        open fun equalNumber(val1: Number?, val2: Number?): Boolean {
            return if (val1 == null || val2 == null) {
                false
            } else val1.toDouble() == val2.toDouble()
        }

        /**
         * Check one value is unset
         * @return if unset, return true
         */
        @Throws(Exception::class)
        open fun isUnset(value: Any?): Boolean {
            return null == value
        }

        /**
         * Stringify the value of map
         * @return the new stringified map
         */
        @Throws(Exception::class)
        open fun stringifyMapValue(m: MutableMap<String, Any?>?): MutableMap<String, String?>? {
            val result: MutableMap<String, String?> = HashMap()
            if (null == m) {
                return m
            }
            m.forEach { (key: String, value: Any?) -> result[key] = value.toString() }
            return result
        }

        /**
         * Anyify the value of map
         * @return the new anyfied map
         */
        @Throws(Exception::class)
        open fun anyifyMapValue(m: MutableMap<String, String>?): MutableMap<String, Any>? {
            val result: MutableMap<String, Any> = HashMap()
            if (null == m) {
                return m
            }
            m.forEach { (key: String, value: Any) -> result[key] = value }
            return result
        }

        /**
         * Assert a value, if it is a boolean, return it, otherwise throws
         * @return the boolean value
         */
        @Throws(Exception::class)
        open fun assertAsBoolean(value: Any): Boolean {
            if (value is Boolean) {
                return value
            } else throw RuntimeException("The value is not a Boolean type")
        }

        /**
         * Assert a value, if it is a string, return it, otherwise throws
         * @return the string value
         */
        @Throws(Exception::class)
        open fun assertAsString(value: Any): String {
            if (value is String) {
                return value
            } else throw RuntimeException("The value is not a String type")
        }

        /**
         * Assert a value, if it is a number, return it, otherwise throws
         * @return the number value
         */
        @Throws(Exception::class)
        open fun assertAsNumber(value: Any): Number {
            if (value is Number) {
                return value
            } else throw RuntimeException("The value is not a Number type")
        }

        /**
         * Assert a value, if it is a map, return it, otherwise throws
         * @return the map value
         */
        @Throws(Exception::class)
        open fun assertAsMap(value: Any?): MutableMap<String, Any> {
            if (value is MutableMap<*, *>) {
                return value as MutableMap<String, Any>
            } else throw RuntimeException("The value is not a MutableMap type")
        }

        /**
         * Get user agent, if it userAgent is not null, splice it with defaultUserAgent and return, otherwise return defaultUserAgent
         * @return the string value
         */
        @Throws(Exception::class)
        open fun getUserAgent(userAgent: String?): String {
            return if (StringUtils.isEmpty(userAgent)) {
                defaultUserAgent
            } else "$defaultUserAgent $userAgent"
        }

        /**
         * If the code between 200 and 300, return true, or return false
         * @return boolean
         */
        @Throws(Exception::class)
        open fun is2xx(code: Number?): Boolean {
            if (null == code) {
                return false
            }
            return code.toInt() in 200..299
        }

        /**
         * If the code between 300 and 400, return true, or return false
         * @return boolean
         */
        @Throws(Exception::class)
        open fun is3xx(code: Number?): Boolean {
            if (null == code) {
                return false
            }
            return code.toInt() in 300..399
        }

        /**
         * If the code between 400 and 500, return true, or return false
         * @return boolean
         */
        @Throws(Exception::class)
        open fun is4xx(code: Number?): Boolean {
            if (null == code) {
                return false
            }
            return code.toInt() in 400..499
        }

        /**
         * If the code between 500 and 600, return true, or return false
         * @return boolean
         */
        @Throws(Exception::class)
        open fun is5xx(code: Number?): Boolean {
            if (null == code) {
                return false
            }
            return code.toInt() in 500..599
        }

        /**
         * Validate model
         * @return void
         */
        @Throws(Exception::class)
        open fun validateModel(m: TeaModel): Unit {
            m.validate()
        }

        /**
         * Model transforms to map[string]any
         * @return map[string]any
         */
        @Throws(Exception::class)
        open fun toMap(_in: TeaModel): MutableMap<String, Any> {
            return _in.toMap()
        }
    }
}
