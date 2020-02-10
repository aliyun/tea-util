using System.Collections.Generic;

namespace AlibabaCloud.TeaUtil.Utils
{
    internal static class DictUtils
    {
        internal static object GetDicValue(Dictionary<string, object> dic, string keyName)
        {
            if (dic.ContainsKey(keyName))
            {
                return dic[keyName];
            }
            return null;
        }

        internal static string GetDicValue(Dictionary<string, string> dic, string keyName)
        {
            if (dic != null && dic.ContainsKey(keyName))
            {
                return dic[keyName];
            }
            return null;
        }
    }
}
