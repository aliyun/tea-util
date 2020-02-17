import Client, { RuntimeOptions } from '../src/client';

import { Readable } from 'stream';
import * as $tea from '@alicloud/tea-typescript';
import assert from 'assert';
import 'mocha';

class MyReadable extends Readable {
    value: Buffer

    constructor(value: Buffer) {
        super();
        this.value = value;
    }

    _read() {
        this.push(this.value);
        this.push(null);
    }
}

describe('Tea Util', function() {
    it('Module should ok', function() {
        assert.ok(Client);
    });

    it('defaultNumber should ok', function () {
        assert.deepStrictEqual(Client.defaultNumber(10, 2), 10);
        assert.deepStrictEqual(Client.defaultNumber(undefined, 2), 2);
    });

    it('toJSONString should ok', function () {
        assert.deepStrictEqual(Client.toJSONString({}), '{}');
    });

    it('defaultString should ok', function () {
        assert.deepStrictEqual(Client.defaultString('', 'default'), 'default');
        assert.deepStrictEqual(Client.defaultString('input', 'default'), 'input');
    });

    it('toFormString should ok', function () {
        assert.deepStrictEqual(Client.toFormString({}), '');
        assert.deepStrictEqual(Client.toFormString({a: 'b c d'}), 'a=b%20c%20d');
    });

    it('toBytes', function () {
        assert.deepStrictEqual(Client.toBytes('Hello world!'), Buffer.from('Hello world!'));
    });

    it('equalString', function() {
        assert.deepStrictEqual(Client.equalString('100', '120'), false);
        assert.deepStrictEqual(Client.equalString('100', '100'), true);
    });

    it('equalNumber', function() {
        assert.deepStrictEqual(Client.equalNumber(100, 120), false);
        assert.deepStrictEqual(Client.equalNumber(100, 100), true);
    });

    it('readAsJSON', async function () {
        const readable = new MyReadable(Buffer.from(JSON.stringify({'a': 'b'})));
        const result = await Client.readAsJSON(readable);
        assert.deepStrictEqual(result, {'a': 'b'});
    });

    it('readAsBytes', async function () {
        const readable = new MyReadable(Buffer.from(JSON.stringify({'a': 'b'})));
        const result = await Client.readAsBytes(readable);
        assert.deepStrictEqual(result, Buffer.from('{"a":"b"}'));
    });

    it('readAsString', async function () {
        const readable = new MyReadable(Buffer.from(JSON.stringify({'a': 'b'})));
        const result = await Client.readAsString(readable);
        assert.deepStrictEqual(result, '{"a":"b"}');
    });

    it('getDateUTCString', function () {
        let regexp = /[A-Z][a-z]{2}, \d{2} Feb \d{4} \d{2}:\d{2}:\d{2} GMT/;
        assert.ok(regexp.test(Client.getDateUTCString()));
    });

    it('empty', function () {
        assert.deepStrictEqual(Client.empty(''), true);
    });

    it('isUnset', function () {
        assert.deepStrictEqual(Client.isUnset(null), true);
        assert.deepStrictEqual(Client.isUnset(undefined), true);
        assert.deepStrictEqual(Client.isUnset(false), false);
        assert.deepStrictEqual(Client.isUnset({}), false);
    });

    it('getNonce', function () {
        const nonce0 = Client.getNonce();
        const nonce1 = Client.getNonce();
        const nonce2 = Client.getNonce();
        const nonce3 = Client.getNonce();
        const nonce4 = Client.getNonce();
        assert.notDeepStrictEqual(nonce0, nonce1);
        assert.notDeepStrictEqual(nonce1, nonce2);
        assert.notDeepStrictEqual(nonce2, nonce3);
        assert.notDeepStrictEqual(nonce3, nonce4);
    });

    it('RuntimeOptions', function () {
        const opts = new RuntimeOptions();
        assert.ok(opts);
        const casted = $tea.cast({}, opts);
        assert.ok(casted);
    });

    it('stringifyMapValue', function () {
        assert.deepStrictEqual(Client.stringifyMapValue({}), {});
        assert.deepStrictEqual(Client.stringifyMapValue({'number': 100}), {'number': '100'});
        assert.deepStrictEqual(Client.stringifyMapValue({'bool': true}), {'bool': 'true'});
        assert.deepStrictEqual(Client.stringifyMapValue(null), null);
    });

    it('assertAsBoolean', function () {
        assert.deepStrictEqual(Client.assertAsBoolean(true), true);
        assert.deepStrictEqual(Client.assertAsBoolean(false), false);
        assert.throws(() => {
            Client.assertAsBoolean('true');
        }, /The value is not a boolean/);
        assert.throws(() => {
            Client.assertAsBoolean('false');
        }, /The value is not a boolean/);
        assert.throws(() => {
            Client.assertAsBoolean(undefined);
        }, /The value is not a boolean/);
    });

    it('assertAsString', function () {
        assert.deepStrictEqual(Client.assertAsString('string'), 'string');
        assert.deepStrictEqual(Client.assertAsString(''), '');
        assert.throws(() => {
            Client.assertAsString(1);
        }, /The value is not a string/);
        assert.throws(() => {
            Client.assertAsString(true);
        }, /The value is not a string/);
        assert.throws(() => {
            Client.assertAsString(undefined);
        }, /The value is not a string/);
    });

    it('assertAsNumber', function () {
        assert.deepStrictEqual(Client.assertAsNumber(1), 1);
        assert.deepStrictEqual(Client.assertAsNumber(-1), -1);
        assert.deepStrictEqual(Client.assertAsNumber(0), 0);
        assert.throws(() => {
            Client.assertAsNumber('1');
        }, /The value is not a number/);
        assert.throws(() => {
            Client.assertAsNumber(true);
        }, /The value is not a number/);
        assert.throws(() => {
            Client.assertAsNumber(undefined);
        }, /The value is not a number/);
    });

    it('assertAsMap', function () {
        assert.deepStrictEqual(Client.assertAsMap({}), {});
        assert.throws(() => {
            Client.assertAsMap([]);
        }, /The value is not a object/);
        assert.throws(() => {
            Client.assertAsMap(true);
        }, /The value is not a object/);
        assert.throws(() => {
            Client.assertAsMap(123);
        }, /The value is not a object/);
    });

});
