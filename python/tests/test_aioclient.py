import unittest
import os
import asyncio

from alibabacloud_tea_util.client import AioClient

base_path = os.path.dirname(__file__)


class TestAioClient(unittest.TestCase):
    def test_read_as_bytes(self):
        loop = asyncio.get_event_loop()
        task1 = asyncio.ensure_future(AioClient.read_as_bytes(b'test'))
        loop.run_until_complete(task1)

        task2 = asyncio.ensure_future(AioClient.read_as_bytes('testStr'))
        loop.run_until_complete(task2)
        self.assertEqual(b'test', task1.result())
        self.assertEqual(b'testStr', task2.result())

    def test_read_as_string(self):
        loop = asyncio.get_event_loop()
        task1 = asyncio.ensure_future(AioClient.read_as_string(b'test'))
        task2 = asyncio.ensure_future(AioClient.read_as_string('testStr'))
        tasks = [task1, task2]
        loop.run_until_complete(asyncio.wait(tasks))
        self.assertEqual('test', task1.result())
        self.assertEqual('testStr', task2.result())

    def test_read_as_json(self):
        loop = asyncio.get_event_loop()
        task1 = asyncio.ensure_future(AioClient.read_as_json(b'{"key": "value"}'))
        task2 = asyncio.ensure_future(AioClient.read_as_json("{1:'2'}"))
        loop.run_until_complete(task1)
        self.assertEqual({"key": "value"}, task1.result())
        try:
            loop.run_until_complete(task2)
        except Exception as e:
            self.assertEqual('''Failed to parse the value as json format, Value: "{1:'2'}".''', str(e))
