# This file is auto-generated, don't edit it. Thanks.
from Tea.model import TeaModel

"""
The common runtime options model
"""


class RuntimeOptions(TeaModel):
    def __init__(self, autoretry=False, ignore_ssl=False, max_attempts=0, backoff_policy="", backoff_period=0, read_timeout=0, connect_timeout=0, http_proxy="", https_proxy="", no_proxy="", max_idle_conns=0, local_addr="", socks_5proxy="", socks_5net_work=""):
        self.autoretry = autoretry
        self.ignore_ssl = ignore_ssl
        self.max_attempts = max_attempts
        self.backoff_policy = backoff_policy
        self.backoff_period = backoff_period
        self.read_timeout = read_timeout
        self.connect_timeout = connect_timeout
        self.http_proxy = http_proxy
        self.https_proxy = https_proxy
        self.no_proxy = no_proxy
        self.max_idle_conns = max_idle_conns
        self.local_addr = local_addr
        self.socks_5proxy = socks_5proxy
        self.socks_5net_work = socks_5net_work

    def validate(self):
        pass

    def to_map(self):
        result = {}
        result['autoretry'] = self.autoretry
        result['ignoreSSL'] = self.ignoreSSL
        result['max_attempts'] = self.maxAttempts
        result['backoff_policy'] = self.backoffPolicy
        result['backoff_period'] = self.backoffPeriod
        result['readTimeout'] = self.readTimeout
        result['connectTimeout'] = self.connectTimeout
        result['httpProxy'] = self.httpProxy
        result['httpsProxy'] = self.httpsProxy
        result['noProxy'] = self.noProxy
        result['maxIdleConns'] = self.maxIdleConns
        result['localAddr'] = self.localAddr
        result['socks5Proxy'] = self.socks5Proxy
        result['socks5NetWork'] = self.socks5NetWork
        return result

    def from_map(self, map={}):
        self.autoretry = map.get('autoretry')
        self.ignore_ssl = map.get('ignoreSSL')
        self.max_attempts = map.get('max_attempts')
        self.backoff_policy = map.get('backoff_policy')
        self.backoff_period = map.get('backoff_period')
        self.read_timeout = map.get('readTimeout')
        self.connect_timeout = map.get('connectTimeout')
        self.http_proxy = map.get('httpProxy')
        self.https_proxy = map.get('httpsProxy')
        self.no_proxy = map.get('noProxy')
        self.max_idle_conns = map.get('maxIdleConns')
        self.local_addr = map.get('localAddr')
        self.socks_5proxy = map.get('socks5Proxy')
        self.socks_5net_work = map.get('socks5NetWork')
        return self

