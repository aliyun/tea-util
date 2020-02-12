<?php

namespace AlibabaCloud\Tea\Utils\Tests\unit;

use AlibabaCloud\Tea\Utils\Common;
use PHPUnit\Framework\TestCase;

final class CommonTest extends TestCase
{
    private $stream;

    public function setUp()
    {
        parent::setUp();
        $this->stream = fopen('http://httpbin.org/get', 'r');
    }

    public function testToBytes()
    {
        $this->assertEquals([
            115, 116, 114, 105, 110, 103,
        ], Common::toBytes('string'));
    }

    public function testToString()
    {
        $this->assertEquals('string', Common::toString([
            115, 116, 114, 105, 110, 103,
        ]));
    }

    public function testParseJSON()
    {
        $this->assertEquals([
            'a' => 'b',
        ], Common::parseJSON('{"a":"b"}'));
    }

    public function testReadAsBytes()
    {
        $bytes = Common::readAsBytes($this->stream);
        $this->assertEquals(123, $bytes[0]);
    }

    public function testReadAsString()
    {
        $string = Common::readAsString($this->stream);
        $this->assertEquals($string[0], '{');
    }

    public function testReadAsJSON()
    {
        $result = Common::readAsJSON($this->stream);
        $this->assertEquals('http://httpbin.org/get', $result['url']);
    }

    public function testGetNonce()
    {
        $nonce1 = Common::getNonce();
        $nonce2 = Common::getNonce();

        $this->assertNotEquals($nonce1, $nonce2);
    }

    public function testGetDateUTCString()
    {
        $gmdate = Common::getDateUTCString();
        $now    = time();
        $this->assertTrue(abs($now - strtotime($gmdate)) <= 1);
    }

    public function testDefaultString()
    {
        $this->assertEquals('', Common::defaultString(null));
        $this->assertEquals('default', Common::defaultString(null, 'default'));
        $this->assertEquals('real', Common::defaultString('real', 'default'));
    }

    public function testDefaultNumber()
    {
        $this->assertEquals(0, Common::defaultNumber(null));
        $this->assertEquals(404, Common::defaultNumber(null, 404));
        $this->assertEquals(200, Common::defaultNumber(200, 404));
    }

    public function testToFormString()
    {
        $query = [
            'foo'            => 'bar',
            'empty'          => '',
            'a'              => null,
            'withWhiteSpace' => 'a b',
        ];
        $this->assertEquals('foo=bar&empty=&withWhiteSpace=a%20b', Common::toFormString($query));
    }

    public function testToJSONString()
    {
        $object = new \stdClass();
        $this->assertJson(Common::toJSONString($object));
    }

    public function testEmpty()
    {
        $this->assertTrue(Common::_empty(''));
        $this->assertFalse(Common::_empty('not empty'));
    }

    public function testEqualString()
    {
        $this->assertTrue(Common::equalString('a', 'a'));
        $this->assertFalse(Common::equalString('a', 'b'));
    }

    public function testEqualNumber()
    {
        $this->assertTrue(Common::equalNumber(1, 1));
        $this->assertFalse(Common::equalNumber(1, 2));
    }

    public function isUnset()
    {
        $this->assertTrue(Common::isUnset($a));
        $b = 1;
        $this->assertFalse(Common::isUnset($b));
    }

    public function testStringifyMapValue()
    {
        $this->assertEquals([
            'foo'    => 'bar',
            'null'   => "",
            'true'   => 'true',
            'false'  => 'false',
            'number' => '1000'
        ], Common::stringifyMapValue([
            'foo'    => 'bar',
            'null'   => null,
            'true'   => true,
            'false'  => false,
            'number' => 1000
        ]));
    }

    public function testAssertAsMap()
    {
        $this->expectException(\InvalidArgumentException::class);
        $this->expectExceptionMessage('It is not a map value.');
        Common::assertAsMap('is not array');

        try {
            $map = ['foo' => 'bar'];
            $this->assertEquals($map, Common::assertAsMap(['foo' => 'bar']));
        } catch (\Exception $e) {
            // should not be here
            $this->assertTrue(false);
        }
    }
}
