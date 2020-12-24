# -*- coding: utf-8 -*-
import unittest
from alibabacloud_tea_util.models import RuntimeOptions


class TestClient(unittest.TestCase):
    def test_init(self):
        option = RuntimeOptions()
        option.validate()
        self.assertEqual(None, option.autoretry)

        option = RuntimeOptions(
            autoretry=True,
            ignore_ssl=True,
            max_attempts=1,
            backoff_policy="test",
            backoff_period=1,
            read_timeout=1,
            connect_timeout=1,
            http_proxy="test",
            https_proxy="test",
            no_proxy="test",
            max_idle_conns=1,
            local_addr="test",
            socks_5proxy="test",
            socks_5net_work="test"
        )
        self.assertEqual(True, option.autoretry)
        self.assertEqual(True, option.ignore_ssl)
        self.assertEqual(1, option.max_attempts)
        self.assertEqual('test', option.backoff_policy)
        self.assertEqual(1, option.backoff_period)
        self.assertEqual(1, option.read_timeout)
        self.assertEqual(1, option.connect_timeout)
        self.assertEqual('test', option.http_proxy)
        self.assertEqual('test', option.https_proxy)
        self.assertEqual('test', option.no_proxy)
        self.assertEqual(1, option.max_idle_conns)
        self.assertEqual('test', option.local_addr)
        self.assertEqual('test', option.socks_5proxy)
        self.assertEqual('test', option.socks_5net_work)

    def test_to_map(self):
        option = RuntimeOptions(
            autoretry=True,
            ignore_ssl=True,
            max_attempts=1,
            backoff_policy="test",
            backoff_period=1,
            read_timeout=1,
            connect_timeout=1,
            http_proxy="test",
            https_proxy="test",
            no_proxy="test",
            max_idle_conns=1,
            local_addr="test",
            socks_5proxy="test",
            socks_5net_work="test"
        )
        result = option.to_map()
        self.assertEqual(True, result.get('autoretry'))
        self.assertEqual(True, result.get('ignoreSSL'))
        self.assertEqual(1, result.get('max_attempts'))
        self.assertEqual('test', result.get('backoff_policy'))
        self.assertEqual(1, result.get('backoff_period'))
        self.assertEqual(1, result.get('readTimeout'))
        self.assertEqual(1, result.get('connectTimeout'))
        self.assertEqual('test', result.get('httpProxy'))
        self.assertEqual('test', result.get('httpsProxy'))
        self.assertEqual('test', result.get('noProxy'))
        self.assertEqual(1, result.get('maxIdleConns'))
        self.assertEqual('test', result.get('localAddr'))
        self.assertEqual('test', result.get('socks5Proxy'))
        self.assertEqual('test', result.get('socks5NetWork'))

    def test_from_map(self):
        option = RuntimeOptions()
        dic = {
            'autoretry': True,
            'ignoreSSL': True,
            'max_attempts': 1,
            'backoff_policy': 'test',
            'backoff_period': 1,
            'readTimeout': 1,
            'connectTimeout': 1,
            'httpProxy': 'test',
            'httpsProxy': 'test',
            'noProxy': 'test',
            'maxIdleConns': 1,
            'localAddr': 'test',
            'socks5Proxy': 'test',
            'socks5NetWork': 'test'
        }
        option.from_map(dic)
        self.assertEqual(True, option.autoretry)
        self.assertEqual(True, option.ignore_ssl)
        self.assertEqual(1, option.max_attempts)
        self.assertEqual('test', option.backoff_policy)
        self.assertEqual(1, option.backoff_period)
        self.assertEqual(1, option.read_timeout)
        self.assertEqual(1, option.connect_timeout)
        self.assertEqual('test', option.http_proxy)
        self.assertEqual('test', option.https_proxy)
        self.assertEqual('test', option.no_proxy)
        self.assertEqual(1, option.max_idle_conns)
        self.assertEqual('test', option.local_addr)
        self.assertEqual('test', option.socks_5proxy)
        self.assertEqual('test', option.socks_5net_work)
