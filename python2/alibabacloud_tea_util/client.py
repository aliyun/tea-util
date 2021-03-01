# -*- coding: utf-8 -*-
import Tea
import json
import uuid
import platform
import socket
import time

from io import BytesIO
from datetime import datetime
try:
    from urllib import urlencode
except ImportError:
    from urllib.parse import urlencode

from Tea.converter import TeaConverter
from Tea.model import TeaModel
from Tea.stream import READABLE


class Client(object):
    """
    This is a utility module
    """
    class _ModelEncoder(json.JSONEncoder):
        def default(self, o):
            if isinstance(o, TeaModel):
                return o.to_map()
            elif isinstance(o, bytes):
                return TeaConverter.to_str(o)
            super(Client._ModelEncoder, self).default(o)

    @staticmethod
    def __read_part(f, size=1024):
        while True:
            part = f.read(size)
            if part:
                yield part
            else:
                return

    @staticmethod
    def __get_default_agent():
        return 'AlibabaCloud (%s;%s) Python/%s Core/%s TeaDSL/1' % (
            platform.system(), platform.machine(), platform.python_version(), Tea.__version__
        )

    @staticmethod
    def to_bytes(val):
        """
        Convert a string(utf8) to bytes
        @return: the return bytes
        """
        return TeaConverter.to_bytes(val)

    @staticmethod
    def to_string(val):
        """
        Convert a bytes to string(utf8)
        @return: the return string
        """
        return TeaConverter.to_string(val)

    @staticmethod
    def parse_json(val):
        """
        Parse it by JSON format
        @return: the parsed result
        """
        try:
            return json.loads(val)
        except ValueError:
            raise RuntimeError('Failed to parse the value as json format, Value: "%s".' % TeaConverter.to_str(val))

    @staticmethod
    def read_as_bytes(stream):
        """
        Read data from a readable stream, and compose it to a bytes
        @param stream: the readable stream
        @return: the bytes result
        """
        if isinstance(stream, TeaConverter.basestring):
            return TeaConverter.to_bytes(stream)
        else:
            b = ''
            for part in Client.__read_part(stream, 1024):
                b += part
            return b

    @staticmethod
    def read_as_string(stream):
        """
        Read data from a readable stream, and compose it to a string
        @param stream: the readable stream
        @return: the string result
        """
        buff = Client.read_as_bytes(stream)
        return Client.to_string(buff)

    @staticmethod
    def read_as_json(stream):
        """
        Read data from a readable stream, and parse it by JSON format
        @param stream: the readable stream
        @return: the parsed result
        """
        return Client.parse_json(Client.read_as_string(stream))

    @staticmethod
    def get_nonce():
        """
        Generate a nonce string
        @return: the nonce string
        """
        name = socket.gethostname() + str(uuid.uuid1())
        namespace = uuid.NAMESPACE_URL
        return str(uuid.uuid5(namespace, name))

    @staticmethod
    def get_date_utcstring():
        """
        Get an UTC format string by current date, e.g. 'Thu, 06 Feb 2020 07:32:54 GMT'
        @return: the UTC format string
        """
        return datetime.utcnow().strftime('%a, %d %b %Y %H:%M:%S GMT')

    @staticmethod
    def default_string(real, default):
        """
        If not set the real, use default value
        @return: the return string
        """
        return real if real is not None else default

    @staticmethod
    def default_number(real, default):
        """
        If not set the real, use default value
        @return: the return number
        """
        return real if real is not None else default

    @staticmethod
    def to_form_string(val):
        """
        Format a map to form string, like a=a%20b%20c
        @return: the form string
        """
        if not val:
            return ""
        keys = sorted(list(val))
        dic = [(k, TeaConverter.to_str(val[k])) for k in keys if not isinstance(val[k], READABLE)]
        return urlencode(dic)

    @staticmethod
    def to_jsonstring(val):
        """
        Stringify a value by JSON format
        @return: the JSON format string
        """
        return json.dumps(val, cls=Client._ModelEncoder)

    @staticmethod
    def empty(val):
        """
        Check the string is empty?
        @return: if string is null or zero length, return true
        """
        return not val

    @staticmethod
    def equal_string(val1, val2):
        """
        Check one string equals another one?
        @return: if equals, return true
        """
        return val1 == val2

    @staticmethod
    def equal_number(val1, val2):
        """
        Check one number equals another one?
        @return: if equals, return true
        """
        return val1 == val2

    @staticmethod
    def is_unset(value):
        """
        Check one value is unset
        @return: if unset, return true
        """
        return value is None

    @staticmethod
    def stringify_map_value(m):
        """
        Stringify the value of map
        @return: the new stringified map
        """
        if m is None:
            return {}

        dic_result = {}
        for k, v in m.items():
            if v is not None:
                v = TeaConverter.to_string(v)
            dic_result[k] = v
        return dic_result

    @staticmethod
    def anyify_map_value(m):
        """
        Anyify the value of map
        @return: the new anyfied map
        """
        return m

    @staticmethod
    def assert_as_boolean(value):
        """
        Assert a value, if it is a boolean, return it, otherwise throws
        @return: the boolean value
        """
        if not isinstance(value, bool):
            raise ValueError('%s is not a bool' % TeaConverter.to_str(value))
        return value

    @staticmethod
    def assert_as_string(value):
        """
        Assert a value, if it is a string, return it, otherwise throws
        @return: the string value
        """
        if not isinstance(value, TeaConverter.unicode):
            raise ValueError('%s is not a string' % TeaConverter.to_str(value))
        return value

    @staticmethod
    def assert_as_bytes(value):
        """
        Assert a value, if it is a bytes, return it, otherwise throws
        @return: the bytes value
        """
        if not isinstance(value, bytes):
            raise ValueError('%s is not a bytes' % TeaConverter.to_str(value))
        return value

    @staticmethod
    def assert_as_number(value):
        """
        Assert a value, if it is a number, return it, otherwise throws
        @return: the number value
        """
        if not isinstance(value, TeaConverter.number):
            raise ValueError('%s is not a number' % TeaConverter.to_str(value))
        return value

    @staticmethod
    def assert_as_map(value):
        """
        Assert a value, if it is a map, return it, otherwise throws
        @return: the map value
        """
        if not isinstance(value, dict):
            raise ValueError('%s is not a dict' % TeaConverter.to_str(value))
        return value

    @staticmethod
    def get_user_agent(user_agent):
        """
        Get user agent, if it userAgent is not null, splice it with defaultUserAgent and return, otherwise return defaultUserAgent
        @return: the string value
        """
        if user_agent:
            return '%s %s' % (
                Client.__get_default_agent(), user_agent
            )
        return Client.__get_default_agent()

    @staticmethod
    def is_2xx(code):
        """
        If the code between 200 and 300, return true, or return false
        @return: boolean
        """
        return 200 <= code < 300

    @staticmethod
    def is_3xx(code):
        """
        If the code between 300 and 400, return true, or return false
        @return: boolean
        """
        return 300 <= code < 400

    @staticmethod
    def is_4xx(code):
        """
        If the code between 400 and 500, return true, or return false
        @return: boolean
        """
        return 400 <= code < 500

    @staticmethod
    def is_5xx(code):
        """
        If the code between 500 and 600, return true, or return false
        @return: boolean
        """
        return 500 <= code < 600

    @staticmethod
    def validate_model(m):
        """
        Validate model
        @return: void
        """
        if isinstance(m, TeaModel):
            m.validate()

    @staticmethod
    def to_map(in_):
        """
        Model transforms to map[string]any
        @return: map[string]any
        """
        if isinstance(in_, TeaModel):
            return in_.to_map()
        else:
            return in_

    @staticmethod
    def sleep(millisecond):
        """
        Suspends the current thread for the specified number of milliseconds.
        """
        time.sleep(millisecond / 1000)

    @staticmethod
    def to_array(input):
        """
        Transform input as array.
        """
        if input is None:
            return []

        out = []
        for i in input:
            if isinstance(i, TeaModel):
                out.append(i.to_map())
            else:
                out.append(i)
        return out

    @staticmethod
    def assert_as_readable(value):
        """
        Assert a value, if it is a readable, return it, otherwise throws
        @return: the readable value
        """
        if isinstance(value, TeaConverter.basestring):
            value = BytesIO(TeaConverter.to_bytes(value))
        if not isinstance(value, READABLE):
            raise ValueError('The value is not a readable')
        return value

    @staticmethod
    def assert_as_array(value):
        """
        Assert a value, if it is a array, return it, otherwise throws
        @return the array value
        """
        if not isinstance(value, list):
            raise ValueError('The value is not a list')
        return value
