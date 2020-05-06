from Tea.model import TeaModel


class RuntimeOptions(TeaModel):
    def __init__(self, autoretry=None, ignore_ssl=None, max_attempts=None, backoff_policy=None, backoff_period=None, read_timeout=None, connect_timeout=None, local_addr=None, http_proxy=None, https_proxy=None, no_proxy=None, max_idle_conns=None, socks5_proxy=None, socks5_net_work=None):
        self.autoretry = autoretry
        self.ignore_ssl = ignore_ssl
        self.max_attempts = max_attempts
        self.backoff_policy = backoff_policy
        self.backoff_period = backoff_period
        self.read_timeout = read_timeout
        self.connect_timeout = connect_timeout
        self.local_addr = local_addr
        self.http_proxy = http_proxy
        self.https_proxy = https_proxy
        self.no_proxy = no_proxy
        self.max_idle_conns = max_idle_conns
        self.socks5_proxy = socks5_proxy
        self.socks5_net_work = socks5_net_work

    def validate(self):
        pass
