import json
import uuid
import platform

from _io import TextIOWrapper
from datetime import datetime
from urllib.parse import urlencode


def __read_part(f, size=1024, encoding="utf-8"):
    while True:
        part = f.read(size)
        if part:
            yield part
        else:
            return None


def __get_default_agent():
    user_agent = ""
    user_agent += "Alibaba Cloud ("
    user_agent += platform.platform()
    user_agent += ") "
    user_agent += " python/"
    user_agent += platform.python_version()
    user_agent += " TeaDSL/1"
    return user_agent


def to_bytes(val):
    return val.encode(encoding="utf-8")


def to_string(val):
    return val.decode()


def parse_json(val):
    return json.loads(val)


def read_as_bytes(body):
    if isinstance(body, TextIOWrapper):
        bts_array = bytearray()
        for part in __read_part(body, 1024):
            if not isinstance(part, bytes):
                bts_array.extend(bytes(part, encoding='utf-8'))
            else:
                bts_array.extend(part)
        return bytes(bts_array)
    elif isinstance(body, bytes):
        return body
    else:
        return bytes(body, encoding='utf-8')


def read_as_string(body):
    return to_string(read_as_bytes(body))


def read_as_json(body):
    return parse_json(read_as_string(body))


def get_nonce():
    return uuid.uuid1()


def get_date_utc_string():
    return datetime.utcnow().strftime('%a, %d %b %Y %H:%M:%S GMT')


def default_string(rea_str, default_str):
    return rea_str if rea_str else default_str


def default_number(rea_num, default_num):
    return rea_num if rea_num else default_num


def to_form_string(dic):
    if not dic:
        return ""
    return urlencode(dic)


def to_json_string(val):
    return json.dumps(val)


def empty(val):
    if val is None or val == "":
        return True
    else:
        return False


def equal_string(val1, val2):
    return val1 == val2


def equal_number(val1, val2):
    return val1 == val2


def is_unset(obj):
    return obj is None


def stringify_map_value(dic):
    if dic is None:
        return None
    dic_result = {}
    for k in dic:
        dic_result[k] = str(dic[k])
    return dic_result


def assert_as_map(val):
    if val:
        if isinstance(val, type("string")):
            return json.loads(val)
        else:
            return val
    raise NameError("val")


def get_user_agent(user_agent=""):
    if user_agent:
        return __get_default_agent() + " " + user_agent
    return __get_default_agent()


def is_2xx(code):
    return 200 <= code < 300


def is_3xx(code):
    return 300 <= code < 400


def is_4xx(code):
    return 400 <= code < 500


def is_5xx(code):
    return 500 <= code < 600


def anyify_map_value(dic):
    return dic
