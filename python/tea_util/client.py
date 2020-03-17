import json
import uuid
import platform

from _io import TextIOWrapper
from datetime import datetime
from urllib.parse import urlencode
from collections import OrderedDict


class Client:

    @staticmethod
    def to_bytes(val):
        return val.encode(encoding="utf-8")

    @staticmethod
    def to_string(val):
        return val.decode()

    @staticmethod
    def parse_json(val):
        return json.loads(val)

    @staticmethod
    def read_as_bytes(body):
        if isinstance(body, TextIOWrapper):
            bts_array = bytearray()
            for part in Client.__readPart(body, 1024):
                if not isinstance(part, bytes):
                    bts_array.extend(bytes(part, encoding='utf-8'))
                else:
                    bts_array.extend(part, encoding='utf-8')
            return bytes(bts_array)
        elif isinstance(body, bytes):
            return body
        else:
            return bytes(body, encoding='utf-8')

    @staticmethod
    def read_as_string(body):
        return Client.to_string(Client.read_as_bytes(body))

    @staticmethod
    def read_as_json(body):
        return Client.parse_json(Client.read_as_string(body))

    @staticmethod
    def get_nonce():
        return uuid.uuid1()

    @staticmethod
    def get_date_utc_string():
        return datetime.utcnow().strftime('%a, %d %b %Y %H:%M:%S GMT')

    @staticmethod
    def default_string(rea_str, default_str):
        return rea_str if rea_str else default_str

    @staticmethod
    def default_number(rea_num, default_num):
        return rea_num if rea_num else default_num

    @staticmethod
    def to_form_string(dic):
        if not dic:
            return ""
        return urlencode(dic)

    @staticmethod
    def to_json_string(val):
        return json.dumps(val)

    @staticmethod
    def empty(val):
        if val is None or val == "":
            return True
        else:
            return False

    @staticmethod
    def equal_string(val1, val2):
        return val1 == val2

    @staticmethod
    def equal_number(val1, val2):
        return val1 == val2

    @staticmethod
    def is_unset(obj):
        return obj is None

    @staticmethod
    def stringify_map_value(dic):
        if dic is None:
            return None
        dic_result = {}
        for k in dic:
            dic_result[k] = str(dic[k])
        return dic_result

    @staticmethod
    def assert_as_map(val):
        if val:
            if isinstance(val, type("string")):
                return json.loads(val)
            else:
                return val
        raise NameError("val")

    @staticmethod
    def get_user_agent(user_agent=""):
        if user_agent:
            return Client.__get_default_agent() + " " + user_agent
        return Client.__get_default_agent()

    @staticmethod
    def is_2xx(code):
        return code >= 200 and code < 300

    @staticmethod
    def is_3xx(code):
        return code >= 300 and code < 400

    @staticmethod
    def is_4xx(code):
        return code >= 400 and code < 500

    @staticmethod
    def is_5xx(code):
        return code >= 500 and code < 600

    @staticmethod
    def anyify_map_value(dic):
        return dic

    @staticmethod
    def __readPart(f, size=1024, encoding="utf-8"):
        while True:
            part = f.read(size)
            if part:
                yield part
            else:
                return None

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
