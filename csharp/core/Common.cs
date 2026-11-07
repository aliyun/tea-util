﻿using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Web;

using AlibabaCloud.TeaUtil.Utils;

using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Tea;

namespace AlibabaCloud.TeaUtil
{
    public static class Common
    {
        private static readonly string _defaultUserAgent;
        private static readonly long _processStartTime;
        private static long _seqId = 0;

        static Common()
        {
            _defaultUserAgent = GetDefaultUserAgent();
            double ticks = (DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc)).TotalSeconds;
            _processStartTime = (long)(ticks * 1000);
        }

        public static byte[] ToBytes(string val)
        {
            return Encoding.UTF8.GetBytes(val);
        }

        public static string ToString(byte[] val)
        {
            return Encoding.UTF8.GetString(val);
        }

        public static object ParseJSON(string val)
        {
            return JsonConvert.DeserializeObject(val);
        }

        public static string ReadAsString(Stream stream)
        {
            return ToString(ReadAsBytes(stream));
        }

        public async static Task<string> ReadAsStringAsync(Stream stream)
        {
            return ToString(await ReadAsBytesAsync(stream));
        }

        public static object ReadAsJSON(Stream stream)
        {
            object jResult = ParseJSON(ReadAsString(stream));
            object result = ReadJsonUtil.Deserialize(jResult);
            return result;
        }

        public async static Task<object> ReadAsJSONAsync(Stream stream)
        {
            object jResult = ParseJSON(await ReadAsStringAsync(stream));
            object result = ReadJsonUtil.Deserialize(jResult);
            return result;
        }

        public static byte[] ReadAsBytes(Stream stream)
        {
            int bufferLength = 4096;
            using (var ms = new MemoryStream())
            {
                var buffer = new byte[bufferLength];

                while (true)
                {
                    var length = stream.Read(buffer, 0, bufferLength);
                    if (length == 0)
                    {
                        break;
                    }

                    ms.Write(buffer, 0, length);
                }

                ms.Seek(0, SeekOrigin.Begin);
                var bytes = new byte[ms.Length];
                ms.Read(bytes, 0, bytes.Length);

                stream.Close();
                stream.Dispose();

                return bytes;
            }
        }

        public async static Task<byte[]> ReadAsBytesAsync(Stream stream)
        {
            int bufferLength = 4096;
            using (var ms = new MemoryStream())
            {
                var buffer = new byte[bufferLength];

                while (true)
                {
                    var length = await stream.ReadAsync(buffer, 0, bufferLength);
                    if (length == 0)
                    {
                        break;
                    }

                    await ms.WriteAsync(buffer, 0, length);
                }

                ms.Seek(0, SeekOrigin.Begin);
                var bytes = new byte[ms.Length];
                await ms.ReadAsync(bytes, 0, bytes.Length);

                stream.Close();
                stream.Dispose();

                return bytes;
            }
        }

        public static string GetNonce()
        {
            int threadId = Thread.CurrentThread.ManagedThreadId;
            long currentTime = DateTimeOffset.UtcNow.ToUnixTimeMilliseconds();
            long seq = Interlocked.Increment(ref seqId);
            long randNum = new Random().NextInt64();
            string msg = string.Format("{0}-{1}-{2}-{3}", _processStartTime, threadId, currentTime, seq, randNum);
            using (MD5 md5 = MD5.Create())
            {
                byte[] hash = md5.ComputeHash(System.Text.Encoding.UTF8.GetBytes(msg));
                return BitConverter.ToString(hash).Replace("-", "").ToLower();
            }
            //return Guid.NewGuid().ToString();
        }

        public static string GetDateUTCString()
        {
            return DateTime.UtcNow.ToUniversalTime().GetDateTimeFormats('r')[0];
        }

        public static string DefaultString(string reaStr, string defaultStr)
        {
            if (string.IsNullOrWhiteSpace(reaStr))
            {
                return defaultStr;
            }
            return reaStr;
        }

        public static int? DefaultNumber(int? reaNum, int? defaultNum)
        {
            if (reaNum == null || reaNum == 0)
            {
                return defaultNum;
            }
            return reaNum;
        }

        public static string ToFormString(Dictionary<string, object> map)
        {
            if (map == null || map.Count <= 0)
            {
                return "";
            }
            StringBuilder result = new StringBuilder();
            bool first = true;
            foreach (var entry in map)
            {
                if (entry.Value == null)
                {
                    continue;
                }
                if (first)
                {
                    first = false;
                }
                else
                {
                    result.Append("&");
                }
                result.Append(HttpUtility.UrlEncode(entry.Key, Encoding.UTF8));
                result.Append("=");
                result.Append(HttpUtility.UrlEncode(entry.Value.ToSafeString(""), Encoding.UTF8));
            }
            return result.ToString();
        }

        public static string ToJSONString(object value)
        {
            if (value is string)
            {
                return value.ToString();
            }
            return JsonConvert.SerializeObject(value);
        }
        
        /**
         * Transform input as map.
         */
        public static Dictionary<string, object> ParseToMap(object input)
        {
            if (input == null)
            {
                return null;
            }

            Type type = input.GetType();
            var map = (Dictionary<string, object>)TeaModelExtensions.ToMapFactory(type, input);

            return map;
        }
        
        public static object ReadPath(object obj, string path)
        {
            var jsonStr = ToJSONString(ParseToMap(obj));
            var result = JObject.Parse(jsonStr).SelectToken(path);
            return ConvertNumber(result);
        }

        private static object ConvertNumber(object input)
        {
            if (input == null) return null;

            var token = input as JToken;
            if (token != null)
            {
                if (token.Type == JTokenType.Integer)
                {
                    return token.ToObject<long>();
                }
                if (token.Type == JTokenType.Float)
                {
                    return token.ToObject<double>();
                }
                if (token.Type == JTokenType.String)
                {
                    return token.ToString();
                }
                if (token.Type == JTokenType.Array)
                {
                    return HandleList(token.Children());
                }
                if (token.Type == JTokenType.Object)
                {
                    return HandleMap(token.ToObject<Dictionary<string, object>>());
                }
                if (token.Type == JTokenType.Boolean)
                {
                    return token.ToObject<bool>();
                }
            }

            return input; 
        }
        
        private static object HandleList(IEnumerable<JToken> list)
        {
            var convertedList = new List<object>();
            foreach (var item in list)
            {
                convertedList.Add(ConvertNumber(item));
            }
            return convertedList;
        }

        private static object HandleMap(IDictionary<string, object> map)
        {
            var convertedMap = new Dictionary<string, object>();
            foreach (var entry in map)
            {
                convertedMap[entry.Key] = ConvertNumber(entry.Value);
            }
            return convertedMap;
        }

        public static bool Empty(string val)
        {
            return string.IsNullOrEmpty(val);
        }

        public static bool EqualString(string val1, string val2)
        {
            return val1 == val2;
        }

        public static bool EqualNumber(int? val1, int val2)
        {
            return val1 == val2;
        }

        public static bool IsUnset(object obj)
        {
            return obj == null;
        }

        public static Dictionary<string, string> StringifyMapValue(Dictionary<string, object> dict)
        {
            if (dict == null)
            {
                return null;
            }

            Dictionary<string, string> dictStr = new Dictionary<string, string>();
            foreach (var keypair in dict)
            {
                dictStr.Add(keypair.Key, keypair.Value.ToSafeString());
            }

            return dictStr;
        }

        public static Dictionary<string, object> AssertAsMap(object value)
        {
            if (value != null && value is IDictionary)
            {
                var dic = (IDictionary)value;
                var dicObj = dic.Keys.Cast<string>().ToDictionary(key => key, key => dic[key]);
                return dicObj;
            }
            else if (value is JObject)
            {
                return (Dictionary<string, object>)ReadJsonUtil.Deserialize(value);
            }

            throw new ArgumentException("The value is not Dictionary");
        }

        public static byte[] AssertAsBytes(object obj)
        {
            if (obj is byte[])
            {
                return (byte[])obj;
            }

            throw new ArgumentException("The value is not byte[]");
        }

        public static bool AssertAsBoolean(object obj)
        {
            if (obj is bool)
            {
                return (bool)obj;
            }

            throw new ArgumentException("The value is not boolean");
        }

        public static string AssertAsString(object obj)
        {
            if (obj is string)
            {
                return obj.ToString();
            }

            throw new ArgumentException("The value is not string");
        }

        public static int AssertAsNumber(object obj)
        {
            if (obj is int)
            {
                return (int)obj;
            }

            throw new ArgumentException("The value is not number");
        }

        /**
         * Assert a value, if it is a integer, return it, otherwise throws
         * @return the integer value
         */
        public static int? AssertAsInteger(object value)
        {
            if (value is int)
            {
                return (int)value;
            }

            throw new ArgumentException("The value is not int number");
        }

        public static List<object> AssertAsArray(object obj)
        {
            if (obj is IList)
            {
                var list = (IList)obj;
                var result = new List<object>();
                foreach (var item in list)
                {
                    result.Add(item);
                }

                return result;

            }
            throw new ArgumentException("The value is not list");
        }

        public static string GetUserAgent(string userAgent)
        {
            if (!string.IsNullOrEmpty(userAgent))
            {
                return _defaultUserAgent + " " + userAgent;
            }
            return _defaultUserAgent;
        }

        /// <summary>
        /// Is2xx
        /// </summary>
        /// <param name="code"></param>
        /// <returns></returns>
        /// <remarks>If the code between 200 and 300, return true, or return false</remarks>
        public static bool Is2xx(int? code)
        {
            return code >= 200 && code < 300;
        }

        /// <summary>
        /// Is3xx
        /// </summary>
        /// <param name="code"></param>
        /// <returns></returns>
        /// <remarks>If the code between 300 and 400, return true, or return false</remarks>
        public static bool Is3xx(int? code)
        {
            return code >= 300 && code < 400;
        }

        /// <summary>
        /// Is4xx
        /// </summary>
        /// <param name="code"></param>
        /// <returns></returns>
        /// <remarks>If the code between 400 and 500, return true, or return false</remarks>
        public static bool Is4xx(int? code)
        {
            return code >= 400 && code < 500;
        }

        /// <summary>
        /// Is5xx
        /// </summary>
        /// <param name="code"></param>
        /// <returns></returns>
        /// <remarks>If the code between 500 and 600, return true, or return false</remarks>
        public static bool Is5xx(int? code)
        {
            return code >= 500 && code < 600;
        }

        /// <summary>
        /// Anyify the value of map
        /// </summary>
        /// <param name="m"></param>
        /// <returns>return the new anyfied map</returns>
        public static Dictionary<string, object> AnyifyMapValue(Dictionary<string, string> m)
        {
            if (m == null)
            {
                return null;
            }

            Dictionary<string, object> dict = new Dictionary<string, object>();
            foreach (var keypair in m)
            {
                dict.Add(keypair.Key, keypair.Value);
            }
            return dict;
        }

        /// <summary>
        /// Validate model
        /// </summary>
        /// <param name="model"></param>
        public static void ValidateModel(TeaModel model)
        {
            model.Validate();
        }

        /// <summary>
        /// Model transforms to map[string]any
        /// </summary>
        /// <param name="model"></param>
        /// <returns>map[string]any</returns>
        public static Dictionary<string, object> ToMap(TeaModel model)
        {
            return model.ToMap();
        }

        public static void Sleep(int? millisecond)
        {
            if (millisecond != null)
            {
                Thread.Sleep(millisecond.Value);
            }
        }

        public async static Task SleepAsync(int? millisecond)
        {
            if (millisecond != null)
            {
                await Task.Run(() =>
                {
                    Thread.Sleep(millisecond.Value);
                });
            }
        }

        public static List<Dictionary<string, object>> ToArray(object input)
        {
            try
            {
                var listModel = (IList)input;
                var listResult = new List<Dictionary<string, object>>();
                foreach (var model in listModel)
                {
                    if (model != null)
                    {
                        listResult.Add(((TeaModel)model).ToMap());
                    }
                }
                return listResult;
            }
            catch
            {
                return null;
            }
        }

        public static Stream AssertAsReadable(object a)
        {
            if (a is Stream)
            {
                return (Stream)a;
            }

            throw new ArgumentException("The value is not Stream");
        }

        /// <summary>
        /// Get hostname of current machine
        /// </summary>
        /// <returns>the string value</returns>
        public static string GetHostName()
        {
            try
            {
                return System.Net.Dns.GetHostName();
            }
            catch
            {
                return "";
            }
        }

        internal static string GetDefaultUserAgent()
        {
            string OSVersion = Environment.OSVersion.ToString();
            string ClientVersion = GetRuntimeRegexValue(RuntimeEnvironment.GetRuntimeDirectory());
            string CoreVersion = Assembly.GetExecutingAssembly().GetName().Version.ToString();
            return string.Format("AlibabaCloud ({0}) {1} Core/{2} TeaDSL/1", OSVersion, ClientVersion, CoreVersion);
        }

        internal static string GetRuntimeRegexValue(string value)
        {
            var rx = new Regex(@"(\.NET).*(\\|\/).*(\d)", RegexOptions.Compiled | RegexOptions.IgnoreCase);
            var matches = rx.Match(value);
            char[] separator = { '\\', '/' };

            if (matches.Success)
            {
                var clientValueArray = matches.Value.Split(separator);
                return BuildClientVersion(clientValueArray);
            }

            return "RuntimeNotFound";
        }

        internal static string BuildClientVersion(string[] value)
        {
            var finalValue = "";
            for (var i = 0; i < value.Length - 1; ++i)
            {
                finalValue += value[i].Replace(".", "").ToLower();
            }

            finalValue += "/" + value[value.Length - 1];

            return finalValue;
        }
    }
}
