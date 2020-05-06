import unittest
import json
import os

from tea_util import client


class TestClient(unittest.TestCase):

    def test_to_bytes(self):
        result = client.to_bytes("test")
        self.assertEqual(b'test', result)

    def test_to_string(self):
        self.assertEqual("test", client.to_string(b'test'))

    def test_parse_json(self):
        json_str = "{\"arrayObj\":[[{\"itemName\":\"item\",\"itemInt\":1},{\"itemName\":\"item2\",\"itemInt\":2}],[{\"itemName\":\"item3\",\"itemInt\":3}]],\"arrayList\":[[[1,2],[3,4]],[[5,6],[7]],[]],\"listStr\":[1,2,3],\"items\":[{\"total_size\":18,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]},{\"total_size\":20,\"partNumber\":2,\"tags\":[{\"aa\":\"22\"}]}],\"next_marker\":\"\",\"test\":{\"total_size\":19,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]}}"
        obj = client.parse_json(json_str)
        self.assertIsNotNone(obj)

    def test_read_as_bytes(self):
        result = None
        module_path = os.path.dirname(__file__)
        filename = module_path + "/test_open.txt"
        with open(filename) as f:
            result = client.read_as_bytes(f)
        self.assertIsNotNone(result)
        self.assertEqual(b'hello alibabaCloud!', result)
        self.assertEqual(b'test', client.read_as_bytes(b'test'))
        self.assertEqual(b'testStr', client.read_as_bytes('testStr'))

    def test_read_as_string(self):
        result = None
        module_path = os.path.dirname(__file__)
        filename = module_path + "/test_open.txt"
        with open(filename) as f:
            result = client.read_as_string(f)
        self.assertIsNotNone(result)
        self.assertEqual('hello alibabaCloud!', result)
        self.assertEqual('test', client.read_as_string(b'test'))
        self.assertEqual('testStr', client.read_as_string('testStr'))

    def test_read_as_json(self):
        self.assertEqual({"key": "value"},
                         client.read_as_json('{"key":"value"}'))

    def test_get_nonce(self):
        self.assertIsNotNone(client.get_nonce())

    def test_get_date_utc_string(self):
        self.assertIn('GMT', client.get_date_utc_string())

    def test_default_string(self):
        self.assertEqual("default", client.default_string("", "default"))
        self.assertEqual("default", client.default_string(None, "default"))
        self.assertEqual("str", client.default_string("str", "default"))

    def test_default_number(self):
        self.assertEqual(100, client.default_number(None, 100))
        self.assertEqual(100, client.default_number(0, 100))
        self.assertEqual(1, client.default_number(1, 100))

    def test_to_form_string(self):
        self.assertEqual("", client.to_form_string(None))
        self.assertEqual("", client.to_form_string({}))
        dic = {}
        dic["form"] = "test"
        dic["param"] = "test"
        self.assertEqual("form=test&param=test", client.to_form_string(dic))

    def test_to_jsonstring(self):
        self.assertEqual('{"key": "value"}',
                         client.to_jsonstring({"key": "value"}))

    def test_empty(self):
        self.assertTrue(client.empty_(None))
        self.assertTrue(client.empty_(""))
        self.assertFalse(client.empty_("test"))

    def test_equal_string(self):
        self.assertTrue(client.equal_string("test", "test"))
        self.assertFalse(client.equal_string("a", "b"))

    def test_equal_number(self):
        self.assertTrue(client.equal_number(100, 100))
        self.assertFalse(client.equal_number(1, 2))

    def test_is_unset(self):
        self.assertTrue(client.is_unset(None))
        self.assertFalse(client.is_unset(""))
        self.assertFalse(client.is_unset("11"))

    def test_stringify_map_value(self):
        self.assertIsNone(client.stringify_map_value(None))
        self.assertEqual({}, client.stringify_map_value({}))
        dic = {}
        dic["test"] = 100
        self.assertEqual("100", client.stringify_map_value(dic)["test"])

    def test_assert_as_map(self):
        json_str = '{"key":"value"}'
        self.assertEqual({'key': 'value'}, client.assert_as_map(json_str))
        self.assertEqual({'key': 'value'},
                         client.assert_as_map({'key': 'value'}))

    def test_get_user_agent(self):
        self.assertIsNotNone(client.get_user_agent())
        self.assertIn("test", client.get_user_agent("test"))

    def test_is_xx(self):
        self.assertFalse(client.is_2xx(100))
        self.assertTrue(client.is_2xx(200))
        self.assertFalse(client.is_2xx(300))

        self.assertFalse(client.is_3xx(200))
        self.assertTrue(client.is_3xx(300))
        self.assertFalse(client.is_3xx(400))

        self.assertFalse(client.is_4xx(300))
        self.assertTrue(client.is_4xx(400))
        self.assertFalse(client.is_4xx(500))

        self.assertFalse(client.is_5xx(400))
        self.assertTrue(client.is_5xx(500))
        self.assertFalse(client.is_5xx(600))

    def test_anyify_map_value(self):
        dic = {}
        dic["key"] = "value"
        self.assertEqual(dic, client.anyify_map_value(dic))
