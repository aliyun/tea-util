# -*- coding: utf-8 -*-
# This file is auto-generated, don't edit it. Thanks.
from Tea.model import TeaModel


class RuntimeOptions(TeaModel):
    """
    The common runtime options model
    """
    def __init__(self, autoretry=None, ignore_ssl=None, max_attempts=None,
                 backoff_policy=None, backoff_period=None, read_timeout=None, connect_timeout=None, http_proxy=None,
                 https_proxy=None, no_proxy=None, max_idle_conns=None, local_addr=None, socks_5proxy=None, socks_5net_work=None,
                 keep_alive=None, key=None, cert=None, ca=None):
        # whether to try again
        self.autoretry = autoretry  # type: bool
        # ignore SSL validation
        self.ignore_ssl = ignore_ssl  # type: bool
        # privite key for client certificate
        self.key = key  # type: str
        # client certificate
        self.cert = cert  # type: str
        # server certificate
        self.ca = ca  # type: str
        # maximum number of retries
        self.max_attempts = max_attempts  # type: int
        # backoff policy
        self.backoff_policy = backoff_policy  # type: str
        # backoff period
        self.backoff_period = backoff_period  # type: int
        # read timeout
        self.read_timeout = read_timeout  # type: int
        # connect timeout
        self.connect_timeout = connect_timeout  # type: int
        # http proxy url
        self.http_proxy = http_proxy  # type: str
        # https Proxy url
        self.https_proxy = https_proxy  # type: str
        # agent blacklist
        self.no_proxy = no_proxy  # type: str
        # maximum number of connections
        self.max_idle_conns = max_idle_conns  # type: int
        # local addr
        self.local_addr = local_addr  # type: str
        # SOCKS5 proxy
        self.socks_5proxy = socks_5proxy  # type: str
        # SOCKS5 netWork
        self.socks_5net_work = socks_5net_work  # type: str
        # whether to enable keep-alive
        self.keep_alive = keep_alive  # type: bool

    def validate(self):
        pass

    def to_map(self):
        result = dict()
        if self.autoretry is not None:
            result['autoretry'] = self.autoretry
        if self.ignore_ssl is not None:
            result['ignoreSSL'] = self.ignore_ssl
        if self.key is not None:
            result['key'] = self.key
        if self.cert is not None:
            result['cert'] = self.cert
        if self.ca is not None:
            result['ca'] = self.ca
        if self.max_attempts is not None:
            result['max_attempts'] = self.max_attempts
        if self.backoff_policy is not None:
            result['backoff_policy'] = self.backoff_policy
        if self.backoff_period is not None:
            result['backoff_period'] = self.backoff_period
        if self.read_timeout is not None:
            result['readTimeout'] = self.read_timeout
        if self.connect_timeout is not None:
            result['connectTimeout'] = self.connect_timeout
        if self.http_proxy is not None:
            result['httpProxy'] = self.http_proxy
        if self.https_proxy is not None:
            result['httpsProxy'] = self.https_proxy
        if self.no_proxy is not None:
            result['noProxy'] = self.no_proxy
        if self.max_idle_conns is not None:
            result['maxIdleConns'] = self.max_idle_conns
        if self.local_addr is not None:
            result['localAddr'] = self.local_addr
        if self.socks_5proxy is not None:
            result['socks5Proxy'] = self.socks_5proxy
        if self.socks_5net_work is not None:
            result['socks5NetWork'] = self.socks_5net_work
        if self.keep_alive is not None:
            result['keepAlive'] = self.keep_alive
        return result

    def from_map(self, m=None):
        m = m or dict()
        if m.get('autoretry') is not None:
            self.autoretry = m.get('autoretry')
        if m.get('ignoreSSL') is not None:
            self.ignore_ssl = m.get('ignoreSSL')
        if m.get('key') is not None:
            self.key = m.get('key')
        if m.get('cert') is not None:
            self.cert = m.get('cert')
        if m.get('ca') is not None:
            self.ca = m.get('ca')
        if m.get('max_attempts') is not None:
            self.max_attempts = m.get('max_attempts')
        if m.get('backoff_policy') is not None:
            self.backoff_policy = m.get('backoff_policy')
        if m.get('backoff_period') is not None:
            self.backoff_period = m.get('backoff_period')
        if m.get('readTimeout') is not None:
            self.read_timeout = m.get('readTimeout')
        if m.get('connectTimeout') is not None:
            self.connect_timeout = m.get('connectTimeout')
        if m.get('httpProxy') is not None:
            self.http_proxy = m.get('httpProxy')
        if m.get('httpsProxy') is not None:
            self.https_proxy = m.get('httpsProxy')
        if m.get('noProxy') is not None:
            self.no_proxy = m.get('noProxy')
        if m.get('maxIdleConns') is not None:
            self.max_idle_conns = m.get('maxIdleConns')
        if m.get('localAddr') is not None:
            self.local_addr = m.get('localAddr')
        if m.get('socks5Proxy') is not None:
            self.socks_5proxy = m.get('socks5Proxy')
        if m.get('socks5NetWork') is not None:
            self.socks_5net_work = m.get('socks5NetWork')
        if m.get('keepAlive') is not None:
            self.keep_alive = m.get('keepAlive')
        return self
