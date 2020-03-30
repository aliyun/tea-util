using System.Collections.Generic;

using Newtonsoft.Json.Linq;

namespace AlibabaCloud.TeaUtil.Utils
{
    internal static class ReadJsonUtil
    {
        internal static object Deserialize(object obj)
        {
            if (obj == null)
            {
                return null;
            }
            Dictionary<string, object> dic = new Dictionary<string, object>();
            if (obj is JArray)
            {
                return DeserializeJArray((JArray) obj);
            }
            else if (obj is JObject)
            {
                return DeserializeJObject((JObject) obj);
            }
            else
            {
                return obj;
            }
        }

        private static Dictionary<string, object> DeserializeJObject(JObject obj)
        {
            Dictionary<string, object> dic = new Dictionary<string, object>();
            Dictionary<string, object> dicJObj = obj.ToObject<Dictionary<string, object>>();
            foreach (var keypair in dicJObj)
            {
                dic.Add(keypair.Key, Deserialize(keypair.Value));
            }
            return dic;
        }

        private static List<object> DeserializeJArray(JArray obj)
        {
            if (obj.Count == 0)
            {
                return new List<object>();
            }

            if (obj[0].Type == JTokenType.Object)
            {
                List<object> dicList = new List<object>();
                List<Dictionary<string, object>> dicObjList = obj.ToObject<List<Dictionary<string, object>>>();
                foreach (Dictionary<string, object> objItem in dicObjList)
                {
                    Dictionary<string, object> objDict = new Dictionary<string, object>();
                    foreach (var keypair in objItem)
                    {
                        objDict.Add(keypair.Key, Deserialize(keypair.Value));
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
                    dicList.Add(Deserialize((JArray) item));
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
