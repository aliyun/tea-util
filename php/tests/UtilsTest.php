<?php

namespace AlibabaCloud\Tea\Utils\Tests;

use AlibabaCloud\Tea\Model;
use AlibabaCloud\Tea\Utils\Utils;
use AlibabaCloud\Tea\Utils\Utils\ExtendsParameters;
use AlibabaCloud\Tea\Utils\Utils\RuntimeOptions;
use GuzzleHttp\Psr7\Stream;
use PHPUnit\Framework\TestCase;
use Psr\Http\Message\StreamInterface;

/**
 * @internal
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
        $this->assertEquals([
            115, 116, 114, 105, 110, 103,
        ], Utils::toBytes([
            115, 116, 114, 105, 110, 103,
        ]));
    }

    public function testToString()
    {
        $this->assertEquals('string', Utils::toString([
            115, 116, 114, 105, 110, 103,
        ]));
        $this->assertEquals('string', Utils::toString('string'));
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

    public function testReadSeekableStream()
    {
        $handle = fopen('php://temp', 'r+');
        fwrite($handle, 'string');
        $stream = new Stream($handle);
        $this->assertEquals('string', Utils::readAsString($stream));
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
        $this->assertEquals('', Utils::toFormString(null));

        $object = json_decode(json_encode($query));
        $this->assertEquals('foo=bar&empty=&withWhiteSpace=a%20b', Utils::toFormString($object));
    }

    public function testToJSONString()
    {
        $object = new \stdClass();
        $this->assertJson(Utils::toJSONString($object));
        $this->assertEquals('[]', Utils::toJSONString([]));
        $this->assertEquals('["foo"]', Utils::toJSONString(['foo']));
        $this->assertEquals(
            '{"str":"test","number":1,"bool":false,"null":null,"chinese":"中文","http":"https://aliyun.com:8080/zh/中文.html"}',
            Utils::toJSONString([
                'str'            => 'test',
                'number'         => 1,
                'bool'           => FALSE,
                'null'           => null,
                'chinese'        => '中文',
                'http'           => 'https://aliyun.com:8080/zh/中文.html',
            ])
        );
        $this->assertEquals('1', Utils::toJSONString(1));
        $this->assertEquals('true', Utils::toJSONString(TRUE));
        $this->assertEquals('null', Utils::toJSONString(null));
        $this->assertEquals('plain', Utils::toJSONString('plain'));

        $model        = new RequestTest();
        $model->query = 'foo';
        $encoded      = Utils::toJSONString($model);
        $this->assertTrue(false !== strpos($encoded, 'foo'));
    }

    public function testEmpty()
    {
        $this->assertTrue(Utils::_empty(''));
        $this->assertFalse(Utils::_empty('not empty'));
        $this->assertTrue(Utils::empty_(''));
        $this->assertFalse(Utils::empty_('not empty'));
        $this->assertTrue(Utils::emptyWithSuffix(null));
        $this->assertFalse(Utils::emptyWithSuffix('not empty'));
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

        $object    = new \stdClass();
        $object->a = 1;
        $this->assertEquals([
            'obj' => ['a' => 1],
        ], Utils::stringifyMapValue([
            'obj' => $object,
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
        $this->assertFalse(Utils::assertAsBoolean(false));
        try {
            Utils::assertAsBoolean('true');
            $this->assertTrue(false);
        } catch (\InvalidArgumentException $e) {
            $this->assertEquals('It is not a boolean value.', $e->getMessage());
        }
    }

    public function testAssertAsString()
    {
        $this->assertEquals('123', Utils::assertAsString('123'));
        try {
            Utils::assertAsString(123);
            $this->assertTrue(false);
        } catch (\InvalidArgumentException $e) {
            $this->assertEquals('It is not a string value.', $e->getMessage());
        }
    }

    public function testAssertAsBytes()
    {
        $map = [1, 2, 3];
        $this->assertEquals($map, Utils::assertAsBytes($map));
        $this->assertEquals([], Utils::assertAsBytes([]));
        $this->assertEquals([
            115, 116, 114, 105, 110, 103,
        ], Utils::assertAsBytes(Utils::toBytes('string')));

        $invalid = ['test', ['foo' => 1], ['1'], [256], [-1]];
        foreach ($invalid as $value) {
            try {
                Utils::assertAsBytes($value);
                $this->assertTrue(false);
            } catch (\InvalidArgumentException $e) {
                $this->assertEquals('It is not a bytes value.', $e->getMessage());
            }
        }
    }

    public function testAssertAsNumber()
    {
        $this->assertEquals(123, Utils::assertAsNumber(123));
        $this->assertEquals('1.5', Utils::assertAsNumber('1.5'));
        try {
            Utils::assertAsNumber('is not number');
            $this->assertTrue(false);
        } catch (\InvalidArgumentException $e) {
            $this->assertEquals('It is not a number value.', $e->getMessage());
        }
    }

    public function testAssertAsInteger()
    {
        $this->assertEquals(123, Utils::assertAsInteger(123));
        try {
            Utils::assertAsInteger('is not int');
            $this->assertTrue(false);
        } catch (\InvalidArgumentException $e) {
            $this->assertEquals('It is not a int value.', $e->getMessage());
        }
    }

    public function testAssertAsMap()
    {
        $map = ['foo' => 'bar'];
        $this->assertEquals($map, Utils::assertAsMap($map));
        try {
            Utils::assertAsMap('is not array');
            $this->assertTrue(false);
        } catch (\InvalidArgumentException $e) {
            $this->assertEquals('It is not a map value.', $e->getMessage());
        }
    }

    public function testAssertAsArray()
    {
        $map = ['foo'];
        $this->assertEquals($map, Utils::assertAsArray($map));
        try {
            Utils::assertAsArray('is not array');
            $this->assertTrue(false);
        } catch (\InvalidArgumentException $e) {
            $this->assertEquals('It is not a array value.', $e->getMessage());
        }
    }

    public function testGetUserAgent()
    {
        $default = Utils::getUserAgent();
        $this->assertTrue(false !== strpos($default, 'AlibabaCloud'));
        $this->assertEquals($default, Utils::getUserAgent(''));
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
        $this->assertEquals('x', Utils::toArray('x'));
        $this->assertEquals(['a' => ['b' => 1]], Utils::toArray(['a' => ['b' => 1]]));
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

    public function testRuntimeOptions()
    {
        $opts = new RuntimeOptions([
            "autoretry" => false,
            "ignoreSSL" => false,
            "key" => "key",
            "cert" => "cert",
            "ca" => "ca",
            "maxAttempts" => 3,
            "backoffPolicy" => "backoffPolicy",
            "backoffPeriod" => 10,
            "readTimeout" => 3000,
            "connectTimeout" => 3000,
            "httpProxy" => "httpProxy",
            "httpsProxy" => "httpsProxy",
            "noProxy" => "noProxy",
            "maxIdleConns" => 300,
            "keepAlive" => true,
            "extendsParameters" => new ExtendsParameters([
                "headers" => ['key' => 'value'],
                "queries" => ['key' => 'value'],
            ]),
        ]);
        $this->assertEquals(false, $opts->autoretry);
        $this->assertEquals(false, $opts->ignoreSSL);
        $this->assertEquals("key", $opts->key);
        $this->assertEquals("cert", $opts->cert);
        $this->assertEquals("ca", $opts->ca);
        $this->assertEquals(3, $opts->maxAttempts);
        $this->assertEquals("backoffPolicy", $opts->backoffPolicy);
        $this->assertEquals(10, $opts->backoffPeriod);
        $this->assertEquals(3000, $opts->readTimeout);
        $this->assertEquals(3000, $opts->connectTimeout);
        $this->assertEquals("httpProxy", $opts->httpProxy);
        $this->assertEquals("httpsProxy", $opts->httpsProxy);
        $this->assertEquals("noProxy", $opts->noProxy);
        $this->assertEquals(300, $opts->maxIdleConns);
        $this->assertEquals(true, $opts->keepAlive);
        $this->assertEquals('value', $opts->extendsParameters->headers['key']);
        $this->assertEquals('value', $opts->extendsParameters->queries['key']);
    }

    public function testRuntimeOptionsMap()
    {
        $opts = RuntimeOptions::fromMap([
            'autoretry'          => true,
            'ignoreSSL'          => false,
            'key'                => 'key',
            'cert'               => 'cert',
            'ca'                 => 'ca',
            'max_attempts'       => 3,
            'backoff_policy'     => 'backoffPolicy',
            'backoff_period'     => 10,
            'readTimeout'        => 3000,
            'connectTimeout'     => 3000,
            'httpProxy'          => 'httpProxy',
            'httpsProxy'         => 'httpsProxy',
            'noProxy'            => 'noProxy',
            'maxIdleConns'       => 300,
            'localAddr'          => '127.0.0.1',
            'socks5Proxy'        => 'socks5://127.0.0.1',
            'socks5NetWork'      => 'tcp',
            'keepAlive'          => true,
            'extendsParameters'  => [
                'headers' => ['key' => 'value'],
                'queries' => ['key' => 'value'],
            ],
        ]);
        $opts->validate();
        $map = $opts->toMap();
        $this->assertEquals(true, $map['autoretry']);
        $this->assertEquals(false, $map['ignoreSSL']);
        $this->assertEquals('key', $map['key']);
        $this->assertEquals('cert', $map['cert']);
        $this->assertEquals('ca', $map['ca']);
        $this->assertEquals(3, $map['max_attempts']);
        $this->assertEquals('backoffPolicy', $map['backoff_policy']);
        $this->assertEquals(10, $map['backoff_period']);
        $this->assertEquals(3000, $map['readTimeout']);
        $this->assertEquals(3000, $map['connectTimeout']);
        $this->assertEquals('httpProxy', $map['httpProxy']);
        $this->assertEquals('httpsProxy', $map['httpsProxy']);
        $this->assertEquals('noProxy', $map['noProxy']);
        $this->assertEquals(300, $map['maxIdleConns']);
        $this->assertEquals('127.0.0.1', $map['localAddr']);
        $this->assertEquals('socks5://127.0.0.1', $map['socks5Proxy']);
        $this->assertEquals('tcp', $map['socks5NetWork']);
        $this->assertEquals(true, $map['keepAlive']);
        $this->assertEquals('value', $map['extendsParameters']['headers']['key']);
        $this->assertEquals('value', $map['extendsParameters']['queries']['key']);

        $this->assertEquals([], RuntimeOptions::fromMap([])->toMap());

        $extends = ExtendsParameters::fromMap([
            'headers' => ['a' => 'b'],
            'queries' => ['c' => 'd'],
        ]);
        $extends->validate();
        $this->assertEquals([
            'headers' => ['a' => 'b'],
            'queries' => ['c' => 'd'],
        ], $extends->toMap());
        $this->assertEquals([], ExtendsParameters::fromMap([])->toMap());
    }

    public function testValidateModel()
    {
        $this->assertNull(Utils::validateModel(null));
        $this->assertNull(Utils::validateModel(new RequestTest()));
    }

    public function testToMapBranches()
    {
        $this->assertEquals([], Utils::toMap(null));

        $model                         = new ShrinkGapModel();
        $model->mapParamInQueryShrink  = 'replaced';
        $model->otherShrink            = 'ignored';
        $this->assertEquals([
            'MapParamInQuery' => 'replaced',
        ], Utils::toMap($model));
    }

    public function testGetHostName()
    {
        $hostname = Utils::getHostName();
        $this->assertTrue(is_string($hostname));
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

class ShrinkGapModel extends Model
{
    public $mapParamInQueryShrink;
    public $otherShrink;
    protected $_name = [];

    public function toMap()
    {
        return [
            'MapParamInQuery' => 'keep',
        ];
    }
}
