<?php

namespace AlibabaCloud\Tea\Utils;

class Common
{
    /**
     * Convert a string(utf8) to bytes.
     *
     * @param string $string
     *
     * @return array the return bytes
     */
    public static function toBytes($string)
    {
        $bytes = [];
        for ($i = 0; $i < strlen($string); ++$i) {
            $bytes[] = ord($string[$i]);
        }

        return $bytes;
    }

    /**
     * Convert a bytes to string(utf8).
     *
     * @param array $bytes
     *
     * @return string the return string
     */
    public static function toString($bytes)
    {
        $str = '';
        foreach ($bytes as $ch) {
            $str .= chr($ch);
        }

        return $str;
    }

    /**
     * Parse it by JSON format.
     *
     * @param string $jsonString
     *
     * @return array the parsed result
     */
    public static function parseJSON($jsonString)
    {
        return json_decode($jsonString, true);
    }

    /**
     * Read data from a readable stream, and compose it to a bytes.
     *
     * @param resource $stream the readable stream
     *
     * @return array the bytes result
     */
    public static function readAsBytes($stream)
    {
        $str = self::readAsString($stream);

        return self::toBytes($str);
    }

    /**
     * Read data from a readable stream, and compose it to a string.
     *
     * @param resource the readable stream
     *
     * @return string the string result
     */
    public static function readAsString($stream)
    {
        return stream_get_contents($stream);
    }

    /**
     * Read data from a readable stream, and parse it by JSON format.
     *
     * @param resource the readable stream
     *
     * @return array the parsed result
     */
    public static function readAsJSON($stream)
    {
        return self::parseJSON(self::readAsString($stream));
    }

    /**
     * Generate a nonce string.
     *
     * @return string the nonce string
     */
    public static function getNonce()
    {
        return md5('alibabacloud.tea.utils' . uniqid(md5(microtime(true)), true));
    }

    /**
     * Get an UTC format string by current date, e.g. 'Thu, 06 Feb 2020 07:32:54 GMT'.
     *
     * @return string the UTC format string
     */
    public static function getDateUTCString()
    {
        return gmdate("Y-m-d\TH:i:s\Z");
    }

    /**
     * If not set the real, use default value.
     *
     * @param string $real
     * @param string $default
     *
     * @return string
     */
    public static function defaultString($real, $default = '')
    {
        return null == $real ? $default : $real;
    }

    /**
     * If not set the real, use default value.
     *
     * @param int $real
     * @param int $default
     *
     * @return int the return number
     */
    public static function defaultNumber($real, $default = 0)
    {
        return empty($real) ? $default : $real;
    }

    /**
     * Format a map to form string, like a=a%20b%20c.
     *
     * @param array|object $query
     *
     * @return string the form string
     */
    public static function toFormString($query)
    {
        if (is_object($query)) {
            $query = json_decode(self::toJSONString($query), true);
        }

        return str_replace('+', '%20', http_build_query($query));
    }

    /**
     * If not set the real, use default value.
     *
     * @param object $object
     *
     * @return string the return string
     */
    public static function toJSONString($object)
    {
        return json_encode($object);
    }

    /**
     * Check the string is empty?
     *
     * @param string $val
     *
     * @return bool if string is null or zero length, return true
     */
    public static function _empty($val)
    {
        return empty($val);
    }

    /**
     * Check one string equals another one?
     *
     * @param int $left
     * @param int $right
     *
     * @return bool if equals, return true
     */
    public static function equalString($left, $right)
    {
        return $left === $right;
    }

    /**
     * Check one number equals another one?
     *
     * @param int $left
     * @param int $right
     *
     * @return bool if equals, return true
     */
    public static function equalNumber($left, $right)
    {
        return $left === $right;
    }

    /**
     * Check one value is unset.
     *
     * @param mixed $value
     *
     * @return bool if unset, return true
     */
    public static function isUnset(&$value = null)
    {
        return !isset($value) || is_null($value);
    }

    /**
     * Stringify the value of map.
     *
     * @param array $map
     *
     * @return array the new stringified map
     */
    public static function stringifyMapValue($map)
    {
        foreach ($map as &$node) {
            if (is_numeric($node)) {
                $node = strval($node);
            } elseif (is_null($node)) {
                $node = '';
            } elseif (is_bool($node)) {
                $node = $node === true ? 'true' : 'false';
            } elseif (is_object($node)) {
                $node = json_decode(json_encode($node), true);
            }
        }
        return $map;
    }

    /**
     * Assert a value, if it is a map, return it, otherwise throws.
     *
     * @param $any
     *
     * @return array the map value
     */
    public static function assertAsMap($any)
    {
        if (is_array($any)) {
            return $any;
        }
        throw new \InvalidArgumentException('It is not a map value.');
    }
}
