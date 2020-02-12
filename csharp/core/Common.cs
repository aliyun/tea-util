using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Web;

using AlibabaCloud.TeaUtil.Utils;

using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AlibabaCloud.TeaUtil
{
    public static class Common
    {
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
            byte[] bytes = new byte[stream.Length];
            stream.Read(bytes, 0, bytes.Length);
            return bytes;
        }

        public async static Task<byte[]> ReadAsBytesAsync(Stream stream)
        {
            byte[] bytes = new byte[stream.Length];
            await stream.ReadAsync(bytes, 0, bytes.Length);
            return bytes;
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
            return JsonConvert.SerializeObject(dict);
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
    }
}
