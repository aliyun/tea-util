using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

using AlibabaCloud.TeaUtil;
using AlibabaCloud.TeaUtil.Utils;

using Newtonsoft.Json.Linq;

using Tea;

using Xunit;

namespace tests
{
    public class CommonTest
    {
        [Fact]
        public void Test_ToBytes()
        {
            byte[] bytes = Common.ToBytes("test");
            Assert.NotNull(bytes);
            Assert.NotEmpty(bytes);
        }

        [Fact]
        public void Test_ToString()
        {
            byte[] bytes = Encoding.UTF8.GetBytes("test");
            Assert.Equal("test", Common.ToString(bytes));
        }

        [Fact]
        public void Test_ParseJSON()
        {
            string jsonStr = "{\"arrayObj\":[[{\"itemName\":\"item\",\"itemInt\":1},{\"itemName\":\"item2\",\"itemInt\":2}],[{\"itemName\":\"item3\",\"itemInt\":3}]],\"arrayList\":[[[1,2],[3,4]],[[5,6],[7]],[]],\"listStr\":[1,2,3],\"items\":[{\"total_size\":18,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]},{\"total_size\":20,\"partNumber\":2,\"tags\":[{\"aa\":\"22\"}]}],\"next_marker\":\"\",\"test\":{\"total_size\":19,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]}}";
            object obj = Common.ParseJSON(jsonStr);
            Assert.NotNull(obj);
        }

        [Fact]
        public void Test_ReadAsString()
        {
            using(MemoryStream stream = new MemoryStream(Encoding.UTF8.GetBytes("test")))
            {
                Assert.Equal("test", Common.ReadAsString(stream));
            }
        }

        [Fact]
        public async void Test_ReadAsStringAsync()
        {
            using(MemoryStream stream = new MemoryStream(Encoding.UTF8.GetBytes("test")))
            {
                Assert.Equal("test", await Common.ReadAsStringAsync(stream));
            }
        }

        [Fact]
        public void Test_ReadAsJSON()
        {
            string jsonStr = "{\"arrayObj\":[[{\"itemName\":\"item\",\"itemInt\":1},{\"itemName\":\"item2\",\"itemInt\":2}],[{\"itemName\":\"item3\",\"itemInt\":3}]],\"arrayList\":[[[1,2],[3,4]],[[5,6],[7]],[]],\"listStr\":[1,2,3],\"items\":[{\"total_size\":18,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]},{\"total_size\":20,\"partNumber\":2,\"tags\":[{\"aa\":\"22\"}]}],\"next_marker\":\"\",\"test\":{\"total_size\":19,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]}}";
            byte[] array = Encoding.UTF8.GetBytes(jsonStr);
            using(MemoryStream stream = new MemoryStream(array))
            {
                Dictionary<string, object> dic = (Dictionary<string, object>) Common.ReadAsJSON(stream);
                Assert.NotNull(dic);
                List<object> listResult = (List<object>) dic["items"];
                Dictionary<string, object> item1 = (Dictionary<string, object>) listResult[0];
                Assert.Equal(18L, item1["total_size"]);
                Assert.Empty((string) dic["next_marker"]);
                Assert.Equal(2, ((List<object>) dic["arrayObj"]).Count);
            }

            jsonStr = "[{\"itemName\":\"item\",\"itemInt\":1},{\"itemName\":\"item2\",\"itemInt\":2}]";
            array = Encoding.UTF8.GetBytes(jsonStr);
            using(MemoryStream stream = new MemoryStream(array))
            {
                List<object> listResult = (List<object>) Common.ReadAsJSON(stream);
                Assert.NotNull(listResult);
                Dictionary<string, object> item1 = (Dictionary<string, object>) listResult[0];
                Assert.Equal("item", item1["itemName"]);
                Assert.Equal(1L, item1["itemInt"]);
            }
        }

        [Fact]
        public async void Test_ReadAsJSONAsync()
        {
            string jsonStr = "{\"arrayObj\":[[{\"itemName\":\"item\",\"itemInt\":1},{\"itemName\":\"item2\",\"itemInt\":2}],[{\"itemName\":\"item3\",\"itemInt\":3}]],\"arrayList\":[[[1,2],[3,4]],[[5,6],[7]],[]],\"listStr\":[1,2,3],\"items\":[{\"total_size\":18,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]},{\"total_size\":20,\"partNumber\":2,\"tags\":[{\"aa\":\"22\"}]}],\"next_marker\":\"\",\"test\":{\"total_size\":19,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]}}";
            byte[] array = Encoding.UTF8.GetBytes(jsonStr);
            using(MemoryStream stream = new MemoryStream(array))
            {
                Dictionary<string, object> dic = (Dictionary<string, object>) await Common.ReadAsJSONAsync(stream);
                Assert.NotNull(dic);
                List<object> listResult = (List<object>) dic["items"];
                Dictionary<string, object> item1 = (Dictionary<string, object>) listResult[0];
                Assert.Equal(18L, item1["total_size"]);
                Assert.Empty((string) dic["next_marker"]);
                Assert.Equal(2, ((List<object>) dic["arrayObj"]).Count);
            }

            jsonStr = "[{\"itemName\":\"item\",\"itemInt\":1},{\"itemName\":\"item2\",\"itemInt\":2}]";
            array = Encoding.UTF8.GetBytes(jsonStr);
            using(MemoryStream stream = new MemoryStream(array))
            {
                List<object> listResult = (List<object>) await Common.ReadAsJSONAsync(stream);
                Assert.NotNull(listResult);
                Dictionary<string, object> item1 = (Dictionary<string, object>) listResult[0];
                Assert.Equal("item", item1["itemName"]);
                Assert.Equal(1L, item1["itemInt"]);
            }
        }

        [Fact]
        public void Test_ReadAsBytes()
        {
            using(MemoryStream stream = new MemoryStream(Encoding.UTF8.GetBytes("test")))
            {
                Assert.NotNull(Common.ReadAsBytes(stream));
            }
        }

        [Fact]
        public async void Test_ReadAsBytesAsync()
        {
            using(MemoryStream stream = new MemoryStream(Encoding.UTF8.GetBytes("test")))
            {
                Assert.NotNull(await Common.ReadAsBytesAsync(stream));
            }
        }

        [Fact]
        public void Test_GetNonce()
        {
            Assert.NotNull(Common.GetNonce());
        }

        [Fact]
        public void Test_GetDateUTCString()
        {
            string GMTStr = Common.GetDateUTCString();
            Assert.NotNull(GMTStr);
            Assert.Contains("GMT", GMTStr);
        }

        [Fact]
        public void Test_DefaultString()
        {
            Assert.Equal("default", Common.DefaultString("", "default"));

            Assert.Equal("input", Common.DefaultString("input", "default"));
        }

        [Fact]
        public void Test_DefaultNumber()
        {
            Assert.Equal(100, Common.DefaultNumber(null, 100));

            Assert.Equal(100, Common.DefaultNumber(0, 100));

            Assert.Equal(1, Common.DefaultNumber(1, 100));
        }

        [Fact]
        public void Test_ToFormString()
        {
            Assert.Empty(Common.ToFormString(null));
            Assert.Empty(Common.ToFormString(new Dictionary<string, object>()));

            Dictionary<string, object> dict = new Dictionary<string, object>();
            dict.Add("form", "test");
            dict.Add("param", "test");
            Assert.Equal("form=test&param=test", Common.ToFormString(dict));
        }

        [Fact]
        public void Test_ToJSONString()
        {
            Dictionary<string, object> dict = new Dictionary<string, object>
            { { "key", "value" }
            };
            string jsonStr = Common.ToJSONString(dict);
            Assert.NotNull(jsonStr);
            Assert.NotEmpty(jsonStr);
        }

        [Fact]
        public void Test_Empty()
        {
            Assert.True(Common.Empty(null));

            Assert.False(Common.Empty("test"));

            Assert.True(Common.Empty(string.Empty));
        }

        [Fact]
        public void Test_EqualString()
        {
            Assert.True(Common.EqualString("test", "test"));

            Assert.False(Common.EqualString("a", "b"));
        }

        [Fact]
        public void Test_EqualNumber()
        {
            Assert.True(Common.EqualNumber(1, 1));

            Assert.False(Common.EqualNumber(1, 2));
        }

        [Fact]
        public void Test_IsUnset()
        {
            Assert.True(Common.IsUnset(null));

            Assert.False(Common.IsUnset("test"));
        }

        [Fact]
        public void Test_StringifyMapValue()
        {
            Assert.Equal(new Dictionary<string, string>(), Common.StringifyMapValue(new Dictionary<string, object>()));
            Assert.Equal("100", Common.StringifyMapValue(new Dictionary<string, object> { { "number", 100 } }) ["number"]);
            Assert.Null(Common.StringifyMapValue(null));
        }

        [Fact]
        public void Test_AssertAsMap()
        {
            Assert.Throws<ArgumentException>(() => { Common.AssertAsMap(null); });
            string jsonStr = "{\"arrayObj\":[[{\"itemName\":\"item\",\"itemInt\":1},{\"itemName\":\"item2\",\"itemInt\":2}],[{\"itemName\":\"item3\",\"itemInt\":3}]],\"arrayList\":[[[1,2],[3,4]],[[5,6],[7]],[]],\"listStr\":[1,2,3],\"items\":[{\"total_size\":18,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]},{\"total_size\":20,\"partNumber\":2,\"tags\":[{\"aa\":\"22\"}]}],\"next_marker\":\"\",\"test\":{\"total_size\":19,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]}}";
            JObject obj = JObject.Parse(jsonStr);
            
            Dictionary<string, object> dict = Common.AssertAsMap(obj);
            Assert.NotNull(dict);
            Assert.Equal(6, dict.Count);

            object map = ReadJsonUtil.Deserialize(obj);
            dict = Common.AssertAsMap(map);
            Assert.NotNull(dict);
            Assert.Equal(6, dict.Count);

            Assert.Throws<ArgumentException>(() => Common.AssertAsMap("string"));
        }

        [Fact]
        public void Test_AssertAsString()
        {
            Assert.Equal("ok", Common.AssertAsString("ok"));

            Assert.Throws<ArgumentException>(() => { Common.AssertAsString(10); });
        }

        [Fact]
        public void Test_AssertAsBytes()
        {
            Assert.Equal(Encoding.UTF8.GetBytes("ok"), Common.AssertAsBytes(Encoding.UTF8.GetBytes("ok")));

            Assert.Throws<ArgumentException>(() => { Common.AssertAsBytes(10); });
        }

        [Fact]
        public void Test_AssertAsNumber()
        {
            Assert.Equal(10, Common.AssertAsNumber(10));

            Assert.Throws<ArgumentException>(() => { Common.AssertAsNumber("ok"); });
        }

        [Fact]
        public void Test_AssertAsBoolean()
        {
            Assert.True(Common.AssertAsBoolean(true));

            Assert.Throws<ArgumentException>(() => { Common.AssertAsBoolean("ok"); });
        }

        [Fact]
        public void Test_GetUserAgent()
        {
            Assert.NotNull(Common.GetUserAgent(null));

            Assert.Contains("test", Common.GetUserAgent("test"));
        }

        [Fact]
        public void Test_CodeIsXX()
        {
            Assert.False(Common.Is2xx(100));
            Assert.True(Common.Is2xx(200));
            Assert.False(Common.Is2xx(300));

            Assert.False(Common.Is3xx(100));
            Assert.True(Common.Is3xx(300));
            Assert.False(Common.Is3xx(400));

            Assert.False(Common.Is4xx(100));
            Assert.True(Common.Is4xx(400));
            Assert.False(Common.Is4xx(500));

            Assert.False(Common.Is5xx(100));
            Assert.True(Common.Is5xx(500));
            Assert.False(Common.Is5xx(600));
        }

        [Fact]
        public void Test_AnyifyMapValue()
        {
            Assert.Equal(new Dictionary<string, object>(), Common.AnyifyMapValue(new Dictionary<string, string>()));
            Assert.Equal("100", Common.AnyifyMapValue(new Dictionary<string, string> { { "number", "100" } }) ["number"]);
            Assert.Null(Common.StringifyMapValue(null));
        }

        [Fact]
        public void Test_ToMap()
        {
            TestRegModel model = new TestRegModel();
            model.RequestId = "requestID";
            model.Items = new List<TestRegSubModel> { new TestRegSubModel { RequestId = "sub" }, null };
            model.NextMarker = "next";
            model.testNoAttr = "noAttr";
            model.subModel = new TestRegSubModel();
            model.testListStr = new List<string> { "str" };
            Dictionary<string, object> dic = model.ToMap();
            Assert.NotNull(dic);
            Assert.IsType<List<Dictionary<string, object>>>(dic["items"]);

            TestRegModel modelEmpty = new TestRegModel();
            modelEmpty.RequestId = "1";
            Dictionary<string, object> dicEmpty = modelEmpty.ToMap();
            Assert.Null(dicEmpty["items"]);
            Assert.Null(dicEmpty["subModel"]);
        }

        [Fact]
        public void Test_ValidateModel()
        {
            TeaModel modelNull = null;
            Assert.Throws<ArgumentException>(() => { modelNull.Validate(); });

            TestRegModel successModel = new TestRegModel();
            successModel.RequestId = "reTest";
            successModel.NextMarker = "nextMarker";
            successModel.testListStr = new List<string> { "listStr1" };
            successModel.Items = new List<TestRegSubModel> { new TestRegSubModel { RequestId = "rTest" } };
            successModel.subModel = new TestRegSubModel { RequestId = "rTest", testInt = 10 };
            successModel.Validate();

            successModel.testListStr = null;
            successModel.Validate();

            TestRegModel modelRequired = new TestRegModel();
            Assert.Equal("RequestId is required.",
                Assert.Throws<ArgumentException>(() => { modelRequired.Validate(); }).Message
            );

            modelRequired.RequestId = "reTest";
            modelRequired.NextMarker = "nextMarker";
            Assert.Equal("Items is required.",
                Assert.Throws<ArgumentException>(() => { modelRequired.Validate(); }).Message
            );

            TestRegModel modelReg = new TestRegModel();
            modelReg.RequestId = "123";
            modelReg.Items = new List<TestRegSubModel> { new TestRegSubModel { RequestId = "rTest" } };
            modelReg.NextMarker = "nextMarker";
            Assert.Equal("RequestId is not match re",
                Assert.Throws<ArgumentException>(() => { modelReg.Validate(); }).Message
            );

            modelReg.RequestId = "reTest";
            modelReg.testListStr = new List<string> { "test" };
            Assert.Equal("testListStr is not match listStr",
                Assert.Throws<ArgumentException>(() => { modelReg.Validate(); }).Message
            );
        }
    }

    public class TestRegModel : TeaModel
    {
        [NameInMap("requestId")]
        [Validation(Pattern = "re", MaxLength = 0, Required = true)]
        public string RequestId { get; set; }

        [NameInMap("items")]
        [Validation(Required = true)]
        public List<TestRegSubModel> Items { get; set; }

        [NameInMap("next_marker")]
        [Validation(Pattern = "next", MaxLength = 0, Required = true)]
        public string NextMarker { get; set; }

        public string testNoAttr { get; set; }

        [NameInMap("testListStr")]
        [Validation(Pattern = "listStr", MaxLength = 0)]
        public List<string> testListStr { get; set; }

        public TestRegSubModel subModel { get; set; }

        public Dictionary<string, object> dict { get; set; }

        public int? testInt32 { get; set; }

        public long? testLong { get; set; }

        public float? testFloat { get; set; }

        public double? testDouble { get; set; }

        public bool? testBool { get; set; }

        public short? testShort { get; set; }

        public ushort? testUShort { get; set; }

        public uint? testUInt { get; set; }

        public ulong? testULong { get; set; }

        public string testNull { get; set; }

    }

    public class TestRegSubModel : TeaModel
    {
        [NameInMap("requestId")]
        [Validation(Pattern = "r", MaxLength = 0, Required = true)]
        public string RequestId { get; set; }

        public int? testInt { get; set; }
    }
}
