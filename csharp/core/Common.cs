using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Web;

using AlibabaCloud.TeaUtil.Utils;

using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AlibabaCloud.TeaUtil
{
    public static class Common
    {
        private static readonly string _defaultUserAgent;

        static Common()
        {
            _defaultUserAgent = GetDefaultUserAgent();
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
            return ParseJSON(ReadAsString(stream));
        }

        public async static Task<object> ReadAsJSONAsync(Stream stream)
        {
            return ParseJSON(await ReadAsStringAsync(stream));
        }

        public static byte[] ReadAsBytes(Stream stream)
        {
            int bufferLength = 4096;
            using(var ms = new MemoryStream())
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
            using(var ms = new MemoryStream())
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
            return Guid.NewGuid().ToString();
        }

        public static string GetDateUTCString()
        {
            return DateTime.UtcNow.ToUniversalTime().GetDateTimeFormats('r') [0];
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

        public static string ToJSONString(Object value)
        {
            return JsonConvert.SerializeObject(value);
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
            if (value != null && value is JObject)
            {
                return (Dictionary<string, object>) ReadJsonUtil.DeserializeToDic(value);
            }

            throw new ArgumentException("The value is not a object");
        }

        public static string GetUserAgent(string userAgent)
        {
            if (!string.IsNullOrEmpty(userAgent))
            {
                return _defaultUserAgent + " " + userAgent;
            }
            return _defaultUserAgent;
        }

        internal static string GetDefaultUserAgent()
        {
            string defaultUserAgent = string.Empty;
            string OSVersion = Environment.OSVersion.ToString();
            string ClientVersion = GetRuntimeRegexValue(RuntimeEnvironment.GetRuntimeDirectory());
            string CoreVersion = Assembly.GetExecutingAssembly().GetName().Version.ToString();
            defaultUserAgent = "Alibaba Cloud (" + OSVersion + ") ";
            defaultUserAgent += ClientVersion;
            defaultUserAgent += " Core/" + CoreVersion;
            defaultUserAgent += " TeaDSL/1";
            return defaultUserAgent;
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
