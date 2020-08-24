import unittest
import time
import os

from Tea.model import TeaModel
from alibabacloud_tea_util.client import Client


class TestClient(unittest.TestCase):

    class TestModel(TeaModel):
        def __init__(self):
            self.test_a = 'a'
            self.test_b = 'b'

        def validate(self):
            raise ValueError('test validate')

        def to_map(self):
            return {
                'test_a': self.test_a,
                'test_b': self.test_b
            }

    def test_to_bytes(self):
        result = Client.to_bytes("test")
        self.assertEqual(b'test', result)

    def test_to_string(self):
        self.assertEqual("test", Client.to_string(b'test'))

    def test_parse_json(self):
        json_str = "{\"arrayObj\":[[{\"itemName\":\"item\",\"itemInt\":1},{\"itemName\":\"item2\",\"itemInt\":2}],[{\"itemName\":\"item3\",\"itemInt\":3}]],\"arrayList\":[[[1,2],[3,4]],[[5,6],[7]],[]],\"listStr\":[1,2,3],\"items\":[{\"total_size\":18,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]},{\"total_size\":20,\"partNumber\":2,\"tags\":[{\"aa\":\"22\"}]}],\"next_marker\":\"\",\"test\":{\"total_size\":19,\"partNumber\":1,\"tags\":[{\"aa\":\"11\"}]}}"
        obj = Client.parse_json(json_str)
        self.assertIsNotNone(obj)

    def test_read_as_bytes(self):
        result = None
        module_path = os.path.dirname(__file__)
        filename = module_path + "/test_open.txt"
        with open(filename) as f:
            result = Client.read_as_bytes(f)
        self.assertIsNotNone(result)
        self.assertEqual(b'hello alibabaCloud!', result)
        self.assertEqual(b'test', Client.read_as_bytes(b'test'))
        self.assertEqual(b'testStr', Client.read_as_bytes('testStr'))

    def test_read_as_string(self):
        result = None
        module_path = os.path.dirname(__file__)
        filename = module_path + "/test_open.txt"
        with open(filename) as f:
            result = Client.read_as_string(f)
        self.assertIsNotNone(result)
        self.assertEqual('hello alibabaCloud!', result)
        self.assertEqual('test', Client.read_as_string(b'test'))
        self.assertEqual('testStr', Client.read_as_string('testStr'))

    def test_read_as_json(self):
        self.assertEqual({"key": "value"},
                         Client.read_as_json('{"key":"value"}'))

    def test_get_nonce(self):
        self.assertIsNotNone(Client.get_nonce())

    def test_get_date_utc_string(self):
        self.assertIn('GMT', Client.get_date_utcstring())

    def test_default_string(self):
        self.assertEqual("default", Client.default_string("", "default"))
        self.assertEqual("default", Client.default_string(None, "default"))
        self.assertEqual("str", Client.default_string("str", "default"))

    def test_default_number(self):
        self.assertEqual(100, Client.default_number(None, 100))
        self.assertEqual(100, Client.default_number(0, 100))
        self.assertEqual(1, Client.default_number(1, 100))

    def test_to_form_string(self):
        self.assertEqual("", Client.to_form_string(None))
        self.assertEqual("", Client.to_form_string({}))
        dic = {}
        dic["form"] = "test"
        dic["param"] = "test"
        self.assertEqual("form=test&param=test", Client.to_form_string(dic))

    def test_to_json_string(self):
        self.assertEqual('{"key": "value"}',
                         Client.to_jsonstring({"key": "value"}))

    def test_empty(self):
        self.assertTrue(Client.empty(None))
        self.assertTrue(Client.empty(""))
        self.assertFalse(Client.empty("test"))

    def test_equal_string(self):
        self.assertTrue(Client.equal_string("test", "test"))
        self.assertFalse(Client.equal_string("a", "b"))

    def test_equal_number(self):
        self.assertTrue(Client.equal_number(100, 100))
        self.assertFalse(Client.equal_number(1, 2))

    def test_is_unset(self):
        self.assertTrue(Client.is_unset(None))
        self.assertFalse(Client.is_unset(""))
        self.assertFalse(Client.is_unset("11"))

    def test_stringify_map_value(self):
        self.assertIsNone(Client.stringify_map_value(None))
        self.assertEqual({}, Client.stringify_map_value({}))
        dic = {}
        dic["test"] = 100
        self.assertEqual("100", Client.stringify_map_value(dic)["test"])

    def test_assert_as_map(self):
        dic = {'key': 'value'}
        s = 'test'
        res = Client.assert_as_map(dic)
        self.assertEqual(dic, res)
        try:
            Client.assert_as_map(s)
        except ValueError as e:
            self.assertEqual('test is not a dict', str(e))

    def test_get_user_agent(self):
        self.assertIsNotNone(Client.get_user_agent())
        self.assertIn("test", Client.get_user_agent("test"))

    def test_is_xx(self):
        self.assertFalse(Client.is_2xx(100))
        self.assertTrue(Client.is_2xx(200))
        self.assertFalse(Client.is_2xx(300))

        self.assertFalse(Client.is_3xx(200))
        self.assertTrue(Client.is_3xx(300))
        self.assertFalse(Client.is_3xx(400))

        self.assertFalse(Client.is_4xx(300))
        self.assertTrue(Client.is_4xx(400))
        self.assertFalse(Client.is_4xx(500))

        self.assertFalse(Client.is_5xx(400))
        self.assertTrue(Client.is_5xx(500))
        self.assertFalse(Client.is_5xx(600))

    def test_anyify_map_value(self):
        dic = {}
        dic["key"] = "value"
        self.assertEqual(dic, Client.anyify_map_value(dic))

    def test_assert_as_bytes(self):
        s = 'test'
        b = b'test'
        res = Client.assert_as_bytes(b)
        self.assertEqual(b, res)
        try:
            Client.assert_as_bytes(s)
        except ValueError as e:
            self.assertEqual('test is not a bytes', str(e))

    def test_assert_as_string(self):
        num = 1
        s = 'test'
        res = Client.assert_as_string(s)
        self.assertEqual(s, res)
        try:
            Client.assert_as_string(num)
        except ValueError as e:
            self.assertEqual('1 is not a string', str(e))

    def test_assert_as_number(self):
        s = 'test'
        num = 1
        res = Client.assert_as_number(num)
        self.assertEqual(num, res)
        try:
            Client.assert_as_number(s)
        except ValueError as e:
            self.assertEqual('test is not a integer', str(e))

    def test_assert_as_boolean(self):
        s = 'test'
        boolean = True
        res = Client.assert_as_boolean(boolean)
        self.assertEqual(boolean, res)
        try:
            Client.assert_as_boolean(s)
        except ValueError as e:
            self.assertEqual('test is not a boolean', str(e))

    def test_validate_model(self):
        model = {'t': 'ok'}
        Client.validate_model(model)
        model = self.TestModel()
        try:
            Client.validate_model(model)
        except ValueError as e:
            self.assertEqual('test validate', str(e))

    def test_to_map(self):
        model = {'t': 'ok'}
        dic = Client.to_map(model)
        self.assertEqual(dic, model)

        model = self.TestModel()
        dic = Client.to_map(model)
        self.assertEqual(
            'a',
            dic.get('test_a')
        )

        self.assertEqual(
            'b',
            dic.get('test_b')
        )

    def test_sleep(self):
        t1 = time.time()
        Client.sleep(2000)
        self.assertEqual(2, int(time.time() - t1))
