package com.aliyun.teautil;

import com.aliyun.tea.TeaModel;
import com.aliyun.tea.ValidateException;
import com.aliyun.tea.utils.StringUtils;
import com.google.gson.Gson;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.*;

public class Common {

    private static final String defaultUserAgent;

    static {
        Properties sysProps = System.getProperties();
        defaultUserAgent = String.format("AlibabaCloud (%s; %s) Java/%s %s/%s TeaDSL/1", sysProps.getProperty("os.name"), sysProps
                .getProperty("os.arch"), sysProps.getProperty("java.runtime.version"), "tea-util", JavaProject.teaUtilVersion);
    }

    /**
     * Convert a string(utf8) to bytes
     *
     * @return the return bytes
     */
    public static byte[] toBytes(String str) throws UnsupportedEncodingException {
        return str.getBytes("UTF-8");
    }

    /**
     * Convert a bytes to string(utf8)
     *
     * @return the return string
     */
    public static String toString(byte[] bytes) throws UnsupportedEncodingException {
        return new String(bytes, "UTF-8");
    }

    /**
     * Parse it by JSON format
     *
     * @return the parsed result
     */
    public static Object parseJSON(String json) {
        return new Gson().fromJson(json, Map.class);
    }

    /**
     * Assert a value, if it is a map, return it, otherwise throws
     *
     * @return the map value
     */
    public static Map<String, Object> assertAsMap(Object object) {
        if (null != object && Map.class.isAssignableFrom(object.getClass())) {
            return (Map<String, Object>) object;
        }
        throw new RuntimeException("The value is not a object");
    }

    /**
     * Read data from a readable stream, and compose it to a bytes
     *
     * @param stream the readable stream
     * @return the bytes result
     */
    public static byte[] readAsBytes(InputStream stream) throws IOException {
        if (null == stream) {
            return new byte[]{};
        } else {
            ByteArrayOutputStream os = new ByteArrayOutputStream();
            byte[] buff = new byte[1024];

            while (true) {
                int read = stream.read(buff);
                if (read == -1) {
                    return os.toByteArray();
                }
                os.write(buff, 0, read);
            }
        }
    }

    /**
     * Read data from a readable stream, and compose it to a string
     *
     * @param stream the readable stream
     * @return the string result
     */
    public static String readAsString(InputStream stream) throws IOException {
        return new String(readAsBytes(stream), "UTF-8");
    }

    /**
     * Read data from a readable stream, and parse it by JSON format
     *
     * @param stream the readable stream
     * @return the parsed result
     */
    public static Object readAsJSON(InputStream stream) throws IOException {
        String body = readAsString(stream);
        return parseJSON(body);
    }

    /**
     * Generate a nonce string
     *
     * @return the nonce string
     */
    public static String getNonce() {
        StringBuffer uniqueNonce = new StringBuffer();
        UUID uuid = UUID.randomUUID();
        uniqueNonce.append(uuid.toString());
        uniqueNonce.append(System.currentTimeMillis());
        uniqueNonce.append(Thread.currentThread().getId());
        return uniqueNonce.toString();
    }

    /**
     * Get an UTC format string by current date, e.g. 'Thu, 06 Feb 2020 07:32:54 GMT'
     *
     * @return the UTC format string
     */
    public static String getDateUTCString() {
        SimpleDateFormat df = new SimpleDateFormat("EEE, dd MMM yyyy HH:mm:ss z", Locale.US);
        df.setTimeZone(new SimpleTimeZone(0, "GMT"));
        return df.format(new Date());
    }

    /**
     * If not set the real, use default value
     *
     * @return the return string
     */
    public static String defaultString(String str, String defaultStr) {
        if (!StringUtils.isEmpty(str)) {
            return str;
        }
        return defaultStr;
    }

    /**
     * If not set the real, use default value
     *
     * @return the return string
     */
    public static Number defaultNumber(Number number, Number defaultNumber) {
        if (number != null && number.doubleValue() >= 0) {
            return number;
        }
        return defaultNumber;
    }

    /**
     * Format a map to form string, like a=a%20b%20c
     *
     * @return the form string
     */
    public static String toFormString(Map<String, ?> map) throws UnsupportedEncodingException {
        if (null == map) {
            return "";
        }
        StringBuilder result = new StringBuilder();
        boolean first = true;
        for (Map.Entry<String, ?> entry : map.entrySet()) {
            if (StringUtils.isEmpty(entry.getValue())) {
                continue;
            }
            if (first) {
                first = false;
            } else {
                result.append("&");
            }
            result.append(URLEncoder.encode(entry.getKey(), "UTF-8"));
            result.append("=");
            result.append(URLEncoder.encode(String.valueOf(entry.getValue()), "UTF-8"));
        }
        return result.toString();
    }

    /**
     * If not set the real, use default value
     *
     * @return the return string
     */
    public static String toJSONString(Object object) {
        return new Gson().toJson(object);
    }

    /**
     * Check the string is empty?
     *
     * @return if string is null or zero length, return true
     */
    public static boolean empty(String str) {
        return StringUtils.isEmpty(str);
    }

    /**
     * Check one string equals another one?
     *
     * @return if equals, return true
     */
    public static boolean equalString(String str, String val) {
        if (str == null || val == null) {
            return false;
        }
        return str.equals(val);
    }

    /**
     * Check one number equals another one?
     *
     * @return if equals, return true
     */
    public static boolean equalNumber(Number num, Number val) {
        if (num == null || val == null) {
            return false;
        }
        return num.doubleValue() == val.doubleValue();
    }

    /**
     * Check one value is unset
     *
     * @return if unset, return true
     */
    public static boolean isUnset(Object object) {
        return null == object;
    }

    /**
     * Stringify the value of map
     *
     * @return the new stringified map
     */
    public static Map<String, String> stringifyMapValue(Map<String, ?> map) {
        Map<String, String> result = new HashMap<>();
        if (null == map) {
            return null;
        }
        for (Map.Entry<String, ?> entry : map.entrySet()) {
            result.put(entry.getKey(), String.valueOf(entry.getValue()));
        }
        return result;
    }

    /**
     * Anyify the value of map
     *
     * @return the new anyfied map
     */
    public static Map<String, Object> anyifyMapValue(Map<String, ?> map) {
        Map<String, Object> result = new HashMap<>();
        if (null == map) {
            return null;
        }
        for (Map.Entry<String, ?> entry : map.entrySet()) {
            result.put(entry.getKey(), entry.getValue());
        }
        return result;
    }


    /**
     * Get user agent, if it userAgent is not null, splice it with defaultUserAgent and return, otherwise return defaultUserAgent
     *
     * @return the string value
     */
    public static String getUserAgent(String val) throws Exception {
        if (StringUtils.isEmpty(val)) {
            return defaultUserAgent;
        }
        return defaultUserAgent + " " + val;
    }

    /**
     * If the code between 200 and 300, return true, or return false
     *
     * @return boolean
     */
    public static boolean is2xx(Number code) throws Exception {
        if (null == code) {
            return false;
        }
        return code.intValue() >= 200 && code.intValue() < 300 ? true : false;
    }

    /**
     * If the code between 300 and 400, return true, or return false
     *
     * @return boolean
     */
    public static boolean is3xx(Number code) throws Exception {
        if (null == code) {
            return false;
        }
        return code.intValue() >= 300 && code.intValue() < 400 ? true : false;
    }

    /**
     * If the code between 400 and 500, return true, or return false
     *
     * @return boolean
     */
    public static boolean is4xx(Number code) throws Exception {
        if (null == code) {
            return false;
        }
        return code.intValue() >= 400 && code.intValue() < 500 ? true : false;
    }

    /**
     * If the code between 500 and 600, return true, or return false
     *
     * @return boolean
     */
    public static boolean is5xx(Number code) throws Exception {
        if (null == code) {
            return false;
        }
        return code.intValue() >= 500 && code.intValue() < 600 ? true : false;
    }

    /**
     * Validate model
     *
     * @return void
     */
    public static void validateModel(TeaModel m) throws Exception {
        if (null == m) {
            throw new ValidateException("parameter is not allowed as null");
        }
        m.validate();
    }

    /**
     * Model transforms to map[string]any
     *
     * @return map[string]any
     */
    public static java.util.Map<String, Object> toMap(TeaModel in) throws Exception {
        return TeaModel.toMap(in);
    }
}

