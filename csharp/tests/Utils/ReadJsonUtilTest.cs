using System.Collections.Generic;

using AlibabaCloud.TeaUtil.Utils;

using Newtonsoft.Json.Linq;

using Xunit;

namespace tests.Utils
{
    public class ReadJsonUtilTest
    {
        [Fact]
        public void TestDeserializeToDic()
        {
            Assert.Null(ReadJsonUtil.DeserializeToDic(null));

            string jsonStr = "{\"arrayObj\":[[{\"itemName\":\"item\",\"itemInt\":1},{\"itemName\":\"item2\",\"itemInt\":2}],[{\"itemName\":\"item3\",\"itemInt\":3}]],\"arrayList\":[[[1,2],[3,4]],[[5,6],[7]],[]],\"listStr\":[1,2,3],\"items\":[{\"total_size\":18,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]},{\"total_size\":20,\"partNumber\":2,\"tags\":[{\"aa\":\"22\"}]}],\"next_marker\":\"\",\"test\":{\"total_size\":19,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]}}";
            JObject jObject = JObject.Parse(jsonStr);
            Dictionary<string, object> dic = (Dictionary<string, object>) ReadJsonUtil.DeserializeToDic(jObject);
            Assert.NotNull(dic);
        }

    }
}
