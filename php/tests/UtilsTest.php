<?php

namespace AlibabaCloud\Tea\Utils\Tests;

use AlibabaCloud\Tea\Model;
use AlibabaCloud\Tea\Utils\Utils;
use GuzzleHttp\Psr7\Stream;
use PHPUnit\Framework\TestCase;
use Psr\Http\Message\StreamInterface;

/**
 * @internal
 * @coversNothing
 */
final class UtilsTest extends TestCase
{
    public function getStream()
    {
        return new Stream(fopen('http://httpbin.org/get', 'r'));
    }

    public function testToBytes()
    {
        $this->assertEquals([
            115, 116, 114, 105, 110, 103,
        ], Utils::toBytes('string'));
    }

    public function testToString()
    {
        $this->assertEquals('string', Utils::toString([
            115, 116, 114, 105, 110, 103,
        ]));
    }

    public function testParseJSON()
    {
        $this->assertEquals([
            'a' => 'b',
        ], Utils::parseJSON('{"a":"b"}'));
    }

    public function testReadAsBytes()
    {
        $bytes = Utils::readAsBytes($this->getStream());
        $this->assertEquals(123, $bytes[0]);
    }

    public function testReadAsString()
    {
        $string = Utils::readAsString($this->getStream());
        $this->assertEquals($string[0], '{');
    }

    public function testReadAsJSON()
    {
        $result = Utils::readAsJSON($this->getStream());
        $this->assertEquals('http://httpbin.org/get', $result['url']);
    }

    public function testGetNonce()
    {
        $nonce1 = Utils::getNonce();
        $nonce2 = Utils::getNonce();

        $this->assertNotEquals($nonce1, $nonce2);
    }

    public function testGetDateUTCString()
    {
        $gmdate = Utils::getDateUTCString();
        $now    = time();
        $this->assertTrue(abs($now - strtotime($gmdate)) <= 1);
    }

    public function testDefaultString()
    {
        $this->assertEquals('', Utils::defaultString(null));
        $this->assertEquals('default', Utils::defaultString(null, 'default'));
        $this->assertEquals('real', Utils::defaultString('real', 'default'));
    }

    public function testDefaultNumber()
    {
        $this->assertEquals(0, Utils::defaultNumber(null));
        $this->assertEquals(0, Utils::defaultNumber(0, 3));
        $this->assertEquals(404, Utils::defaultNumber(null, 404));
        $this->assertEquals(200, Utils::defaultNumber(200, 404));
    }

    public function testToFormString()
    {
        $query = [
            'foo'            => 'bar',
            'empty'          => '',
            'a'              => null,
            'withWhiteSpace' => 'a b',
        ];
        $this->assertEquals('foo=bar&empty=&withWhiteSpace=a%20b', Utils::toFormString($query));

        $object = json_decode(json_encode($query));
        $this->assertEquals('foo=bar&empty=&withWhiteSpace=a%20b', Utils::toFormString($object));
    }

    public function testToJSONString()
    {
        $object = new \stdClass();
        $this->assertJson(Utils::toJSONString($object));
    }

    public function testEmpty()
    {
        $this->assertTrue(Utils::_empty(''));
        $this->assertFalse(Utils::_empty('not empty'));
    }

    public function testEqualString()
    {
        $this->assertTrue(Utils::equalString('a', 'a'));
        $this->assertFalse(Utils::equalString('a', 'b'));
    }

    public function testEqualNumber()
    {
        $this->assertTrue(Utils::equalNumber(1, 1));
        $this->assertFalse(Utils::equalNumber(1, 2));
    }

    public function testIsUnset()
    {
        $this->assertTrue(Utils::isUnset($a));
        $b = 1;
        $this->assertFalse(Utils::isUnset($b));
    }

    public function testStringifyMapValue()
    {
        $this->assertEquals([], Utils::stringifyMapValue(null));
        $this->assertEquals([
            'foo'    => 'bar',
            'null'   => '',
            'true'   => 'true',
            'false'  => 'false',
            'number' => '1000',
        ], Utils::stringifyMapValue([
            'foo'    => 'bar',
            'null'   => null,
            'true'   => true,
            'false'  => false,
            'number' => 1000,
        ]));
    }

    public function testAnyifyMapValue()
    {
        $this->assertEquals([
            'foo'    => 'bar',
            'null'   => null,
            'true'   => true,
            'false'  => false,
            'number' => 1000,
        ], Utils::anyifyMapValue([
            'foo'    => 'bar',
            'null'   => null,
            'true'   => true,
            'false'  => false,
            'number' => 1000,
        ]));
    }

    public function testAssertAsBoolean()
    {
        $this->assertTrue(Utils::assertAsBoolean(true));
        $this->assertFalse(Utils::assertAsBoolean('true'));
    }

    public function testAssertAsString()
    {
        $this->assertTrue(Utils::assertAsString('123'));
        $this->assertFalse(Utils::assertAsString(123));
    }

    public function testAssertAsBytes()
    {
        // failed because $var is not array
        $this->assertFalse(Utils::assertAsBytes('test'));

        // failed because $var is map not array
        $this->assertFalse(Utils::assertAsBytes(['foo' => 1]));

        // failed because item value is not int
        $this->assertFalse(Utils::assertAsBytes(['1']));

        // failed because item value is out off range
        $this->assertFalse(Utils::assertAsBytes([256]));

        // success
        $this->assertTrue(Utils::assertAsBytes([1, 2, 3]));
        $this->assertTrue(Utils::assertAsBytes(Utils::toBytes('string')));
    }

    public function testAssertAsNumber()
    {
        $this->assertTrue(Utils::assertAsNumber(123));
        $this->assertFalse(Utils::assertAsNumber('string'));
    }

    public function testAssertAsMap()
    {
        $this->expectException(\InvalidArgumentException::class);
        $this->expectExceptionMessage('It is not a map value.');
        Utils::assertAsMap('is not array');

        try {
            $map = ['foo' => 'bar'];
            $this->assertEquals($map, Utils::assertAsMap($map));
        } catch (\Exception $e) {
            // should not be here
            $this->assertTrue(false);
        }
    }

    public function testAssertAsArray()
    {
        $this->expectException(\InvalidArgumentException::class);
        $this->expectExceptionMessage('It is not a array value.');
        Utils::assertAsArray('is not array');

        try {
            $map = ['foo'];
            $this->assertEquals($map, Utils::assertAsArray($map));
        } catch (\Exception $e) {
            // should not be here
            $this->assertTrue(false);
        }
    }

    public function testGetUserAgent()
    {
        $this->assertTrue(false !== strpos(Utils::getUserAgent('CustomUserAgent'), 'CustomUserAgent'));
    }

    public function testIs2xx()
    {
        $this->assertTrue(Utils::is2xx(200));
        $this->assertFalse(Utils::is2xx(300));
    }

    public function testIs3xx()
    {
        $this->assertTrue(Utils::is3xx(300));
        $this->assertFalse(Utils::is3xx(400));
    }

    public function testIs4xx()
    {
        $this->assertTrue(Utils::is4xx(400));
        $this->assertFalse(Utils::is4xx(500));
    }

    public function testIs5xx()
    {
        $this->assertTrue(Utils::is5xx(500));
        $this->assertFalse(Utils::is5xx(600));
    }

    public function testToMap()
    {
        $from        = new RequestTest();
        $from->query = new RequestTestQuery([
            'booleanParamInQuery' => true,
            'mapParamInQuery'     => [1, 2, 3],
        ]);
        $this->assertTrue($from->query->booleanParamInQuery);
        $this->assertEquals([1, 2, 3], $from->query->mapParamInQuery);

        $target = new RequestShrinkTest([]);
        $this->convert($from, $target);
        $this->assertEquals([
            'BooleanParamInQuery' => true,
            'MapParamInQuery'     => [1, 2, 3],
        ], $target->query->toMap());

        $target->query->mapParamInQueryShrink = json_encode($from->query->mapParamInQuery);
        $this->assertEquals([
            'BooleanParamInQuery' => true,
            'MapParamInQuery'     => '[1,2,3]',
        ], Utils::toMap($target->query));
    }

    public function testSleep()
    {
        $before = microtime(true) * 1000;
        Utils::sleep(1000);
        $after = microtime(true) * 1000;
        $sub   = $after - $before;
        $this->assertTrue(990 <= $sub && $sub <= 1100);
    }

    public function testToArray()
    {
        $model        = new RequestTest();
        $model->query = 'foo';
        $this->assertEquals([
            ['query' => 'foo'],
        ], Utils::toArray([$model]));

        $subModel        = new RequestTest();
        $subModel->query = 'bar';
        $model->query    = $subModel;
        $this->assertEquals([
            ['query' => ['query' => 'bar']],
        ], Utils::toArray([$model]));
    }

    public function testAssertAsReadable()
    {
        $s0 = Utils::assertAsReadable('string content');
        $this->assertTrue($s0 instanceof Stream);

        $s1 = Utils::assertAsReadable($s0);
        $this->assertEquals($s1, $s0);

        $this->expectException(\InvalidArgumentException::class);
        $this->expectExceptionMessage('It is not a stream value.');
        Utils::assertAsReadable(0);
    }

    private function convert($body, &$content)
    {
        $class = new \ReflectionClass($body);
        foreach ($class->getProperties(\ReflectionProperty::IS_PUBLIC) as $property) {
            $name = $property->getName();
            if (!$property->isStatic()) {
                $value = $property->getValue($body);
                if ($value instanceof StreamInterface) {
                    continue;
                }
                $content->{$name} = $value;
            }
        }
    }
}

/**
 * @internal
 * @coversNothing
 */
class RequestTest extends Model
{
    /**
     * @var RequestTestQuery
     */
    public $query;
}

/**
 * @internal
 * @coversNothing
 */
class RequestShrinkTest extends Model
{
    /**
     * @var RequestTestShrinkQuery
     */
    public $query;
}

class RequestTestQuery extends Model
{
    /**
     * @description test
     *
     * @var bool
     */
    public $booleanParamInQuery;

    /**
     * @description test
     *
     * @var array
     */
    public $mapParamInQuery;
    protected $_name = [
        'booleanParamInQuery' => 'BooleanParamInQuery',
        'mapParamInQuery'     => 'MapParamInQuery',
    ];

    public function toMap()
    {
        $res = [];
        if (null !== $this->booleanParamInQuery) {
            $res['BooleanParamInQuery'] = $this->booleanParamInQuery;
        }
        if (null !== $this->mapParamInQuery) {
            $res['MapParamInQuery'] = $this->mapParamInQuery;
        }

        return $res;
    }
}

class RequestTestShrinkQuery extends Model
{
    /**
     * @description test
     *
     * @var float
     */
    public $booleanParamInQuery;

    /**
     * @description test
     *
     * @var string
     */
    public $mapParamInQueryShrink;
    protected $_name = [
        'booleanParamInQuery'   => 'BooleanParamInQuery',
        'mapParamInQueryShrink' => 'MapParamInQuery',
    ];

    public function toMap()
    {
        $res = [];
        if (null !== $this->booleanParamInQuery) {
            $res['BooleanParamInQuery'] = $this->booleanParamInQuery;
        }
        if (null !== $this->mapParamInQueryShrink) {
            $res['MapParamInQuery'] = $this->mapParamInQueryShrink;
        }

        return $res;
    }
}
