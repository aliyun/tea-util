import unittest
import time
import os
import asyncio

from Tea.model import TeaModel
from alibabacloud_tea_util.client import Client

base_path = os.path.dirname(__file__)


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
        result = Client.to_bytes(b'test')
        self.assertEqual(b'test', result)
        result = Client.to_bytes(["test"])
        self.assertEqual(b"['test']", result)

    def test_to_string(self):
        self.assertEqual("test", Client.to_string(b'test'))
        self.assertEqual("test", Client.to_string("test"))
        self.assertEqual("['test']", Client.to_string(["test"]))

    def test_parse_json(self):
        json_str = '{"arrayObj":[[{"itemName":"item","itemInt":1},{"itemName":"item2","itemInt":2}],[{"itemName":"item3","itemInt":3}]],"arrayList":[[[1,2],[3,4]],[[5,6],[7]],[]],"listStr":[1,2,3],"items":[{"total_size":18,"partNumber":1,"tags":[{"aa":"11"}]},{"total_size":20,"partNumber":2,"tags":[{"aa":"22"}]}],"next_marker":"","test":{"total_size":19,"partNumber":1,"tags":[{"aa":"11"}]}}'
        obj = Client.parse_json(json_str)
        self.assertIsNotNone(obj)

    def test_read_as_bytes(self):
        self.assertEqual(b'test', Client.read_as_bytes(b'test'))
        self.assertEqual(b'testStr', Client.read_as_bytes('testStr'))

        filename = base_path + "/test_open.txt"
        with open(filename, 'rb') as f:
            result = Client.read_as_bytes(f)
        self.assertIsNotNone(result)
        self.assertEqual(b'hello alibabaCloud!', result)

    def test_read_as_string(self):
        module_path = os.path.dirname(__file__)
        filename = module_path + "/test_open.txt"
        with open(filename, 'rb') as f:
            result = Client.read_as_string(f)
        self.assertIsNotNone(result)
        self.assertEqual('hello alibabaCloud!', result)
        self.assertEqual('test', Client.read_as_string(b'test'))
        self.assertEqual('testStr', Client.read_as_string('testStr'))

    def test_read_as_json(self):
        self.assertEqual({"key": "value"},
                         Client.read_as_json('{"key":"value"}'))
        try:
            Client.read_as_json("{1:'2'}")
            assert False
        except Exception as e:
            self.assertEqual('''Failed to parse the value as json format, Value: "{1:'2'}".''', str(e))

    def test_get_nonce(self):
        self.assertIsNotNone(Client.get_nonce())

    def test_get_date_utc_string(self):
        self.assertIn('GMT', Client.get_date_utcstring())

    def test_default_string(self):
        self.assertEqual("", Client.default_string("", "default"))
        self.assertEqual("default", Client.default_string(None, "default"))
        self.assertEqual("str", Client.default_string("str", "default"))

    def test_default_number(self):
        self.assertEqual(100, Client.default_number(None, 100))
        self.assertEqual(0, Client.default_number(0, 100))
        self.assertEqual(1, Client.default_number(1, 100))

    def test_to_form_string(self):
        self.assertEqual("", Client.to_form_string(None))
        self.assertEqual("", Client.to_form_string({}))
        dic = {}
        dic["form"] = "test"
        dic["param"] = "test"
        self.assertEqual("form=test&param=test", Client.to_form_string(dic))
        with open(os.path.join(base_path, 'test_open.txt'), 'rb') as f:
            dic = {
                'form': 'test',
                'param': 'test',
                'file': f
            }
            self.assertEqual("form=test&param=test", Client.to_form_string(dic))

    def test_to_json_string(self):
        self.assertEqual('test string for to_jsonstring',
                         Client.to_jsonstring('test string for to_jsonstring'))
        self.assertEqual('{"key":"value"}',
                         Client.to_jsonstring({"key": "value"}))
        model = self.TestModel()
        any_dict = {
            'bytes': b'100',
            'str': '100',
            'int': 100,
            'model': model,
            'float': 100.1,
            'bool': True,
            'utf8': '你好'
        }
        self.assertEqual(
            '{"bytes":"100","str":"100","int":100,"model":{"test_a":"a","test_b":"b"},"float":100.1,"bool":true,"utf8":"你好"}',
            Client.to_jsonstring(any_dict)
        )

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
        self.assertEqual({}, Client.stringify_map_value(None))
        self.assertEqual({}, Client.stringify_map_value({}))
        dic = {
            'test': 100,
            'bkey': b'bytes',
            'key': None
        }
        self.assertEqual("100", Client.stringify_map_value(dic)["test"])

    def test_assert_as_map(self):
        dic = {'key': 'value'}
        s = 'test'
        res = Client.assert_as_map(dic)
        self.assertEqual(dic, res)
        try:
            Client.assert_as_map(s)
            assert False
        except ValueError as e:
            self.assertEqual('test is not a dict', str(e))

    def test_get_user_agent(self):
        self.assertIsNotNone(Client.get_user_agent(''))
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
        dic = {
            'key': 'value'
        }
        self.assertEqual(dic, Client.anyify_map_value(dic))

    def test_assert_as_bytes(self):
        s = 'test'
        b = b'test'
        res = Client.assert_as_bytes(b)
        self.assertEqual(b, res)
        try:
            Client.assert_as_bytes(s)
            assert False
        except ValueError as e:
            self.assertEqual('test is not a bytes', str(e))

    def test_assert_as_string(self):
        num = 1
        s = 'test'
        res = Client.assert_as_string(s)
        self.assertEqual(s, res)
        try:
            Client.assert_as_string(num)
            assert False
        except ValueError as e:
            self.assertEqual('1 is not a str', str(e))

    def test_assert_as_number(self):
        s = 'test'
        num = 1
        res = Client.assert_as_number(num)
        self.assertEqual(num, res)
        try:
            Client.assert_as_number(s)
            assert False
        except ValueError as e:
            self.assertEqual('test is not a number', str(e))

    def test_assert_as_integer(self):
        s = 'test'
        num = 1
        res = Client.assert_as_integer(num)
        self.assertEqual(num, res)
        try:
            Client.assert_as_integer(s)
            assert False
        except ValueError as e:
            self.assertEqual('test is not a int number', str(e))

    def test_assert_as_boolean(self):
        s = 'test'
        boolean = True
        res = Client.assert_as_boolean(boolean)
        self.assertEqual(boolean, res)
        try:
            Client.assert_as_boolean(s)
            assert False
        except ValueError as e:
            self.assertEqual('test is not a bool', str(e))

    def test_validate_model(self):
        model = {'t': 'ok'}
        Client.validate_model(model)
        model = self.TestModel()
        try:
            Client.validate_model(model)
            assert False
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

    def test_to_array(self):
        tm = self.TestModel()
        lis = [tm, tm]
        res = Client.to_array(lis)
        self.assertEqual('a', res[0]['test_a'])
        res = Client.to_array(None)
        self.assertEqual([], res)
        lis = ['tm', 'tm']
        res = Client.to_array(lis)
        self.assertEqual(lis, res)

    def test_assert_as_readable(self):
        with open(os.path.join(base_path, 'test_open.txt'), 'rb') as f:
            f = Client.assert_as_readable(f)
            f.read()

        try:
            Client.assert_as_readable(100)
            assert False
        except ValueError as e:
            self.assertEqual('The value is not a readable', str(e))

        Client.assert_as_readable(b'test')
        readable = Client.assert_as_readable('test')
        self.assertEqual(b'test', readable.read())

    def test_read_as_bytes_async(self):
        loop = asyncio.get_event_loop()
        task1 = asyncio.ensure_future(Client.read_as_bytes_async(b'test'))
        loop.run_until_complete(task1)

        task2 = asyncio.ensure_future(Client.read_as_bytes_async('testStr'))
        loop.run_until_complete(task2)
        self.assertEqual(b'test', task1.result())
        self.assertEqual(b'testStr', task2.result())

    def test_read_as_string_async(self):
        loop = asyncio.get_event_loop()
        task1 = asyncio.ensure_future(Client.read_as_string_async(b'test'))
        task2 = asyncio.ensure_future(Client.read_as_string_async('testStr'))
        tasks = [task1, task2]
        loop.run_until_complete(asyncio.wait(tasks))
        self.assertEqual('test', task1.result())
        self.assertEqual('testStr', task2.result())

    def test_read_as_json_async(self):
        loop = asyncio.get_event_loop()
        task1 = asyncio.ensure_future(Client.read_as_json_async(b'{"key": "value"}'))
        task2 = asyncio.ensure_future(Client.read_as_json_async("{1:'2'}"))
        loop.run_until_complete(task1)
        self.assertEqual({"key": "value"}, task1.result())
        try:
            loop.run_until_complete(task2)
            assert False
        except Exception as e:
            self.assertEqual('''Failed to parse the value as json format, Value: "{1:'2'}".''', str(e))

    def test_sleep_async(self):
        loop = asyncio.get_event_loop()

        async def main():
            t1 = time.time()
            await Client.sleep_async(1500)
            self.assertTrue(1 < time.time() - t1 < 2)

        loop.run_until_complete(main())

    def test_assert_as_array(self):
        array = ['str', 'int', 'bool']
        self.assertEqual(array, Client.assert_as_array(array))

        try:
            num = 10
            Client.assert_as_array(num)
            assert False
        except Exception as e:
            self.assertEqual('The value is not a list', str(e))

    def test_get_host_name(self):
        hostname = Client.get_host_name()
        self.assertIsNotNone(hostname)
        # hostname should not be empty in most cases
        if hostname:
            self.assertTrue(len(hostname) > 0)
