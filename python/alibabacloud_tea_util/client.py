import json
import uuid
import platform
import socket
import time

from datetime import datetime
from urllib.parse import urlencode

from Tea.model import TeaModel
from Tea.stream import STREAM_CLASS


class Client:
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
        user_agent = ""
        user_agent += "Alibaba Cloud ("
        user_agent += platform.platform()
        user_agent += ") "
        user_agent += " python/"
        user_agent += platform.python_version()
        user_agent += " TeaDSL/1"
        return user_agent

    @staticmethod
    def to_bytes(val):
        """
        Convert a string(utf8) to bytes
        @return the return bytes
        """
        return val.encode(encoding="utf-8")

    @staticmethod
    def to_string(val):
        """
        Convert a bytes to string(utf8)
        @return the return string
        """
        return val.decode('utf-8')

    @staticmethod
    def parse_json(val):
        """
        Parse it by JSON format
        @return the parsed result
        """
        return json.loads(val)

    @staticmethod
    def read_as_bytes(body):
        """
        Read data from a readable stream, and compose it to a bytes
        @param body: the readable stream
        @return the bytes result
        """
        if isinstance(body, STREAM_CLASS):
            bts_array = bytearray()
            for part in Client.__read_part(body, 1024):
                if not isinstance(part, bytes):
                    bts_array.extend(bytes(part, encoding='utf-8'))
                else:
                    bts_array.extend(part)
            return bytes(bts_array)
        elif isinstance(body, bytes):
            return body
        else:
            return bytes(body, encoding='utf-8')

    @staticmethod
    def read_as_string(body):
        """
        Read data from a readable stream, and compose it to a string
        @param body: the readable stream
        @return the string result
        """
        return Client.to_string(Client.read_as_bytes(body))

    @staticmethod
    def read_as_json(body):
        """
        Read data from a readable stream, and parse it by JSON format
        @param body: the readable stream
        @return the parsed result
        """
        return Client.parse_json(Client.read_as_string(body))

    @staticmethod
    def get_nonce():
        """
        Generate a nonce string
        @return the nonce string
        """
        name = socket.gethostname() + str(uuid.uuid1())
        namespace = uuid.NAMESPACE_URL
        return str(uuid.uuid5(namespace, name))

    @staticmethod
    def get_date_utcstring():
        """
        Get an UTC format string by current date, e.g. 'Thu, 06 Feb 2020 07:32:54 GMT'
        @return the UTC format string
        """
        return datetime.utcnow().strftime('%a, %d %b %Y %H:%M:%S GMT')

    @staticmethod
    def default_string(rea_str, default_str):
        """
        If not set the real, use default value
        @return the return string
        """
        return rea_str if rea_str else default_str

    @staticmethod
    def default_number(rea_num, default_num):
        """
        If not set the real, use default value
        @return the return number
        """
        return rea_num if rea_num else default_num

    @staticmethod
    def to_form_string(dic):
        """
        Format a map to form string, like a=a%20b%20c
        @return the form string
        """
        if not dic:
            return ""
        keys = sorted(list(dic))
        dic = [(k, dic[k]) for k in keys]
        return urlencode(dic)

    @staticmethod
    def to_jsonstring(val):
        """
        Stringify a value by JSON format
        @return the JSON format string
        """
        return json.dumps(val)

    @staticmethod
    def empty(val):
        """
        Check the string is empty?
        @return if string is null or zero length, return true
        """
        if val is None or val == "":
            return True
        else:
            return False

    @staticmethod
    def equal_string(val1, val2):
        """
        Check one string equals another one?
        @return if equals, return true
        """
        return val1 == val2

    @staticmethod
    def equal_number(val1, val2):
        """
        Check one number equals another one?
        @return if equals, return true
        """
        return val1 == val2

    @staticmethod
    def is_unset(obj):
        """
        Check one value is unset
        @return if unset, return true
        """
        return obj is None

    @staticmethod
    def stringify_map_value(dic):
        """
        Stringify the value of map
        @return the new stringified map
        """
        if dic is None:
            return

        dic_result = {}
        for k in dic:
            if dic[k] is None:
                value = dic[k]
            else:
                value = str(dic[k])
            dic_result[k] = value
        return dic_result

    @staticmethod
    def assert_as_map(val):
        """
        Assert a value, if it is a map, return it, otherwise throws
        @return the map value
        """
        if not isinstance(val, dict):
            ValueError('{} is not a dict'.format(val))
        return val

    @staticmethod
    def get_user_agent(user_agent=""):
        """
        Get user agent, if it userAgent is not null, splice it with defaultUserAgent and return, otherwise return defaultUserAgent
        @return the string value
        """
        if user_agent:
            return Client.__get_default_agent() + " " + user_agent
        return Client.__get_default_agent()

    @staticmethod
    def is_2xx(code):
        """
        If the code between 200 and 300, return true, or return false
        @return boolean
        """
        return 200 <= code < 300

    @staticmethod
    def is_3xx(code):
        """
        If the code between 300 and 400, return true, or return false
        @return boolean
        """
        return 300 <= code < 400

    @staticmethod
    def is_4xx(code):
        """
        If the code between 400 and 500, return true, or return false
        @return boolean
        """
        return 400 <= code < 500

    @staticmethod
    def is_5xx(code):
        """
        If the code between 500 and 600, return true, or return false
        @return boolean
        """
        return 500 <= code < 600

    @staticmethod
    def anyify_map_value(dic):
        """
        Anyify the value of map
        @return the new anyfied map
        """
        return dic

    @staticmethod
    def validate_model(model):
        """
        Validate model
        @return void
        """
        if isinstance(model, TeaModel):
            model.validate()

    @staticmethod
    def to_map(model):
        """
        Model transforms to map[string]any
        @return map[string]any
        """
        if isinstance(model, TeaModel):
            return model.to_map()
        else:
            return model

    @staticmethod
    def assert_as_bytes(value):
        """
        Assert a value, if it is a bytes, return it, otherwise throws
        @return the bytes value
        """
        if not isinstance(value, bytes):
            raise ValueError('{} is not a bytes'.format(value))
        return value

    @staticmethod
    def assert_as_string(value):
        """
        Assert a value, if it is a string, return it, otherwise throws
        @return the string value
        """
        if not isinstance(value, str):
            raise ValueError('{} is not a string'.format(value))
        return value

    @staticmethod
    def assert_as_boolean(value):
        """
        Assert a value, if it is a boolean, return it, otherwise throws
        @return the boolean value
        """
        if not isinstance(value, bool):
            raise ValueError('{} is not a boolean'.format(value))
        return value

    @staticmethod
    def assert_as_number(value):
        """
        Assert a value, if it is a number, return it, otherwise throws
        @return the number value
        """
        if not isinstance(value, int):
            raise ValueError('{} is not a integer'.format(value))
        return value

    @staticmethod
    def sleep(ms):
        """Suspends the current thread for the specified number of milliseconds."""
        time.sleep(ms/1000)

    @staticmethod
    def to_array(inp):
        """Transform input as array."""
        if inp is None:
            return None

        out = []
        for i in inp:
            if isinstance(i, TeaModel):
                out.append(i.to_map())
            else:
                out.append(i)
        return out
