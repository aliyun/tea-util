using System.Collections.Generic;

using Newtonsoft.Json.Linq;

namespace AlibabaCloud.TeaUtil.Utils
{
    internal static class ReadJsonUtil
    {
        internal static object DeserializeToDic(object obj)
        {
            if (obj == null)
            {
                return null;
            }
            Dictionary<string, object> dic = new Dictionary<string, object>();
            if (obj is JArray)
            {
                return JArrayToDictionary((JArray) obj);
            }
            else if (obj is JObject)
            {
                return JObjToDictionary((JObject) obj);
            }
            else
            {
                return obj;
            }
        }

        private static Dictionary<string, object> JObjToDictionary(JObject obj)
        {
            Dictionary<string, object> dic = new Dictionary<string, object>();
            Dictionary<string, object> dicJObj = obj.ToObject<Dictionary<string, object>>();
            foreach (var keypair in dicJObj)
            {
                dic.Add(keypair.Key, DeserializeToDic(keypair.Value));
            }
            return dic;
        }

        private static object JArrayToDictionary(JArray obj)
        {
            if (obj.Count == 0)
            {
                return new List<object>();
            }

            if (obj[0].Type == JTokenType.Object)
            {
                List<Dictionary<string, object>> dicList = new List<Dictionary<string, object>>();
                List<Dictionary<string, object>> dicObjList = obj.ToObject<List<Dictionary<string, object>>>();
                foreach (Dictionary<string, object> objItem in dicObjList)
                {
                    Dictionary<string, object> objDict = new Dictionary<string, object>();
                    foreach (var keypair in objItem)
                    {
                        objDict.Add(keypair.Key, DeserializeToDic(keypair.Value));
                    }
                    dicList.Add(objDict);
                }
                return dicList;
            }
            else if (obj[0].Type == JTokenType.Array)
            {
                List<object> dicObjList = obj.ToObject<List<object>>();
                List<object> dicList = new List<object>();
                foreach (var item in dicObjList)
                {
                    dicList.Add(DeserializeToDic((JArray) item));
                }

                return dicList;
            }
            else
            {
                List<object> dicObjList = obj.ToObject<List<object>>();
                return dicObjList;
            }
        }
    }
}
